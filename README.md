![roofba pic](https://github.com/user-attachments/assets/6b7565b8-8714-43d5-acf4-9a044380adce)

# 🏠 Roofba

## 📖 Project Overview
Roofba is a Praxis 3 ESC204 project that integrates sensor technology and microcontroller-based automation to respond to the Wildfire in Canada Request for Proposal to clean debris from roofs. This project uses Arduino-based firmware to process sensor inputs and execute real-time commands efficiently. The system consists of two primary Arduino components that manage different functionalities.

## 📁 Repository Structure
arduino_1/: Manages core sensor integration and Bluetooth communication.
- BluefruitConfig.h – Configuration file for Adafruit Bluefruit module.
- integrate.cpp – Handles data integration from multiple sensors.
- main.ino – Main script that initializes and controls the system.
- packetParser.cpp – Parses incoming data packets for processing.

arduino_2/: Implements actuation mechanisms.
- pusher_final.ino – Controls an actuator for mechanical response.

## 🚀 Getting Started
### 🔧 Prerequisites
- Arduino IDE
- Adafruit Bluefruit Library (for Bluetooth communication)
- Required hardware (Arduino boards, actuators, sensors)

### 📦 Installation
1. Clone this repository:
    git clone https://github.com/yourusername/roofba.git
    cd roofba
2. Open the respective .ino files in the Arduino IDE.
3. Install necessary libraries via Arduino Library Manager.
4. Upload the firmware to the respective Arduino boards.

## 🔌 Usage
1. Power up both Arduino boards.
2. The arduino_1 board will initialize and start reading sensor data.
3. The arduino_2 board will receive signals and trigger the actuator accordingly.

## ✨ Features
- 📡 Bluetooth Communication: Wireless connectivity for remote operation.
- 📊 Sensor Integration: Real-time data acquisition.
