import rclpy # ROS library
from rclpy.node import Node

class MyNode(Node): 
    def __init__(self): 
        super().__init__("py_test")
        self.get_logger().info("Hello ROS2!")


def main(args=None): 
    rclpy.init(args=args) # start ROS2 communication
    node = MyNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()