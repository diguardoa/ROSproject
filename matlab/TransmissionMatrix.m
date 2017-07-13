%% Transmission Matrix
R = zeros(20,9);
%% Motors
Thumb_flexion = 1;
Thumb_opposition = 2;
Index_distal = 3;
Index_proxi = 4;
Middle_proxi = 5;
Middle_distal = 6;
Ring = 7;
Pinky = 8;
Fingers_spread = 9;

%% Actuated Joints

%% Pinky
%      j17
R(17,Pinky) = 1.42307;
%      j13
R(13,Pinky) = 1.334;
%      pinky                   j9
R(9,Pinky) = 1;
%      finger_spread           j20
R(20,Fingers_spread) = 1;
%% Ring
%      j16
R(16,Ring) = 1.42093;
%      j12
R(12,Ring) = 1.3588;
%      ring_finger             j8
R(8,Ring) = 1;
%      ring_spread             j19
R(9,Fingers_spread) = 0.5;

%% Middle
%      j15
R(15,Middle_distal) = 1.0454;
%      middle_finger_distal    j11
R(11,Middle_distal) = 1;
%     middle_finger_proximal  j7
R(7,Middle_proxi) = 1;
%% Index
%     j14
R(14,Index_distal) = 1.0450;
%     index_finger_distal     j10
R(10,Index_distal) = 1;
%     index_finger_proximal   j6
R(6, Index_proxi) = 1;
%     index_spread            j18
R(18,Fingers_spread) = 0.5;
%% Thumb
%     j4
R(4,Thumb_flexion) = 1.44889;
%     j3
R(3,Thumb_flexion) = 1.01511;
%     thumb_flexion           j2
R(2,Thumb_flexion) = 1;

%% Wrist
%     thumb_opposition        j1
R(1,Thumb_opposition) = 1;
%     j5
R(5,Thumb_opposition) = 1;
%% 
