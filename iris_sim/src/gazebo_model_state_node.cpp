#include "gazebo_model_state_node.h"
gazebo_model_state_node::gazebo_model_state_node() : rate_(kDefaultRate)
{
  ros::NodeHandle pnh("~");

  std::string states_sub_topic;
  std::string pose_pub_topic;
  std::string model_name;
  double rate;
  // Get params if given
  pnh.param("StatesSubTopic", states_sub_topic, kDefaultStatesSubTopic);
  pnh.param("PosePubTopic", pose_pub_topic, kDefaultPubTopic);
  pnh.param("ModelName", model_name, kDefaultModelName);
  // Subscribe to topics
  states_subscriber_ = nh_.subscribe<gazebo_msgs::ModelStates>(
      states_sub_topic, 60, boost::bind(&gazebo_model_state_node::StatesCallback, this, _1));
  pose_publisher_ = nh_.advertise<geometry_msgs::PoseStamped>(pose_pub_topic, 60);
  model_name_.data = model_name;
}
gazebo_model_state_node::~gazebo_model_state_node()
{
}
void gazebo_model_state_node::StatesCallback(const gazebo_msgs::ModelStatesConstPtr& msg)
{
  int index;
  for (int i = 0; i < msg->pose.size(); i++)
  {
    if (msg->name[i] == model_name_.data)
    {
      pose_.pose = msg->pose[i];
      pose_.header.stamp = ros::Time::now();

      return;
    }
  }
  return;
}
void gazebo_model_state_node::Main_task()
{
  while (ros::ok())
  {
    ros::spinOnce();
    rate_.sleep();
    pose_publisher_.publish(pose_);
  }
}

int main(int argc, char** argv)
{
  // std::setprecision (10);
  ros::init(argc, argv, "gazebo_model");
  ros::Time::init();
  gazebo_model_state_node state_publisher;
  /*while(ros::ok()){
    #ifdef DEBUG
    ROS_WARN_ONCE("Plese verify that all servers have been initialized");
    #endif
  }*/
  state_publisher.Main_task();
  return 0;
}
