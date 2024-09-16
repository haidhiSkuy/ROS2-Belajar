#include "rclcpp/rclcpp.hpp" 
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include <random>

class TurtleSpawner : public rclcpp::Node
{
    public: 
        TurtleSpawner() : Node("turtle_spawner"), gen(rd()) 
        { 
            RCLCPP_INFO(this->get_logger(), "Turtle Spawner Node");
            
            turtle_spawner_publisher = this->create_publisher<my_robot_interfaces::msg::TurtleArray>("alive_turtle", 10);

            timer_ = this->create_wall_timer(
                std::chrono::seconds(3),
                std::bind(&TurtleSpawner::PublishSpawnNpcTurtles, this)
            );

        }  
    
    private: 

        void GenerateRandomXY()
        { 
            std::uniform_real_distribution<> dis(0.0, 11.0); 
            
            float rand_x = dis(gen);  
            random_x.push_back(rand_x);

            float rand_y = dis(gen); 
            random_y.push_back(rand_y);

            int turtle_num = random_x.size(); 
            std::string name = "npx_"+std::to_string(turtle_num);
            random_name.push_back(name);
        }

        void PublishSpawnNpcTurtles()
        {
            GenerateRandomXY();

            auto msg = my_robot_interfaces::msg::TurtleArray(); 
            
            msg.turtle_name = random_name; 
            msg.x = random_x; 
            msg.y = random_y;
            
            turtle_spawner_publisher->publish(msg); 
        }

 
        rclcpp::Publisher<my_robot_interfaces::msg::TurtleArray>::SharedPtr turtle_spawner_publisher; 
        rclcpp::TimerBase::SharedPtr timer_;

        // random coordinate vector and name 
        std::vector<std::string> random_name;
        std::vector<float> random_x;
        std::vector<float> random_y;

        // for random number
        std::random_device rd;  
        std::mt19937 gen;
        


}; 

int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<TurtleSpawner>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
};