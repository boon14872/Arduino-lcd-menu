

# Arduino Tea Brewing Controller

This project controls a tea brewing process using an Arduino. It includes a menu system operated via a joystick, a relay to control the heating element, and an LCD display to show the status and options.

## Components

- Arduino Board (e.g., Uno, Nano)
- LCD Display (16x2 I2C)
- Joystick Module
- Relay Module
- Optional: Additional components like resistors, buttons, etc.

## Features

- **Main Menu**: Select between Green Tea, Black Tea, and Custom settings.
- **Sub-Menus**: Start, Back, and Stop brewing.
- **Custom Settings**: Adjust brewing time and temperature.
- **Real-time Progress**: View brewing progress on the LCD display.
- **Debounce Mechanism**: Prevents multiple inputs from being registered too quickly.

## Project Structure

- **`main.ino`**: The main Arduino sketch that initializes and updates the `MenuService`.
- **`MenuService.h`**: Header file for the `MenuService` class.
- **`MenuService.cpp`**: Implementation file for the `MenuService` class.
- **`JoyService.h`**: Header file for the `JoyService` class.
- **`JoyService.cpp`**: Implementation file for the `JoyService` class.

## Installation

1. **Download the Project Files**: Ensure you have all the necessary files in the same folder.
2. **Open Arduino IDE**:
   - Open the `main.ino` file using the Arduino IDE.
3. **Verify Libraries**:
   - Ensure the required libraries are installed (`LiquidCrystal_I2C` for the LCD and any necessary libraries for the joystick).
4. **Upload the Sketch**:
   - Connect your Arduino to your computer.
   - Select the appropriate board and port from the Arduino IDE.
   - Click the upload button to compile and upload the code.

## Usage

1. **Power On**: Power your Arduino and ensure all components are connected properly.
2. **Navigate the Menu**:
   - Use the joystick to navigate between options.
   - Push the joystick to select an option.
3. **Start Brewing**:
   - Select the type of tea or custom settings.
   - Press "Start" to begin brewing.
   - The relay will activate, and the LCD will display the progress.
4. **Stop Brewing**:
   - Press "Stop" to halt the brewing process at any time.

## Troubleshooting

- **No Display**:
  - Check the wiring connections for the LCD.
  - Verify that the LCD library is correctly installed.

- **Joystick Not Responding**:
  - Ensure the joystick module is connected to the correct pins.
  - Check the `JoyService` configuration.

- **Relay Not Activating**:
  - Confirm that the relay is wired correctly.
  - Ensure that the relay pin is set up correctly in the code.

- **Debounce Issues**:
  - If inputs are registered too quickly, adjust the `debounceDelay` value in the `MenuService` class.

## Customization

- **Change Brewing Time and Temperature**: Modify the default values in the `MenuService` class.
- **Adjust Relay Control**: Update the `startBrew` and `stopBrew` methods in `MenuService.cpp`.

## License

This project is open-source and can be freely used, modified, and distributed. Attribution is appreciated.

