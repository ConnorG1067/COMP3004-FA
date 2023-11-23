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
#include "AED.h"
#include "Victim.h"
#include "CardiacArrhythmias.h"
#include "NormalSinusRhythm.h"
#include "VentricularFibrillation.h"
#include "VentricularTachycardia.h"
#include "ChildElectrode.h"
#include "AdultElectrode.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* instructionScene;
    QGraphicsScene* waveFormScene;
    AED* aed;
    // function to setup connections-
    void initializeBtns();
    void initializeStartingUI();
    void selfCheckUI(bool);
    void displayDummy();

    // Helpers
    void placeImage(QGraphicsScene*, string, int, int, int, int);
    string determineCondition();
    CardiacArrhythmias* imgPathToCardiac(string);
    void updateVictimInfo();
    void placePadsUI(bool);
    ElectrodePadPair* generateElectrodePadPair(bool);

private slots:  
    void powerBtn();
    void failAEDSetupBtn();
    void placeAdultElectrodeBtn();
    void placeChildElectrodeBtn();


};
#endif // MAINWINDOW_H
