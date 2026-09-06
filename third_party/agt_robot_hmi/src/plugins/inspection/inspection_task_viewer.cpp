#include "inspection_task_viewer.h"
#include <QVBoxLayout>
InspectionTaskViewer::InspectionTaskViewer(QWidget *parent):QWidget(parent){auto*l=new QVBoxLayout(this);status_=new QLabel(tr("Status: IDLE"),this);list_=new QListWidget(this);l->addWidget(status_);l->addWidget(list_);connect(list_,&QListWidget::currentRowChanged,this,[this](int i){if(i>=0)emit pointSelected(list_->item(i)->data(Qt::UserRole).value<InspectionPoint>());});}
void InspectionTaskViewer::setTask(const InspectionTask&t){list_->clear();for(const auto&p:t.points){auto*i=new QListWidgetItem(p.id+QString("  (%1, %2)").arg(p.x,0,'f',2).arg(p.y,0,'f',2));i->setData(Qt::UserRole,QVariant::fromValue(p));list_->addItem(i);}}
void InspectionTaskViewer::setStatus(const QString &status){status_->setText(tr("Status: ") + status);}
