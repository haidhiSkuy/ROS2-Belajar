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

            publisher = this->create_publisher<example_interfaces::msg::Int64>("number_publisher", 10);

            timer_ = this->create_wall_timer(
                std::chrono::seconds(1),
                std::bind(&NumberPublisher::PublishNumber, this)
            );

        }
        

    private: 
        void PublishNumber()
        {
            auto msg = example_interfaces::msg::Int64(); 
            msg.data = counter; 
            publisher->publish(msg); 

            counter += 2;
        }



        int counter = 1; 
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher; 
        rclcpp::TimerBase::SharedPtr timer_;
}; 


int main(int argc, char** argv) 
{ 
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisher>(); 
    rclcpp:spin(node); 
    rclcpp::shutdown(); 
    return 0; 
} 