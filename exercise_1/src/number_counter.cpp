#include <rclcpp/rclcpp.hpp> 
#include <example_interfaces/msg/int64.hpp> 



class NumberCounter : public rclcpp::Node
{ 
    public: 
        NumberCounter() : Node("number_counter")
        { 
            RCLCPP_INFO(this->get_logger(), "This is number_counter");
            subscriber = this->create_subscription<example_interfaces::msg::Int64>(
                "number", 10, std::bind(&NumberCounter::AddNumber, this, std::placeholders::_1)
            ); 

            publisher = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
            timer_ = this->create_wall_timer(
                std::chrono::seconds(1),
                std::bind(&NumberCounter::PublishNew, this)
            );
        }


    private: 
        void AddNumber(const example_interfaces::msg::Int64::SharedPtr msg)
        { 
            counter += msg->data; 
            RCLCPP_INFO(this->get_logger(), "Received number: %d", counter);
        }

        void PublishNew()
        {   
            auto msg = example_interfaces::msg::Int64();  
            msg.data = counter;
            publisher->publish(msg); 
        }
        
        int counter = 0;

        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber; 
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher; 
        rclcpp::TimerBase::SharedPtr timer_;

};


int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<NumberCounter>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
};