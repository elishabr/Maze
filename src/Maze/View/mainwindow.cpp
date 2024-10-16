#include "mainwindow.h"

#include <qapplication.h>

#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QStandardPaths>
#include <QString>
#include <QTextEdit>
#include <QTranslator>
#include <QVBoxLayout>

MainWindow::MainWindow(s21::FileParserController *parserController,
                       QWidget *parent) {
  //передача контролера
  parserController_ = parserController;

  //главный виджет
  setWindowTitle(tr("Maze"));
  auto outer = new QVBoxLayout(this);
  outer->setContentsMargins(0, 0, 0, 0);

  //поле для отрисовки лабиринта
  mazeView_ = new s21::MazeView(parserController_);
  mazeView_->setMinimumSize(500, 500);
  mazeView_->setMaximumSize(500, 500);
  mazeView_->setToolTip(tr(
      "To find the shortest path in the maze, you need to specify two key "
      "points:\n"
      " the starting point (from where the movement begins) and the end point\n"
      " (where you need to come). These points are the starting point and the "
      "goal,\n"
      " respectively. By specifying them, you set the boundaries for finding "
      "the optimal route."));
  outer->addWidget(mazeView_, 1, Qt::AlignCenter);

  //виджет для элементов управления
  auto foneBottom = new QWidget;
  foneBottom->setMaximumHeight(180);
  foneBottom->setMinimumHeight(180);

  //менеджеры макета для виджета элементов управления
  auto layoutV = new QVBoxLayout(foneBottom);
  auto layoutH1inLayoutV = new QHBoxLayout;
  auto layoutH2inLayoutV = new QHBoxLayout;
  auto layoutH3inLayoutV = new QHBoxLayout;
  layoutV->addLayout(layoutH1inLayoutV);
  layoutV->addLayout(layoutH2inLayoutV);
  layoutV->addLayout(layoutH3inLayoutV);

  //интерфейс выбора языка
  labelComboBoxLang_ = new QLabel(tr("Select Language:"));
  layoutH1inLayoutV->addWidget(labelComboBoxLang_);

  auto comboBoxLang = new QComboBox;
  comboBoxLang->addItem("Russian", "ru");
  comboBoxLang->addItem("English", "en");
  comboBoxLang->setMaximumWidth(140);
  comboBoxLang->setMinimumWidth(140);
  layoutH1inLayoutV->addWidget(comboBoxLang);

  // интерфейс открытияи сохранения файла
  auto lineEdit = new QLineEdit();
  lineEdit->setReadOnly(true);
  layoutH2inLayoutV->addWidget(lineEdit);

  pushOpenFile_ = new QPushButton(tr("Open File"));
  pushOpenFile_->setMaximumWidth(140);
  pushOpenFile_->setMinimumWidth(140);
  layoutH2inLayoutV->addWidget(pushOpenFile_);

  //интерфйс генреации лабиринта
  groupBox_ = new QGroupBox(tr("Generation of a perfect maze"));
  auto groupBoxLayout = new QHBoxLayout(groupBox_);

  labelSpinBoxCol_ = new QLabel(tr("Size by X:"));
  groupBoxLayout->addWidget(labelSpinBoxCol_, 1, Qt::AlignRight);

  auto spinBoxCol = new QSpinBox();
  spinBoxCol->setRange(1, 50);
  groupBoxLayout->addWidget(spinBoxCol);

  labelSpinBoxRow_ = new QLabel(tr("Size by Y:"));
  groupBoxLayout->addWidget(labelSpinBoxRow_, 1, Qt::AlignRight);

  auto spinBoxRow = new QSpinBox();
  spinBoxRow->setRange(1, 50);
  groupBoxLayout->addWidget(spinBoxRow);

  pushGenerateMaze_ = new QPushButton(tr("Generate"));
  pushGenerateMaze_->setMaximumWidth(140);
  pushGenerateMaze_->setMinimumWidth(140);
  groupBoxLayout->addWidget(pushGenerateMaze_);

  pushSaveFile_ = new QPushButton(tr("Save Maze"));
  pushSaveFile_->setEnabled(false);
  pushSaveFile_->setMaximumWidth(140);
  pushSaveFile_->setMinimumWidth(140);
  groupBoxLayout->addWidget(pushSaveFile_);
  layoutH3inLayoutV->addWidget(groupBox_);

  outer->addWidget(foneBottom);

  if (qtLanguageTranslator_.load(":/res/myapp_ru.qm")) {
    qApp->installTranslator(&qtLanguageTranslator_);
  }

  connect(comboBoxLang, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, [=](int index) {
            QString str = comboBoxLang->itemData(index).toString();
            if (qtLanguageTranslator_.load(":/res/myapp_" + str)) {
              qApp->installTranslator(&qtLanguageTranslator_);
            }
          });

  connect(pushOpenFile_, &QPushButton::clicked, this, [=]() {
    pushSaveFile_->setEnabled(false);
    auto fileContentReady = [=](const QString &fileName,
                                const QByteArray &fileContent) {
      if (fileName.isEmpty() || fileName == "") {
        qDebug() << "Файл не выбран.";
      } else {
        errorCode_ = parserController_->ParseFile(fileContent.toStdString());
        mazeView_->SetMazeWalls(parserController_);
        mazeView_->update();
        if (errorCode_) {
          lineEdit->setStyleSheet("color: red;");
          if (errorCode_ == 1) {
            lineEdit->setText("the matrix is given incorrectly");
          } else if (errorCode_ == 2) {
            lineEdit->setText("incorrect dimension of the matrix");
          } else if (errorCode_ == 3) {
            lineEdit->setText("extra empty lines");
          } else if (errorCode_ == 4) {
            lineEdit->setText("error open file");
          }
        } else {
          lineEdit->setStyleSheet("color: black;");
          lineEdit->setText(fileName);
        }
      }
    };
    QFileDialog::getOpenFileContent("Files (*.txt)", fileContentReady);
  });

  connect(pushGenerateMaze_, &QPushButton::clicked, this, [=]() {
    lineEdit->setText("");
    pushSaveFile_->setEnabled(true);
    if (mazeGenController_ != nullptr) delete mazeGenController_;
    mazeGenController_ = new s21::MazeGenerationController(spinBoxCol->value(),
                                                           spinBoxRow->value());
    mazeView_->SetMazeWalls(mazeGenController_);
    mazeView_->update();
  });

  connect(pushSaveFile_, &QPushButton::clicked, this, [=]() {
    QByteArray fileContent;
    std::string mazeFileInfo;
    if (mazeGenController_ != nullptr) {
      mazeGenController_->SaveFile(mazeFileInfo);
      fileContent.append(mazeFileInfo);
    }
    QFileDialog::saveFileContent(fileContent, "new_file.txt");
  });
}

MainWindow::~MainWindow() { delete mazeGenController_; }

void MainWindow::changeEvent(QEvent *event) {
  if (event->type() == QEvent::LanguageChange) {
    setWindowTitle(tr("Maze"));
    labelComboBoxLang_->setText(tr("Select Language:"));
    pushOpenFile_->setText(tr("Open File"));
    pushSaveFile_->setText(tr("Save Maze"));
    groupBox_->setTitle(tr("Generation of a perfect maze"));
    labelSpinBoxCol_->setText(tr("Size by X:"));
    labelSpinBoxRow_->setText(tr("Size by Y:"));
    pushGenerateMaze_->setText(tr("Generate"));
    mazeView_->setToolTip(
        tr("To find the shortest path in the maze, you need to specify two key "
           "points:\n"
           " the starting point (from where the movement begins) and the end "
           "point\n"
           " (where you need to come). These points are the starting point and "
           "the goal,\n"
           " respectively. By specifying them, you set the boundaries for "
           "finding the optimal route."));
  }
}
