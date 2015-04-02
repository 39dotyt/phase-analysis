#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsView>

class Graph : public QGraphicsView {
 public:
  explicit Graph(QWidget* parent = 0);
  void draw(const std::vector<QPointF>& graph, bool drawHLines = false);
 protected:
  virtual void resizeEvent(QResizeEvent* event);
  virtual void onRedraw(QGraphicsScene* scene);
  void redraw();
  static const quint8 OFFSET = 45;
  static const quint8 NUMBER_HEIGHT = 12;
  qreal maxX_;
  qreal maxY_;
  qreal minX_;
  qreal minY_;
  quint32 xAxisMax_;
  quint32 yAxisMax_;
  bool drawHLines_;
 private:
  static qreal calculateRealStep(const qreal& step);
  void drawAxis(QGraphicsScene* scene);
  std::vector<QPointF> points_;
};

#endif // GRAPH_H
