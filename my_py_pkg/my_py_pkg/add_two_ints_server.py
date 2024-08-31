import rclpy # ROS library
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class AddTowIntsServerNode(Node): 
    def __init__(self): 
        super().__init__("add_two_ints_server")
        self.server = self.create_service(AddTwoInts, "add_two_ints")
       


def main(args=None): 
    rclpy.init(args=args) 
    node = AddTowIntsServerNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()