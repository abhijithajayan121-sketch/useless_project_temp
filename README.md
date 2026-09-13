<img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



# [ARROGANT CALCULATOR ] 🎯


## Basic Details
### Team Name: [Server56]


### Team Members
- Team Lead: [Akshay Joseph] - [SaintGits College of Engineering]
- Member 2: [Abhijith Ajayan] - [SaintGits College of Engineering]


### Project Description
[This is a type of calculator that wastes clock cycles and resources and gives the right answers only at a random instance.This calculator has a feed from the web can using which its able to decide whether to give the correct answer or not ,if your eyer are open u get the wrong answer if closed it might give the correct answer.]

### The Problem (that doesn't exist)
[Is'nt all other calculators a bit too efficient in what they do?]

### The Solution (that nobody asked for)
[Hoho say less an arrogant one specially designed to use up resources and u'r time just to give u the wrong answers ? Keepin it less efficient!]

## Technical Details
### Technologies/Components Used
For Software:
- [python and c++]
- [Mediapipe and OpenCV]
- [opencv-python ,mediapipe ,pyserial ,math ,time ,random ,LiquidCrystal_I2C.h ,Wire.h]
- [Arduino IDE , python]

For Hardware:
ESP32 Development Board (30-pin variant)
16x2 LCD Display with I2C Adapter Module (connected via GPIO 21 for SDA and GPIO 22 for SCL)
10k Potentiometer (wiper connected to GPIO 34 for analog number selection)
5 Pushbuttons (for active-LOW inputs with internal pull-up resistors):
Addition (+): GPIO 13
Subtraction (-): GPIO 12
Multiplication (*): GPIO 14
Division (/): GPIO 27
Clear / Reset: GPIO 26
L298N Motor Driver Module (used for its onboard 5V linear voltage regulator to step down main DC input power to 5V for the ESP32 VIN and LCD VCC)
DC Power Supply / Battery (7V–12V input connected to the L298N power terminal)
Solderless Breadboard
Male-to-Male Jumper Wires
USB Type-A to Type-B Cable
Integrated Laptop Webcam]

-ESP32 Development Board: Acts as the central microcontroller. It reads user inputs from the potentiometer and pushbuttons, performs all arithmetic and arrogant logic locally, makes HTTP GET requests over Wi-Fi to fetch eye-tracking status, and drives the LCD display.
16x2 I2C LCD Display: Provides the visual interface for the user. It displays the current number inputs selected via the potentiometer, active mathematical operations, status indicators (Thinking..., Connecting Wi-Fi), final calculated outputs, and dynamic insult/error messages.
10k Potentiometer: Serves as the continuous analog input mechanism. As you turn the dial, its varying voltage output is read by the ESP32 ADC (GPIO 34) and mapped to select integer values from 0 to 99 for calculations.
5 Pushbuttons: Act as digital inputs configured with internal pull-up resistors (INPUT_PULLUP). Four buttons set the arithmetic operators (+, -, *, /) and trigger the calculation state, while the fifth button serves as a dedicated system reset/clear function (which tracks press counts to trigger reset insults).
L298N Motor Driver Module: Functions solely as a power regulator for the project. Its onboard 5V regulator steps down higher DC input voltage (7V–12V) to a stable 5V output to safely power the ESP32 via its VIN pin and the 16x2 LCD display.
7V–12V DC Power Source: Supplies primary raw electrical power to the system (connected to the L298N input terminals), enabling fully wireless untethered operation without relying on USB power.
- [Arduino IDE: To compile and upload C++ code to the ESP 32 DEV module.
Python 3 Interpreter: To execute brain.py and run eye-tracking algorithms.
Command Prompt / Terminal: To execute the Python script and view live system logs.
Circuit Simulator (Cirkit Designer / Tinkercad): To design, prototype, and test the schematic layout.
Wire Strippers / Snips (Optional): For trimming or preparing solid-core jumper wires.]

### Implementation
For Software:
# Installation
[commands]

# Run
[commands]

### Project Documentation
For Software:

# Screenshots (Add at least 3)
![img1 (1).jpeg](<img1 (1).jpeg>)
*the image showing the model giving a wrong answer and saying its easy*

![img1 (2)](<img1 (2).jpeg>)
*eye detection to check if it need to give the right or wrong answers*

![img1 (3)](<img1 (3).jpeg>)
*setting up a mathematical operation*

![entire pic]()
*literally the picture of the hardware*

# Diagrams
![Workflow](<workflow.png)
*A basic workflow image*

For Hardware:

# Schematic & Circuit
![Circuit](Add your circuit diagram here)
*Add caption explaining connections*

![Schematic](<schem.png>)
*same thing as the circuit , just black and whitw*

# Build Photos
![Components](Add photo of your components here)
*List out all components shown*

![Build](Add photos of build process here)
*Explain the build steps*

![Final](Add photo of final product here)
*Explain the final build*

### Project Demo
# Video
[Add your demo video link here]
*Explain what the video demonstrates*

# Additional Demos
[Add any extra demo materials/links]

## Team Contributions
- [AKSHAY JOSEPH]: [INITIAL CODDING , INITIAL CIRCUIT DESIGN , BUILDING THE TENSOR FLOW MODEL , CREATING THE DOCUMENTATION , UPDATED THE CODE FOR THE ARDUINO MODEL OF THE PROJECT]
- [ABHIJITH AJAYAN]: [WIRING THE CIRCUIT , CHANGES TO THE PRIMARY CODE , ADDED FEW MORE TXT TO  THE ANSWERS , SIMULATED THE MODEL]


---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



