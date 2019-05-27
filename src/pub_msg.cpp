#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include"show_msg/info.h"
#include <string>
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pub_node");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub = nh.advertise<show_msg::info>("chatter1", 1000);

  ros::Rate loop_rate(10);

  show_msg::info vehicle_msg;

  int count = 0;

  string state;
  float u_speed = 60;
  float u_steer_angle = 3.28;
  float u_error1 = 10.04;
  double u_error2 = 0.0082;

  while (ros::ok())
  {
    std_msgs::Float32 msg;


    if(count>=10)
    {
       state = "Terminal!";
       u_speed = 60;
       u_speed = 60;
       u_steer_angle = 3.28;
       u_error1 = 10.04;
       u_error2 = 0.0082;
       count = 0;

    }
    else
    {
       state = "Normal";
       u_speed +=count/2.4;
       u_steer_angle += 1.28;
       u_error1 -= 1.04;
       u_error2 += count*0.0082;
       count++;
    }


    //msg.data = u;
    vehicle_msg.speed = u_speed;
    vehicle_msg.steer_angle = u_steer_angle;
    vehicle_msg.error1 = u_error1;
    vehicle_msg.error2 = u_error2;
    vehicle_msg.state = state;



    chatter_pub.publish(vehicle_msg);
    ROS_INFO("CURRENT SPEED DATA IS: [%f]",vehicle_msg.speed);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
