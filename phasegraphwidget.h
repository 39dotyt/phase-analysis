#ifndef PHASEGRAPHWIDGET_H
#define PHASEGRAPHWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <functional>
#include "phasegraph.h"

namespace Ui {
 class PhaseGraphWidget;
}

class HoverableBase : public QObject {
  Q_OBJECT
 signals:
  void enter();
  void leave();
};

template<class C>
class Hoverable : public C, public HoverableBase {
 public:
  explicit Hoverable(QWidget* parent = 0)
      : C(parent),
        entered_(false) {
  }
  bool isEntered() {
    return entered_;
  }
 protected:
  void enterEvent(QEvent* event) {
    emit enter();
    entered_ = true;
    C::enterEvent(event);
  }
  void leaveEvent(QEvent* event) {
    emit leave();
    entered_ = false;
    C::leaveEvent(event);
  }
 private:
  bool entered_;
};

class PhaseGraphWidget : public QWidget {
  Q_OBJECT
 public:
  explicit PhaseGraphWidget(QWidget* parent = 0);
  ~PhaseGraphWidget();
  void draw(const std::vector<qreal>& data);
  PhaseGraph* graph();
 private:
  Ui::PhaseGraphWidget* ui;
  PhaseGraph* graph_;
  QPushButton* bZoom_;
  Hoverable<QLabel>* lActions_;
  Hoverable<QFrame>* wActions_;
  QCheckBox* cbDrawBorders_;
  QCheckBox* cbDrawDiagonals_;
  QPixmap pxmCircleMoreDetail_;
  QPixmap pxmCircleBackArrow_;
  QPixmap pxmEditorZoomIn_;
  std::function<void()> fnHideActions_;
  std::function<void()> fnStartHideTimeout_;
};

#endif // PHASEGRAPHWIDGET_H
