#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include <string> 

class Smartphone: public rclcpp::Node 
{ 
    public: 
        Smartphone(): Node("smartphone")
        { 
            RCLCPP_INFO(this->get_logger(), "Hello this is subscriber");  
        }

    private: 

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