// my_lib.h

extern std::vector<std::string> joint_commands_names;

class Joints_Controllers_Manager {
public:
    void prova();
    void init(ros::NodeHandle * ndhn);
    void elaborate(const sensor_msgs::JointState::ConstPtr &js);
    
    void thumbFlexCallback(float val);
    void thumbOppositionCallback(float val);
    
    void indexDistalCallback(float val);
    void indexProximalCallback(float val);

    void middleDistalCallback(float val);
    void middleProximalCallback(float val);

    void ringFingerCallback(float val);
    void pinkyCallback(float val);

    void fingerSpreadCallback(float val);
    
private:
    ros::NodeHandle *nh;
	std::vector<ros::Publisher> pubs;

    void moveMimicTags(int index, float value);
    int translate(std::string joint_name);
    int getIndex(std::string joint);

};

void Joints_Controllers_Manager::thumbOppositionCallback(float val) {
	    std_msgs::Float64 msg;

        msg.data = val;
        pubs[getIndex("right_hand_Thumb_Opposition")].publish(msg);

        msg.data = val;
        pubs[getIndex("right_hand_j5")].publish(msg);

}

void Joints_Controllers_Manager::thumbFlexCallback(float val) {
	    std_msgs::Float64 msg;

        msg.data = val*1.44889;
        pubs[getIndex("right_hand_j4")].publish(msg);

        msg.data = val*1.01511;
        pubs[getIndex("right_hand_j3")].publish(msg);

        msg.data = val;
        pubs[getIndex("right_hand_Thumb_Flexion")].publish(msg);

}

void Joints_Controllers_Manager::indexDistalCallback(float val) {
    std_msgs::Float64 msg;

    msg.data = val*1.0450;
    pubs[getIndex("right_hand_j14")].publish(msg);

    msg.data = val;
    pubs[getIndex("right_hand_Index_Finger_Distal")].publish(msg);
}

void Joints_Controllers_Manager::indexProximalCallback(float val) {
    std_msgs::Float64 msg;

    msg.data = val;
    pubs[getIndex("right_hand_Index_Finger_Proximal")].publish(msg);

}

void Joints_Controllers_Manager::middleDistalCallback(float val) {
    std_msgs::Float64 msg;

    msg.data = val*1.0454;
    pubs[getIndex("right_hand_j15")].publish(msg);

    msg.data = val;
    pubs[getIndex("right_hand_Middle_Finger_Distal")].publish(msg);

}
void Joints_Controllers_Manager::middleProximalCallback(float val) {
    std_msgs::Float64 msg;

    msg.data = val;
    pubs[getIndex("right_hand_Middle_Finger_Proximal")].publish(msg);
}

void Joints_Controllers_Manager::ringFingerCallback(float val) {
    std_msgs::Float64 msg;

    msg.data = val*1.42093;
    pubs[getIndex("right_hand_j16")].publish(msg);

    msg.data = val*1.3588;
    pubs[getIndex("right_hand_j12")].publish(msg);

    msg.data = val;
    pubs[getIndex("right_hand_Ring_Finger")].publish(msg);
}

void Joints_Controllers_Manager::pinkyCallback(float val) {
    std_msgs::Float64 msg;

    msg.data = val*1.42307;
    pubs[getIndex("right_hand_j17")].publish(msg);

    msg.data = val*1.334;
    pubs[getIndex("right_hand_j13")].publish(msg);

    msg.data = val;
    pubs[getIndex("right_hand_Pinky")].publish(msg);

}

void Joints_Controllers_Manager::fingerSpreadCallback(float val) {
    std_msgs::Float64 msg;
    msg.data = val;
    pubs[getIndex("right_hand_Finger_Spread")].publish(msg);

    msg.data = val*0.5;
    pubs[getIndex("right_hand_index_spread")].publish(msg);

    msg.data = val*0.5;
    pubs[getIndex("right_hand_ring_spread")].publish(msg);

}

void Joints_Controllers_Manager::moveMimicTags(int index, float value) {
	   switch (index) {
	   	case 0: // Thumb flexion

	   		break;
   		case 1: // Thumb opposition

   			break;
   		case 5: // Index Distal

   			break;
   		case 6: // Index Proximal

   			break;
   		case 8: // Middle Distal

   			break;
   		case 9: // Middle Proximal

   			break;
   		case 11: // Ring

   			break;
   		case 14: // Pinky

   			break;
   		case 19: // Spread

   			break;
	   }
       std_msgs::Float64 msg;
       msg.data = value;
       pubs[index].publish(msg);
}

void Joints_Controllers_Manager::elaborate(const sensor_msgs::JointState::ConstPtr &js) {

    //for (unsigned int i = 0; i < joint_commands_names.size(); i++){
    for (unsigned int i = 0; i < js->position.size(); i++){

    	//moveMimicTags(getIndex(js->name[i]), js->position[i]);

        int index = getIndex(js->name[i]);
        std_msgs::Float64 msg;
        msg.data = js->position[i];
        pubs[index].publish(msg);
        
    }

}

void Joints_Controllers_Manager::init(ros::NodeHandle *ndhn) {
	nh = ndhn;
    for(unsigned int i=0; i<joint_commands_names.size(); i++){        
        pubs.push_back(nh->advertise<std_msgs::Float64>("/svh/"+joint_commands_names[i]+"_position_controller/command", 1000));
    }

    int temp = getIndex("right_hand_j5");
    ROS_INFO("giunto numero %d",temp);

}

int Joints_Controllers_Manager::translate(std::string joint_name) {
    return 1;
}

void Joints_Controllers_Manager::prova() {
	ROS_INFO("classe importata ---------------------------------------------");
}

int Joints_Controllers_Manager::getIndex(std::string joint) {
	int temp = -1;
	for (unsigned int i=0; i<joint_commands_names.size(); i++) 
		if (joint == joint_commands_names[i])
			temp = i;
	
	return temp;
}