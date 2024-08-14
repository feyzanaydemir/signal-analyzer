////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include "../include/windowing.h"
#include <cmath>


////////////////////////////////////////////////////////
// Private Function Definitions
////////////////////////////////////////////////////////
void applyHanningWindow(QLineSeries *signalSeries) {
    int numSamples = signalSeries->count();
    int i = 0;
    for (QPointF &point : signalSeries->points()) {
        point.setY(point.y() * (0.5 * (1 - cos(2 * M_PI * i / (numSamples - 1)))));
        signalSeries->replace(i++, point);
    }
}

void applyHammingWindow(QLineSeries *signalSeries) {
    int numSamples = signalSeries->count();
    int i = 0;
    for (QPointF &point : signalSeries->points()) {
        point.setY(point.y() * (0.54 - 0.46 * cos(2 * M_PI * i / (numSamples - 1))));
        signalSeries->replace(i++, point);
    }
}

void applyBlackmanWindow(QLineSeries *signalSeries) {
    int numSamples = signalSeries->count();
    int i = 0;
    for (QPointF &point : signalSeries->points()) {
        point.setY(point.y() * (0.42 - 0.5 * cos(2 * M_PI * i / (numSamples - 1)) 
                                + 0.08 * cos(4 * M_PI * i / (numSamples - 1))));
        signalSeries->replace(i++, point);
    }
}

void applyBartlettWindow(QLineSeries *signalSeries) {
    int numSamples = signalSeries->count();
    int i = 0;
    for (QPointF &point : signalSeries->points()) {
        point.setY(point.y() * (1.0 - fabs((i - (numSamples - 1) / 2.0) / ((numSamples - 1) / 2.0))));
        signalSeries->replace(i++, point);
    }
}

void applyBlackmanHarrisWindow(QLineSeries *signalSeries) {
    int numSamples = signalSeries->count();
    int i = 0;
    for (QPointF &point : signalSeries->points()) {
        point.setY(point.y() * (0.35875 - 0.48829 * cos(2 * M_PI * i / (numSamples - 1)) + 
                                0.14128 * cos(4 * M_PI * i / (numSamples - 1)) - 
                                0.01168 * cos(6 * M_PI * i / (numSamples - 1))));
        signalSeries->replace(i++, point);
    }
}

void applyFlatTopWindow(QLineSeries *signalSeries) {
    int numSamples = signalSeries->count();
    int i = 0;
    for (QPointF &point : signalSeries->points()) {
        point.setY(point.y() * (1 - 1.93 * cos(2 * M_PI * i / (numSamples - 1)) + 
                                1.29 * cos(4 * M_PI * i / (numSamples - 1)) - 
                                0.388 * cos(6 * M_PI * i / (numSamples - 1)) + 
                                0.0322 * cos(8 * M_PI * i / (numSamples - 1))));
        signalSeries->replace(i++, point);
    }
}

// double _besseli0(double x) {
//     double sum = 1.0;
//     double u = 1.0;
//     for (int k = 1; k < 50; ++k) {
//         u = u * (x * x) / (4.0 * k * k);
//         sum += u;
//     }
//     return sum;
// }

// void applyKaiserWindow(QLineSeries *signalSeries, int numSamples, double beta) {
//     double denom = besseli0(beta);
//     for (int i = 0; i < numSamples; ++i) {
//         double ratio = (2.0 * i) / (numSamples - 1) - 1.0;
//         signalSeries[i] *= besseli0(beta * sqrt(1 - ratio * ratio)) / denom;
//     }
// }


////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////
QMap<QString, std::function<void(QtCharts::QLineSeries*)>> windowingFuncs = {
    {"Hanning", applyHanningWindow},
    {"Hamming", applyHammingWindow},
    {"Blackman", applyBlackmanWindow},
    {"Bartlett", applyBartlettWindow},
    {"Blackman-Harris", applyBlackmanHarrisWindow},
    {"Flat Top", applyFlatTopWindow}
};
