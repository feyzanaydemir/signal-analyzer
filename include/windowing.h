#ifndef WINDOWING_H
#define WINDOWING_H

////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include "MainWindow.h"


////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////
extern QMap<QString, std::function<void(QtCharts::QLineSeries*)>> windowingFuncs;

#endif