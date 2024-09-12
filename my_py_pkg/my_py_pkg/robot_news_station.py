import rclpy # ROS library
from rclpy.node import Node
from example_interfaces.msg import String

class RobotNewsStationNode(Node): 
    def __init__(self): 
        super().__init__("robot_news_station")

        # declare parameter for msg.data 
        self.declare_parameter("msg_data", "Hello")

                                                       # robot_news is the name of topic you want to send data to it
        self.publisher = self.create_publisher(String, "robot_news", 10)
        self.timer = self.create_timer(0.5, self.publish_news)
        self.get_logger().info("Robot News Station has been Started")

    def publish_news(self): 
        msg = String()
        msg.data = "Hello"
        self.publisher.publish(msg)

def main(args=None): 
    rclpy.init(args=args) 
    node = RobotNewsStationNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()
