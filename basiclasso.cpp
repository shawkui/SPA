#include "basiclasso.h"
#include "canva.h"
#include "imageitem.h"
#include "math.h"
#include <QPainter>
#include <QApplication>
#include <QClipboard>

/* Implementation of the constructor */

BasicLasso::BasicLasso(QObject *parent) : QObject(parent) {
    isLassoExists = false;
            isLassoMoving = isLassoResizing
            = isPaint = isImageSelected = isMouseMoved
            = isLassoAdjusting = false;
}

BasicLasso::~BasicLasso() {
}

/* Implementation of mousePressEvent, mouseMoveEvent, mouseReleaseEvent*/

void BasicLasso::mousePressEvent(QMouseEvent *event, Canva & canva) {
    button = event->button();
    isMouseMoved = false;
    if (isLassoExists) {
        canva.setImage(imageCopy);
        paint(canva);
        if (event->pos().x() > topLeftPoint.x() &&    //test whether the press event happend in the selected event
                event->pos().x() < bottomRightPoint.x() &&
                event->pos().y() > topLeftPoint.y() &&
                event->pos().y() < bottomRightPoint.y()) {
            if (!isImageSelected) {
                startMoving(canva);
                isImageSelected = true;
            } else {
                drawBorder(canva);
            }
            isLassoMoving = true;
            moveDifferentPoint = bottomRightPoint - event->pos();
            return;
        } else {
            return;
            clearLasso(canva);
        }

        }
    if (event->button() == Qt::LeftButton) {
        bottomRightPoint = topLeftPoint = event->pos();
        height = width = 0;
        imageCopy = *canva.getImage();
        startLasso(canva);
        isPaint = true;
    }
}

void BasicLasso::mouseMoveEvent(QMouseEvent *event, Canva & canva) {
    isMouseMoved = true;
    if (isLassoExists) {
        if (isLassoMoving) {
            bottomRightPoint = event->pos() + moveDifferentPoint; // record two points of the seleted region
            topLeftPoint = event->pos() + moveDifferentPoint - QPoint(width - 1, height - 1);//
            canva.setImage(imageCopy);
            move(canva);
            drawBorder(canva);
            isPaint = false;
        }
        else if (isLassoResizing) {
            bottomRightPoint = event->pos();
            height = fabs(topLeftPoint.y() - bottomRightPoint.y()) + 1;//get absolute value of height and width
            width = fabs(topLeftPoint.x() - bottomRightPoint.x()) + 1;
            canva.setImage(imageCopy);
            resize(canva);
            drawBorder(canva);
            isPaint = false;
        }
    }
    if (isPaint) {
        bottomRightPoint = event->pos();
        height = fabs(topLeftPoint.y() - bottomRightPoint.y()) + 1;
        width = fabs(topLeftPoint.x() - bottomRightPoint.x()) + 1;
        canva.setImage(imageCopy);
        drawBorder(canva);
        select(canva);
    }
    updateCursor(event, canva);
}

void BasicLasso::mouseReleaseEvent(QMouseEvent *event, Canva & canva) {
    int right = topLeftPoint.x() > bottomRightPoint.x() ? topLeftPoint.x() : bottomRightPoint.x(); // four points
    int bottom = topLeftPoint.y() > bottomRightPoint.y() ? topLeftPoint.y() : bottomRightPoint.y();// to locate
    int left = topLeftPoint.x() < bottomRightPoint.x() ? topLeftPoint.x() : bottomRightPoint.x();// the selected
    int top = topLeftPoint.y() < bottomRightPoint.y() ? topLeftPoint.y() : bottomRightPoint.y();//region
    bottomRightPoint = QPoint(right, bottom);
    topLeftPoint = QPoint(left, top);
    if (isLassoExists) {
        updateCursor(event, canva);
        if (isLassoMoving) {
            canva.setImage(imageCopy);
            completeMoving(canva);
            paint(canva);
            drawBorder(canva);
            isPaint = false;
            isLassoMoving = false;
        }
        else if (isLassoResizing) {
            canva.setImage(imageCopy);
            paint(canva);
            completeResizing(canva);
            paint(canva);
            drawBorder(canva);
            isPaint = false;
            isLassoResizing = false;
        }
    }
    if (isPaint) {
        if (event->button() == Qt::LeftButton) {
            canva.setImage(imageCopy);
            if (topLeftPoint != bottomRightPoint) {
                canva.setImage(imageCopy);
                paint(canva);
                completeLasso(canva);
                paint(canva);
                isLassoExists = true;
            }
            drawBorder(canva);
            isPaint = false;
        }
    }
    isLassoAdjusting = false;
}

/* Implementation of drawBorder */

