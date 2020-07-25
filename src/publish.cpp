#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Imu.h"
#include <ros/ros.h>

using namespace std;


int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "IMU_GPS_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为/odom_info的topic，消息类型为learning_topic::Person，队列长度10
    ros::Publisher IMU_info_pub = n.advertise<sensor_msgs::Imu>("/imu", 10);
    ros::Publisher GPS_info_pub=n.advertise<sensor_msgs::NavSatFix>("/fix", 10);

    // 设置循环的频率
    ros::Rate loop_rate(1);
    ROS_INFO("The data of IMU already published!");
    int count = 0;
    while (ros::ok())
    {
        // 初始化learning_topic::Person类型的消息
    	sensor_msgs::Imu msg;
        sensor_msgs::NavSatFix msg2;
        msg.linear_acceleration.x=10;
        msg2.latitude=132;      
         // 发布消息
        IMU_info_pub.publish(msg);
        GPS_info_pub.publish(msg2);
               // ROS_INFO("The data of IMU: x:%d  y:%d  z:%d w:%d", 
			//	  msg.x, msg.y, msg.z,msg.w);
		loop_rate.sleep();

                  }

    

       	//ROS_INFO("The data is processing which is developed by Jack JU: a:%d  b:%d  c:%d d:%d e:%d", 
			//	  msg.a, msg.b, msg.c,msg.d,msg.e);

        // 按照循环频率延时
       // loop_rate.sleep(
    return 0;
}
