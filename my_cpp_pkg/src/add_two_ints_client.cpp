#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp> 


int main(int argc, char** argv) 
{   
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<rclcpp::Node>("add_two_ints_client"); 

    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    while (!client->wait_for_service(std::chrono::seconds(1)))
    {
        RCLCPP_WARN(node->get_logger(), "server is not started, waiting for server");
    } 

    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 1; 
    request->b = 2;

    auto future = client->async_send_request(request); 
    rclcpp::spin_until_future_complete(node, future); 

    if (rclcpp::spin_until_future_complete(node, future) == rclcpp::FutureReturnCode::SUCCESS) {
        auto response = future.get();
        RCLCPP_INFO(node->get_logger(), "%ld + %ld = %ld", request->a, request->b, response->sum);
    } else {
        RCLCPP_ERROR(node->get_logger(), "Failed to call service add_two_ints");
    }

    rclcpp::shutdown();

    return 0;
}