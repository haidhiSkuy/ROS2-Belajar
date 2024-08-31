import rclpy 
from rclpy.node import Node 
from example_interfaces.srv import AddTwoInts 


def main(args=None): 
    rclpy.init(args=args) 
    node = Node("add_two_ints_client")

    client = node.create_client(AddTwoInts, "add_two_ints")
    
    # Wait until service is up
    while not client.wait_for_service(1.0): 
        node.get_logger().warn("Waiting for server")

    # Create request
    request = AddTwoInts.Request()
    request.a = 5 
    request.b = 10 

    future = client.call_async(request) # Send request
    rclpy.spin_until_future_complete(node, future) # Spin until request is complete

    # Get response
    try: 
        response = future.result()
    except Exception as e: 
        node.get_logger().error(f"Failed {e}")

    rclpy.shutdown()

if __name__ == "__main__": 
    main()
