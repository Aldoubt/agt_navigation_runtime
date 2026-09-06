#pragma once
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <nav_msgs/msg/occupancy_grid.hpp>
class MapWidget:public QGraphicsView{Q_OBJECT public:explicit MapWidget(QWidget*p=nullptr);public slots:void setMap(const nav_msgs::msg::OccupancyGrid::SharedPtr&);void setPose(double,double,double);signals:void addInspectionPoint(double,double);void navigationGoal(double,double);protected:void contextMenuEvent(QContextMenuEvent*)override;private:QGraphicsScene scene_;QGraphicsPixmapItem* map_{nullptr};};
