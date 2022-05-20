#ifndef __ROSNODE_H
#define __ROSNODE_H

#include <ros/ros.h>

#include "callbacks.h"

#include <QTimer>
#include <string>
#include <QThread>

#include <vector>
#include <map>

class RNode : public QThread{
    Q_OBJECT
public:

    explicit RNode(int argc, char** argv, const std::string& nodeName)
    {

        //pub = m_node->advertise<demo02_self_topic::Person>("/person_info",10);

    }

    void subscribe(const std::string& topic, uint32_t queue_size)
    {

        ros::NodeHandle node;

        // sub = node.subscribe(topic, queue_size, personinfoCallBack);
        printf("subscribe\n");
    }

    void run() override 
    {
        ros::Rate loop_rate(1);
        size_t count = 0;
        while ( ros::ok() ) {
            ros::spin();
            printf("ros loop\n");
            //pub.publish(this->person_msg);
            loop_rate.sleep();
            ++count;
            //std::printf("node spin\n");
        }
    }

    ~RNode() override
    {
        if(ros::isStarted()) {
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
        }
        wait();
    }

    bool init(const std::string &master_url, const std::string &host_url)
    {
        std::map<std::string,std::string> remappings;
        remappings["__master"] = master_url;
        remappings["__hostname"] = host_url;
        ros::init(remappings, "robot_ui");

        if ( ! ros::master::check() ) {
            return false;
        }

        // m_node = new ros::NodeHandle();


        ros::start();

        start();
        return true;
    }

private:
    ros::Subscriber sub;
    ros::Publisher pub;
    // ros::NodeHandle *m_node;
};

#endif //__ROSNODE_H