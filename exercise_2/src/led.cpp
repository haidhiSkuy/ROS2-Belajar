#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"
#include "my_robot_interfaces/msg/led_states.hpp"

class LedPanel : public rclcpp::Node 
{ 
    public: 
        LedPanel() : Node("led_panel") 
        { 
            RCLCPP_INFO(this->get_logger(), "LED PANEL SERVER START");
            
            // Server 
            LedServer = this->create_service<my_robot_interfaces::srv::SetLed>(
                "set_led", 
                std::bind(&LedPanel::SetLedCallback, this, std::placeholders::_1, std::placeholders::_2)
            );
            
            // Publish LED States
            publisher = this->create_publisher<my_robot_interfaces::msg::LedStates>("led_panel_state", 10);
            timer_ = this->create_wall_timer(
                std::chrono::seconds(4),
                std::bind(&LedPanel::PublishLedState, this)
            );
        };


    private: 
        void SetLedCallback(my_robot_interfaces::srv::SetLed::Request::SharedPtr request, 
                            my_robot_interfaces::srv::SetLed::Response::SharedPtr response)
        { 
            int led_number = request->led_number; 
            bool led_status = request->state; // 0 for off and 1 for on   

            if (led_status) {
                 for (int i = 0; i < 3; ++i) {
                    led_states[i] = 0;
                }

                if (led_number >= 1 && led_number <= 3) {
                    led_states[led_number - 1] = 1; 
                }
            } else { 
                led_states[led_number - 1] = 0;
            }

            response->success = true;
        } 

        void PublishLedState()
        { 
            auto msg = my_robot_interfaces::msg::LedStates(); 
            msg.states = std::vector<int32_t>(std::begin(led_states), std::end(led_states));
            publisher->publish(msg);
        }



        int led_states[3] = {0, 0, 0};
        rclcpp::Publisher<my_robot_interfaces::msg::LedStates>::SharedPtr publisher;
        rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr LedServer; 
        rclcpp::TimerBase::SharedPtr timer_;
}; 

int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedPanel>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}