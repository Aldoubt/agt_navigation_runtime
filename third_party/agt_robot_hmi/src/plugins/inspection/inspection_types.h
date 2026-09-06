#pragma once
#include <QString>
#include <QStringList>
#include <QVector>
#include <QMetaType>

struct InspectionPoint {
  QString id;
  double x{0.0};
  double y{0.0};
  double yaw{0.0};
  QStringList actions;
};

struct InspectionTask {
  QString name{"field_inspection"};
  QVector<InspectionPoint> points;
};

Q_DECLARE_METATYPE(InspectionPoint)
Q_DECLARE_METATYPE(InspectionTask)
