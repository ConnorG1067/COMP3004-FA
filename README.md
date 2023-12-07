# COMP 3004 Final Project

# Automated External Defibrillator (AED) Device

![AED Device](Documentation/AED.png)

## Table of Contents

- [Introduction](#introduction)
- [Team Members](#team-members)
- [Distribution of Deliverables](#distribution-of-deliverables)
  - [Implementation](#implementation)
  - [Documentation](#documentation)
- [Features](#features)
- [Dependencies](#dependencies)
- [Installation and Usage](#installation-and-usage)
- [Testing Videos](#testing-videos)

## Introduction

Welcome to the Automated External Defibrillator (AED) Device repository, developed as the final project for the Carleton University COMP 3004 course. This project serves as the culmination of our academic endeavors, where we were tasked with the development of an AED device as part of our coursework. Designed for educational purposes, this repository showcases our efforts in creating a user-friendly and efficient AED, incorporating automated analysis, real-time feedback, and customization features.

## Team Members

Connor Gomes
Will Chartrand

## Distribution of Deliverables

### Implementation

#### Shared Work
- Simulated user interaction controls (e.g., buttons for electrode placement).
- Include a display panel to show the simulated ECG (electrocardiogram) waveform and device status.
- Simulate the analysis process where the AED Plus detects the heart rhythm.
- Implement an interactive system that allows users to perform actions mimicking real-world AED operation.
- Provide input mechanisms for electrode placement, shock delivery, and CPR initiation.

#### Connor
- Cardiac arrhythmia diagnosis results (see the shockable-non-shockable).
- Device status indicators (e.g., battery, electrode placement).
- Specify scenarios of a simulated cardiac emergency with visual prompts and their timing to guide the user through a rescue situation.
- Develop scenarios with varying patient conditions, user responses, and outcomes to test your software.

#### Will
- Design the software for a graphical user interface (GUI) that resembles the AED Plus's display.
- Real-time CPR feedback.
- If a shockable rhythm is detected, display a message on the screen and provide textual instructions on how to prepare and deliver a shock.
- If a non-shockable rhythm is detected, provide appropriate textual guidance for CPR (Cardiopulmonary Resuscitation).
- Create a system that emulates the real-time CPR feedback feature of the AED Plus.
- Simulate the measurement and assessment of chest compressions, delivering visual and textual feedback to guide the user.

### Documentation

#### Connor
- UML Class Diagram.
- Use Cases.
- Textual Explanation.
- Videos.

#### Will
- Sequence Diagrams.
- State Diagram.
- Traceability Matrix.


## Features

- **User-Friendly Interface**: Simple and intuitive design for ease of use in emergency situations.
- **Automated Analysis**: Algorithms to analyze the patient's condition and provide accurate defibrillation recommendations.
- **Real-time Feedback**: Clear audio and visual feedback to guide users through the CPR and defibrillation process.
- **Data Logging**: Log and store critical data for post-incident analysis and reporting.
- **Customization**: Configurable settings to adapt to various scenarios and user preferences.

## Dependencies:

audio codec for mp3 files

        sudo apt-get install ubuntu-restricted-extras

pulseaudio to connect QMediaPlayer

        sudo apt-get install pulseaudio

- make sure that this is running. May need to reboot VM

volume control

        sudo apt-get install alsa-utils

- Set volume from the terminal with "amixer sset 'Master' 100%"


multimedia support:

        sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5

## Installation and Usage

1. Clone the repository.
   ```bash
   git clone https://github.com/your-username/AED-Device.git
   ```
2. Unzip the file
3. Download all [Dependencies](#dependencies)
4. Open the project in QT Creator
5. Run the project

## Testing Videos

Explore our testing videos to observe the AED device in various scenarios:

1. **Normal Sinus Rhythm Situation:** <br>
   [![Normal Sinus Rhythm](https://img.youtube.com/vi/eY60vmv3HHE/0.jpg)](https://youtu.be/eY60vmv3HHE)

2. **Multiple Iteration Shock:** <br>
   [![Multiple Iteration Shock](https://img.youtube.com/vi/GQFw9w6Xq3s/0.jpg)](https://youtu.be/GQFw9w6Xq3s)

3. **Ventricular Tachycardia:** <br>
   [![Ventricular Tachycardia](https://img.youtube.com/vi/_QIoJ-EoVts/0.jpg)](https://youtu.be/_QIoJ-EoVts)

4. **Ventricular Fibrillation:** <br>
   [![Ventricular Fibrillation](https://img.youtube.com/vi/_CYXNq2JeBI/0.jpg)](https://youtu.be/_CYXNq2JeBI)

5. **Electro Pad Misplacement:** <br>
   [![Electro Pad Misplacement](https://img.youtube.com/vi/vWiX5KCGt-M/0.jpg)](https://youtu.be/vWiX5KCGt-M)

6. **Compressions:** <br>
   [![Compressions](https://img.youtube.com/vi/5Cq4QjJUxbI/0.jpg)](https://youtu.be/5Cq4QjJUxbI)

7. **Child Pads:** <br>
   [![Child Pads](https://img.youtube.com/vi/oTlzZroOPsw/0.jpg)](https://youtu.be/oTlzZroOPsw)

8. **Disturb Patient:** <br>
   [![Disturb Patient](https://img.youtube.com/vi/sDjFFqJ2KaQ/0.jpg)](https://youtu.be/sDjFFqJ2KaQ)
   
9. **On/Off/Failed Setup:** <br>
   [![On/Off/Failed Setup](https://img.youtube.com/vi/tTE2ng15ZUY/0.jpg)](https://youtu.be/tTE2ng15ZUY)
