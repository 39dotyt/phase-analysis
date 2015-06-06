#include "phasegraph.h"
#include <algorithm>

PhaseGraph::PhaseGraph(QWidget* parent)
    : Graph(parent),
      drawBorders_(true),
      drawDiagonals_(true) {
}

void PhaseGraph::draw(const std::vector<qreal>& data) {
  std::vector<QPointF> points;
  for (std::size_t i = 0; i < data.size() - 1; ++i) {
    points.push_back(QPointF(data[i], data[i + 1]));
  }
  draw(points, false, true);
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
    drawDiagonals_ = false;
  }
  redraw();
}

void PhaseGraph::drawDiagonals(bool draw) {
  drawDiagonals_ = draw;
  if (drawDiagonals_) {
    drawBorders_ = true;
  }
  redraw();
}

void PhaseGraph::onRedraw(
    QGraphicsScene *scene,
    const qreal& widthDecimal, const qreal& heightDecimal,
    const qreal& realOffsetX, const qreal& realOffsetY) {
  if (!drawBorders_ && !drawDiagonals_) {
    return;
  }
  QPen dashPen(Qt::DashLine);
  if (drawBorders_) {
    scene->addRect(QRectF(QPointF(maxX_ * widthDecimal + realOffsetX, scene->height() - (maxY_ * heightDecimal + realOffsetY)),
                          QPointF(minX_ * widthDecimal + realOffsetX, scene->height() - (minY_ * heightDecimal + realOffsetY))), dashPen);
  }
  if (drawDiagonals_) {
    scene->addLine(maxX_ * widthDecimal + realOffsetX, scene->height() - (maxY_ * heightDecimal + realOffsetY),
                   minX_ * widthDecimal + realOffsetX, scene->height() - (minY_ * heightDecimal + realOffsetY), dashPen);
    scene->addLine(maxX_ * widthDecimal + realOffsetX, scene->height() - (minY_ * heightDecimal + realOffsetY),
                   minX_ * widthDecimal + realOffsetX, scene->height() - (maxY_ * heightDecimal + realOffsetY), dashPen);
  }
}
