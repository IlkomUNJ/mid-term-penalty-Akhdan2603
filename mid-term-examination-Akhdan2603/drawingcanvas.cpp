#include "drawingcanvas.h"

<<<<<<< HEAD
<<<<<<< HEAD
DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent) {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);

    // Set a solid background color
=======
DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
>>>>>>> origin
    setStyleSheet("background-color: white; border: 1px solid gray;");

    // Load detector patterns for segment detection
    loadDetectorPatterns();
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
<<<<<<< HEAD
<<<<<<< HEAD
    candidatePositions.clear();
    allWindows.clear();
    windowPositions.clear();
    isDetectionDone = false;
    isPaintLinesClicked = false;
    // Trigger a repaint to clear the canvas
=======
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
>>>>>>> origin
    update();
}

void DrawingCanvas::paintLines(){
<<<<<<< HEAD
<<<<<<< HEAD
    /* Implement lines drawing per even pair */
=======
=======
>>>>>>> origin

>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::loadDetectorPatterns(){
    // Horizontal line patterns
    CustomMatrix horizontal;
    bool h_pattern[3][3] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}
    };
    horizontal.fillMatrix(h_pattern);
    detectorPatterns.push_back(horizontal);

    // Vertical line patterns
    CustomMatrix vertical;
    bool v_pattern[3][3] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    };
    vertical.fillMatrix(v_pattern);
    detectorPatterns.push_back(vertical);

    // Diagonal line patterns (top-left to bottom-right)
    CustomMatrix diagonal1;
    bool d1_pattern[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    diagonal1.fillMatrix(d1_pattern);
    detectorPatterns.push_back(diagonal1);

    // Diagonal line patterns (top-right to bottom-left)
    CustomMatrix diagonal2;
    bool d2_pattern[3][3] = {
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };
    diagonal2.fillMatrix(d2_pattern);
    detectorPatterns.push_back(diagonal2);

    // Partial horizontal patterns
    CustomMatrix partial_h1;
    bool ph1_pattern[3][3] = {
        {0, 0, 0},
        {1, 1, 0},
        {0, 0, 0}
    };
    partial_h1.fillMatrix(ph1_pattern);
    detectorPatterns.push_back(partial_h1);

    CustomMatrix partial_h2;
    bool ph2_pattern[3][3] = {
        {0, 0, 0},
        {0, 1, 1},
        {0, 0, 0}
    };
    partial_h2.fillMatrix(ph2_pattern);
    detectorPatterns.push_back(partial_h2);

    // Partial vertical patterns
    CustomMatrix partial_v1;
    bool pv1_pattern[3][3] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    partial_v1.fillMatrix(pv1_pattern);
    detectorPatterns.push_back(partial_v1);

    CustomMatrix partial_v2;
    bool pv2_pattern[3][3] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 1, 0}
    };
    partial_v2.fillMatrix(pv2_pattern);
    detectorPatterns.push_back(partial_v2);

    cout << "Loaded " << detectorPatterns.size() << " detector patterns" << endl;
}

bool DrawingCanvas::matchPattern(const CustomMatrix& window, const CustomMatrix& pattern, float threshold){
    float similarity = window.similarity(pattern);
    return similarity >= threshold;
}

void DrawingCanvas::dumpWindowsToFile(const string& filename){
    ofstream outFile(filename);

    if(!outFile.is_open()){
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    outFile << "Total Windows: " << allWindows.size() << endl;
    outFile << "Non-empty Windows: ";

    int nonEmptyCount = 0;
    for(const auto& window : allWindows){
        if(!window.isEmpty()) nonEmptyCount++;
    }
    outFile << nonEmptyCount << endl << endl;

    outFile << "=== NON-EMPTY WINDOWS DATA ===" << endl << endl;

    for(size_t idx = 0; idx < allWindows.size(); idx++){
        if(!allWindows[idx].isEmpty()){
            outFile << "Window #" << idx << " at position ("
                    << windowPositions[idx].x() << ", "
                    << windowPositions[idx].y() << ")" << endl;

            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    outFile << allWindows[idx].mat[i][j] << " ";
                }
                outFile << endl;
            }
            outFile << endl;
        }
    }

    outFile.close();
    cout << "Window data dumped to " << filename << endl;
}

