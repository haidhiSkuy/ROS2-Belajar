from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description(): 
    ld = LaunchDescription()

    remap_number_topic = ("number", "my_number")

    number_publisher_node = Node(
        package="exercise_1", 
        executable="number_publisher", 
        name="my_number_publisher",  # node name 
        remappings=[
            remap_number_topic
        ], 
        parameters=[
            {"test123" : "sanszzz"},
            {"number" : 10}
        ]
    )

    number_counter_node = Node( 
        package="exercise_1", 
        executable="number_counter", 
        name="my_number_counter", 
        remappings=[
            remap_number_topic, 
            ("number_count", "my_number_count")
        ]
    )

    ld.add_action(number_publisher_node)
    ld.add_action(number_counter_node)
    return ld