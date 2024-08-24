#include "rclcpp/rclcpp.hpp" 
#include "example_interfaces/msg/string.hpp"
#include <string>
#include <sstream> 

class RobotNewsStationNode: public rclcpp::Node
{ 
    public:
        RobotNewsStationNode(): Node("robot_news_station")
        {
            RCLCPP_INFO(this->get_logger(), "Hello This is publisher");  
                                                                        //robot_news is the name of topic you want to send data to it
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
            std::ostringstream oss;
            oss << "Hello " << counter; 

            msg.data = oss.str();
            publisher->publish(msg);  

            counter += 1;
        }

        int counter = 1; 
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