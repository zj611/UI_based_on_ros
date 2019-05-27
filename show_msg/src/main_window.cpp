#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/msg/main_window.hpp"


namespace msg {

using namespace Qt;

MainWindow::MainWindow(int argc, char** argv, QWidget *parent) : QMainWindow(parent), qnode(argc,argv)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("HMI DESIGNED BY ZJ"));
    setWindowIcon(QIcon(":/images/bit.jpeg"));
    ui.view_logging_sub->setModel(qnode.loggingModel_sub());
    QObject::connect(&qnode, SIGNAL(loggingUpdated_sub(QString,float,float,float,double)), this, SLOT(updateLoggingView_sub(QString,float,float,float,double)));

}

MainWindow::~MainWindow() {}

void MainWindow::showNoMasterMessage()
{
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
  close();
}

void MainWindow::on_start_clicked(bool check )
{
    if ( !qnode.init() )
    {
      showNoMasterMessage();
    }
    else
    {
      ui.start->setEnabled(false);
    }
}


void MainWindow::on_quit_clicked(bool check )
{
    close();
}

void MainWindow::updateLoggingView_sub(QString state,float speed,float steer_angle,float error1,double error2)
{
         ui.l_state->setText(state);
         ui.l_speed->setText(QString::number(speed));
         ui.l_steer_angle->setText(QString::number(steer_angle));
         ui.l_error1->setText(QString::number(error1));
         ui.l_error2->setText(QString::number(error2));
         ui.view_logging_sub->scrollToBottom();
}

void MainWindow::closeEvent(QCloseEvent *event)
{

	QMainWindow::closeEvent(event);
}

}  // namespace msg

