#pragma once
#include "map_widget.h"
#include "../ros_interface/ros_interface.h"
#include "../plugins/inspection/inspection_panel.h"
#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
class MainWindow:public QMainWindow{Q_OBJECT public:explicit MainWindow(QWidget *parent=nullptr);private slots:void addPoint(double,double);private:MapWidget*map_;InspectionPanel*inspection_;AgtRosInterface ros_;QLabel*connection_;QLabel*pose_;QProgressBar*battery_;};
