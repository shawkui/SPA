/*
 * ImageItem.cpp: this file implement a class inherit from QImage to load image
 */

#include "imageitem.h"
#include <QDebug>

/*
 * constructor of imageItem
 */
ImageItem::ImageItem()
    : QImage()
{
    initialzePara();
}

ImageItem::ImageItem(const QImage &image)
    :QImage(image)
{
    initialzePara();
}

ImageItem::ImageItem(const QSize &size,Format format)
    :QImage(size,format)
{
    initialzePara();
}

ImageItem::ImageItem(int width, int height, Format format)
    :QImage(width,height,format)
{
    initialzePara();
}

ImageItem::ImageItem(const QString &fileName, const char *format)
    :QImage(fileName,format)
{
    initialzePara();
}

/*
 * initilaize the parameters
 */
void ImageItem::initialzePara()
{
    show=true;
    zoomFactor=1.0;
    qDebug()<<"initila active";
    position=QPoint(0,0);
    fileName="";
    layer=-1;
    bottmRightCorner.addEllipse(QRect(rect().bottomRight().rx()+position.rx()-100,rect().bottomRight().ry()+position.ry()-100, 200, 200));

}

/*
 * move the image to the new position given position difference/offset
 */

void ImageItem::moveTo(const QPoint dPosition){
    position+=dPosition;
    qDebug()<<dPosition;
}

/*
 * get & set methods for ImageItem data
 */

void ImageItem::setPosition(const QPoint newPosition){
    position=newPosition;
}

void ImageItem::SetFileName(const QString newFileName){
    fileName=newFileName;
}

void ImageItem::setLayer(const int newLayer){
    layer=newLayer;
}

void ImageItem::showLayer(){
    show=!show;
    qDebug()<<"showlyaer active";
}

bool ImageItem::isShow() const{
    return show;
}

int ImageItem::getLayer()const {
    return layer;
}

QPoint ImageItem::getPosition()const {
    return position;
}

QString ImageItem::getFileName()const {
    return fileName;
}

/*
 * deep copy constructor if ImageItem
 */

void ImageItem::operator =(const QImage &newImage){
    //cpoy the para of sub-class
    QPoint tempPosition=this->getPosition();
    int tempLayer=this->getLayer();
    bool tempSHow=this->isShow();
    QString tempFileName=this->getFileName();

    *this=ImageItem(newImage);

    //reset the para of sub-class
    position=tempPosition;
    show=tempSHow;
    layer=tempLayer;
    fileName=tempFileName;
    bottmRightCorner.addEllipse(QRect(rect().bottomRight().rx()+position.rx()-5,rect().bottomRight().ry()+position.ry()+5, 10, 10));

}

/*
 * get & set function for zoomfactor
 */
float ImageItem:: getZoomFactor() const{
    return zoomFactor;
}


void ImageItem:: setZoomFactor(float factor){
    zoomFactor=factor;
}

/*
 * used to get the absolute bottomRightCOrner for image position
 */
QPainterPath ImageItem::getBottomRightCorner(){
    return bottmRightCorner;

}
