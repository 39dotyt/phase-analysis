#ifndef CHANGESGRAPH_H
#define CHANGESGRAPH_H

#include "graph.h"

class ChangesGraph : public Graph {
 public:
  explicit ChangesGraph(QWidget* parent = 0);
  ~ChangesGraph();
  void draw(const std::vector<qreal>& data);
  qreal max();
  qreal min();
  qreal average();
 private:
  using Graph::draw;
  qreal max_;
  qreal min_;
  qreal average_;
};

#endif // CHANGESGRAPH_H
