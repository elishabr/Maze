#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include <QWidget>

#include "mazeview.h"

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow(s21::FileParserController* parserController,
             QWidget* parent = nullptr);
  ~MainWindow();

 protected:
  void changeEvent(QEvent* event) override;

 private:
  QTranslator qtLanguageTranslator_{};
  QLabel* labelComboBoxLang_ = nullptr;
  QPushButton* pushOpenFile_ = nullptr;
  QPushButton* pushSaveFile_ = nullptr;
  QGroupBox* groupBox_ = nullptr;
  QPushButton* pushGenerateMaze_ = nullptr;
  QLabel* labelSpinBoxCol_ = nullptr;
  QLabel* labelSpinBoxRow_ = nullptr;
  s21::FileParserController* parserController_ = nullptr;
  s21::MazeGenerationController* mazeGenController_ = nullptr;
  s21::MazeView* mazeView_ = nullptr;
  int errorCode_ = 0;
};

#endif  // MAINWINDOW_H
