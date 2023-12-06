# Project Class Overview

## MainWindow.h

`MainWindow.h` is primarily responsible for UI updates. This class focuses on interacting with user interface elements. The main window contains an AED and various UI objects.

## AED.h

`AED.h` handles the majority of the backend functionality. It manages victim diagnoses, CPR, shock, electrode storage, battery, CPR feedback, and the self-evaluation sequence. The AED was implemented to be the main backend functionality since the entire device is the AED. It specifically focuses on functionality while communicating with `MainWindow.h` for strictly UI updates.

## Electrode.h (Adult & Child)

`AdultElectrode.h` and `ChildElectrode.h` are both inherited from `Electrode.h`. `Electrode` is a parent abstract class that creates a general form for both the Adult and Child Electrode classes. The adult electrodes are black, and the child electrodes are green.

## ElectrodePadPair.h

`ElectrodePadPair.h` is a class to hold two electrodes named upper and lower electrodes. It has a getter and setter for both. The class has a constructor that takes in two electrodes, in which they're either both adult or child electrodes.

## CardiacArrhythmias.h (NSR, VF, VT)

`NormalSinusRhythm.h`, `VentricularFibrillation.h`, and `VentricularTachycardia.h` all inherit from `CardiacArrhythmias.h`. While Normal Sinus Rhythm is not a subtype of a cardiac arrhythmia, an abstract class for all these conditions is appropriate within the scope of this program. They share similar characteristics, such as treatment procedure, condition name, as well as its association to the `Victim`.

## Victim.h

`Victim.h` takes in an integer and an instance of `CardiacArrhythmias`. One named "age" and the other named "condition". It includes a function to generate a random name. The `Victim` class is purely informational and does not have much functionality.

## VoiceSystem.h

`VoiceSystem.h` is primarily utilized for auditory messages but also has functionality for images and text displays. A `VoiceSystem.h` instance is contained within the `AED.h` as this is the object which conveys the instructions to the operator in a real life scenario.
