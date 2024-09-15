from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description(): 
    ld = LaunchDescription()

    publisher_nodes = [
        "robot_news_station_giskard", 
        "robot_news_station_bb8", 
        "robot_news_station_daneel", 
        "robot_news_station_jander", 
        "robot_news_station_c3po"
    ]   

    for node_name in publisher_nodes: 
        node = Node(
            package="my_cpp_pkg", 
            executable="robot_news_station", 
            name=node_name,
        )

        ld.add_action(node)

    subsciber_node = Node(  # Smartphone
        package="my_cpp_pkg", 
        executable="smartphone", 
    )
    ld.add_action(subsciber_node)

    return ld