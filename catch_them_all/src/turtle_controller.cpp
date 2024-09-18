#include "rclcpp/rclcpp.hpp" 
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include "geometry_msgs/msg/twist.hpp" 
#include "turtlesim/msg/pose.hpp" 

class TurtleController : public rclcpp::Node
{
    public: 
        TurtleController() : Node("turtle_controller"), goal_reached(false)
        { 
            RCLCPP_INFO(this->get_logger(), "Turtle controller Node");

            velocity_publisher = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10); 

            pose_subscription = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose", 10, std::bind(&TurtleController::UpdatePose, this, std::placeholders::_1));

            timer_ = this->create_wall_timer(
                std::chrono::milliseconds(100), std::bind(&TurtleController::MoveTurtle, this));

            // Input for goal position
            GetGoalInput();
        }   

    private:
        turtlesim::msg::Pose pose; 
        turtlesim::msg::Pose goal_pose;
        rclcpp::TimerBase::SharedPtr timer_;
        
        float distance_tolerance = 0.1;
        bool goal_reached;

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher; 
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscription;

        void GetGoalInput()
        {   
            goal_pose.x = 3.0; 
            goal_pose.y = 3.0;               
        }

        void UpdatePose(const turtlesim::msg::Pose::SharedPtr data)
        { 
            pose = *data; 
            pose.x = std::round(pose.x * 10000.0) / 10000.0; 
            pose.y = std::round(pose.y * 10000.0) / 10000.0;
        } 

        double EuclideanDistance()
        {
        return std::sqrt(std::pow((goal_pose.x - pose.x), 2) + std::pow((goal_pose.y - pose.y), 2));
        }

        double LinearVel(float constant = 1.5)
        {
            return constant * EuclideanDistance();
        }

        double SteeringAngle()
        {
            return std::atan2(goal_pose.y - pose.y, goal_pose.x - pose.x);
        } 

        double AngularVel(float constant = 6.0)
        {
            return constant * (SteeringAngle() - pose.theta);
        } 

        void StopTurtle()
        { 
            geometry_msgs::msg::Twist vel_msg; 
            vel_msg.linear.x = 0.0; 
            vel_msg.angular.z = 0.0;  
            velocity_publisher->publish(vel_msg); 

            // set goal_reached to True and log info
            goal_reached = true;
            RCLCPP_INFO(this->get_logger(), "Goal Reached!");
        }


        void MoveTurtle()
        { 
            if (EuclideanDistance() >= distance_tolerance) { 
                geometry_msgs::msg::Twist vel_msg; 

                // Set Linear velocity 
                vel_msg.linear.x = LinearVel(); 
                vel_msg.linear.y = 0.0; 
                vel_msg.linear.z = 0.0; 

                // Set angular velocity 
                vel_msg.angular.x = 0.0;
                vel_msg.angular.y = 0.0;
                vel_msg.angular.z = AngularVel(); \

                // Publish the velocity 
                velocity_publisher->publish(vel_msg);

            } else { 
                StopTurtle();
            }

        }        
}; 

int main(int argc, char** argv)
{ 
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<TurtleController>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown();
    return 0;
};