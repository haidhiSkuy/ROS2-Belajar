import rclpy 
from rclpy.node import Node 

# import create custom msg
from robot_news_station.msg import HardwareStatus

class HardwareStatusPublisherNode(Node): 
    def __init__(self): 
        super().__init__("hardware_status_publisher") 


def main(args=None): 
    rclpy.init(args=args)
    node = HardwareStatusPublisherNode() 
    rclpy.spin(node)
    rclpy.shutdown() 

if __name__ == "__main__": 
    main()