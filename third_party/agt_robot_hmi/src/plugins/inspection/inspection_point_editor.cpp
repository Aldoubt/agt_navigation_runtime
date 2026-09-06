#include "inspection_point_editor.h"
#include <QFormLayout>
#include <QDialogButtonBox>

InspectionPointEditor::InspectionPointEditor(const InspectionPoint &p, QWidget *parent) : QDialog(parent) {
  setWindowTitle(tr("Inspection Point"));
  auto *form = new QFormLayout(this);
  id_ = new QLineEdit(p.id, this); x_ = new QDoubleSpinBox(this); y_ = new QDoubleSpinBox(this); yaw_ = new QDoubleSpinBox(this); actions_ = new QLineEdit(this);
  for (auto *box : {x_, y_, yaw_}) { box->setRange(-10000, 10000); box->setDecimals(4); }
  x_->setValue(p.x); y_->setValue(p.y); yaw_->setValue(p.yaw); actions_->setText(p.actions.join(","));
  form->addRow(tr("ID"), id_); form->addRow(tr("X (m)"), x_); form->addRow(tr("Y (m)"), y_); form->addRow(tr("Yaw (rad)"), yaw_); form->addRow(tr("Actions"), actions_);
  auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this); form->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept); connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}
InspectionPoint InspectionPointEditor::point() const { InspectionPoint p; p.id=id_->text(); p.x=x_->value(); p.y=y_->value(); p.yaw=yaw_->value(); p.actions=actions_->text().split(',', Qt::SkipEmptyParts); for(auto &a:p.actions)a=a.trimmed(); return p; }
