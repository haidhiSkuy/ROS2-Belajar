import rclpy 
from rclpy.node import Node 
from example_interfaces.msg import String

class Smartphone(Node):
    def __init__(self): 
        super().__init__("smartphone") 
        self.get_logger().info("Smartphone has been started")
        self.subscriber = self.create_subscription(
            String, 
            "robot_news", # publisher topic name 
            self.callback_robot_news,
            10
        )

    def callback_robot_news(self, msg): 
        self.get_logger().info(msg.data)
    
def main(args=None): 
    rclpy.init(args=args)
    node = Smartphone() 
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()