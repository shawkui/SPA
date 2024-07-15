#ifndef BASICLASSO_H
#define BASICLASSO_H


#include "canva.h"
#include <QObject>
#include <QMouseEvent>
#include <QImage>
#include "canva.h"
#include "imageitem.h"

class Canva;

/*
 * Class: BasicLasso
 * -----------------
 * This class is original designed to select the irregular shape, but now
 * the rectangualr shape selection is contained.
 */

class BasicLasso : public QObject {

    Q_OBJECT

public:
    BasicLasso(QObject *parent = 0);
    ~BasicLasso();

/* Methods:mousePressEvent, mouseMoveEvent, mouseReleaseEvent
 * ----------------------------------------------------------
 * The corresponding mouse events of basic lasso
 */
    void mousePressEvent(QMouseEvent *event, Canva & canva);
    void mouseMoveEvent(QMouseEvent *event, Canva & canva);
    void mouseReleaseEvent(QMouseEvent *event, Canva & canva);

    void clearLasso(Canva & canva);
    void saveImageChange(Canva &);

/* Methods:clearLassoSelect, copySelect, pasteSelect, cutSelect
 * ------------------------------------------------------------
 * These methods clear the selection, and copy, cut, paste
 * the selected part
 */
    void clearLassoSelect(Canva &canva);
    void copySelect(Canva &canva);
    void pasteSelect(Canva &canva);
    void cutSelect(Canva &canva);

private:

/* Methods:startAdjusting, startLasso, startResizing, startMoving
 * --------------------------------------------------------------
 * These methods renews the boolean varial of each state
 */

    void startAdjusting(Canva & canva);
    void startLasso(Canva & canva);
    void startResizing(Canva & canva);
    void startMoving(Canva & canva);

/* Methods:completeLass, completeResizing, completeMoving, cutSelect
 * ------------------------------------------------------------
 * These methods record the final image state after each kind of
 * operation
 */

    void completeLasso(Canva & canva);
    void completeResizing(Canva & canva);
    void completeMoving(Canva & canva);
    void clear();

/* This method updates the image  */

    void paint(Canva & canva);

    void select(Canva &);
    void resize(Canva &);
    void move(Canva &);


    QImage lassoImage, pasteImage;

signals:
    void sendCopyCutEnable(bool enable);
    void sendLassoEnable(bool enable);



protected:
    void drawBorder(Canva & canva);
    void updateCursor(QMouseEvent *event, Canva & canva);


    QImage imageCopy;
    QPoint startPoint, endPoint, topLeftPoint, bottomRightPoint, moveDifferentPoint;
    bool isPaint, isLassoExists, isLassoMoving, isLassoResizing, isImageSelected,
         isMouseMoved, isLassoAdjusting,isLasso;
    int height, width;
    Qt::MouseButton button;

};


#endif // BASICLASSO_H
