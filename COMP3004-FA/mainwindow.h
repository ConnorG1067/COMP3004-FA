#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsOpacityEffect>
#include <QThread>
#include <QRadioButton>
#include "AED.h"
#include "Victim.h"
#include "CardiacArrhythmias.h"
#include "NormalSinusRhythm.h"
#include "VentricularFibrillation.h"
#include "VentricularTachycardia.h"
#include "ChildElectrode.h"
#include "AdultElectrode.h"
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // Public functions
    public:
        // Constructor and Deconstructor
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    // Private member variables
    private:
        // UI pointer
        Ui::MainWindow *ui;

        // QGraphicsScenes
        QGraphicsScene* instructionScene;
        QGraphicsScene* imageInstructionScene;
        QGraphicsScene* waveFormScene;

        // AED for the MainWindow
        AED* aed;

        // Timers
        QTimer* flashTimer;

        // QRadioButton StyleSheets
        static QString yellowRBIndicator;
        static QString greenRBIndicator;
        static QString redRBIndicator;
        static QString blackUnfilledRBIndicator;

        // function to setup connections-
        void initializeBtns();
        void initializeStartingUI();
        void selfCheckUI(bool);
        void displayDummy();
        void callIndicatorSwitchLambdas();

        // Helpers
        void resetRadioBtns();
        void placeImage(QGraphicsScene*, QString, int, int, int, int);
        QString determineCondition();
        CardiacArrhythmias* imgPathToCardiac(QString);
        void updateVictimInfo();
        void placePadsUI(bool);
        ElectrodePadPair* generateElectrodePadPair(bool);
        void indiciatorSwitch(QRadioButton*, std::function<void()>, std::function<void()>, bool);
        void placeAdultElectrodeBtn();
        void placeChildElectrodeBtn();

    // Private slots for the btns
    private slots:
        void powerBtn();
        void failAEDSetupBtn();
        void displayTextInstruction(QString);
        void flashShockButton();
        void determineElectrodes();
};
#endif // MAINWINDOW_H
