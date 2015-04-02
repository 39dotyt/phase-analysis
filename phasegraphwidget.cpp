#include "phasegraphwidget.h"
#include "ui_phasegraphwidget.h"
#include <QGridLayout>

PhaseGraphWidget::PhaseGraphWidget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::PhaseGraphWidget),
      graph_(new PhaseGraph(this)),
      wActions_(new QWidget(this)),
      cbShowBorder_(new QCheckBox(wActions_)),
      cbShowCenter_(new QCheckBox(wActions_)),
      btnSavePNG_(new QPushButton(wActions_)) {
  ui->setupUi(this);
  wActions_->hide();
  QGridLayout* l = (QGridLayout* )layout();
  l->addWidget(graph_, 0, 1);
}

PhaseGraphWidget::~PhaseGraphWidget() {
  delete ui;
}

void PhaseGraphWidget::draw(const std::vector<qreal>& data) {
  const QObjectList& labels = ui->pointsLayout->children();
  for (QObject* label : labels) {
    label->deleteLater();
  }
  ui->pointsLayout->addWidget(new QLabel("...", this), 0, 0);
  ui->pointsLayout->addWidget(new QLabel(QString::number(data[0]), this), 0, 1);
  for (std::size_t i = 0; i < data.size() - 1; ++i) {
    ui->pointsLayout->addWidget(new QLabel(QString::number(data[i]), this), i + 1, 0);
    ui->pointsLayout->addWidget(new QLabel(QString::number(data[i + 1]), this), i + 1, 1);
  }
  ui->pointsLayout->addWidget(new QLabel(QString::number(data[data.size() - 1]), this), data.size(), 0);
  ui->pointsLayout->addWidget(new QLabel("...", this), data.size(), 1);
  graph_->draw(data);
  ui->lMax->setText(QString::number(graph_->max()));
  ui->lMin->setText(QString::number(graph_->min()));
  ui->lSquare->setText(QString::number(graph_->square()));
  const QPointF& center = graph_->center();
  ui->lCenter->setText(QString("(%1, %2)").arg(center.x()).arg(center.y()));
}

PhaseGraph* PhaseGraphWidget::graph() {
  return graph_;
}
