#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

<<<<<<< HEAD
<<<<<<< HEAD
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a central widget to hold the layout
=======
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
>>>>>>> origin
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *subLayout = new QHBoxLayout();

    DrawingCanvas *m_canvas = new DrawingCanvas(this);
    mainLayout->addWidget(m_canvas);

    m_clearButton = new QPushButton("Clear Canvas", this);
    m_detectButton = new QPushButton("Detect Segment", this);
    m_drawButton = new QPushButton("Draw Lines", this);

    mainLayout->addLayout(subLayout, 1);
    subLayout->addWidget(m_drawButton, 0);
    subLayout->addWidget(m_detectButton, 0);
    subLayout->addWidget(m_clearButton, 0);

<<<<<<< HEAD
<<<<<<< HEAD
    // Connect the buttons clicked signal to the slot that clears the canvas
=======
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
>>>>>>> origin
    connect(m_clearButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::clearPoints);
    connect(m_drawButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::paintLines);
    connect(m_detectButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::segmentDetection);

<<<<<<< HEAD
    // Set the central widget for the main window
=======

    centralWidget->setLayout(mainLayout);
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow(){}
