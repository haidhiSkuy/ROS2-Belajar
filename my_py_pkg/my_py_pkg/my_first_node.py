import rclpy # ROS library
from rclpy.node import Node

class MyNode(Node): 
    def __init__(self): 
        super().__init__("py_test")
        self.counter = 0
        self.get_logger().info("Hello ROS2!")
        self.create_timer(0.5, self.timer_callback)


    def timer_callback(self):
        self.counter += 1 
        self.get_logger().info(f"Testing {self.counter}")

# WILL ALWAYS BE SAME ON ALL PROJECT 
def main(args=None): 
    rclpy.init(args=args) # start ROS2 communication
    node = MyNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()