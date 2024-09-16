#include "rclcpp/rclcpp.hpp" 
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include "turtlesim/srv/spawn.hpp"
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

            // thread_.push_back(std::thread(std::bind(&TurtleSpawner::Spawn, this, "npc_1", 3.0, 3.0)));

        }  
    
    private: 

        void GenerateRandomXY()
        { 
            std::uniform_real_distribution<> dis(0.1, 10.9); 
            
            float rand_x = dis(gen);  
            random_x.push_back(rand_x);

            float rand_y = dis(gen); 
            random_y.push_back(rand_y);

            int turtle_num = random_x.size(); 
            std::string name = "npc_"+std::to_string(turtle_num);
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


            // call Spawn Service 
            int last_idx = random_x.size() - 1; 

            thread_.push_back(
                std::thread(std::bind(
                    &TurtleSpawner::Spawn, this, random_name[last_idx], random_x[last_idx], random_y[last_idx]
                    ))); 
        }   

        void Spawn(std::string name, float x, float y)  
        {    
            auto spawn_client = this->create_client<turtlesim::srv::Spawn>("spawn");

            while (!spawn_client->wait_for_service(std::chrono::seconds(1)))
            {
                RCLCPP_WARN(this->get_logger(), "server is not started, waiting for server");
            } 

            auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
            request->x = x; 
            request->y = y; 
            request->theta = 0.0; 
            request->name = name; 

            auto future = spawn_client->async_send_request(request); 
            try 
            { 
                auto response = future.get();
                std::string npc_responses = response->name;
                RCLCPP_INFO(this->get_logger(), "%s spawned on x: %f y: %f", npc_responses.c_str(), x, y);
            }
            catch (const std::exception &e)
            {
                RCLCPP_ERROR(this->get_logger(), "service call failed");
            }
            RCLCPP_INFO(this->get_logger(), "Service call done");
        }

        // publisher for /alive_turtles
        rclcpp::Publisher<my_robot_interfaces::msg::TurtleArray>::SharedPtr turtle_spawner_publisher; 

        rclcpp::TimerBase::SharedPtr timer_;
        
        // random coordinate vector and name 
        std::vector<std::string> random_name;
        std::vector<float> random_x;
        std::vector<float> random_y;
        int last_idx;

        // for random number
        std::random_device rd;  
        std::mt19937 gen;

        std::vector<std::thread> thread_;
        


}; 

int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<TurtleSpawner>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
};