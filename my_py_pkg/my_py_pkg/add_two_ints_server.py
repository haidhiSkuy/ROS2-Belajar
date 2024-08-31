import rclpy # ROS library
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class AddTowIntsServerNode(Node): 
    def __init__(self): 
        super().__init__("add_two_ints_server")
        self.server = self.create_service(AddTwoInts, "add_two_ints", self.callback_add_two_ints)
       
    def callback_add_two_ints(self, request, response): 
        # see the ros2 interfaces show example_interfaces/srv/AddTwoInts to understand
        response.sum = request.a + request.b

        response_msg = f"{request.a} + {request.b} = {response.sum}"
        self.get_logger().info(response_msg)
        return response


def main(args=None): 
    rclpy.init(args=args) 
    node = AddTowIntsServerNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()