#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <math.h>
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Imu.h"
using namespace std;

using namespace sensor_msgs;
using namespace message_filters;
void callback(const sensor_msgs::Imu::ConstPtr& imu, const sensor_msgs::NavSatFix::ConstPtr& gps)
{
  // Solve all of perception here...?>
  cout<<"传感器数据同步..."<<endl;
  cout<<"imu:"<<imu->linear_acceleration.x<<endl;
  cout<<"gps:"<<gps->latitude<<endl;
}
 

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vision_node");
 
  ros::NodeHandle nh;
 // message_filters::Subscriber<Image> image_sub(nh, "image", 1);
  message_filters::Subscriber<sensor_msgs::Imu> imu_sub(nh, "/imu", 1);
  //message_filters::Subscriber<CameraInfo> info_sub(nh, "camera_info", 1);
 message_filters::Subscriber<sensor_msgs::NavSatFix> gps_sub(nh, "/fix", 1);
  typedef sync_policies::ExactTime<Imu, NavSatFix> MySyncPolicy;
  // ExactTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), imu_sub, gps_sub);
  sync.registerCallback(boost::bind(&callback, _1, _2));
 
  ros::spin();
 
  return 0;
}

