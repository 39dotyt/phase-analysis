#include "graph.h"
#include <QGraphicsTextItem>
#include <algorithm>
#include <qmath.h>

Graph::Graph(QWidget* parent)
    : QGraphicsView(parent) {
  setMinimumHeight(3 * OFFSET);
  setMinimumWidth(3 * OFFSET);
}

void Graph::draw(const std::vector<QPointF>& graph, bool drawHLines) {
  points_ = graph;
  drawHLines_ = drawHLines;
  if (!graph.size()) {
    scene()->clear();
    return;
  }
  maxX_ = points_[0].x();
  minX_ = points_[0].x();
  maxY_ = points_[0].y();
  minY_ = points_[0].y();
  for (QPointF point : points_) {
    const qreal& x = point.x();
    const qreal& y = point.y();
    maxX_ = std::max(x, maxX_);
    maxY_ = std::max(y, maxY_);
    minX_ = std::min(x, minX_);
    minY_ = std::min(y, minY_);
  }
  redraw();
}

void Graph::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);
  redraw();
}

void Graph::onRedraw(QGraphicsScene *) {
}

qreal Graph::calculateRealStep_(const qreal &step) {
  if (step < 5) {
    return qFloor(step) + 1;
  } else if (step < 25) {
    return qFloor(step / 5) * 5 + 5;
  } else {
    return qFloor(step / 25) * 25 + 25;
  }
}

void Graph::redraw() {
  if (!points_.size()) {
    return;
  }
  QGraphicsScene* scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, width(), height());
  drawAxis_(scene);
  qreal widthDecimal = qreal(scene->width() - (2 * OFFSET)) / xAxisMax_;
  qreal heightDecimal = qreal(scene->height() - (2 * OFFSET)) / yAxisMax_;
  QPainterPath curve;
  QPen bluePen = QPen(QColor(Qt::blue));
  for (std::size_t i = 0; i < points_.size(); ++i) {
    QPointF point(
          points_[i].x() * widthDecimal + OFFSET,
          scene->height() - (points_[i].y() * heightDecimal + OFFSET));
    scene->addEllipse(point.x() - 2, point.y() - 2, 5, 5, bluePen, QBrush(Qt::SolidPattern));
    if (0 == i) {
      curve.moveTo(point);
    } else {
      curve.lineTo(point);
    }
  }
  scene->addPath(curve, bluePen);
  onRedraw(scene);
  setScene(scene);
}

void Graph::drawAxis_(QGraphicsScene* scene) {
  scene->addLine(
        OFFSET, OFFSET,
        OFFSET, scene->height() - OFFSET);
  scene->addLine(
        OFFSET, scene->height() - OFFSET,
        scene->width() - OFFSET, scene->height() - OFFSET);
  qreal xAxis = scene->width() - (2 * OFFSET);
  qreal yAxis = scene->height() - (2 * OFFSET);
  quint8 lineHeight = NUMBER_HEIGHT + 8;

  quint16 yNumbersCount = yAxis / lineHeight;
  qreal step = calculateRealStep_(qreal(maxY_) / yNumbersCount);
  yNumbersCount = (maxY_ / step) + 1;
  yAxisMax_ = yNumbersCount * step;
  qreal stepDifference = yAxis / yNumbersCount;
  for (quint16 i = 0; i <= yNumbersCount; ++i) {
    qreal yPos = scene->height() - (OFFSET + stepDifference * i);
    scene->addLine(OFFSET - 3, yPos, OFFSET + (drawHLines_ ? xAxis : 0), yPos);
    QGraphicsTextItem* label = new QGraphicsTextItem();
    label->setPlainText(QString::number(step * i));
    label->setFont(QFont("Arial", 12));
    label->setPos(OFFSET - 5 - label->boundingRect().width(), yPos - (label->boundingRect().height() / 2));
    scene->addItem(label);
  }

  quint16 xNumbersCount = xAxis / lineHeight;
  step = calculateRealStep_(qreal(maxX_) / xNumbersCount);
  xNumbersCount = (maxX_ / step) + 1;
  xAxisMax_ = xNumbersCount * step;
  stepDifference = xAxis / xNumbersCount;
  for (quint16 i = 0; i <= xNumbersCount; ++i) {
    qreal xPos = OFFSET + stepDifference * i;
    scene->addLine(xPos, scene->height() - OFFSET, xPos, scene->height() - OFFSET + 3);
    QGraphicsTextItem* label = new QGraphicsTextItem();
    label->setPlainText(QString::number(step * i));
    label->setFont(QFont("Arial", 12));
    label->setRotation(-90);
    label->setPos(xPos - (label->boundingRect().height() / 2), scene->height() - OFFSET + 5 + label->boundingRect().width());
    scene->addItem(label);
  }
}
