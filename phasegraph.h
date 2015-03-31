#ifndef PHASEGRAPH_H
#define PHASEGRAPH_H

#include "graph.h"

class PhaseGraph : public Graph {
 public:
  explicit PhaseGraph(QWidget* parent = 0);
  ~PhaseGraph();
  void draw(const std::vector<qreal>& data);
  qreal max();
  qreal min();
  qreal square();
  QPointF center();
 public slots:
  void drawBorders(bool draw = true);
  void drawCenter(bool draw = true);
 protected:
  void onRedraw(QGraphicsScene *scene);
 private:
  using Graph::draw;
  qreal max_;
  qreal min_;
  qreal square_;
  QPointF center_;
  bool drawBorders_;
  bool drawCenter_;
};

#endif // PHASEGRAPH_H
