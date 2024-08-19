////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////
#include "../include/MainWindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QChartView>
#include <QValueAxis>
#include <QDebug>


////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent)
    :   QMainWindow(parent),
        signalWidget(new QStackedWidget),
        signalTypeComboBox(new QComboBox),
        windowTypeComboBox(new QComboBox),
        plotTypeComboBox(new QComboBox),
        chart(new QChart) {

    //-----------------------------------------------------//
    // Variables
    //-----------------------------------------------------//
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *centralLayout = new QHBoxLayout;
    QWidget *centralWidget = new QWidget;
    QWidget *inputWidget = new QWidget;
    QChartView *chartView = new QChartView;


    //-----------------------------------------------------//
    // Signal Selection Widget
    //-----------------------------------------------------//
    QStringList signalNames = {
        "Sine Wave", "Square Wave", "Sawtooth Wave", "Triangle Wave",
        "White Noise", "Chirp Signal", "Impulse Signal", "Gaussian Pulse"
    };

    foreach (const QString &signalName, signalNames) {
        signalTypeComboBox->addItem(signalName);
        signalWidget->addWidget(CreateSignalWidget(signalName));
    }

    QWidget *signalSelectionWidget = new QWidget;
    QFormLayout *signalSelectionLayout = new QFormLayout;
    signalSelectionLayout->addRow(new QLabel("Signal Type: "), signalTypeComboBox);
    connect(signalTypeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::OnSignalSelectionChanged);
    OnSignalSelectionChanged(signalTypeComboBox->currentText());
    signalSelectionWidget->setLayout(signalSelectionLayout);
    mainLayout->addWidget(signalSelectionWidget);
    mainLayout->addWidget(signalWidget);


    //-----------------------------------------------------//
    // Window Selection Widget
    //-----------------------------------------------------//
    QStringList windowNames = {
        "No Window", "Hanning", "Hamming", "Blackman",
        "Bartlett", "Blackman-Harris", "Flat Top"
    };

    QWidget *windowSelectionWidget = new QWidget;
    QFormLayout *windowSelectionLayout = new QFormLayout;
    windowSelectionLayout->addRow(new QLabel("Window Type: "), windowTypeComboBox);
    foreach (const QString &windowName, windowNames) {
        windowTypeComboBox->addItem(windowName);
    }

    windowSelectionWidget->setLayout(windowSelectionLayout);
    mainLayout->addWidget(windowSelectionWidget);


    //-----------------------------------------------------//
    // TODO: Filter Selection Widget
    //-----------------------------------------------------//
    // QStringList filterNames = {
    //     "No Filter", "High-Pass Butterworth", "Low-Pass Butterworth",
    //     "Band-Pass Butterworth", "High-Pass Chebyshev", "Low-Pass Chebyshev", 
    //     "Band-Pass Chebyshev", "High-Pass Bessel", "Low-Pass Bessel", "Band-Pass Bessel"
    // };

    // QComboBox filterTypeCombobox = new QComboBox;
    // foreach (const QString &filterName, filterNames) {
    //     filterTypeComboBox->addItem(filterName);
    // }

    // QWidget *filterSelectionWidget = new QWidget;
    // QFormLayout *filterSelectionLayout = new QFormLayout;
    // filterSelectionLayout->addRow(new QLabel("Filter Type: "), filterTypeComboBox);
    // connect(filterTypeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::OnFilterSelectionChanged);
    // OnFilterSelectionChanged(filterTypeComboBox->currentText());
    // filterSelectionWidget->setLayout(filterSelectionLayout);
    // mainLayout->addWidget(filterSelectionWidget);
    // mainLayout->addWidget(filterWidget);


    //-----------------------------------------------------//
    // Generate Button
    //-----------------------------------------------------//
    QPushButton *generateButton = new QPushButton("Generate", this);
    mainLayout->addWidget(generateButton);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::OnGenerateButtonClicked);
    

    //-----------------------------------------------------//
    // Plot Selection Widget
    //-----------------------------------------------------//
    QWidget *plotSelectionWidget = new QWidget;
    QFormLayout *plotSelectionLayout = new QFormLayout;
    plotTypeComboBox->addItem("Original Signal");
    plotSelectionLayout->addRow(new QLabel("Plot Type: "), plotTypeComboBox);
    connect(plotTypeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::OnPlotSelectionChanged);
    OnPlotSelectionChanged(plotTypeComboBox->currentText());
    plotTypeComboBox->setEnabled(false);
    plotSelectionWidget->setLayout(plotSelectionLayout);
    plotSelectionWidget->setContentsMargins(0, 40, 0, 0);
    mainLayout->addWidget(plotSelectionWidget);

    mainLayout->addItem(new QSpacerItem(0, 1000, QSizePolicy::Expanding, QSizePolicy::Expanding));        
    inputWidget->setLayout(mainLayout);
    inputWidget->setMaximumWidth(400);
 
    // Add input widget and chart view to the central layout
    centralLayout->addWidget(inputWidget, 1);
    centralLayout->addWidget(chartView, 3);

    // Set central widget
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    // Initialize the chart
    chart->legend()->setVisible(false);
    chartView->setChart(chart);

    // Resize window
    resize(1200, 600);
    setMinimumWidth(800); 
    setMinimumHeight(500); 
}

MainWindow::~MainWindow() = default;