void DrawingCanvas::analyzeWindows(){
    ofstream analysisFile("window_analysis.txt");

    if(!analysisFile.is_open()){
        cout << "Error: Could not open analysis file" << endl;
        return;
    }

    analysisFile << "=== WINDOW SIZE ANALYSIS ===" << endl << endl;
    analysisFile << "Current window size: 3x3" << endl;
    analysisFile << "Total windows analyzed: " << allWindows.size() << endl;

    int nonEmptyCount = 0;
    for(const auto& window : allWindows){
        if(!window.isEmpty()) nonEmptyCount++;
    }

    analysisFile << "Non-empty windows: " << nonEmptyCount << endl;
    analysisFile << "Empty windows: " << (allWindows.size() - nonEmptyCount) << endl;
    analysisFile << "Non-empty ratio: "
                 << (float)nonEmptyCount / allWindows.size() * 100 << "%" << endl << endl;

    analysisFile << "=== PATTERN MATCHING RESULTS ===" << endl << endl;

    vector<int> patternMatches(detectorPatterns.size(), 0);

    for(size_t idx = 0; idx < allWindows.size(); idx++){
        if(!allWindows[idx].isEmpty()){
            for(size_t p = 0; p < detectorPatterns.size(); p++){
                if(matchPattern(allWindows[idx], detectorPatterns[p], 0.7f)){
                    patternMatches[p]++;
                }
            }
        }
    }

    vector<string> patternNames = {
        "Horizontal Line",
        "Vertical Line",
        "Diagonal (TL-BR)",
        "Diagonal (TR-BL)",
        "Partial Horizontal 1",
        "Partial Horizontal 2",
        "Partial Vertical 1",
        "Partial Vertical 2"
    };

    for(size_t p = 0; p < detectorPatterns.size(); p++){
        analysisFile << "Pattern: " << patternNames[p] << endl;
        analysisFile << "Matches: " << patternMatches[p] << endl;
        analysisFile << "Pattern matrix:" << endl;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                analysisFile << detectorPatterns[p].mat[i][j] << " ";
            }
            analysisFile << endl;
        }
        analysisFile << endl;
    }

    analysisFile.close();
    cout << "Window analysis completed and saved to window_analysis.txt" << endl;
}

void DrawingCanvas::segmentDetection(){
    cout << "Starting segment detection..." << endl;

    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "Image width: " << image.width() << endl;
    cout << "Image height: " << image.height() << endl;

<<<<<<< HEAD
<<<<<<< HEAD
    // Clear previous data
    allWindows.clear();
    windowPositions.clear();
    candidatePositions.clear();

    // Sliding window with 3x3 size
    for(int i = 1; i < image.width()-1; i++){
        for(int j = 1; j < image.height()-1; j++){
=======
=======
>>>>>>> origin
    vector<CustomMatrix> windows(image.width()*image.height());

    for(int i = 1; i < image.width()-1;i++){
        for(int j = 1; j < image.height()-1;j++){
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
            bool local_window[3][3] = {false};

            // Extract 3x3 window
            for(int m=-1; m<=1; m++){
                for(int n=-1; n<=1; n++){
                    QRgb rgbValue = image.pixel(i+m, j+n);
                    local_window[m+1][n+1] = (rgbValue != 0xffffffff);
                }
            }

            CustomMatrix mat(local_window);
            allWindows.push_back(mat);
            windowPositions.push_back(QPoint(i, j));

            // Check if this window matches any detector pattern
            if(!mat.isEmpty()){
                for(const auto& pattern : detectorPatterns){
                    if(matchPattern(mat, pattern, 0.66f)){ // 66% threshold (6 out of 9 cells)
                        candidatePositions.push_back(QPoint(i, j));
                        break; // Only add once even if multiple patterns match
                    }
                }
            }
        }
    }

    cout << "Total windows extracted: " << allWindows.size() << endl;
    cout << "Segment candidates found: " << candidatePositions.size() << endl;

    // Dump windows to file for Objective 1 & 2
    dumpWindowsToFile("window_dump.txt");

    // Analyze windows for report
    analyzeWindows();

    // Mark detection as done
    isDetectionDone = true;

    // Trigger repaint to show candidates
    update();

    cout << "Segment detection completed!" << endl;
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    // Draw lines if paintLines was clicked
    if(isPaintLinesClicked){
        cout << "Paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

<<<<<<< HEAD
<<<<<<< HEAD
        for(int i=0; i<m_points.size()-1; i+=2){
            if(i+1 < m_points.size()){
                painter.drawLine(m_points[i], m_points[i+1]);
            }
=======
=======
>>>>>>> origin
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            painter.drawLine(m_points[i], m_points[i+1]);
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
        }
    }

<<<<<<< HEAD
<<<<<<< HEAD
    // Draw purple rectangles for segment candidates (Objective 3)
    if(isDetectionDone && !candidatePositions.empty()){
        QPen purplePen(Qt::magenta, 1);
        painter.setPen(purplePen);
        painter.setBrush(Qt::NoBrush);

        for(const QPoint& candidate : candidatePositions){
            // Draw small purple rectangle to mark the candidate
            painter.drawRect(candidate.x()-2, candidate.y()-2, 4, 4);
        }

        cout << "Drew " << candidatePositions.size() << " candidate markers" << endl;
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event){
    // Add the clicked point to our vector
    m_points.append(event->pos());

    // Trigger a repaint
=======
=======
>>>>>>> origin
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    m_points.append(event->pos());
<<<<<<< HEAD
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
>>>>>>> origin
    update();
}
