#include "rclcpp/rclcpp.hpp" 
#include <string>

class MyNode: public rclcpp::Node
{ 
    public:
        MyNode(): Node("cpp_test")
        {
            RCLCPP_INFO(this->get_logger(), "Hello ROS2 CPP");  

            timer_ = this->create_wall_timer(
                std::chrono::seconds(1), 
                std::bind(&MyNode::timerCallback, this)
            );

        }
        
    
    private: 
        void timerCallback()
        {   
            std::string counter_str = std::to_string(counter);
            RCLCPP_INFO(this->get_logger(), "Hello %s", counter_str.c_str());
            counter += 1; 
        }

        int counter = 0;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}