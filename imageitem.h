/*
 * ImageItem.h: this file design a class inherit from QImage to load image
 */
#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QImage>
/*
 * Class ImageItem
 * A self-defined calss from QImage
 * ADD:
 *  position: the left-top position of the image
 *  fileName: the name/path of a file
 *  layer: the layer the immage belongs to
 */

class ImageItem:public QImage
{
public:
    //constructor for image
    ImageItem();
    ImageItem(const QImage &image);
    ImageItem(const QSize &size,Format format);
    ImageItem(int width, int height, Format format);
    ImageItem(const QString &fileName, const char *format = Q_NULLPTR);

    //methods for users
    void moveTo(const QPoint dPosition);
    void setPosition(const QPoint newPosition);
    void SetFileName(const QString newFileName);
    void setLayer(const int newLayer);
    void showLayer();
    bool isShow() const;
    int getLayer() const;
    float getZoomFactor() const;
    void setZoomFactor(float factor);
    QPoint getPosition() const;
    QString getFileName() const;
    QPainterPath getBottomRightCorner();

    //operator/ deep copy constructor
    void operator =(const QImage &newImage);

private:
    void initialzePara();

    //para
    /*
     * show: a bool variable for layer/imageItem
     */
    bool show;

    /*
     * lefttop position of image;
     */
    QPoint position;

    /*
     * filename/path
     */
    QString fileName;

    /*
     * layer index/key
     */
    int layer;

    /*
     * return a absolute path around the imageItems bottmRightCorner
     */
    QPainterPath bottmRightCorner;

    /*
     * zoomfactor of imageitem compared with the orignal imageitem
     * in order to avoid memory problems and distortion of image;
     */
    float zoomFactor;

};

#endif // IMAGEITEM_H
