#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include <string> 

class Smartphone: public rclcpp::Node 
{ 
    public: 
        Smartphone(): Node("smartphone")
        { 
            RCLCPP_INFO(this->get_logger(), "Hello this is subscriber");  

            subscriber = this->create_subscription<example_interfaces::msg::String>(
                "robot_news", 10, std::bind(&Smartphone::SubscribeNews, this, std::placeholders::_1)
            );
        
        }

    private: 
        void SubscribeNews(const example_interfaces::msg::String::SharedPtr msg)
        {
            RCLCPP_INFO(this->get_logger(), msg->data.c_str());
        }


        rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber;
}; 


int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<Smartphone>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
};