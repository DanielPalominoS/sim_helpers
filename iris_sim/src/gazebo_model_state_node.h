#ifndef GAZEBO_MODEL_STATE_NODE_H
#define GAZEBO_MODEL_STATE_NODE_H
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <gazebo_msgs/ModelStates.h>
#include <std_msgs/String.h>
#include <stdio.h>

static const std::string kDefaultModelName = "iris_demo";
static const std::string kDefaultStatesSubTopic = "gazebo/model_states";
static const std::string kDefaultPubTopic = "/mavros/vision_pose/pose";

static constexpr double kDefaultRate =100.0;

class gazebo_model_state_node
{
  ros::Rate rate_;
  ros::NodeHandle nh_;

  ros::Subscriber states_subscriber_;
  ros::Time now_;
  ros::Publisher pose_publisher_;
  std_msgs::String model_name_;
  geometry_msgs::PoseStamped pose_;
public:
  gazebo_model_state_node();
  ~gazebo_model_state_node();
  void StatesCallback(const gazebo_msgs::ModelStatesConstPtr& msg);
  void Main_task();
  //void main();
};

#endif // GAZEBO_MODEL_STATE_NODE_H
