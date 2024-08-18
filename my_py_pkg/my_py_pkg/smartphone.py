import rclpy 
from rclpy.node import Node 

class Smartphone(Node):
    def __init__(self): 
        super().__init__("smartphone") 
        self.get_logger().info("Smartphone has been started")

    
def main(args=None): 
    rclpy.init(args=args)
    node = Smartphone() 
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()