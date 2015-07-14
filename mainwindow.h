#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "changesgraph.h"
#include "phasegraphwidget.h"

namespace Ui {
 class MainWindow;
}

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_actionLoadCsv_triggered();

  void on_actionExportCsv_triggered();

private:
  Ui::MainWindow* ui;
  std::vector<PhaseGraphWidget*> phaseGraphWidgets_;
  ChangesGraph* highsGraph_;
  ChangesGraph* lowsGraph_;
  ChangesGraph* squaresGraph_;
  ChangesGraph* centersGraph_;
  Graph* trendGraph_;
};

#endif // MAINWINDOW_H
