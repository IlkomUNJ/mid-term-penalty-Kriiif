#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");

    //Ideal Pattern Horizontal
    bool horizontal_line[3][3] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}
    };
    m_ideal_patterns.append(CustomMatrix(horizontal_line));

    //Ideal Pattern Vertical
    bool vertical_line[3][3] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    };
    m_ideal_patterns.append(CustomMatrix(vertical_line));

    // Ideal Pattern Diagonal from top-left to bottom-right
    bool diagonal_tl_br[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    m_ideal_patterns.append(CustomMatrix(diagonal_tl_br));

    // Ideal Pattern Diagonal from top-right to bottom-left
    bool diagonal_tr_bl[3][3] = {
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };
    m_ideal_patterns.append(CustomMatrix(diagonal_tr_bl));
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    m_drawLinesEnabled = false;
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    m_drawLinesEnabled = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    m_detected_candidates.clear();

    QPixmap pixmap(this->size());
    this->render(&pixmap);
    QImage image = pixmap.toImage();

    cout << "--- Starting Segment Detection ---" << endl;
    cout << "Image size: " << image.width() << "x" << image.height() << endl;

    for(int i = 1; i < image.width() - 1; i++){
        for(int j = 1; j < image.height() - 1; j++){
            bool local_window[3][3] = {false};
            bool is_window_empty = true;

            // Create the 3x3 window centered at (i, j)
            for(int m = -1; m <= 1; m++){
                for(int n = -1; n <= 1; n++){
                    QRgb rgbValue = image.pixel(i + m, j + n);
                    if (rgbValue != 0xffffffff) {
                        local_window[m + 1][n + 1] = true;
                        is_window_empty = false;
                    }
                }
            }
            if (!is_window_empty) {
                cout << "Found non-empty window at (" << i << ", " << j << "):" << endl;
                for (int row = 0; row < 3; ++row) {
                    for (int col = 0; col < 3; ++col) {
                        cout << (local_window[row][col] ? "1" : "0") << " ";
                    }
                    cout << endl;
                }
                cout << "--------------------" << endl;
            }
        }
    }
    cout << "--- Detection Finished ---" << endl;
    update();
    return;
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(m_drawLinesEnabled){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4);
        painter.setPen(pen);

        for(int i=0; i < m_points.size() - 1; i += 2){
            painter.drawLine(m_points[i], m_points[i+1]);
        }

        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
    if (!m_detected_candidates.isEmpty()) {
        QPen purplePen(QColor("purple"), 2);
        painter.setPen(purplePen);
        painter.setPen(purplePen);
        painter.setBrush(Qt::NoBrush);

        for (const QPoint& candidate_pos : std::as_const(m_detected_candidates)) {
            // Draw a 3x3 rectangle at the candidate's position.
            // The coordinate (i,j) was the center, so we offset by -1.
            painter.drawRect(candidate_pos.x() - 1, candidate_pos.y() - 1, 3, 3);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


