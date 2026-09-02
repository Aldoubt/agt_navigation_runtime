#include "mainwindow.h"
#include <QApplication>
#include <csignal>
#include <rclcpp/rclcpp.hpp>
int main(int argc,char**argv){rclcpp::init(argc,argv);QApplication app(argc,argv);MainWindow window;window.show();const int rc=app.exec();rclcpp::shutdown();return rc;}
