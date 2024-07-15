/*
 * file: mainwindow2.cpp
 * This file implements a window for screen shoot
 */
#include "MainWindow2.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QDateTime>
#include <QDesktopServices>
#include <QDebug>
#include <QClipboard>
#include "iostream"
#define STRETCH_RECT_WIDTH 6
#define STRETCH_RECT_HEIGHT 6


MainWindow2::MainWindow2(QWidget *parent)
    : QWidget(parent)
    , m_currentCaptureState(InitCapture)
{
    initWindow();
    initStretchRect();
    loadBackgroundPixmap();
}

MainWindow2::~MainWindow2()
{

}

void MainWindow2::initWindow()
{
    this->setMouseTracking(true);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
    this->setMouseTracking(true);
}

void MainWindow2::initStretchRect()
{
    m_stretchRectState = NotSelect;
    m_topLeftRect = QRect(0 , 0 , 0 , 0);
    m_topRightRect = QRect(0, 0, 0, 0);
    m_bottomLeftRect = QRect(0, 0, 0, 0);
    m_bottomRightRect = QRect(0, 0, 0, 0);

    m_leftCenterRect = QRect(0, 0, 0, 0);
    m_topCenterRect = QRect(0, 0, 0, 0);
    m_rightCenterRect = QRect(0, 0, 0, 0);
    m_bottomCenterRect = QRect(0, 0, 0, 0);
}

// this part set the background of the mainwindow as target area.
void MainWindow2::loadBackgroundPixmap()
{
    m_loadPixmap = QPixmap::grabWindow(QApplication::desktop()->winId()); //scratch the current screen.
    m_screenwidth = m_loadPixmap.width();                                 // load the width.
    m_screenheight = m_loadPixmap.height();                               //load the height.
}

/* Method:MainWindow2::mousePressEvent
 * this method defines the press event of the mouse.
 */

void MainWindow2::mousePressEvent(QMouseEvent *event)
{
    m_stretchRectState = getStrethRectState(event->pos());
    if (event->button() == Qt::LeftButton)
    {
        if (m_currentCaptureState == InitCapture)
        {
            m_currentCaptureState = BeginCaptureImage;
            m_beginPoint = event->pos();
        }
        // whether the mouse is in the rectangle we choose.
        else if (m_stretchRectState != NotSelect)
        {
            m_currentCaptureState = BeginMoveStretchRect;
            // when the mouse if put on the frontier of the rectangle, set mouse style.
            setStretchCursorStyle(m_stretchRectState);
            m_beginMovePoint = event->pos();
        }
        // check whether mouse is inside the rectangle.
        else if (isPressPointInSelectRect(event->pos()))
        {
            m_currentCaptureState = BeginMoveCaptureArea;
            m_beginMovePoint = event->pos();
        }
    }

    return QWidget::mousePressEvent(event);
}


/* Method:MainWindow2::mouseMoveEvent
 * this method defines the move event of the mouse.
 */
void MainWindow2::mouseMoveEvent(QMouseEvent* event)
{
    if (m_currentCaptureState == BeginCaptureImage) // if is undergoing capturing
    {
        m_endPoint = event->pos();                  // update the position of mouse.
        update();
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea)
    {
        m_endMovePoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect)
    {
        m_endMovePoint = event->pos();
        update();
        return QWidget::mouseMoveEvent(event);
    }


    // check the style of mouse by its position.
    StretchRectState stretchRectState = getStrethRectState(event->pos());
    if (stretchRectState != NotSelect)
    {
        setStretchCursorStyle(stretchRectState);
    }
    else if (isPressPointInSelectRect(event->pos()))
    {
        setCursor(Qt::SizeAllCursor);
    }
    else if (!isPressPointInSelectRect(event->pos()) && m_currentCaptureState != BeginMoveCaptureArea)
    {
        setCursor(Qt::ArrowCursor);
    }

    return QWidget::mouseMoveEvent(event);
}


/* Method:MainWindow2::mouseReleaseEvent
 * this method defines the press event of the mouse.
 */
void MainWindow2::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_currentCaptureState = FinishCaptureImage;
        m_endPoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea)
    {
        m_currentCaptureState = FinishMoveCaptureArea;
        m_endMovePoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect)
    {
        m_currentCaptureState = FinishMoveStretchRect;
        m_endMovePoint = event->pos();
        update();
    }

    return QWidget::mouseReleaseEvent(event);
}

/* Method:MainWindow2::isPressPointInSelectRect
 * this method returns whether the mouse is in the rectangle we choose.
 */
bool MainWindow2::isPressPointInSelectRect(QPoint mousePressPoint)
{
    QRect selectRect = getRect(m_beginPoint, m_endPoint);
    if (selectRect.contains(mousePressPoint))
    {
        return true;
    }
    return false;
}
/* Method:MainWindow2::paintEvent
 * this method initialize the background color and make action by current state.
 */
