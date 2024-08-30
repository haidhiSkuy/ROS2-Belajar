#include "rclcpp/rclcpp.hpp" 
#include "example_interfaces/msg/int64.hpp"
#include <string> 
#include <sstream> 


class NumberPublisher: public rclcpp::Node 
{ 
    public: 
        NumberPublisher(): Node("number_publisher")
        { 
            RCLCPP_INFO(this->get_logger(), "This is number_publisher");
        }
}; 


int main(int argc, char** argv) 
{ 
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisher>(); 
    rclcpp:spin(node); 
    rclcpp::shutdown(); 
    return 0; 
} 