// This file simulates the communication with the real driver
// Author: Antonio Di Guardo <antonio.diguardo@santannapisa.it>
// From a previus work of
// Diego Rodriguez <rodriguez@ais.uni-bonn.de>
//#include <ros/ros.h>
#include <ros/node_handle.h>

#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include "my_lib.h"


std::vector<std::string> joint_commands_names;
Joints_Controllers_Manager manager;

// std_msgs/Float64


void thumbFlexCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.thumbFlexCallback(js->data);
    /*
        std_msgs::Float64 msg;
        msg.data = js->data;
        manager.pubs[0].publish(msg);
        */
}

void thumbOppositionCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.thumbOppositionCallback(js->data);
}

void Index_DistalCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.indexDistalCallback(js->data);
}

void Index_ProximalCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.indexProximalCallback(js->data);
}

void Middle_DistalCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.middleDistalCallback(js->data);
}

void Middle_ProximalCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.middleProximalCallback(js->data);
}

void Finger_SpreadCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.fingerSpreadCallback(js->data);
}

void Ring_FingerCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.ringFingerCallback(js->data);
}

void PinkyCallback(const std_msgs::Float64::ConstPtr &js)
{
    manager.pinkyCallback(js->data);
}

void subJointStatesCallback(const sensor_msgs::JointState::ConstPtr &js)
{
        manager.elaborate(js);
        // Mappatura seguendo la matrice di trasmissione
}


int main(int argc, char** argv){


    ros::init(argc, argv, "cmd_publisher_2");
    ros::NodeHandle nh;


    ros::Subscriber sub_js;
    sub_js = nh.subscribe("/svh_controller/channel_targets", 1000, subJointStatesCallback);

    // Creo un topic per ogni variabile controllata

    ros::Subscriber sub_Thumb_Flexion;
    sub_Thumb_Flexion = nh.subscribe("/svh_controller/Thumb_Flexion", 1000, thumbFlexCallback);

    ros::Subscriber sub_Thumb_Opposition;
    sub_Thumb_Opposition = nh.subscribe("/svh_controller/Thumb_Opposition", 1000, thumbOppositionCallback);

    ros::Subscriber sub_Index_Distal;
    sub_Index_Distal = nh.subscribe("/svh_controller/Index_Distal", 1000, Index_DistalCallback);
    
    ros::Subscriber sub_Index_Proximal;
    sub_Index_Proximal = nh.subscribe("/svh_controller/Index_Proximal", 1000, Index_ProximalCallback);

    ros::Subscriber sub_Middle_Proximal;
    sub_Middle_Proximal = nh.subscribe("/svh_controller/Middle_Proximal", 1000, Middle_ProximalCallback);

    ros::Subscriber sub_Middle_Distal;
    sub_Middle_Distal = nh.subscribe("/svh_controller/Middle_Distal", 1000, Middle_DistalCallback);

    ros::Subscriber sub_Pinky;
    sub_Pinky = nh.subscribe("/svh_controller/Pinky", 1000, PinkyCallback);

    ros::Subscriber sub_Ring_Finger;
    sub_Ring_Finger = nh.subscribe("/svh_controller/Ring_Finger", 1000, Ring_FingerCallback);

    ros::Subscriber sub_Finger_Spread;
    sub_Finger_Spread = nh.subscribe("/svh_controller/Finger_Spread", 1000, Finger_SpreadCallback);
    //FIXME: do not give the names directly but read them from somewhere 
    
    joint_commands_names.push_back("right_hand_Thumb_Flexion");             // controlled
    joint_commands_names.push_back("right_hand_Thumb_Opposition");          // controlled 
    joint_commands_names.push_back("right_hand_j5"); // pr: e1  chld: e2  val: 1*right_hand_Thumb_Opposition      
    joint_commands_names.push_back("right_hand_j3"); // pr: a   chld: b   val: 1.01511*right_hand_Thumb_Flexion
    joint_commands_names.push_back("right_hand_j4"); // pr: b   chld: c   val: 1.44889*right_hand_Thumb_Flexion
    joint_commands_names.push_back("right_hand_Index_Finger_Distal"); // pr: l  chld: p     ----CONTROLLED----
    joint_commands_names.push_back("right_hand_Index_Finger_Proximal"); // pr: virtual_l chld: l ----CONTROLLED----
    joint_commands_names.push_back("right_hand_j14"); // pr: p  chld: t   val: 1.0450*right_hand_Index_Finger_Distal
    joint_commands_names.push_back("right_hand_Middle_Finger_Proximal");    // controlled
    joint_commands_names.push_back("right_hand_Middle_Finger_Distal");      // controlled
    joint_commands_names.push_back("right_hand_j15");
    joint_commands_names.push_back("right_hand_Ring_Finger");               // controlled
    joint_commands_names.push_back("right_hand_j12");
    joint_commands_names.push_back("right_hand_j16");
    joint_commands_names.push_back("right_hand_Pinky");                     // controlled
    joint_commands_names.push_back("right_hand_j13");
    joint_commands_names.push_back("right_hand_j17");
    joint_commands_names.push_back("right_hand_index_spread");
    joint_commands_names.push_back("right_hand_ring_spread");
    joint_commands_names.push_back("right_hand_Finger_Spread");             // controlled
    joint_commands_names.push_back("my_joint_1");
    joint_commands_names.push_back("my_joint_2");
    joint_commands_names.push_back("my_joint_3");
    joint_commands_names.push_back("my_joint_4");
    joint_commands_names.push_back("my_joint_5");
    joint_commands_names.push_back("my_joint_6");
    joint_commands_names.push_back("my_joint_7");

    //unsigned int n = joint_commands_names.size();
    //for(unsigned int i=0; i<n; i++){
        //joint_commands.position.push_back(0.0);    
        //joint_commands.velocity.push_back(0.0);    
        //joint_commands.acceleration.push_back(0.0);    
        //joint_commands.rawPosition.push_back(0.0);    
        //joint_commands.torque();     // TODO: inverse dynamics to fill this array
        //joint_commands.effort.push_back(0.2); // Default value   
    //}

    /*
    * Controllers ai quali mi sottoscrivo
    */
    manager.init(&nh);
    ros::spin();

    return 0;
}
