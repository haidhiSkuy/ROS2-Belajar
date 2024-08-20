#include "rclcpp/rclcpp.hpp" 
#include "example_interfaces/msg/string.hpp"
#include <string>

class RobotNewsStationNode: public rclcpp::Node
{ 
    public:
        RobotNewsStationNode(): Node("robot_news_station")
        {
            RCLCPP_INFO(this->get_logger(), "Hello This is publisher");  

            publisher = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);

            timer_ = this->create_wall_timer(
                std::chrono::seconds(1),
                std::bind(&RobotNewsStationNode::publishNews, this)
            );
        }

    private:
        void publishNews()
        { 
            auto msg = example_interfaces::msg::String();
            msg.data = "hello"; 
            publisher->publish(msg);  
        }

        rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}