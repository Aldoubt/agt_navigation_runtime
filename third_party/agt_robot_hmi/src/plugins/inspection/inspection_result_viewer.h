#pragma once
#include <QWidget>
#include <QLabel>
class InspectionResultViewer : public QWidget { Q_OBJECT public: explicit InspectionResultViewer(QWidget* parent=nullptr); public slots: void showResult(const QString &pointId, const QString &result, double confidence, const QString &imagePath); private: QLabel *label_; QLabel *image_; };
