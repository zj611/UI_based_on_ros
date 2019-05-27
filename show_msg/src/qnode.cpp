#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include<std_msgs/Float32.h>
#include <sstream>
#include "../include/msg/qnode.hpp"

using namespace std;

namespace msg {

QNode::QNode(int argc, char** argv ) :init_argc(argc),init_argv(argv){}

QNode::~QNode()
{
    if(ros::isStarted())
    {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init()
{
  ros::init(init_argc,init_argv,"recive_and_show");
  if ( ! ros::master::check() )
  {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
  chatter_subscriber = n.subscribe("chatter1", 1000, &QNode::Callback, this);
	start();
	return true;
}

void QNode::run()
{
  ros::Rate loop_rate(10);
	int count = 0;
  while ( ros::ok() )
  {

		std_msgs::String msg;
		std::stringstream ss;
		ss << "hello world " << count;
		msg.data = ss.str();
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log_sub( const string &state,const float &speed, const float &steer_angle,const float &error1, const double &error2)
{
  logging_model_sub.insertRows(logging_model_sub.rowCount(),1);
  std::stringstream logging_model_msg;
  //ROS_DEBUG_STREAM(data);
  logging_model_msg << "[" << ros::Time::now() << "]: " << state<<"->speed: "<<speed<<" km/h";

  QVariant new_row(QString(logging_model_msg.str().c_str()));
  logging_model_sub.setData(logging_model_sub.index(logging_model_sub.rowCount()-1),new_row);

  QString b_state(state.c_str());//=QString::fromLocal8Bit("你好");
  Q_EMIT loggingUpdated_sub(b_state,speed,steer_angle,error1,error2);

}

void QNode::Callback(const show_msg::info::ConstPtr &data)
{

  log_sub(data->state,data->speed,data->steer_angle,data->error1,data->error2);
}

}  // namespace msg
