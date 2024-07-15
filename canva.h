/*
 * Canva.h: this file make new widget class to show image and provide some oprations to edit images
 */
#ifndef CANVA_H
#define CANVA_H
#include <QWidget>
#include <QString>
#include <QPen>
#include "canva.h"
#include "shapeitem.h"
#include "imageitem.h"
#include "shapetype.h"
#include "colorFilter/abstractfilter.h"
#include <QClipboard>

#include "basiclasso.h"

class AbstractFilter;
class BasicLasso;

class Canva : public QWidget
{
    Q_OBJECT

signals:
    /*
     * basic signals to connect with the parent widget of cannva;
     */

    /*
     * when new layer is create, send this signal to parent
     */
    void createNewLayer();

    /*
     * when item is selected, sent siganl to parent to open item-edit page
     */
    void ShapeItemOn();
    void ImageItemOn();

protected:

    /*
     * override methods for paintevent and mouse event
     */
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

public:
    Canva();
    ~Canva();

    /*
     * get & set function;
     */
    void setImage(const ImageItem &newImage);
    void addImage(const ImageItem &newImage);
    ImageItem* getImage();
    QRect getImageSize();
    qreal getZoomFactor();

    /*
     * active & show function;
     */
    void layerActive(int index);
//    void exchangeOrder(int oldIndex,int NewIndex);

    /*
     * Basic function for load/save image
     * Load will laod image as an imageItem in the current layer
     * while open will load image as a new layer
     * Save will save images in the active image's path
     * Save as will open a window for user to select file path
     * To export image to different format, use can just choose different postfix when choose the file path
     * by default, it will save images as PNG, format
     */

    void open();
    void open(const QString &filePath);
    void open(const QString &filePath, bool load=false);
    void load();
    void load(const QString &filePath);
    void load(ImageItem const &newImageItem);
    void save();
    void save(const QString &filePath);
    void saveAs(QString format="png");


    /*
     * basic image operation
     */
    void zoomIn();
    void zoomOut();
    void zoomAny(qreal factor);
    void rotateClockWise();
    void rotateCounterClockWise();


    /*
     * assistant function
     */
    void showGrid();
    void saveWithGrid();
    void layerShow(int index);

    /*
     * create Item and choose items when different mouse event happends;
     */
    void createCircle();
    int itemAt(const QPoint &pos);
    int imageAt(const QPoint&pos);
    void moveItemTo(const QPoint &pos);
    void moveImageTo(const QPoint &pos);
    void resizeImage(const QPoint &pos);

    void createShapeItem(shapeType ShapeName);
    void setGrayFilter();
    void setNegativeFilter();

    /*
     * basic operations for items;
     */
    void setPenColor(QColor color);
    void setPenWidth(int width);
    QColor getColor();
    int getWidth();
    void zoomItem(float factor);
    void rotateItem(float angle);
    void deleteItem();
    void Copy();
    void Paste();

    /*
     * set different mouse operatons
     */
    void activeSlection();
    void setNroaml();
    void setPaintOn();

    void setWireOn();
    void lassOn();

    void setSolidPencil();
    void setDotPencil();
    void setDashPecil();

private:
    /*
     * struct: layer
     * basic struct for layer with 3 data fields for layer data
     */
    struct layer{
        QList<ImageItem*> *images; /* store images of this layer */
        QList<ShapeItem*> *shapes; /* store shapes of this layer */
        bool show;                 /* show layer or hide layer   */
    };

    QList<layer*> layers; /* store different layers */
    layer* activeLayer;   /* current active layer   */
    ImageItem  *ActiveImage; /* active image of current active layer */
    QList<ShapeItem*>* activeShapeItems; /* iamges of current active layer */
    QList<ImageItem*>* ActiveImages; /* shapes of current active layer */
    qreal zoomFactor; /* zoom factor for all layers */
    bool isNormal;  /* normal mouse event: for selection, move and edit */
    bool selectionOn; /* rect selection window and select rect shape */
    bool gridOn;     /* show grid for asistance. ALl shapeitems will located to grid point */
    bool saveGridOn; /* save with grid */
    bool boundaryOn; /* show boundary of items */
    bool wireOn;
    //bool imageResizeOn;
    bool needPaint; /* mouse move will cause paint event */
    QPoint previousPosition; /* position for mouse tracking */
    ShapeItem *itemInMotion; /* current item in motion */
    ImageItem *imageInMotion;/* current iamge in motion */
    BasicLasso *basicLasso;  /* basiclasso item */
    AbstractFilter *filterappli; /* filter effect */
    ImageItem* copyImage; /* copy image */
    ShapeItem* copyShape; /* copy shape */

    /* global data for color and pen */
    QColor globalColor;
    int globalWidth;
    QPen myPencil;

    bool wireExist;
    bool wireDraw;
    bool lass;
    QPainterPath wire, lastWire;
    QPoint wireStart, wireEnd, wireCurrent;
    QPainterPath classo;

};

#endif // CANVA_H