void BasicLasso::drawBorder(Canva & canva) {
    if (width > 1 && height > 1) {
        QPainter painter(canva.getImage());
        painter.setPen(QPen(Qt::green, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        //painter.setBackgroundMode(Qt::white);
        if(topLeftPoint != bottomRightPoint) {
            painter.drawRect(QRect(topLeftPoint, bottomRightPoint - QPoint(1, 1)));
        }
        painter.end();
        canva.update();
    }
}

/* Implementation of clearLasso */

void BasicLasso::clearLasso(Canva & canva) {
    if (isLassoExists) {
        canva.setImage(imageCopy);// undo the selection by set the image copied before selection
        paint(canva);
        imageCopy = *canva.getImage();
        isLassoExists = isLassoMoving = isLassoResizing
                = isPaint = isImageSelected = false;
        canva.update();
        clear();
    }
}

void BasicLasso::saveImageChange(Canva &){

}


/* Implementation: updateCursor
 * ----------------------------
 * This method update the type of cursor when the cursor
 * moves to the differnent regions
 */

void BasicLasso::updateCursor(QMouseEvent *event, Canva & canva) {
    if (isLassoExists){
        if (event->pos().x() > topLeftPoint.x() &&
                event->pos().x() < bottomRightPoint.x() &&
                event->pos().y() > topLeftPoint.y() &&
                event->pos().y() < bottomRightPoint.y()) {
            canva.setCursor(Qt::SizeAllCursor);
        }
        else if (event->pos().x() >= bottomRightPoint.x() &&
                 event->pos().x() <= bottomRightPoint.x() + 6 &&
                 event->pos().y() >= bottomRightPoint.y() &&
                 event->pos().y() <= bottomRightPoint.y() + 6) {
            canva.setCursor(Qt::SizeFDiagCursor);
        }
        else {
        }
    }
    else {
    }
}

/* Implementation: copySelect
 * ----------------------------
 * This method copies the selected region to the clipboard
 */

void BasicLasso::copySelect(Canva & canva) {
    if (isLassoExists) {
        canva.setImage(imageCopy);
        QClipboard *globalClipboard = QApplication::clipboard();
        QImage copyImage;
        if (isImageSelected) {
            copyImage = lassoImage;
        }
        else {
            copyImage = canva.getImage()->copy(topLeftPoint.x(), topLeftPoint.y(), width, height);// copy the selected region
        }
        globalClipboard->setImage(copyImage, QClipboard::Clipboard);
    }
}


void BasicLasso::cutSelect(Canva & canva) {
    if (isLassoExists) {
        copySelect(canva);
        if (isLassoExists) {
            canva.setImage(imageCopy);
            paint(canva);
        }
        if (isImageSelected) {
            canva.setImage(imageCopy);
        } else {
            clearLassoSelect(canva);
        }
        topLeftPoint = QPoint(0, 0);
        bottomRightPoint = QPoint(0, 0);
        imageCopy = *canva.getImage();
        canva.update();
        isLassoExists = false;
    }
}

/* Implementation: pasteSelect
 * ----------------------------
 * This method gets the stored image in the clipborad and paste it onto
 * the canva
 */

void BasicLasso::pasteSelect(Canva & canva) {
    QClipboard *globalClipboard = QApplication::clipboard();
    if (isLassoExists) {
        canva.setImage(imageCopy);
        imageCopy = *canva.getImage();
    }
    pasteImage = globalClipboard->image();
    if (!pasteImage.isNull()) {
        lassoImage = pasteImage;
        topLeftPoint = QPoint(0, 0);
        bottomRightPoint = QPoint(pasteImage.width(), pasteImage.height())- QPoint(1, 1);
        height = pasteImage.height();
        width = pasteImage.width();
        isImageSelected = isLassoExists = true;
        paint(canva);
        drawBorder(canva);
    }
}

void BasicLasso::startAdjusting(Canva &canva) {
    imageCopy= *canva.getImage();
    isImageSelected = false;
}

void BasicLasso::startLasso(Canva &) {
}

void BasicLasso::startResizing(Canva & canva) {
    if (!isImageSelected) {
        clearLassoSelect(canva);
    }
    if (isLassoAdjusting) {
        isImageSelected = false;
    }
}

void BasicLasso::startMoving(Canva & canva) {
    clearLassoSelect(canva);
    if (isLassoAdjusting) {
        isImageSelected = false;
    }
}

void BasicLasso::select(Canva &) {
}

void BasicLasso::resize(Canva &) {
}

void BasicLasso::move(Canva &) {
}

void BasicLasso::completeLasso(Canva & canva) {
    lassoImage = canva.getImage()->copy(topLeftPoint.x(), topLeftPoint.y(),
                                        width, height);
}

void BasicLasso::completeResizing(Canva & canva) {
    lassoImage = canva.getImage()->copy(topLeftPoint.x(), topLeftPoint.y(),
                                        width, height);
}

void BasicLasso::completeMoving(Canva & canva) {
    if (isLassoAdjusting) {
        lassoImage = canva.getImage()->copy(topLeftPoint.x(), topLeftPoint.y(),
                                            width, height);
    }

}

/* Implementation: clearLassoSelect
 * --------------------------------
 * This method fill the original selected region
 * with white when the selected image is moved away
 * from the original rigion
 */

void BasicLasso::clearLassoSelect(Canva & canva) {
    if (!isLassoAdjusting) {
        QPainter blankPainter(canva.getImage());
        blankPainter.setPen(Qt::white);
        blankPainter.setBrush(QBrush(Qt::white));
        blankPainter.setBackgroundMode(Qt::OpaqueMode);
        blankPainter.drawRect(QRect(topLeftPoint, bottomRightPoint - QPoint(1, 1)));
        blankPainter.end();
        imageCopy = *canva.getImage();
    }
}

void BasicLasso::clear() {
    lassoImage = QImage();
    emit sendCopyCutEnable(false);
}

/* Implementation: copySelect
 * ----------------------------
 * This method paint the current image to canva
 */

void BasicLasso::paint(Canva & canva) {
    if (isLassoExists && !isLassoAdjusting) {
        if(topLeftPoint != bottomRightPoint) {
            QPainter painter(canva.getImage());
            QRect source(0, 0, lassoImage.width(), lassoImage.height());
            QRect target(topLeftPoint, bottomRightPoint);
            painter.drawImage(target, lassoImage, source);
            painter.end();
        }
        canva.update();
    }
}

