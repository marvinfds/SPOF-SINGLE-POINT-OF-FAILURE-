# SPOF-SINGLE-POINT-OF-FAILURE-
An arduino project to demonstrate how SPOF system can be handled
A SPOF is a part of the system that if fails will cause the whole system to stop working.one way to get over this and creating a robust
system is by adding redundancy in any potential point where there are high chances of failure.
To assess the potential SPOF in a system is to identify the critical equipment’s of a complex system that would cause a complete system
failure in case of a malfunction. It is advised that highly reliable system should not rely on such components’

REQUIREMENTS:
•	One led
•	Two Arduinos
•	Breadboard
•	Jumper wires
•	4 x diodes
•	5 x 220 ohms resistor
•	ESP 8266
•	4 x optocouplers



# OBJECTIVE:
Our main objective is to create a system which can control a led using a smart phone over a wireless and a SPOF proof system. As of when the button is pressed on the smart phone to toggle the led status the signal is then sent to both the embedded system instantly and accordingly both the system decides simultaneously who will light up the led and also constantly monitor the led status so if the primary system powering the led fails the other can be used as a redundancy system to powerup the led as desired. And in return feedbacks to the system end user, the live status of led, status of both the Arduino (if it’s on or off).

![image](https://user-images.githubusercontent.com/41652789/43273097-82806c40-90f3-11e8-9120-3e7630bb5835.png)
# DIAGRAM:
![image](https://user-images.githubusercontent.com/41652789/43273362-293d59b2-90f4-11e8-8568-39e738390dcc.png)
# SCHEMATICS:
![image](https://user-images.githubusercontent.com/41652789/43273391-36666dcc-90f4-11e8-9ffa-464a8abe13cb.png)


# SOFTWARE DESIGN:
DECISION CASE:

![image](https://user-images.githubusercontent.com/41652789/43273411-3f14cf90-90f4-11e8-8a54-48a85e6f27b7.png)
