/*
 * file: mainwindow2.cpp
 * This file implements a window for screen shoot
 */
#include <QWidget>
#include <QPainter>

//states when capturing
enum CaptureState{
    InitCapture = 0,
    BeginCaptureImage,
    FinishCaptureImage,
    BeginMoveCaptureArea,
    FinishMoveCaptureArea,
    BeginMoveStretchRect,
    FinishMoveStretchRect
};


//the state of where mouse is.
enum StretchRectState{
    NotSelect = 0,
    TopLeftRect,
    TopRightRect,
    BottomLeftRect,
    BottomRightRect,
    LeftCenterRect,
    TopCenterRect,
    RightCenterRect,
    BottomCenterRect
};

class MainWindow2 : public QWidget
{
    Q_OBJECT

public:
    MainWindow2(QWidget *parent = 0);
    ~MainWindow2();

signals:
    void load();


private:
    void initWindow();
    void initStretchRect();
    void loadBackgroundPixmap();
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
    QRect getMoveRect();
    QRect getStretchRect();
    bool isPressPointInSelectRect(QPoint mousePressPoint);
    QRect getSelectRect();
    QPoint getMovePoint();
    StretchRectState getStrethRectState(QPoint point);
    void setStretchCursorStyle(StretchRectState stretchRectState);
    void drawCaptureImage();
    void drawStretchRect();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_loadPixmap, m_capturePixmap;
    int m_screenwidth;
    int m_screenheight;
    QPoint m_beginPoint, m_endPoint, m_beginMovePoint, m_endMovePoint;
    QPainter m_painter;
    CaptureState m_currentCaptureState;
    QRect m_currentSelectRect;
    QRect m_topLeftRect, m_topRightRect, m_bottomLeftRect, m_bottomRightRect;
    QRect m_leftCenterRect, m_topCenterRect, m_rightCenterRect, m_bottomCenterRect;
    StretchRectState m_stretchRectState;
};
