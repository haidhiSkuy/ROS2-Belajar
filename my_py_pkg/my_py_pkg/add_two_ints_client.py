import rclpy 
from rclpy import Future
from rclpy.node import Node 
from example_interfaces.srv import AddTwoInts 
from functools import partial


class AddTwoIntsClient(Node): 
    def __init__(self): 
        super().__init__("add_two_ints_client")
        self.call_add_two_int_server(3, 7)


    def call_add_two_int_server(self, a : int, b : int): 
        client = self.create_client(AddTwoInts, "add_two_ints")
        
        # Wait until service is up
        while not client.wait_for_service(1.0): 
            self.get_logger().warn("Waiting for server")

        # Create request
        request = AddTwoInts.Request()
        request.a = a
        request.b = b   

        future = client.call_async(request) 
        future.add_done_callback(
            partial(self.callback_add_two_ints, a=a, b=b)
        )

    def callback_add_two_ints(self, future : Future, a : int, b : int): 
        # Get response 
        try: 
            response = future.result()
            self.get_logger().info(f"Response : {a} + {b} = {response.sum}")
        except Exception as e: 
            self.get_logger().error(f"Failed {e}")

def main(args=None): 
    rclpy.init(args=args) # start ROS2 communication
    node = AddTwoIntsClient()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__": 
    main()
