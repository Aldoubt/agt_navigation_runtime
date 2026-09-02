#pragma once
#include "inspection_types.h"
#include <QDialog>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

class InspectionPointEditor : public QDialog {
  Q_OBJECT
 public:
  explicit InspectionPointEditor(const InspectionPoint &point, QWidget *parent = nullptr);
  InspectionPoint point() const;
 private:
  QLineEdit *id_; QDoubleSpinBox *x_; QDoubleSpinBox *y_; QDoubleSpinBox *yaw_;
  QLineEdit *actions_;
};
