%% My first publish
rosinit;

%% Create a publisher
chatpub = rospublisher('/svh/right_hand_Thumb_Flexion_position_controller/command','std_msgs/Float64');

%% Create Message
msg = rosmessage(chatpub);
msg.Data = 1;

%% Publish
send(chatpub,msg);

%% Subscribe
sub = rossubscriber('/joint_states');
pause(1);
clock = rossubscriber('/clock');
%% Receive data (each 10 seconds)
msg2 = receive(sub,10)
msg3 = receive(clock,1)
%% Ros Shut down
%rosshutdown