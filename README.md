# SnakeGameESP32
🕹️ Snake Game with ESP32, Joystick, and OLED Display

# Components Required
- ESP32 (NodeMCU-32S or similar)
- Joystick Module (with VRX, VRY, SW pins)
- 0.96" OLED Display (128x64, SSD1306, I2C)
- Jumper Wires
- Breadboard
# Wiring Diagram
- OLED Display (I2C - 4 Pins)
- VCC → 3.3V (ESP32)
- GND → GND (ESP32)
- SDA → GPIO 21 (ESP32 I2C SDA)
- SCL → GPIO 22 (ESP32 I2C SCL)
# Joystick Module
- VRX (X-Axis) → GPIO 34 (ESP32 Analog)
- VRY (Y-Axis) → GPIO 35 (ESP32 Analog)
- SW (Button) → GPIO 15 (ESP32 Digital)
- VCC → 3.3V (ESP32)
- GND → GND (ESP32)