void MainWindow2::paintEvent(QPaintEvent *event)
{
    m_painter.begin(this);                                          //repainting

    QColor shadowColor = QColor(0, 0, 0, 120);                      //set the shadow color
    m_painter.setPen(QPen(QColor(0 , 174 , 255), 1, Qt::SolidLine, Qt::FlatCap));    //set pen
    m_painter.drawPixmap(0, 0, m_loadPixmap);                       //set background
    m_painter.fillRect(m_loadPixmap.rect(), shadowColor);           //draw the shadowcolor

    switch (m_currentCaptureState)
    {
    case InitCapture:
        break;
    case BeginCaptureImage:
    case FinishCaptureImage:
    case BeginMoveCaptureArea:
    case FinishMoveCaptureArea:
    case BeginMoveStretchRect:
    case FinishMoveStretchRect:
        m_currentSelectRect = getSelectRect();
        drawCaptureImage();
    default:
        break;
    }

    m_painter.end();
}

/* Method:MainWindow2::getSelectRect
 * this method get the picture of the chooseing rectangle.
 */
QRect MainWindow2::getSelectRect()
{
    if (m_currentCaptureState == BeginCaptureImage || m_currentCaptureState == FinishCaptureImage)
    {
        return getRect(m_beginPoint, m_endPoint);
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea || m_currentCaptureState == FinishMoveCaptureArea)
    {
        return getMoveRect();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect || m_currentCaptureState == FinishMoveStretchRect)
    {
        return getStretchRect();
    }

    return QRect(0, 0, 0, 0);
}

// draw the chosen captured area.
void MainWindow2::drawCaptureImage()
{
    m_capturePixmap = m_loadPixmap.copy(m_currentSelectRect);
    m_painter.drawPixmap(m_currentSelectRect.topLeft(), m_capturePixmap);
    m_painter.drawRect(m_currentSelectRect);
    drawStretchRect();
}

