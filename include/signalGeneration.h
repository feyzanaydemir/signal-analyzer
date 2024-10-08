#ifndef WAVEGENERATION_H
#define WAVEGENERATION_H

////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include "MainWindow.h"
#include <functional>

class Signal;


////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////
extern QMap<QString, std::function<QtCharts::QLineSeries*(Signal*)>> signalGenFuncs;


#endif
