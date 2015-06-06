#ifndef PHASEGRAPH_H
#define PHASEGRAPH_H

#include "graph.h"

class PhaseGraph : public Graph {
 public:
  explicit PhaseGraph(QWidget* parent = 0);
  void draw(const std::vector<qreal>& data);
  qreal max();
  qreal min();
  qreal square();
  QPointF center();
 public slots:
  void drawBorders(bool draw = true);
  void drawDiagonals(bool draw = true);
 protected:
  void onRedraw(
      QGraphicsScene *scene,
      const qreal& widthDecimal, const qreal& heightDecimal,
      const qreal& realOffsetX, const qreal& realOffsetY);
 private:
  using Graph::draw;
  qreal max_;
  qreal min_;
  qreal square_;
  QPointF center_;
  bool drawBorders_;
  bool drawDiagonals_;
};

#endif // PHASEGRAPH_H
