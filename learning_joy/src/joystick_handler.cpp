#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include "Configuration.h"
// #include "learning_joy/RoboteqCommand.h"

// To use: run:
// roslaunch turtle_joy.launch

// Or alternatively:
// rosrun joy joynode with rosrun
// and
// rosrun learning_joy turtle_teleop_joy


class JoystickHandler
{
public:
  JoystickHandler();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};

// Set-up subscribers/publishers in constructor
JoystickHandler::JoystickHandler():
  linear_(1),
  angular_(2)
{
  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  // Get joystick info from /joy
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &JoystickHandler::joyCallback, this);

  // Set joystick values in /cmd_vel
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void JoystickHandler::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = joy->axes[angular_]; // Set rotation axis data
  twist.linear.x = joy->axes[linear_]; // Set forward/backward axis data
  vel_pub_.publish(twist);
}

void callback(const geometry_msgs::Twist::ConstPtr& msg){
    double linear = msg->linear.x;
    double angular = msg->angular.z;
    double leftVelocity;  //Velocity 1
    double rightVelocity;  //Velocity 2
    leftVelocity = linear - TRACK_WIDTH * angular/2;
    rightVelocity = linear + TRACK_WIDTH * angular/2;

    ROS_INFO("%f, %f", leftVelocity, rightVelocity);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "joy_handler");

  JoystickHandler joy_handler;

  // Handler for setting calcualted velocity values
  ros::NodeHandle vel_handle;
  ros::Subscriber vel_sub = vel_handle.subscribe("/cmd_vel", 1000, callback);

  ros::spin();
}
