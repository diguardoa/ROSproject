// Publisher for the controllers of the gazebo model of the schunck svh hand
// Author: Diego Rodriguez <rodriguez@ais.uni-bonn.de>
//#include <ros/ros.h>
#include <ros/node_handle.h>

#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>

std::vector<ros::Publisher> pubs;

std::vector<std::string> joint_commands_names;
//std::vector<double> joint_commands_positions;

void subJointStatesCallback(const sensor_msgs::JointState::ConstPtr &js)
{
        for (unsigned int i = 0; i < joint_commands_names.size(); i++){
            //joint_commands.positions[i] = js->position[i];

            std_msgs::Float64 msg;
            msg.data = js->position[i];
            pubs[i].publish(msg);
        }
}


int main(int argc, char** argv){

    ros::init(argc, argv, "cmd_publisher");
    ros::NodeHandle nh;
    

    ros::Subscriber sub_js;
    sub_js = nh.subscribe("/svh_controller/channel_targets", 1000, subJointStatesCallback);

    //FIXME: do not give the names directly but read them from somewhere 
    joint_commands_names.push_back("right_hand_Thumb_Flexion");
    joint_commands_names.push_back("right_hand_Thumb_Opposition");
    joint_commands_names.push_back("right_hand_j5");
    joint_commands_names.push_back("right_hand_j3");
    joint_commands_names.push_back("right_hand_j4");
    joint_commands_names.push_back("right_hand_Index_Finger_Distal");
    joint_commands_names.push_back("right_hand_Index_Finger_Proximal");
    joint_commands_names.push_back("right_hand_j14");
    joint_commands_names.push_back("right_hand_Middle_Finger_Proximal");
    joint_commands_names.push_back("right_hand_Middle_Finger_Distal");
    joint_commands_names.push_back("right_hand_j15");
    joint_commands_names.push_back("right_hand_Ring_Finger");
    joint_commands_names.push_back("right_hand_j12");
    joint_commands_names.push_back("right_hand_j16");
    joint_commands_names.push_back("right_hand_Pinky");
    joint_commands_names.push_back("right_hand_j13");
    joint_commands_names.push_back("right_hand_j17");
    joint_commands_names.push_back("right_hand_index_spread");
    joint_commands_names.push_back("right_hand_ring_spread");
    joint_commands_names.push_back("right_hand_Finger_Spread");

    //unsigned int n = joint_commands_names.size();
    //for(unsigned int i=0; i<n; i++){
        //joint_commands.position.push_back(0.0);    
        //joint_commands.velocity.push_back(0.0);    
        //joint_commands.acceleration.push_back(0.0);    
        //joint_commands.rawPosition.push_back(0.0);    
        //joint_commands.torque();     // TODO: inverse dynamics to fill this array
        //joint_commands.effort.push_back(0.2); // Default value   
    //}

    for(unsigned int i=0; i<joint_commands_names.size(); i++){        
        pubs.push_back(nh.advertise<std_msgs::Float64>("/svh/"+joint_commands_names[i]+"_position_controller/command", 1000));
    }

    ros::spin();

    return 0;
}
