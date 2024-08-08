#ifndef SIGNAL_H
#define SIGNAL_H

////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include <QLineEdit>
#include <QLineSeries>
#include <QMap>
#include <QString>
#include <functional>

QT_CHARTS_USE_NAMESPACE


////////////////////////////////////////////////////////
// Class Definition
////////////////////////////////////////////////////////
class Signal {
    public:
        Signal(const QString &name, const QStringList &params) {
            for (const QString& param : params) {
                parameters[param] = new QLineEdit();
            }

            signalType = name;
        }

        double operator[](const QString& key) const {
            return parameters.value(key, nullptr)->text().toDouble();
        }

        QString signalType;
        QString windowType;
        QLineSeries *series = new QLineSeries;
        QLineSeries *fftSeries;
        QLineSeries *windowedSeries;
        QLineSeries *windowedFFTSeries;
        QMap<QString, QLineEdit*> parameters;
        void generate(void);

    private:
        QLineSeries *computeFFT(QLineSeries*);
};

#endif
