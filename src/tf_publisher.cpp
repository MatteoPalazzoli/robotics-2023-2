#include "ros/ros.h"
#include <time.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Quaternion.h"
#include <tf/transform_broadcaster.h>

class pub_sub
{
	ros::Time time;

	private:
		ros::NodeHandle n;
		ros::Subscriber sub;
		ros::Timer timer1;
		tf::TransformBroadcaster br;
		
	public:
  	pub_sub(){
  	
  		do{
  			time = ros::Time::now();
  		}while(time.toSec() == 0);
		
		/* subscribe to the topic */
  		sub = n.subscribe("/t265/odom", 1, &pub_sub::callback, this);
		ROS_INFO("Listening on /t265/odom topic...");
	}

	void callback(const nav_msgs::Odometry::ConstPtr& msg){
		tf::Transform transform;
		double x,y,z,qx, qy, qz, qw;
		
		//get the msg data
		x = (*msg).pose.pose.position.x;
		y = (*msg).pose.pose.position.y;
		z = (*msg).pose.pose.position.z;
		
		qx = (*msg).pose.pose.orientation.x;
		qy = (*msg).pose.pose.orientation.y;
		qz = (*msg).pose.pose.orientation.z;
		qw = (*msg).pose.pose.orientation.w;
		
		//set the tf
		transform.setOrigin( tf::Vector3(x,y,z) );
		tf::Quaternion q(qx,qy,qz,qw);
		transform.setRotation(q);
		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
	}

};

int main(int argc, char **argv)
{
 	ros::init(argc, argv, "tf_pulisher");
 	pub_sub my_pub_sub;
	ROS_INFO("tf_publisher node started.");
 	ros::spin();
 	return 0;
}
