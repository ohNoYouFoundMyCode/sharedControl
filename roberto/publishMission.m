function publishMission(u1, u2, u3, u4)
thrustPub = rospublisher('/ship/actuation','usv16_msgs/Usv16ActuatorInputs');
msg = rosmessage(thrustPub);
msg.T=0;
msg.ActuatorInputs = [u1, u2, u3, u4];
send(thrustPub,msg);
