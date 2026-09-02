#pragma once
#include "inspection_types.h"
#include "inspection_task_viewer.h"
#include "inspection_result_viewer.h"
#include <QWidget>
class InspectionPanel : public QWidget { Q_OBJECT public: explicit InspectionPanel(QWidget* parent=nullptr); void setTask(const InspectionTask&); InspectionTask task() const{return task_;} public slots: void setTaskStatus(const QString&); void setResult(const QString&,const QString&,double,const QString&); signals: void startRequested(const QString&); void pauseRequested(); void cancelRequested(); private: InspectionTask task_; InspectionTaskViewer* viewer_; InspectionResultViewer* result_; };
