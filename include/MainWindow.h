#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include <QChart>
#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineSeries>
#include "Signal.h"

class Signal;

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void OnSignalSelectionChanged(const QString &text);
        void OnPlotSelectionChanged(const QString &text);
        void OnGenerateButtonClicked(void);

    private:
        QStackedWidget *signalWidget;
        QComboBox *signalTypeComboBox;
        QComboBox *windowTypeComboBox;
        QComboBox *plotTypeComboBox;
        QPushButton *generateButton;    
        QChart *chart;
        QMap<QString, Signal*> signalMap;
        QWidget *CreateSignalWidget(const QString &signalType);
        void PlotSignal(const QString &title, QLineSeries *series, bool isFFT);
};

#endif
