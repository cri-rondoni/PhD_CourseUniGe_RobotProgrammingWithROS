#include "ros/ros.h"
#include "assignment_1_pkg/Velocity_robot.h"
#include <cmath>

bool armonic(assignment_1_pkg::Velocity_robot::Request& req, assignment_1_pkg::Velocity_robot::Response& res){ //qui ho sia req sia res
//nella callback faccio questo:
res.x = 0.1 + 2.0 * (sin(M_PI*req.p/7.0-2.0*M_PI/7.0));
res.z = 0.0;
return true;
}


int main(int argc, char **argv){

ros::init(argc, argv, "position_server");
ros::NodeHandle n;
ros::ServiceServer service_def = n.advertiseService("set_velocity_robot", armonic); //inizializzo il service

ros::spin();
return 0;
}
