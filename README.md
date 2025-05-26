# ESP32 FOTA (Firmware Over-The-Air) Project

This project demonstrates how to implement FOTA updates for ESP32 using GitHub as the firmware repository.

## Project Structure

```
esp32-fota-project/
├── src/
│   └── esp32_fota.ino    # Main Arduino sketch
├── firmware/             # Directory for compiled firmware binaries
└── fota.json             # Firmware update configuration
```

## Setup Instructions

### 1. Prerequisites

- Install [Arduino IDE](https://www.arduino.cc/en/software)
- Install ESP32 board support in Arduino IDE:
  1. Go to File > Preferences
  2. Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to "Additional Boards Manager URLs"
  3. Go to Tools > Board > Boards Manager
  4. Search for "esp32" and install "ESP32 by Espressif Systems"

### 2. Install Required Libraries

1. Open Arduino IDE
2. Go to Sketch > Include Library > Manage Libraries
3. Search for and install these libraries:
   - `esp32FOTA` by chrisjoyce911
   - `WiFi` (should be included with ESP32 board package)

### 3. Configure the Project

1. Open `src/esp32_fota.ino` in Arduino IDE
2. Verify the following settings:
   - WiFi credentials (SSID and password)
   - GitHub repository details
   - Firmware version number

### 4. Upload Initial Firmware

1. Select your ESP32 board:
   - Go to Tools > Board > ESP32 Arduino > DOIT ESP32 DEVKIT V1
2. Select the correct port (Tools > Port)
3. Click the Upload button (right arrow icon)

### 5. Create a GitHub Repository for Firmware

1. Create a new GitHub repository (e.g., `esp32-fota-firmware`)
2. Create a `firmware` folder in the repository
3. Upload the `fota.json` file to the root of the repository
4. To create a new firmware version:
   - Increment the `firmware_version` in `esp32_fota.ino`
   - Compile the sketch (Sketch > Export Compiled Binary)
   - Upload the generated `.bin` file to the `firmware` folder in your GitHub repository
   - Update the version number in `fota.json`

## Usage

- The ESP32 will check for updates every hour
- When an update is available, it will be downloaded and installed automatically
- The device will restart after a successful update

## Troubleshooting

- If the update fails, check the Serial Monitor for error messages
- Make sure the GitHub repository is public or use authentication if private
- Verify the firmware binary URL in `fota.json` is correct
- Ensure the ESP32 has a stable internet connection

## Security Notes

- The code uses HTTPS for secure communication
- Certificate validation is enabled by default
- For production use, consider implementing additional security measures like API keys or authentication
