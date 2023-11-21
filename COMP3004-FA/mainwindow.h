#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    //function to setup connections-
    void setupConnections();

private slots:
    void batteryStatus();
    void onElectrodesBtnPressed();
    void onCardiacArrhythmiaBtnPressed();
    void placeElectrodes();
};
#endif // MAINWINDOW_H
