import rclpy 
from rclpy.node import Node 
from example_interfaces.srv import AddTwoInts 


def main(args=None): 
    rclpy.init(args=args) 
    node = Node("add_two_ints_client")

    client = node.create_client(AddTwoInts, "add_two_ints")
    while not client.wait_for_service(1.0): 
        node.get_logger().warn("Waiting for server")

    rclpy.shutdown()

if __name__ == "__main__": 
    main()
