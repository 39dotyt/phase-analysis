#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  QCoreApplication::setOrganizationName("yttrium software");
  QCoreApplication::setOrganizationDomain("39.yt");
  QCoreApplication::setApplicationName("Phase Analyzer");
  QCoreApplication::setApplicationVersion("1.3.0");
  QTranslator* translator = new QTranslator(&a);
  if (translator->load("i18n/ru.qm")) {
    a.installTranslator(translator);
  }
  MainWindow w;
  w.show();
  return a.exec();
}
