#include "changesgraph.h"
#include <algorithm>

ChangesGraph::ChangesGraph(QWidget* parent)
    : Graph(parent) {
}

ChangesGraph::~ChangesGraph() {
}

void ChangesGraph::draw(const std::vector<qreal>& data) {
  std::vector<QPointF> points;
  max_ = data[0];
  min_ = data[0];
  qreal sum = 0;
  for (std::size_t i = 0; i < data.size(); ++i) {
    const qreal& val = data[i];
    points.push_back(QPointF(i + 1, val));
    max_ = std::max(val, max_);
    min_ = std::min(val, min_);
    sum += val;
  }
  average_ = sum / data.size();
  draw(points, true);
}

qreal ChangesGraph::max() {
  return max_;
}

qreal ChangesGraph::min() {
  return min_;
}

qreal ChangesGraph::average() {
  return average_;
}
