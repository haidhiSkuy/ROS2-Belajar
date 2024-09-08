#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"
#include <chrono>
#include <thread>

class Battery : public rclcpp::Node 
{ 
public: 
    Battery() : Node("battery")
    { 
        client_ = this->create_client<my_robot_interfaces::srv::SetLed>("set_led");

        // Spin up a separate thread to run the battery cycle
        std::thread([this]() {
            while (rclcpp::ok()) 
            {
                // Empty Battery
                std::this_thread::sleep_for(std::chrono::seconds(4));
                this->BatteryStatus(3, true);  // Assume LED 3 indicates battery empty
                RCLCPP_INFO(this->get_logger(), "battery is empty");

                // Full Battery
                std::this_thread::sleep_for(std::chrono::seconds(2));
                this->BatteryStatus(3, false);  // Assume LED 3 indicates battery full
                RCLCPP_INFO(this->get_logger(), "battery is full");
            }
        }).detach();
    }

private:

    rclcpp::Client<my_robot_interfaces::srv::SetLed>::SharedPtr client_;

    void BatteryStatus(int led_number, bool led_state)
    {
        // Wait for the service to be available
        if (!client_->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Service not available, waiting...");
            return;
        }

        // Create request
        auto request = std::make_shared<my_robot_interfaces::srv::SetLed::Request>();
        request->led_number = led_number;
        request->state = led_state;

        // Call the service asynchronously
        auto future = client_->async_send_request(request);

        try 
        {
            auto response = future.get(); // Wait for response
            RCLCPP_INFO(this->get_logger(), "Response success: %s", response->success ? "true" : "false");
        } 
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Service call failed: %s", e.what());
        }
    }
};

int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Battery>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
