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

            // decalare robot_name parameter 
            this->declare_parameter<std::string>("robot_name", "sans");

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

            robot_name = this->get_parameter("robot_name").as_string();
            oss << "Hi, this is " << robot_name; 

            msg.data = oss.str();
            publisher->publish(msg);  
        }

        std::string robot_name; 
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