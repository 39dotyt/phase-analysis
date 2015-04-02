#ifndef PHASEGRAPHWIDGET_H
#define PHASEGRAPHWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include "phasegraph.h"

namespace Ui {
 class PhaseGraphWidget;
}

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
  QWidget* wActions_;
  QCheckBox* cbShowBorder_;
  QCheckBox* cbShowCenter_;
  QPushButton* btnSavePNG_;
};

#endif // PHASEGRAPHWIDGET_H
