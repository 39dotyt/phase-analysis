#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
  ui->setupUi(this);
  highsGraph_ = new ChangesGraph(ui->highs);
  lowsGraph_ = new ChangesGraph(ui->lows);
  squaresGraph_ = new ChangesGraph(ui->squares);
  centersGraph_ = new ChangesGraph(ui->centers);
  trendGraph_ = new Graph(ui->trend);
  ui->highs->layout()->addWidget(highsGraph_);
  ui->lows->layout()->addWidget(lowsGraph_);
  ui->squares->layout()->addWidget(squaresGraph_);
  ui->centers->layout()->addWidget(centersGraph_);
  ui->trend->layout()->addWidget(trendGraph_);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionLoadCsv_triggered() {
  for (PhaseGraphWidget* widget : phaseGraphWidgets_) {
    widget->deleteLater();
  }
  phaseGraphWidgets_.clear();
  QString fileName = QFileDialog::getOpenFileName(
        this, tr("Select data file"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        tr("Data files (*.csv)"));
  if (fileName.isEmpty()) {
    return;
  }
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(this, tr("Error loading file"), file.errorString());
  }
  QTextStream in(&file);
  if (in.atEnd()) {
    QMessageBox::critical(this, tr("Error loading file"), tr("File is empty"));
  }
  QString setup = file.readLine();
  std::vector<std::size_t> phaseLengths;
  bool ok;
  if ('"' == setup[0]) {
    setup = setup.section('"', 1, 1);
    QStringList setupSplitted = setup.split(',');
    for (QString setupEntry : setupSplitted) {
      phaseLengths.push_back(setupEntry.toInt(&ok));
      if (!ok) {
        QMessageBox::critical(this, tr("Error loading file"), tr("Invalid file format"));
        return;
      }
    }
  } else {
    phaseLengths.push_back(setup.toInt(&ok));
    if (!ok) {
      QMessageBox::critical(this, tr("Error loading file"), tr("Invalid file format"));
      return;
    }
  }
  std::vector<qreal> phaseGraphData;
  std::size_t iPhaseLengths = 0;
  while (!in.atEnd()) {
    QString line = in.readLine();
    phaseGraphData.push_back(line.toDouble(&ok));
    if (!ok) {
      for (PhaseGraphWidget* widget : phaseGraphWidgets_) {
        widget->deleteLater();
      }
      phaseGraphWidgets_.clear();
      QMessageBox::critical(this, tr("Error loading file"), tr("Invalid file format"));
      return;
    }
    if (phaseLengths[iPhaseLengths] == phaseGraphData.size()) {
      PhaseGraphWidget* widget = new PhaseGraphWidget(ui->phases);
      widget->draw(phaseGraphData);
      ui->phases->layout()->addWidget(widget);
      phaseGraphWidgets_.push_back(widget);
      phaseGraphData.clear();
      iPhaseLengths += 1;
      if (phaseLengths.size() == iPhaseLengths) {
        iPhaseLengths = 0;
      }
    }
  }
  std::vector<qreal> highs;
  std::vector<qreal> lows;
  std::vector<qreal> squares;
  std::vector<qreal> centers;
  std::vector<QPointF> trend;
  for (PhaseGraphWidget* widget : phaseGraphWidgets_) {
    PhaseGraph* graph = widget->graph();
    highs.push_back(graph->max());
    lows.push_back(graph->min());
    squares.push_back(graph->square());
    const QPointF& center = graph->center();
    centers.push_back((center.x() + center.y()) / 2);
    trend.push_back(center);
  }
  highsGraph_->draw(highs);
  lowsGraph_->draw(lows);
  squaresGraph_->draw(squares);
  centersGraph_->draw(centers);
  trendGraph_->draw(trend, false, true);
}
