%% My first publish
rosinit;

% rostopic pub -r 10 /svh_controller/channel_targets sensor_msgs/JointState '{name: [right_hand_Thumb_Flexion], position:[1]}'


%% Create a publisher
global chatpub
chatpub = rospublisher('/svh_controller/channel_targets','sensor_msgs/JointState');
%%
prova_var = {'right_hand_Thumb_Flexion'};
%% Create Message
msg = rosmessage(chatpub);


msg.Name = {'right_hand_Thumb_Flexion'};

msg.Position = 0;

%% Publish
send(chatpub,msg);

%% Subscribe
sub = rossubscriber('/joint_states');
pause(1);
clock = rossubscriber('/clock');
%% Receive data (each 10 seconds)
msg2 = receive(sub,10);


tic;
while toc < 2
    msg3 = receive(clock);      
    msg3.Clock_.Sec
end
%% Ros Shut down
rosshutdown