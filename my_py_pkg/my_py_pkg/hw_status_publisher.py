import rclpy 
from rclpy.node import Node 

# import create custom msg
from my_robot_interfaces.msg import HardwareStatus

class HardwareStatusPublisherNode(Node): 
    def __init__(self): 
        super().__init__("hw_status_publisher") 
        self.publisher = self.create_publisher(HardwareStatus, "hardware_status", 10)
        self.timer = self.create_timer(0.5, self.publish_hw_status)
        self.get_logger().info("Hardware Status Publisher has been Started")

    def publish_hw_status(self): 
        msg = HardwareStatus() 
        msg.temperature = 45 
        msg.are_motors_ready = True 
        msg.debug_message = "this is custom msg"
        self.publisher.publish(msg)

def main(args=None): 
    rclpy.init(args=args)
    node = HardwareStatusPublisherNode() 
    rclpy.spin(node)
    rclpy.shutdown() 

if __name__ == "__main__": 
    main()