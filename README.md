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

![entire pic](<entimg.jpeg>)
*literally the picture of the hardware*

# Diagrams
![Workflow](<flow.png>)
*A basic workflow image*

For Hardware:

# Schematic & Circuit
![Circuit](<circuit.png>)
*Add caption explaining connections*

![Schematic](<schemm.png>)
*same thing as the circuit , just black and whitw*

# Build Photos
![Components]
*List out all components shown*

![Build](Add photos of build process here)
*Explain the build steps*

![Final](<f.jpeg>)
*The Arrogant Calculator is an IoT-based hardware system that pairs local embedded control with a remote computer vision pipeline to deliberately mock or trick the user depending on their eye status. The physical build operates untethered from computer power through an L298N motor driver module, which uses its onboard regulator to step down a raw 7V–12V DC input to a clean 5V rail. This power line feeds the central brain of the project—an ESP32 microcontroller—and a 16x2 I2C character LCD display. User input is collected through a 10k potentiometer wired to an analog GPIO pin, mapping dial rotations to integer values between 0 and 99. Operating controls are provided by five pushbuttons configured with internal pull-up resistors for four standard arithmetic functions (+, -, *, /) and a system reset function.

Vision processing runs independently on a laptop as a background service written in Python. Using OpenCV, the system continuously reads and horizontally flips the webcam feed to create a mirrored preview display. MediaPipe Face Mesh processes these frames by mapping 3D facial landmarks to compute an Eye Aspect Ratio (EAR) based on vertical and horizontal eye distances. If the EAR exceeds 0.15, the python script flags the user's eye status as open; otherwise, it registers as closed or undetected. This state is constantly exposed across the shared local Wi-Fi network using a Flask REST API endpoint hosting JSON responses on port 5000.

When an arithmetic operation is submitted on the physical hardware, the ESP32 calculates the actual mathematical result locally and executes a HTTP GET request to fetch the user's live eye state. If the server is unreachable or the network drops, the request times out after two seconds and triggers a server error message on the LCD. If the user repeatedly hits the clear button more than three times, the system overrides normal operations with an insult reading id10t error. Similarly, any calculation yielding a value over 2000 is rejected with sarcastic remarks such as wastage of ram u fool....

The calculator's primary behavioral gimmick relies entirely on the eye status retrieved from the Flask server. When the vision model detects that the user's eyes are open and looking at the screen, the device intentionally returns a modified, incorrect result alongside condescending feedback. If the user successfully hides their gaze by closing their eyes before submitting the calculation, the system enters a conditional check: it grants the exact correct answer 30% of the time, while the remaining 70% of the time it returns an intentionally altered result—such as squaring the output or adding a fixed offset—accompanied by playful, arrogant commentary on the LCD screen.*

### Project Demo
# Video


https://github.com/user-attachments/assets/41e73954-2aea-4508-8874-36aacb94110c



https://github.com/user-attachments/assets/1440c002-c024-48ad-b6b3-7dcab68604b1



*Explains how the calculator gets you the correct answer (prob = 30%) when the users eyes are closed and wrong answer when the users eye are open*


## Team Contributions
- [AKSHAY JOSEPH]: [INITIAL CODDING , INITIAL CIRCUIT DESIGN , BUILDING THE TENSOR FLOW MODEL , CREATING THE DOCUMENTATION , UPDATED THE CODE FOR THE ARDUINO MODEL OF THE PROJECT]
- [ABHIJITH AJAYAN]: [WIRING THE CIRCUIT , CHANGES TO THE PRIMARY CODE , ADDED FEW MORE TXT TO  THE ANSWERS , SIMULATED THE MODEL]


---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



