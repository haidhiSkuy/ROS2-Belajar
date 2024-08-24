#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include <string> 

class Smartphone: public rclcpp::Node 
{ 
    public: 
        Smartphone(): Node("smartphone")
        { 

        }

}; 


int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<Smartphone>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
};