// draw each handle of the edges of the chosen rectangle.
void MainWindow2::drawStretchRect()
{
    QColor color = QColor(0, 174, 255);
    // coordinate of corners
    QPoint topLeft = m_currentSelectRect.topLeft();
    QPoint topRight = m_currentSelectRect.topRight();
    QPoint bottomLeft = m_currentSelectRect.bottomLeft();
    QPoint bottomRight = m_currentSelectRect.bottomRight();
    // middle point of edges
    QPoint leftCenter = QPoint(topLeft.x(), (topLeft.y() + bottomLeft.y()) / 2);
    QPoint topCenter = QPoint((topLeft.x() + topRight.x()) / 2, topLeft.y());
    QPoint rightCenter = QPoint(topRight.x(), leftCenter.y());
    QPoint bottomCenter = QPoint(topCenter.x(), bottomLeft.y());

    m_topLeftRect = QRect(topLeft.x() - STRETCH_RECT_WIDTH / 2, topLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topRightRect = QRect(topRight.x() - STRETCH_RECT_WIDTH / 2, topRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomLeftRect = QRect(bottomLeft.x() - STRETCH_RECT_WIDTH / 2, bottomLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomRightRect = QRect(bottomRight.x() - STRETCH_RECT_WIDTH / 2, bottomRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_leftCenterRect = QRect(leftCenter.x() - STRETCH_RECT_WIDTH / 2, leftCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topCenterRect = QRect(topCenter.x() - STRETCH_RECT_WIDTH / 2, topCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightCenterRect = QRect(rightCenter.x() - STRETCH_RECT_WIDTH / 2, rightCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomCenterRect = QRect(bottomCenter.x() - STRETCH_RECT_WIDTH / 2, bottomCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_painter.fillRect(m_topLeftRect, color);
    m_painter.fillRect(m_topRightRect, color);
    m_painter.fillRect(m_bottomLeftRect, color);
    m_painter.fillRect(m_bottomRightRect, color);
    m_painter.fillRect(m_leftCenterRect, color);
    m_painter.fillRect(m_topCenterRect, color);
    m_painter.fillRect(m_rightCenterRect, color);
    m_painter.fillRect(m_bottomCenterRect, color);
}

void MainWindow2::keyPressEvent(QKeyEvent *event)
{
    // press Esc to quit
    if (event->key() == Qt::Key_Escape)
    {
        close();

    }
    // press Eeter to finish shooting
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {

        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setImage(m_capturePixmap.toImage());
        std::cout<<TopLeftRect<<TopRightRect<<BottomLeftRect<<BottomRightRect<<LeftCenterRect<<TopCenterRect<<RightCenterRect<<BottomCenterRect;
        emit load();
        close();
    }
}

// according to the begin/end points, get the chosen rectangle.
QRect MainWindow2::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);

    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}

// if the rectangle is moved, get new rectangle.
QRect MainWindow2::getMoveRect()
{
    QPoint movePoint = getMovePoint();
    QPoint beginPoint = m_beginPoint + movePoint;
    QPoint endPoint = m_endPoint + movePoint;
    if (m_currentCaptureState == FinishMoveCaptureArea)
    {
        m_beginPoint = beginPoint;
        m_endPoint = endPoint;
        m_beginMovePoint = QPoint(0, 0);
        m_endMovePoint = QPoint(0, 0);
    }
    return getRect(beginPoint, endPoint);
}

QPoint MainWindow2::getMovePoint()
{
    QPoint movePoint = m_endMovePoint - m_beginMovePoint;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);

    if (currentRect.topLeft().x() + movePoint.x() < 0)
    {
        movePoint.setX(0 - currentRect.topLeft().x());
    }

    if (currentRect.topLeft().y() + movePoint.y() < 0)
    {
        movePoint.setY(0 - currentRect.topLeft().y());
    }

    if (currentRect.bottomRight().x() + movePoint.x() > m_screenwidth)
    {
        movePoint.setX(m_screenwidth - currentRect.bottomRight().x());
    }

    if (currentRect.bottomRight().y() + movePoint.y() > m_screenheight)
    {
        movePoint.setY(m_screenheight - currentRect.bottomRight().y());
    }

    return movePoint;
}

// get on which handle the mouse is.
StretchRectState MainWindow2::getStrethRectState(QPoint point)
{
    StretchRectState stretchRectState = NotSelect;
    if (m_topLeftRect.contains(point))
    {
        stretchRectState = TopLeftRect;
    }
    else if (m_topCenterRect.contains(point))
    {
        stretchRectState = TopCenterRect;
    }
    else if (m_topRightRect.contains(point))
    {
        stretchRectState = TopRightRect;
    }
    else if (m_rightCenterRect.contains(point))
    {
        stretchRectState = RightCenterRect;
    }
    else if (m_bottomRightRect.contains(point))
    {
        stretchRectState = BottomRightRect;
    }
    else if (m_bottomCenterRect.contains(point))
    {
        stretchRectState = BottomCenterRect;
    }
    else if (m_bottomLeftRect.contains(point))
    {
        stretchRectState = BottomLeftRect;
    }
    else if (m_leftCenterRect.contains(point))
    {
        stretchRectState = LeftCenterRect;
    }

    return stretchRectState;
}

// set mouse style when stop on handle
void MainWindow2::setStretchCursorStyle(StretchRectState stretchRectState)
{
    switch (stretchRectState)
    {
    case NotSelect:
        setCursor(Qt::ArrowCursor);
        break;
    case TopLeftRect:
    case BottomRightRect:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRightRect:
    case BottomLeftRect:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case LeftCenterRect:
    case RightCenterRect:
        setCursor(Qt::SizeHorCursor);
        break;
    case TopCenterRect:
    case BottomCenterRect:
        setCursor(Qt::SizeVerCursor);
        break;
    default:
        break;
    }
}

// get stretched rectangle
QRect MainWindow2::getStretchRect()
{
    QRect stretchRect;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    switch (m_stretchRectState)
    {
    case NotSelect:
        stretchRect = getRect(m_beginPoint, m_endPoint);
        break;
    case TopLeftRect:
        {
            stretchRect = getRect(currentRect.bottomRight(), m_endMovePoint);
        }
        break;
    case TopRightRect:
        {
            QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
            QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
            stretchRect = getRect(beginPoint, endPoint);
        }
        break;
    case BottomLeftRect:
        {
            QPoint beginPoint = QPoint(m_endMovePoint.x() , currentRect.topLeft().y());
            QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
            stretchRect = getRect(beginPoint, endPoint);
        }
        break;
    case BottomRightRect:
        {
            stretchRect = getRect(currentRect.topLeft(), m_endMovePoint);
        }
        break;
    case LeftCenterRect:
        {
            QPoint beginPoint = QPoint(m_endMovePoint.x(), currentRect.topLeft().y());
            stretchRect = getRect(beginPoint, currentRect.bottomRight());
        }
        break;
    case TopCenterRect:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
    }
        break;
    case RightCenterRect:
    {
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    case BottomCenterRect:
    {
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    default:
    {
        stretchRect = getRect(m_beginPoint , m_endPoint );
    }
        break;
    }
    if (m_currentCaptureState == FinishMoveStretchRect)
    {
        m_beginPoint = stretchRect.topLeft();
        m_endPoint = stretchRect.bottomRight();
    }

    return stretchRect;
}
