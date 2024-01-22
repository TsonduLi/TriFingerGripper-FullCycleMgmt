#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "serial/serial.h"
#include <sstream>
#include <iostream>

class GripperInterface {
public:
    GripperInterface() : serial("/dev/ttyUSB0", 9600, serial::Timeout::simpleTimeout(1000)) {
        // Check if serial port is open
        if (!serial.isOpen()) {
            ROS_ERROR("Serial port not opened!");
            // Handle error
        }

        // Initialize ROS node handle
        ros::NodeHandle n;

        // Initialize publishers and subscribers
        command_pub = n.advertise<std_msgs::String>("gripper_command", 1000);
        sensor_data_pub = n.advertise<std_msgs::Float32>("gripper_force_sensor", 1000);
        status_sub = n.subscribe("gripper_status", 1000, &GripperInterface::statusCallback, this);
    }

    // Function to send command to gripper
    void sendCommand(const std::string &command) {
        std_msgs::String msg;
        msg.data = command;
        command_pub.publish(msg);

        // Send command via serial
        serial.write(command + "\n");
    }

    // Function to read sensor data
    void readSensorData() {
        if (serial.available()) {
            std::string sensor_data = serial.readline();
            std_msgs::Float32 msg;
            msg.data = std::stof(sensor_data);
            sensor_data_pub.publish(msg);
        }
    }

    // Callback function for gripper status
    void statusCallback(const std_msgs::String::ConstPtr& msg) {
        ROS_INFO("Received gripper status: [%s]", msg->data.c_str());
        // Process status message here
    }

private:
    ros::Publisher command_pub;
    ros::Publisher sensor_data_pub;
    ros::Subscriber status_sub;
    serial::Serial serial;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "gripper_interface");

    GripperInterface gripper;

    ros::Rate loop_rate(10); // 10 Hz

    while (ros::ok()) {
        // Example command sending
        gripper.sendCommand("Open");

        // Read sensor data
        gripper.readSensorData();

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}