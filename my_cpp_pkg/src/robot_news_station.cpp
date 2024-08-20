#include "rclcpp/rclcpp.hpp" 
#include "example_interfaces/msg/string.hpp"
#include <string>

class RobotNewsStationNode: public rclcpp::Node
{ 
    public:
        RobotNewsStationNode(): Node("robot_news_station")
        {
            RCLCPP_INFO(this->get_logger(), "Hello This is publisher");  


        }

    private: 
        rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher;

};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}