#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define MAX_CHARS 50
#define MAX_SINGLE 15
#define TERM '\0'

#define CHAR_DOT 46
#define CHAR_ZERO 48
#define CHAR_NINE 57
 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace std;

int main(int argc, char** argv){
	ros::init(argc, argv, "navigation");
	MoveBaseClient ac("move_base", true);
	ros::NodeHandle nh;
	std::string dir;
  char row[MAX_CHARS];
	char sep[2] = ",";
	char data[3][MAX_SINGLE];
	char* token;
	int i=0, count=0;
	float theta;
	FILE* fp;
  
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	//compile the static features of the goal
	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.pose.position.z = 0.0;
	goal.target_pose.pose.orientation.x = 0;
	goal.target_pose.pose.orientation.y = 0;
	
	if (nh.getParam("/navigation/waypoints_dir", dir)) {
		fp = fopen(dir.c_str(), "r");
	} else {
		ROS_ERROR("Error opening waypoints file.");
		return -1;
	}
	
	//read one CSV row
	while (fgets (row , MAX_CHARS, fp) != NULL){
		
		//skip the first row (header)
		if(count == 0){
			count = 1;
			ROS_INFO(" --- CSV HEADER READ ---");
			continue;
		}
		
		/*split the string into tokens and assign the parts to the data[] array
			data[0] = x
			data[1] = y
			data[2] = heading
		*/
		token = strtok(row, sep);
		strcpy(data[0], token);
		for(i=1;i<3;i++){
			token = strtok(NULL, sep);
			strcpy(data[i], token);
		}
		
		//remove the newline from the heading
		for(i=1; i<MAX_SINGLE; i++){
			if(data[2][i] != CHAR_DOT && (data[2][i] < CHAR_ZERO || data[2][i] > CHAR_NINE)){
				data[2][i] = TERM;
				break;
			}
		}
		
		//convert data to float and assign them to the goal's fields
		goal.target_pose.pose.position.x = (float)atof(data[0]);
		goal.target_pose.pose.position.y = (float)atof(data[1]);
		//get the angle and convert in radians
		theta = (float)atof(data[2]) * M_PI / 180;
		//convert heading in quaternion 
		goal.target_pose.pose.orientation.w = cos(theta/2);
		goal.target_pose.pose.orientation.z = sin(theta/2);
		
		//header fields
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.header.seq = count;
		
		ROS_INFO("SENDING GOAL %d: (%s, %s, %s)", count, data[0], data[1], data[2]);
		ac.sendGoal(goal);
		ROS_INFO("WAITING FOR RESULT");
		ac.waitForResult();
		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
			ROS_INFO("SUCCESS");
		} else {
			ROS_INFO("FAIL");
		}
		count++;
	}
	ROS_INFO("--- COMPLETED ---");
	fclose(fp);
  return 0;
}