QWidget *MainWindow::CreateSignalWidget(const QString &signalName) {
    QMap<QString, QStringList> signalParamsMap = {
        {"Sine Wave", {"Amplitude", "Frequency", "Number of Samples", "Sample Rate"}},
        {"Square Wave", {"Amplitude", "Frequency", "Duty Cycle", "Number of Samples", "Sample Rate"}},
        {"Sawtooth Wave", {"Amplitude", "Frequency", "Number of Samples", "Sample Rate"}},
        {"Triangle Wave", {"Amplitude", "Frequency", "Number of Samples", "Sample Rate"}},
        {"White Noise", {"Amplitude", "Number of Samples", "Sample Rate"}},
        {"Chirp Signal", {"Start Frequency", "End Frequency", "Amplitude", "Duration", "Number of Samples", "Sample Rate"}},
        {"Impulse Signal", {"Amplitude", "Number of Samples", "Sample Rate"}},
        {"Gaussian Pulse", {"Amplitude", "Center", "Width", "Number of Samples", "Sample Rate"}}
    };

    QWidget *widget = new QWidget;
    QFormLayout *layout = new QFormLayout;
    Signal* signal = new Signal(signalName, signalParamsMap[signalName]);
    signalMap[signalName] = signal;

    for (auto pair = signal->parameters.constBegin(); pair != signal->parameters.constEnd(); ++pair) {
        QString paramName = pair.key();
        QLineEdit* paramInput = pair.value();
        layout->addRow(new QLabel(paramName + ": "), paramInput);
    }

    widget->setLayout(layout);
    return widget;
}

void MainWindow::OnSignalSelectionChanged(const QString &signalName) {
    if (signalName == "Sine Wave") {
        signalWidget->setCurrentIndex(0);
    } else if (signalName == "Square Wave") {
        signalWidget->setCurrentIndex(1);
    } else if (signalName == "Sawtooth Wave") {
        signalWidget->setCurrentIndex(2);
    } else if (signalName == "Triangle Wave") {
        signalWidget->setCurrentIndex(3);
    } else if (signalName == "White Noise") {
        signalWidget->setCurrentIndex(4);
    } else if (signalName == "Chirp Signal") {
        signalWidget->setCurrentIndex(5);
    } else if (signalName == "Impulse Signal") {
        signalWidget->setCurrentIndex(6);
    } else {
        signalWidget->setCurrentIndex(7);
    }
}

void MainWindow::PlotSignal(const QString &title, QLineSeries *signal, bool isFFT) {
    for (QAbstractSeries *series : chart->series()) {
            chart->removeSeries(series);
    }

    chart->addSeries(signal);
    chart->setTitle(title);
    chart->createDefaultAxes();
    QList<QAbstractAxis*> horizontalAxes = chart->axes(Qt::Horizontal);
    if (!horizontalAxes.isEmpty()) {
        QValueAxis* xAxis = qobject_cast<QValueAxis*>(horizontalAxes.first());
        if (xAxis) {
            if (!isFFT) {
                xAxis->setTitleText("Time");
            } else {
                xAxis->setTitleText("Frequency");
            }  
        }
    }

    QList<QAbstractAxis*> verticalAxes = chart->axes(Qt::Vertical);
    if (!verticalAxes.isEmpty()) {
        QValueAxis* yAxis = qobject_cast<QValueAxis*>(verticalAxes.first());
        if (yAxis) {
            if (!isFFT) {
                yAxis->setTitleText("Amplitude");
            } else {
                yAxis->setTitleText("Magnitude");
            } 
        }
    }
}

void MainWindow::OnPlotSelectionChanged(const QString &text) {
    chart->setTitle("Original Signal");
    QString currSignalName = signalTypeComboBox->currentText();

    if (text == "Original Signal") {
        PlotSignal(signalMap[currSignalName]->signalType, signalMap[currSignalName]->series, false);
    } else if (text == "Original Signal FFT") {
        PlotSignal(signalMap[currSignalName]->signalType + " FFT Spectrum", signalMap[currSignalName]->fftSeries, true);
    } else if (text == "Windowed Signal") {
        PlotSignal(signalMap[currSignalName]->signalType + " - " + signalMap[currSignalName]->windowType + " Window", signalMap[currSignalName]->windowedSeries, true);
    } else if (text == "Windowed Signal FFT") {
        PlotSignal(signalMap[currSignalName]->signalType + " - " + signalMap[currSignalName]->windowType + " Window FFT Spectrum", signalMap[currSignalName]->windowedFFTSeries, true);
    }
}

void MainWindow::OnGenerateButtonClicked() {   
    QString currSignalName = signalTypeComboBox->currentText();
    QString currWindowName = windowTypeComboBox->currentText();
    Signal *currSignal = signalMap[currSignalName];
    currSignal->windowType = currWindowName;

    // Check for empty or invalid inputs
    bool ok;
    for (auto pair = currSignal->parameters.constBegin(); pair != currSignal->parameters.constEnd(); ++pair) {
        QString inputValue = pair.value()->text();
        if (inputValue.isEmpty() || !inputValue.toDouble(&ok)) {
            return;
        }
    }

    currSignal->generate();

    plotTypeComboBox->clear();
    plotTypeComboBox->addItem("Original Signal");
    plotTypeComboBox->addItem("Original Signal FFT");

    if (currWindowName != "No Window") {
        plotTypeComboBox->addItem("Windowed Signal");
        plotTypeComboBox->addItem("Windowed Signal FFT");
    }
    
    for (QAbstractSeries *series : chart->series()) {
            chart->removeSeries(series);
    }

    PlotSignal(signalMap[currSignalName]->signalType, signalMap[currSignalName]->series, false);
    plotTypeComboBox->setEnabled(true);
}


////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon.ico"));

    MainWindow window;
    window.show();
    return app.exec();
}
