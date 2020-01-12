# Temp_Management

Fan that turns on when temperature exceeds a certain setpoint.

Runs on Arduino Mega 2560 board
Utilizes: DHT22 Temperature Module, LCD 1602 Module, Membrane Switch Module, 5V DC Motor, L293D Motor Shield Driver

Temperature setpoint can be changed by user. (25 Degrees Celsius is the default).
Motor speed can be changed by user. (50% is the default).
Motor control can be changed to Manual or Automatic. (Automatic is the default).

Arduino temperature gets the temperature while also displaying it on a screen. This process updates every two seconds. Temperature displays up to one decimal place. Accuracy is +-0.5 degrees celsius.

A motor that is connected to the L293D motor shield is programmed to turn on whenever the temperature climbs above the setpoint. The motor will turn off again if the temperature is lower than or equal to the setpoint.

If * is pressed on the keypad, a two-screen menu will appear on the LCD. The screens will switch indefinitely (with a delay fo two seconds) between the two screens until the user makes a decision.

A - Temp Setpoint
B - Fan Speed
C - Manual/Automatic
D - Exit Menu

If A is pressed in the menu, a screen will appear that will prompt the user for the setpoint. After a two digit number is entered, the program will revert back to the menu screen cycle.

If B is pressed in the menu, the user will be prompted to put in a number between 20-99. This number, x, will dictate the speed of the fan. The speed of the fan will be equal to x percent of 255 as 255 is the maximum speed. After entering the number, the program will rever back to the menu screen cycle.

If C is pressed in the menu, the user will be prompted to either press A for Manual Control or B for Automatic Control. Note that if the program is already in manual control or automatic control and the same option is picked, the user will be reverted back to the menu screen with no effect to the program. 

	If Manual is chosen, the fan will turn off (doesn't matter if fan was already off) and consecutive screens will appear telling the user that manual control has been activated and that if they go back to the main screen they can press 1 to toggle the fan on and 0 to toggle the fan off. This mode will override the setpoint functionality. 

	If Automatic is chosen, the fan can no longer be controlled from the main screen by pressing either 1 or 0. The fan will revert back to following the setpoint, turning on only if the temperature ever exceeds the setpoint.

If D is pressed in the menu, the program will exit the cycling menu and go back to the main screen.

If any other key is pressed during the menu cycle, a screen will appear briefly saying invalid option and then the program will revert back to the menu cycle. 

Error checking for user input in menu is implemented.
Error checking for for user input in temp setpoint is implemented.
Error checking for user input in fan speed is implemented.
Error checking for user input in manual/automatic control is implemented.

Project is Finalized





