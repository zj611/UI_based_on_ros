#ifndef msg_MAIN_WINDOW_H
#define msg_MAIN_WINDOW_H

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

namespace msg {

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();


	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

public Q_SLOTS:



  void on_start_clicked(bool check );
  void on_quit_clicked(bool check );
  void updateLoggingView_sub(QString state,float speed, float steer_angle,float error1, double error2); //add

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace msg

#endif // msg_MAIN_WINDOW_H
