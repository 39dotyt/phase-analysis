#include "phasegraph.h"
#include <algorithm>

PhaseGraph::PhaseGraph(QWidget* parent)
    : Graph(parent),
      drawBorders_(true),
      drawCenter_(true) {
}

void PhaseGraph::draw(const std::vector<qreal>& data) {
  std::vector<QPointF> points;
  for (std::size_t i = 0; i < data.size() - 1; ++i) {
    points.push_back(QPointF(data[i], data[i + 1]));
  }
  draw(points);
  max_ = std::max(maxX_, maxY_);
  min_ = std::min(minX_, minY_);
  square_ = (maxX_ - minX_) * (maxY_ - minY_);
  center_.setX((maxX_ + minX_) / 2);
  center_.setY((maxY_ + minY_) / 2);
}

qreal PhaseGraph::max() {
  return max_;
}

qreal PhaseGraph::min() {
  return min_;
}

qreal PhaseGraph::square() {
  return square_;
}

QPointF PhaseGraph::center() {
  return center_;
}

void PhaseGraph::drawBorders(bool draw) {
  drawBorders_ = draw;
  if (!drawBorders_) {
    drawCenter_ = false;
  }
  redraw();
}

void PhaseGraph::drawCenter(bool draw) {
  drawCenter_ = draw;
  if (drawCenter_) {
    drawBorders_ = true;
  }
  redraw();
}

void PhaseGraph::onRedraw(QGraphicsScene *scene) {
  if (!drawBorders_ && !drawCenter_) {
    return;
  }
  qreal widthDecimal = qreal(scene->width() - (2 * OFFSET)) / xAxisMax_;
  qreal heightDecimal = qreal(scene->height() - (2 * OFFSET)) / yAxisMax_;
  QPen dashPen(Qt::DashLine);
  if (drawBorders_) {
    scene->addRect(QRectF(QPointF(maxX_ * widthDecimal + OFFSET, scene->height() - (maxY_ * heightDecimal + OFFSET)),
                          QPointF(minX_ * widthDecimal + OFFSET, scene->height() - (minY_ * heightDecimal + OFFSET))), dashPen);
  }
  if (drawCenter_) {
    scene->addLine(maxX_ * widthDecimal + OFFSET, scene->height() - (maxY_ * heightDecimal + OFFSET),
                   minX_ * widthDecimal + OFFSET, scene->height() - (minY_ * heightDecimal + OFFSET), dashPen);
    scene->addLine(maxX_ * widthDecimal + OFFSET, scene->height() - (minY_ * heightDecimal + OFFSET),
                   minX_ * widthDecimal + OFFSET, scene->height() - (maxY_ * heightDecimal + OFFSET), dashPen);
  }
}
