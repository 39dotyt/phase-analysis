#include "phasegraphwidget.h"
#include "ui_phasegraphwidget.h"
#include <QGridLayout>
#include <QToolButton>
#include <QTimer>

PhaseGraphWidget::PhaseGraphWidget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::PhaseGraphWidget),
      graph_(new PhaseGraph(this)),
      bZoom_(new QPushButton(this)),
      lActions_(new Hoverable<QLabel>(this)),
      wActions_(new Hoverable<QFrame>(this)),
      cbDrawBorders_(new QCheckBox(tr("Draw borders"), wActions_)),
      cbDrawDiagonals_(new QCheckBox(tr("Draw diagonals"), wActions_)),
      pxmCircleMoreDetail_(
        QPixmap(":/img/circle_more_detail-64.png")
        .scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation)),
      pxmCircleBackArrow_(
        QPixmap(":/img/circle_back_arrow-64.png")
        .scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation)),
      pxmEditorZoomIn_(
        QPixmap(":/img/editor_zoom-in-64.png")
        .scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation)) {
  ui->setupUi(this);

  QGridLayout* l = static_cast<QGridLayout*>(layout());
  l->addWidget(graph_, 0, 1);

  bZoom_->setFlat(true);
  bZoom_->setCheckable(true);
  bZoom_->setChecked(true);
  bZoom_->setIcon(pxmEditorZoomIn_);
  bZoom_->setMaximumSize(28, 28);
  ui->infoLayout->addWidget(bZoom_);

  lActions_->setPixmap(pxmCircleMoreDetail_);
  ui->infoLayout->addWidget(lActions_);

  QHBoxLayout* lActions = new QHBoxLayout(wActions_);
  lActions->addWidget(cbDrawBorders_);
  lActions->addWidget(cbDrawDiagonals_);
  cbDrawBorders_->setChecked(true);
  cbDrawDiagonals_->setChecked(true);
  wActions_->adjustSize();
  wActions_->setBackgroundRole(QPalette::Window);
  wActions_->setAutoFillBackground(true);
  wActions_->setFrameStyle(QFrame::StyledPanel || QFrame::Raised);
  wActions_->raise();
  wActions_->hide();

  QObject::connect(cbDrawBorders_, &QCheckBox::clicked, [this] (bool checked) {
    if (!checked) {
      cbDrawDiagonals_->setChecked(false);
    }
    graph_->drawBorders(checked);
  });

  QObject::connect(cbDrawDiagonals_, &QCheckBox::clicked, [this] (bool checked) {
    if (checked) {
      cbDrawBorders_->setChecked(true);
    }
    graph_->drawDiagonals(checked);
  });

  QObject::connect(lActions_, &Hoverable<QToolButton>::enter, [this] {
    lActions_->setPixmap(pxmCircleBackArrow_);
    wActions_->setGeometry(
          lActions_->x() - wActions_->width() - 3,
          lActions_->y() + (lActions_->height() / 2) - (wActions_->height() / 2),
          wActions_->width(), wActions_->height());
    wActions_->show();
  });

  fnHideActions_ = [this] {
    lActions_->setPixmap(pxmCircleMoreDetail_);
    wActions_->hide();
  };

  fnStartHideTimeout_ = [this] {
    QTimer::singleShot(500, [this] {
      if (wActions_->isEntered() || lActions_->isEntered()) {
        return;
      }
      fnHideActions_();
    });
  };

  QObject::connect(lActions_, &Hoverable<QToolButton>::leave, [this] {
    QPoint cursorPosition = this->mapFromGlobal(QCursor::pos());
    if (cursorPosition.x() > lActions_->x()) {
      fnHideActions_();
    } else {
      fnStartHideTimeout_();
    }
  });

  QObject::connect(wActions_, &Hoverable<QFrame>::leave, [this] {
    QPoint cursorPosition = this->mapFromGlobal(QCursor::pos());
    if (cursorPosition.x() < wActions_->x() + wActions_->width()) {
      fnHideActions_();
    } else {
      fnStartHideTimeout_();
    }
  });

  QObject::connect(bZoom_, &QPushButton::clicked, [this] (bool checked) {
    graph_->scale(checked);
  });
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
    ui->pointsLayout->addWidget(new QLabel(QString::number(data[i]), this), int(i + 1), 0);
    ui->pointsLayout->addWidget(new QLabel(QString::number(data[i + 1]), this), int(i + 1), 1);
  }
  ui->pointsLayout->addWidget(new QLabel(QString::number(data[data.size() - 1]), this), int(data.size()), 0);
  ui->pointsLayout->addWidget(new QLabel("...", this), int(data.size()), 1);
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
