#include "ros/ros.h"
#include "nav_msgs/Odometry.h"

void robotCallback(const nav_msgs::Odometry::ConstPtr& msg){
ROS_INFO("The robot position is: %f, %f", msg->pose.pose.position.x, msg->pose.pose.position.y);

}


int main (int argc, char **argv)
	{
	
	//Initialize the node, setup the NodeHandler for handling the communication with 
	//the ROS system
	ros::init(argc, argv, "robot_subscriber");
	ros::NodeHandle nh;
	
	//Define the subscriber to robot's position
	ros::Subscriber sub = nh.subscribe("odom", 1, robotCallback);
	ros::spin();
	return 0;
	}
