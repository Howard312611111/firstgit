#include "ros/ros.h"                        //使用ros必須要加此標頭檔
#include "std_msgs/Float32.h"                //你要使用的msg檔案
#include <sstream>
#include <iostream>

int main(int argc, char **argv){
ros::init(argc, argv, "talker");          //node名稱定義
ros::NodeHandle n;                        //nodehandle名稱定義
                                         
ros::Publisher angle_pub = n.advertise<std_msgs::Float32>("angle", 1000); //pub定義
ros::Rate loop_rate(1);
std_msgs::Float32 msg;

msg.data = 0.0;
int count = 0;
float temp = 0.0;
    while (ros::ok()){
        std::cout << "Type in to change angle:";
        if(!(std::cin >> temp)){
            std::cout << "wrong input type" << std::endl;
            std::cin.clear();//clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        }
        else{
            msg.data = temp;
        }
        while(msg.data>=180){
            msg.data = msg.data - 180;
        }
        ROS_INFO("Talker angle: %f", msg.data);
        angle_pub.publish(msg);//此行將訊息發布，括號內格式須與ros::publisher定義的相同
        ros::spinOnce();         //此行執行所有callback
        loop_rate.sleep();
        ++count;
    }
    return 0;
}