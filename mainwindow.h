#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QListWidgetItem>

#include "resource.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private slots:
    void convertSpinboxValueToSlider(int value);
    void convertSpinboxValueToSlider(double value);
    void convertSliderValueToSpinbox(int value);
    void selectedEmitterChanged(int index);
    void addEmitter();
    void toggleEmitter();
    void deleteEmitter();

    void rearrangeEmitters();

    void glInitialized();

private:
    void connectSpinnersWithSliders();
    void setControlValuesFromEmitter();
    void connectControlsToEmitter();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
