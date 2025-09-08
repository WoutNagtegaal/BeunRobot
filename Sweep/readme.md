# BeunRobot
Ongelofelijke beunimplementatie voor een robot op Arduino met 1 DOF

# Robot Arm Firmware Documentation (1-DoF)

## Overview
- **Project Name:** BeunBot
- **Version:** 1.0.0
- **Author(s):** B. Haas BV.
- **Date:** 08-09-2025
- **Target Hardware:** Arduino Uno R3, T I Ankongrc micro servo 9g SG90 analog
- **Degrees of Freedom:** 1 (Single joint actuation)  

### Description
This firmware attempts to control a single-degree-of-freedom robotic arm joint using serial communication.

---

## System Architecture
### Hardware Components
- **Microcontroller:** Arduino Uno R3
- **Actuator (Motor/Servo):** T I Ankongrc micro servo 9g SG90 analog 

### Software Components
- **Main Control Loop:** We dont do that here
- **Communication Protocols:** Serial  


#### Communication protocol

> Command 1 - Angle and Time
>
> `#<RequestedAngle>|<MovementTime>&`
>
> RequestedAngle --> uint16_t --> Angle to set the actuator
>
> MovementTime --> uint16_t --> Time that the actuator takes to reach the desired angle.
>
> This command is blocking. The arm wil ignore any serial command received during the time of execution.

> Command 2 - Angle with default time
>
> `#<RequestedAngle>& `
> 
> RequestedAngle --> uint16_t --> Angle to set the actuator
>
> Uses a default movement time. 

---

## Firmware Structure
```plaintext
src/
└── sweep.ino
```
