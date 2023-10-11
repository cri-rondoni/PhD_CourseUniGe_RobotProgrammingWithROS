#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "assignment_1_pkg/Vel_robot.h"
#include "assignment_1_pkg/Velocity_robot.h"

ros::Publisher custom_pub;
ros::Publisher vel_pub;
ros::ServiceClient client_custom;

void robotCallback(const nav_msgs::Odometry::ConstPtr& msg){
ROS_INFO("The robot position is: %f, %f", msg->pose.pose.position.x, msg->pose.pose.position.y);

assignment_1_pkg::Velocity_robot server_vel;
server_vel.request.p = msg->pose.pose.position.x;

client_custom.call(server_vel);

geometry_msgs::Twist my_vel;


if (msg->pose.pose.position.x > 2.0 && msg->pose.pose.position.x < 8.0){

my_vel.linear.x = server_vel.response.x; //QUI CI DEVO METTERE COSA CALCOLA IL SERVER PER X
my_vel.angular.z = server_vel.response.z; //QUI CI DEVO METTERE COSA CALCOLA IL SERVER PER Z
}

else if (msg->pose.pose.position.x < 2.0){ 
my_vel.linear.x = 1.0;
my_vel.angular.z = -3.0;
}

else if (msg->pose.pose.position.x > 8.0){
my_vel.linear.x = 1.0;
my_vel.angular.z = 3.0;
}

else if (msg->pose.pose.position.x < 2.0 && msg->pose.pose.position.x > 8.0){
my_vel.linear.x = 0.0;
my_vel.angular.z = 0.0;
}


vel_pub.publish(my_vel);

}

int main (int argc, char **argv)
{
	
//Initialize the node, setup the NodeHandler for handling the communication with 
//the ROS system
ros::init(argc, argv, "robot_ass1_controller");
ros::NodeHandle nh;

//Define the subscriber to robot's position
ros::Subscriber sub = nh.subscribe("odom", 1, robotCallback);

vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
custom_pub = nh.advertise<assignment_1_pkg::Vel_robot>("custom", 10);

client_custom = nh.serviceClient<assignment_1_pkg::Velocity_robot>("set_velocity_robot", 10);

ros::spin();
return 0;

}
