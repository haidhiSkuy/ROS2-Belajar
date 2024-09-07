#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/hardware_status.hpp" 

class HardwareStatusNode: public rclcpp::Node 
{ 
    public: 
        HardwareStatusNode(): Node("hw_status_publisher")
        { 
            RCLCPP_INFO(this->get_logger(), "Hardware Status Publisher has been started");  
            
            publisher = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>("hardware_status", 10); 
            
            timer = this->create_wall_timer( 
                std::chrono::seconds(1), 
                std::bind(&HardwareStatusNode::PublishHwStatus, this)
            );

        } 

    private: 
        void PublishHwStatus()
        { 
            auto msg = my_robot_interfaces::msg::HardwareStatus(); 
            msg.temperatures = 45; 
            msg.are_motors_ready = true; 
            msg.debug_message = "this is custom msg"; 

            publisher->publish(msg);
            
        }
        
        rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr publisher;
        rclcpp::TimerBase::SharedPtr timer;

};

int main(int argc, char** argv) 
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<HardwareStatusNode>();
    rclcpp::spin(node); 
    rclcpp::shutdown(); 
    return 0;
}