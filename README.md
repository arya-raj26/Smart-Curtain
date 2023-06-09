# Smart-Curtain
The Smart Curtain IoT project is designed to control the opening and closing of a curtain
using an ESP32 microcontroller and the Blynk app. The curtain is connected to a gear
motor, and its movement is triggered by pressing buttons on the Blynk app or touching a
touch sensor. The project assumes that the curtain is already installed, and a gear
motor is connected to the motor pins of the ESP32. The enable pin of the motor is
connected to a PWM pin of the ESP32, and a touch sensor is connected to a digital pin.
The project also assumes that a WiFi network is available, and the ESP32 is connected
to it using the SSID and password. The Blynk app controls the curtain and displays the
current temperature and hall sensor reading. The project also assumes that the
temperature sensor is already integrated into the ESP32 board. The gear motor is
stopped after a delay of 17.4 seconds, assuming the curtain requires this much time to
move fully. The project uses the Blynk timer to trigger a function to read the temperature
and hall sensor reading every second. The app also displays a web link button, which,
when clicked, changes the image on the button.
# The GitHub link for the code - https://github.com/arya-raj26/Smart-Curtain
# The working prototype link - https://youtu.be/WbN6u0BdyQk
