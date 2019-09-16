#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int64.h>
// TODO: find out what other libraries are needed

void callback_motor_1(const std_msgs::Int64& vel){
	// TODO: find out what data the motor actually needs to receive to run
	// Print statement below is just filler code to confirm it is subscribing, replace with something useful
	std::cout << "Motor 1 velocity " << vel << "\n";
}

void callback_motor_2(const std_msgs::Int64& vel){
	// TODO: find out what data the motor actually needs to receive to run
	// Print statement below is just filler code to confirm it is subscribing, replace with something useful
	std::cout << "Motor 2 velocity " << vel << "\n";
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "motor_node");
	ros::NodeHandle nh;							// initialize node and nodehandle

	ros::Subscriber motor1 = nh.subscribe("/motor_1", 10, callback_motor_1);
	ros::Subscriber motor2 = nh.subscribe("/motor_2", 10, callback_motor_2);


	ros::spin();
}