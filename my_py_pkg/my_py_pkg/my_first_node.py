import rclpy # ROS library
from rclpy.node import Node

def main(args=None): 
    rclpy.init(args=args) # start ROS2 communication

    node = Node(node_name="py_test")
    node.get_logger().info("Hello ROS2!")

    rclpy.shutdown()

if __name__ == "__main__": 
    main()