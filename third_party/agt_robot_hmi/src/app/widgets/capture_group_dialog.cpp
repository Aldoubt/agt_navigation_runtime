#include "widgets/capture_group_dialog.h"

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

static std::vector<CaptureView> DefaultCaptureViews() {
  const double headings[] = {-150.0, -107.14, -64.29, -21.43,
                              21.43, 64.29, 107.14, 135.0};
  std::vector<CaptureView> views;
  for (int i = 0; i < 8; ++i) {
    CaptureView view;
    view.id = "safe_" + std::to_string(i * 45);
    view.pan_deg = headings[i];
    view.tilt_deg = 20.0;
    view.timeout_s = 20.0;
    view.settle_duration_s = 0.8;
    views.push_back(view);
  }
  return views;
}

CaptureGroupDialog::CaptureGroupDialog(const CaptureGroup &group, QWidget *parent)
    : QDialog(parent) {
  setWindowTitle("Capture Task Group");
  resize(700, 360);
  auto *root = new QVBoxLayout(this);
  auto *form = new QFormLayout();
  enabled_ = new QCheckBox("Enable capture group");
  enabled_->setChecked(group.enabled);
  save_image_ = new QCheckBox("Save images");
  save_image_->setChecked(group.save_image);
  save_image_->setEnabled(false);
  task_id_ = new QLineEdit(QString::fromStdString(group.task_id));
  camera_id_ = new QLineEdit(QString::fromStdString(group.camera_id));
  form->addRow(enabled_);
  form->addRow("Task ID", task_id_);
  form->addRow("Camera ID", camera_id_);
  form->addRow(save_image_);
  root->addLayout(form);

  views_ = new QTableWidget(0, 5);
  views_->setHorizontalHeaderLabels({"ID", "Pan (deg)", "Tilt (deg)",
                                    "Timeout (s)", "Settle (s)"});
  views_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  root->addWidget(views_);
  const auto configured_views = group.views.empty() ? DefaultCaptureViews() : group.views;
  for (const auto &view : configured_views) {
    const int row = views_->rowCount();
    views_->insertRow(row);
    views_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(view.id)));
    views_->setItem(row, 1, new QTableWidgetItem(QString::number(view.pan_deg)));
    views_->setItem(row, 2, new QTableWidgetItem(QString::number(view.tilt_deg)));
    views_->setItem(row, 3, new QTableWidgetItem(QString::number(view.timeout_s)));
    views_->setItem(row, 4, new QTableWidgetItem(QString::number(view.settle_duration_s)));
  }
  auto *tools = new QHBoxLayout();
  auto *add = new QPushButton("Add view");
  auto *remove = new QPushButton("Delete view");
  tools->addWidget(add);
  tools->addWidget(remove);
  tools->addStretch();
  root->addLayout(tools);
  connect(add, &QPushButton::clicked, this, &CaptureGroupDialog::addView);
  connect(remove, &QPushButton::clicked, this, &CaptureGroupDialog::removeView);
  auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  root->addWidget(buttons);
  connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void CaptureGroupDialog::addView() {
  const int row = views_->rowCount();
  views_->insertRow(row);
  views_->setItem(row, 0, new QTableWidgetItem(QString("view_%1").arg(row + 1)));
  views_->setItem(row, 1, new QTableWidgetItem("0"));
  views_->setItem(row, 2, new QTableWidgetItem("-10"));
  views_->setItem(row, 3, new QTableWidgetItem("5"));
  views_->setItem(row, 4, new QTableWidgetItem("0.5"));
}

void CaptureGroupDialog::removeView() {
  if (views_->currentRow() >= 0) views_->removeRow(views_->currentRow());
}

CaptureGroup CaptureGroupDialog::group() const {
  CaptureGroup result;
  result.enabled = enabled_->isChecked();
  result.save_image = save_image_->isChecked();
  result.task_id = task_id_->text().trimmed().toStdString();
  result.camera_id = camera_id_->text().trimmed().toStdString();
  for (int row = 0; row < views_->rowCount(); ++row) {
    auto text = [this, row](int column) {
      auto *item = views_->item(row, column);
      return item ? item->text().trimmed() : QString();
    };
    bool ok[4] = {};
    CaptureView view;
    view.id = text(0).toStdString();
    view.pan_deg = text(1).toDouble(&ok[0]);
    view.tilt_deg = text(2).toDouble(&ok[1]);
    view.timeout_s = text(3).toDouble(&ok[2]);
    view.settle_duration_s = text(4).toDouble(&ok[3]);
    if (!view.id.empty() && ok[0] && ok[1] && ok[2] && ok[3] &&
        view.timeout_s > 0.0 && view.settle_duration_s >= 0.0) {
      result.views.push_back(view);
    }
  }
  return result;
}
