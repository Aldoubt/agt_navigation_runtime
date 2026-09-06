#pragma once

#include <QDialog>
#include "config/task_chain.h"

class QCheckBox;
class QLineEdit;
class QTableWidget;

class CaptureGroupDialog : public QDialog {
  Q_OBJECT
 public:
  CaptureGroupDialog(const CaptureGroup &group, QWidget *parent = nullptr);
  CaptureGroup group() const;

 private slots:
  void addView();
  void removeView();

 private:
  QCheckBox *enabled_;
  QCheckBox *save_image_;
  QLineEdit *task_id_;
  QLineEdit *camera_id_;
  QTableWidget *views_;
};
