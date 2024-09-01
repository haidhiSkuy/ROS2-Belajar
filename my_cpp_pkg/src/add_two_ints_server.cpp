#include <rclcpp/rclcpp.hpp> 
#include <example_interfaces/srv/add_two_ints.hpp> 


class AddTwoIntsServerNode : public rclcpp::Node 
{ 
    public: 
        AddTwoIntsServerNode() : Node("add_two_ints_server")
        {
            RCLCPP_INFO(this->get_logger(), "server start");


        }

    private: 

}; 

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsServerNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}