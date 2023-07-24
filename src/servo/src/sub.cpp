#include "ros/ros.h"
#include "pigpio.h"
#include "std_msgs/Float32.h"
#include "cmath"

#define SERVO_PIN 13   //輸出PWM的pin
#define LOWER_ANGLE 0.203 //sin 函數內最小角度
#define UPPER_ANGLE 1.57  //sin 函數內最大角度
#define MAX_BANDWIDTH 2500 //最大band width
#define ONE_DEGREE 0.0174  //1度
float get_angle;

void angleCallback(const std_msgs::Float32::ConstPtr& msg){
    get_angle = msg->data;
    ROS_INFO("Listener get %f",get_angle);
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"motor");
    ros::NodeHandle nh;

    if(gpioInitialise() < 0)    //初始化
    {
    ROS_INFO("SYSTEM_ERROE");
    return 1;
    }
    gpioSetMode(SERVO_PIN,PI_OUTPUT); //設定pin 13用於輸出

    ros::Rate rate(1);
    float angle=LOWER_ANGLE;

    while(ros::ok())
    {
    ros::Subscriber sub = nh.subscribe("angle",1000, angleCallback);
    angle = get_angle/57.3;
    gpioServo(SERVO_PIN,MAX_BANDWIDTH*sin(angle));  //設定輸出pin和輸出bandwidth
    //ROS_INFO("the bandwidth is %.2f",MAX_BANDWIDTH*sin(angle));
    ROS_INFO("the angle of sin function is %.2f degree",get_angle);
    rate.sleep();
    ros::spinOnce();
    }
    gpioTerminate();    //终止 Pigpio使用
    return 0;
}