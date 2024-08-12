////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include "../include/signalGeneration.h"
#include "../include/MainWindow.h"
#include <QRandomGenerator>
#include <QtMath>


////////////////////////////////////////////////////////
// Private Function Definitions
////////////////////////////////////////////////////////
QLineSeries *generateSineWave(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double amplitude = (*signal)["Amplitude"];
    double frequency = (*signal)["Frequency"];

    QLineSeries *series = new QLineSeries;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, amplitude * qSin(2 * M_PI * frequency * t));
    }

    return series;
}

QLineSeries *generateSquareWave(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double amplitude = (*signal)["Amplitude"];
    double frequency = (*signal)["Frequency"];
    double dutyCycle = (*signal)["Duty Cycle"];
    
    QLineSeries *series = new QLineSeries;
    double period = 1.0 / frequency;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, (fmod(t, period) < (dutyCycle / 100.0) * period) ? amplitude : -amplitude);
    }

    return series;
}

QLineSeries *generateSawtoothWave(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double amplitude = (*signal)["Amplitude"];
    double frequency = (*signal)["Frequency"];
    
    QLineSeries *series = new QLineSeries;
    double period = 1.0 / frequency;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, 2 * amplitude * (t / period - qFloor(0.5 + t / period)));
    }

    return series;
}

QLineSeries *generateTriangleWave(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double amplitude = (*signal)["Amplitude"];
    double frequency = (*signal)["Frequency"];
    
    QLineSeries *series = new QLineSeries;
    double period = 1.0 / frequency;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, 2 * amplitude * qAbs(2 * (t / period - qFloor(t / period + 0.5))) - amplitude);
    }

    return series;
}

QLineSeries *generateWhiteNoise(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double amplitude = (*signal)["Amplitude"];
    QRandomGenerator* randomGenerator = QRandomGenerator::global();
    
    QLineSeries *series = new QLineSeries;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, amplitude * (2.0 * randomGenerator->generateDouble() - 1.0));
    }

    return series;
}

QLineSeries *generateChirpSignal(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double startFrequency = (*signal)["Start Frequency"];
    double endFrequency = (*signal)["End Frequency"];
    double amplitude = (*signal)["Amplitude"];
    double duration = (*signal)["Duration"];
    
    QLineSeries *series = new QLineSeries;
    double k = (endFrequency - startFrequency) / duration;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, amplitude * qSin(2 * M_PI * (startFrequency * t + (k / 2) * t * t)));
    }

    return series;
}

QLineSeries *generateImpulseSignal(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double amplitude = (*signal)["Amplitude"];
    
    QLineSeries *series = new QLineSeries;
    int impulseIndex = numSamples / 2;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, (i == impulseIndex) ? amplitude : 0.0);
    }

    return series;
}

QLineSeries *generateGaussianPulse(Signal *signal) {
    double sampleRate = (*signal)["Sample Rate"];
    int numSamples = (*signal)["Number of Samples"];
    double amplitude = (*signal)["Amplitude"];
    double center = (*signal)["Center"];
    double width = (*signal)["Width"];
    
    QLineSeries *series = new QLineSeries;
    for (int i = 0; i < numSamples; ++i) {
        double t = i / sampleRate;
        series->append(t, amplitude * qExp(-qPow(t - center, 2) / (2 * qPow(width, 2))));
    }

    return series;
}


////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////
QMap<QString, std::function<QtCharts::QLineSeries*(Signal*)>> signalGenFuncs = {
    {"Sine Wave", generateSineWave},
    {"Square Wave", generateSquareWave},
    {"Sawtooth Wave", generateSawtoothWave},
    {"Triangle Wave", generateTriangleWave},
    {"White Noise", generateWhiteNoise},
    {"Chirp Signal", generateChirpSignal},
    {"Impulse Signal", generateImpulseSignal},
    {"Gaussian Pulse", generateGaussianPulse}
};
