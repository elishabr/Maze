#include <QApplication>
#include <QDebug>
#include <QTranslator>

#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/res/icone512.ico"));
  s21::FileOpen parsingModel;
  s21::FileParserController parserController(&parsingModel);
  MainWindow w(&parserController);
  w.show();
  return a.exec();
}
