#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  QTranslator* translator = new QTranslator(&a);
  if (translator->load("i18n/ru.qm")) {
    a.installTranslator(translator);
  }

  MainWindow w;
  w.show();

  return a.exec();
}
