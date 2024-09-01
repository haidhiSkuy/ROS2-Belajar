#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp> 



class AddTwoIntsClient : public rclcpp::Node 
{
    public: 
        AddTwoIntsClient() : Node("add_two_ints_client")
        { 
            thread_.push_back(std::thread(std::bind(&AddTwoIntsClient::CallAddTwoInts, this, 1, 4)));
            thread_.push_back(std::thread(std::bind(&AddTwoIntsClient::CallAddTwoInts, this, 2, 5)));
        };

        void CallAddTwoInts(int a, int b)
        {
            auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

            while (!client->wait_for_service(std::chrono::seconds(1)))
            {
                RCLCPP_WARN(this->get_logger(), "server is not started, waiting for server");
            } 

            auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
            request->a = 1; 
            request->b = 2;

            auto future = client->async_send_request(request); 
            try 
            { 
                auto response = future.get();
                RCLCPP_INFO(this->get_logger(), "%d + %d = %ld", a, b, response->sum);
            }
            catch (const std::exception &e)
            {
                RCLCPP_ERROR(this->get_logger(), "service call failed");
            }


        }

        private: 
            std::vector<std::thread> thread_;
};


int main(int argc, char** argv) 
{   
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsClient>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
  
}