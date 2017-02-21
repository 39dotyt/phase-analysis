#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsView>
#include <QTimer>

class Graph : public QGraphicsView {
 public:
  explicit Graph(QWidget* parent = 0);
  void draw(const std::vector<QPointF>& graph, bool drawHLines = false,
    bool scaled = false);
  void scale(bool scale = true);
  qreal maxX();
  qreal maxY();
  qreal minX();
  qreal minY();
 protected:
  virtual void resizeEvent(QResizeEvent* event);
  virtual void onRedraw(
      QGraphicsScene* scene,
      const qreal& widthDecimal, const qreal& heightDecimal,
      const qreal& realOffsetX, const qreal& realOffsetY);
  void redraw();
  qreal maxX_;
  qreal maxY_;
  qreal minX_;
  qreal minY_;
  bool drawHLines_;
 private:
  static qreal calculateRealStep_(const qreal& step);
  static quint32 calculateAxisStart_(const qreal& minAxis, const qreal& maxAxis);
  void drawAxis_(QGraphicsScene* scene);
  static const quint8 OFFSET = 45;
  static const quint8 NUMBER_HEIGHT = 12;
  QTimer redrawTimer_;
  std::vector<QPointF> points_;
  quint32 xAxisMax_;
  quint32 yAxisMax_;
  quint32 xAxisStart_;
  quint32 yAxisStart_;
};

#endif // GRAPH_H
