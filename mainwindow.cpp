#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "phasegraph.h"
#include "changesgraph.h"
#include "phasegraphwidget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ChangesGraph* graph = new ChangesGraph();
  graph->setGeometry(400, 200, 700, 700);
  graph->draw({34, 36, 95, 284, 457, 491, 397, 148, 90, 71, 45, 33, 29});
  graph->show();
  PhaseGraphWidget* phaseGraph = new PhaseGraphWidget();
  phaseGraph->setGeometry(1400, 200, 700, 700);
  phaseGraph->draw({34, 36, 95, 284, 457, 491, 397, 148, 90, 71, 45, 33, 29});
  phaseGraph->show();
}

MainWindow::~MainWindow() {
  delete ui;
}
