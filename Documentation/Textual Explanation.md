# Project Class Overview

## MainWindow.h

`MainWindow.h` is primarily responsible for UI updates. This class focuses on interacting with user interface elements. The main window contains an AED and various UI objects. The only semi-unrelated thing within `MainWindow.h` is the AED object.

## AED.h

`AED.h` handles the majority of the backend functionality. It manages victim diagnoses, CPR, shock, electrode storage, battery, CPR feedback, and self-check. The AED was implemented to be the main backend functionality since the entire device is the AED. It specifically focuses on functionality while communicating with `MainWindow.h` for strictly UI updates.

## Electrode.h (Adult & Child)

`AdultElectrode.h` and `ChildElectrode.h` are both inherited from `Electrode.h`. `Electrode` is a parent abstract class that creates a general form for both Adult and Child Electrode classes. Adult electrodes are black, and child electrodes are green.

## ElectrodePadPair.h

`ElectrodePadPair.h` is a class to hold two electrodes named upper and lower electrodes. It has a getter and setter for both. The class has a constructor that takes in two electrodes, in which they're either both adult or child electrodes.

## CardiacArrhythmias.h (NSR, VF, VT)

`NormalSinusRhythm.h`, `VentricularFibrillation.h`, and `VentricularTachycardia.h` all inherit from `CardiacArrhythmias.h`. While Normal Sinus Rhythm is not a subtype of a cardiac arrhythmia, an abstract class for all these conditions is appropriate within the scope of this program. They share similar outcomes, such as treatment procedure, condition name, and attachment to a patient.

## Victim.h

`Victim.h` takes in an int and a `CardiacArrhythmias`. One named age and the other named condition. It includes a function to generate a random name. The `Victim` class is purely informational and does not have much functionality.

## VoiceSystem.h

`VoiceSystem.h` is primarily for auditory messages but also has functionality for images and text displays. A `VoiceSystem.h` is contained within the `AED.h` class as its existence is dependent on `AED.h`.
