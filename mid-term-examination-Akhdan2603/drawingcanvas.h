#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <iomanip>
#include <QPixmap>
#include <fstream>
#include <vector>
#include "CustomMatrix.h"

using namespace std;

class DrawingCanvas : public QWidget
{
    Q_OBJECT

private:
    const int WINDOW_WIDTH=600;
    const int WINDOW_HEIGHT=400;

    // For segment detection
    vector<CustomMatrix> allWindows;
    vector<QPoint> windowPositions;
    vector<CustomMatrix> detectorPatterns;
    vector<QPoint> candidatePositions;
    bool isDetectionDone = false;

    // Helper functions
    void loadDetectorPatterns();
    bool matchPattern(const CustomMatrix& window, const CustomMatrix& pattern, float threshold);
    void dumpWindowsToFile(const string& filename);
    void analyzeWindows();

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

    void clearPoints();
    void paintLines();
    void segmentDetection();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<QPoint> m_points;
    bool isPaintLinesClicked = false;

};
<<<<<<< HEAD
<<<<<<< HEAD

#endif // DRAWINGCANVAS_H
=======
#endif 
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
#endif 
>>>>>>> origin
