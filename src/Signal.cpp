////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include "../include/Signal.h"
#include "../include/signalGeneration.h"
#include "../include/windowing.h"
#include <fftw3.h>
#include <cmath>
#include <QVector>
#include <QDebug>


////////////////////////////////////////////////////////
// Public Function Definitions
////////////////////////////////////////////////////////
void Signal::generate(void) {   
    series = (signalGenFuncs[signalType])(this);
    fftSeries = computeFFT(series);

    if (windowType != "No Window") {
        windowedSeries = (signalGenFuncs[signalType])(this);
        (windowingFuncs[windowType])(windowedSeries);
        windowedFFTSeries = computeFFT(windowedSeries);
    }
}


////////////////////////////////////////////////////////
// Private Function Definitions
////////////////////////////////////////////////////////
QLineSeries *Signal::computeFFT(QLineSeries* series) {
    QVector<double> freqData, magnitudeData;
    QVector<double> data;
    for (const QPointF &point : series->points()) {
        data.append(point.y());
    }

    int n = data.size();
    fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
    fftw_plan p = fftw_plan_dft_r2c_1d(n, data.data(), out, FFTW_ESTIMATE);

    for (int i = 0; i < n; ++i) {
        in[i][0] = data[i];
        in[i][1] = 0.0;
    }

    fftw_execute(p);
    
    double sampleRate = (parameters.value("Sample Rate")->text()).toDouble();
    int numSamples = (parameters.value("Number of Samples")->text()).toInt();
    freqData.resize(n / 2);
    magnitudeData.resize(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        freqData[i] = i;
        //freqData[i] = i * sampleRate / n; // Frequency bins normalized to the sample rate
        magnitudeData[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    QLineSeries *fftSeries = new QLineSeries;
    for (int i = 0; i < freqData.size(); ++i) {
        fftSeries->append(freqData[i] * sampleRate / numSamples, magnitudeData[i]);
    }

    return fftSeries;
}
