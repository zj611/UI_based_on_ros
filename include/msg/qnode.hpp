#ifndef msg_QNODE_HPP_
#define msg_QNODE_HPP_

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include "show_msg/info.h"
#include<sstream>
#include<vector>
#include"show_msg/info.h"

using namespace std;

namespace msg {

class QNode : public QThread
{
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
  void run();

  QStringListModel* loggingModel_sub() { return &logging_model_sub; }
  void log_sub( const string &state,const float &speed, const float &steer_angle,const float &error1, const double &error2);

  void Callback(const show_msg::info::ConstPtr &data);

Q_SIGNALS:
	void loggingUpdated();
  void rosShutdown();
  void loggingUpdated_sub(QString,float,float,float,double);  //


private:
	int init_argc;
	char** init_argv;

  ros::Subscriber chatter_subscriber; //add

  QStringListModel logging_model_sub; //add

};

}  // namespace msg

#endif
