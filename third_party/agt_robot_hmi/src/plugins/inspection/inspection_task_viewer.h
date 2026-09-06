#pragma once
#include "inspection_types.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>

class InspectionTaskViewer : public QWidget {
  Q_OBJECT
 public:
  explicit InspectionTaskViewer(QWidget *parent = nullptr);
  void setTask(const InspectionTask &task);
  void setStatus(const QString &status);
 signals: void pointSelected(const InspectionPoint &point);
 private: QListWidget *list_; QLabel *status_;
};
