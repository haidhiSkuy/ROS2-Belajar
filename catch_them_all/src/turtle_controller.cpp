#include "rclcpp/rclcpp.hpp" 
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include "geometry_msgs/msg/twist.hpp"

class TurtleController : public rclcpp::Node
{
    public: 
        TurtleController() : Node("turtle_controller")
        { 
            RCLCPP_INFO(this->get_logger(), "Turtle controller Node");
            
            turtle_spawner_subscriber = this->create_subscription<my_robot_interfaces::msg::TurtleArray>(
                "alive_turtles", 10, std::bind(&TurtleController::SubscribeAliveTurtle, this, std::placeholders::_1)
            );

            


        }   

    private:
        void SubscribeAliveTurtle(const my_robot_interfaces::msg::TurtleArray::SharedPtr msg)
        {
           vector_x = msg->x; 
           vector_y = msg->y;
           vector_name = msg->turtle_name; 
        }

        void MoveMainTurtle()
        { 

        }

        std::vector<float> vector_x;
        std::vector<float> vector_y;
        std::vector<std::string> vector_name;

        // define subscriber 
        rclcpp::Subscription<my_robot_interfaces::msg::TurtleArray>::SharedPtr turtle_spawner_subscriber;   
        
}; 

int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<TurtleController>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
};