/*
 * Canva.cpp: this file implement new widget class to show image and provide some oprations to edit images
 */
#include <QApplication>
#include <QPainter>
#include <QFileDialog>
#include <QtCore/QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QImage>
#include <QMessageBox>
#include <QMimeData>
#include <QImageWriter>
#include <QImageReader>
#include <QClipboard>
#include <QApplication>

#include "error.h"
#include "canva.h"
#include "shapepath.h"
#include "shapeitem.h"
#include "imageitem.h"
#include "shapetype.h"
#include "basiclasso.h"
#include "colorFilter/negativefilter.h"
#include "colorFilter/grayfilter.h"
#include "pencil/pencil.h"

/*
 * constructor & deconstructor
 */

Canva::Canva()
{


    //initial blank image size
    const int width=1000;
    const int height=500;

    //initialize properties

    classo.moveTo(0,0);
    //path.contains(QPoint(0,0));
    //path=QSet<QPoint>;

    //initialize properties
    lass=false;

    zoomFactor=1.0;
    isNormal=true;
    gridOn=false;
    saveGridOn=false;
    selectionOn=false;
    wireExist=false;
    wireDraw=false;
    boundaryOn=true;
    //  imageResizeOn=true;
    setMouseTracking(true);
    needPaint=false;
    globalWidth=1;
//    myPencil=solidPen(globalColor,globalWidth);
    wire = QPainterPath();


    //create blank image
    ImageItem *initalImage=new ImageItem(width,height,ImageItem::Format_ARGB32_Premultiplied);
    initalImage->fill(Qt::transparent);
    initalImage->fill(Qt::white);
    initalImage->setLayer(0);
    initalImage->SetFileName("");

    //create new layer
    activeLayer=new layer;
    activeLayer->shapes=new QList<ShapeItem*>;
    activeLayer->images=new QList<ImageItem*>;
    activeLayer->show=true;
    activeLayer->images->append(initalImage);
    ActiveImages=activeLayer->images;
    layers.append(activeLayer);

    ActiveImage=activeLayer->images->at(0);
    activeShapeItems=activeLayer->shapes;
    resize(ActiveImage->size().width()+5,ActiveImage->size().height()+5);
    globalColor=Qt::black;


    basicLasso = new BasicLasso(this);
    connect(basicLasso, SIGNAL(sendCopyCutEnable(bool)), basicLasso, SIGNAL(sendCopyCutEnable(bool)));
    connect(basicLasso,SIGNAL(sendLassoEnable(bool)), basicLasso, SIGNAL(sendLassoEnable(bool)));
}

Canva::~Canva(){
    for(int i=0;i<layers.size();i++){
        layer* tempLayer=layers.at(i);
        for(int m=0;m<tempLayer->images->size();m++){
            delete tempLayer->images->at(m);
        }
        for(int n=0;n<tempLayer->shapes->size();n++){
            delete tempLayer->shapes->at(n);
        }
    }
    delete basicLasso;
    delete filterappli;
    delete copyShape;
    delete copyImage;
}

/*
 * set & get methods
 */

void Canva::setImage(const ImageItem &newImage){
    *ActiveImage=newImage;
}

ImageItem* Canva::getImage(){
    return ActiveImage;
}

QRect Canva::getImageSize(){
    return ActiveImage->rect();
}


/*
 *  override paintevent of widget
 */
void Canva::paintEvent(QPaintEvent *event){
    QPainter temp(this);
    temp.setCompositionMode(QPainter::CompositionMode_SourceOver);
    //begin paint
    for(layer *paintLayer:layers){
        if(paintLayer->show){
            //get layer data
            QList<ImageItem*> *paintImages=paintLayer->images;
            //paint images
            for(int i=0;i<paintImages->size();i++){
                ImageItem* paintImage=paintImages->at(i);
                if(paintImage->isShow()){
                    temp.translate(paintImage->getPosition());
                    temp.drawImage(event->rect(),*paintImage,event->rect());
                    temp.translate(-paintImage->getPosition());
                }
            }
            //paint shapes
            for(int i=0;i<paintLayer->shapes->size();i++){
                ShapeItem* paintShape=paintLayer->shapes->at(i);
                if(paintShape->isShow()){
                    //temp.setPen(paintShape.color());
                    QPen tempPen;
                    tempPen.setWidth(paintShape->penwidth());
                    tempPen.setColor(paintShape->color());
                    temp.setPen(tempPen);
                    qDebug()<<paintShape->color();
                    temp.translate(paintShape->position());
                    temp.drawPath(paintShape->path());
                    temp.translate(-paintShape->position());
                }
            }
        }
    }

    //paint grid
    if(gridOn){
        //set pen for grid
        QPen penForGrid;
        QVector<qreal> dash;
        dash<<zoomFactor<<zoomFactor;
        penForGrid.setDashPattern(dash);
        penForGrid.setColor(Qt::gray);
        temp.setPen(penForGrid);
        //paint grid
        for(int i=0;i<=1/zoomFactor*ActiveImage->width()/10;++i){
            temp.drawLine(zoomFactor*10*i,0,zoomFactor*10*i,ActiveImage->height());
        }
        for(int j=0;j<=1/zoomFactor*ActiveImage->height()/10;++j){
            temp.drawLine(0,zoomFactor*10*j,ActiveImage->width(),zoomFactor*10*j);
        }
    }
    //paint boundary
    if(boundaryOn){
        temp.setPen(Qt::green);
        temp.drawRect(this->rect());
        if(itemInMotion!=NULL){
            temp.translate(itemInMotion->position());
            temp.drawRect(itemInMotion->path().boundingRect());
            temp.translate(-itemInMotion->position());
        }
        if(imageInMotion!=NULL){
            temp.translate(imageInMotion->getPosition());
            temp.drawRect(imageInMotion->rect());
            temp.translate(-imageInMotion->getPosition());
        }
    }
    temp.setPen(myPencil);
    temp.drawPath(wire);
    temp.setPen(myPencil);
    temp.drawPath(classo);
    temp.end();
    qDebug()<<"paint";
}

/*
 * laod/open function to get image
 */

void Canva::open(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Image"), QDir::currentPath());
    open(filePath,false);
}
void Canva::load(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Image"), QDir::currentPath());
    open(filePath,true);
}

void Canva::load(const QString& filePath){
    open(filePath,true);
}

void Canva::load(ImageItem const &newImageItem){
    qDebug()<<"1";
    ImageItem* addItem=new ImageItem(newImageItem);
    qDebug()<<"2";
    ActiveImages->append(addItem);
    update();
}


void Canva::open(const QString &filePath,bool load){
    if(!filePath.isEmpty()){
        ImageItem *newImage=new ImageItem(filePath);
        if(newImage->isNull()){
            qDebug()<<"Cannot open such a file";
            QMessageBox::warning(this,tr("Load Image Error!"),tr("Sorry, SPA cannot load this image."));
            delete newImage;
            return;
        }else{
            //convert new Image to PNG format & set the para values
            *newImage=newImage->convertToFormat(ImageItem::Format_ARGB32_Premultiplied);
            newImage->SetFileName(filePath);
            if(!load){
                layer *newLayer=new layer;
                newLayer->images=new QList<ImageItem*>;
                newLayer->shapes=new QList<ShapeItem*>;
                newLayer->show=true;

                //set image and append layer
                ActiveImage=newImage;
                newLayer->images->append(newImage);
                layers.append(newLayer);
                activeLayer=newLayer;
                ActiveImages=newLayer->images;
                activeShapeItems=newLayer->shapes;
                imageInMotion=newImage;
                emit createNewLayer();
            }else{
                ActiveImages->append(newImage);
            }

            //resize the Canva widget
            if(ActiveImage->rect().width()+5>this->rect().width()){
                resize(ActiveImage->rect().width()+5,this->rect().height());
            }
            if(ActiveImage->rect().height()+5>this->rect().height()+5){
                resize(this->rect().width(),ActiveImage->rect().height()+5);
            }
            update();
        }
    }else{
        return;
    }
}

/*
 * save function for save image
 */
void Canva::save(){
    if(ActiveImage->getFileName().isEmpty()){
        saveAs();
        return;
    }else{
        save(ActiveImage->getFileName());
        return;
    }
}


void Canva::save(const QString &filePath){
    if(!ActiveImage->save(filePath)){
        QMessageBox::warning(this,tr("Save Image Error!"),tr("SPA cannot Save this Image."));
        return;
    }
}

void Canva::saveAs(QString format){
    //get file path
    QString filePath=QFileDialog::getSaveFileName(this,tr("Save Image...."));
    if(!filePath.isEmpty()){
        // check file name
        QString temp;
        QString extension;
        temp=filePath.split("/").last();
        if(temp.contains('.')){
            temp=temp.split('.').last();
            if(QImageWriter::supportedImageFormats().contains(temp.toLatin1())){
                extension=temp;
            }else{
                extension=format;
            }
        }else{
            extension=format;
            filePath+='.'+format;
        }
        if(!ActiveImage->save(filePath,extension.toLatin1().data())){
            QMessageBox::warning(this,tr("Save As Error!"),tr("SPA cannot save this image"));
        }else{
            //begin save image
            ImageItem* SavedImage=new ImageItem(this->width(),this->height(),
                                                QImage::Format_ARGB32_Premultiplied);
            SavedImage->fill(Qt::transparent);
            QPainter paintForSavedImage(SavedImage);
            for(layer *paintLayer:layers){
                for(int i=0;i<paintLayer->images->size();i++){
                    ImageItem* paintImage=paintLayer->images->at(i);
                    if(paintImage->isShow()){
                        paintForSavedImage.translate(paintImage->getPosition());
                        paintForSavedImage.drawImage(paintImage->rect(),*paintImage,paintImage->rect());
                        paintForSavedImage.translate(-paintImage->getPosition());
                    }
                }
                for(int i=0;i<paintLayer->shapes->size();i++ ){
                    ShapeItem* paintShape=paintLayer->shapes->at(i);
                    if(paintShape->isShow()){
                        //paintForSavedImage.setPen(paintShape[m].color());
                        paintForSavedImage.translate(paintShape->position());
                        paintForSavedImage.drawPath(paintShape->path());
                        paintForSavedImage.translate(-paintShape->position());
                    }
                }
            }
            paintForSavedImage.end();
            QPainter paintForSavedImageGrid(SavedImage);
            if(saveGridOn){
                QPen penForGrid;
                QVector<qreal> dash;
                dash<<1<<1;
                penForGrid.setDashPattern(dash);
                penForGrid.setColor(Qt::gray);
                paintForSavedImageGrid.setPen(penForGrid);
                for(int i=0;i<=1/zoomFactor*SavedImage->width()/10;++i){
                    paintForSavedImageGrid.drawLine(zoomFactor*10*i,0,zoomFactor*10*i,SavedImage->height());
                }
                for(int j=0;j<=1/zoomFactor*SavedImage->height()/10;++j){
                    paintForSavedImageGrid.drawLine(0,zoomFactor*10*j,SavedImage->width(),zoomFactor*10*j);
                }
            }
            paintForSavedImageGrid.end();
            *SavedImage=SavedImage->transformed(QTransform::fromScale(1/zoomFactor,1/zoomFactor));//transform should be excuted after paint.end
            SavedImage->save(filePath,extension.toLatin1().data());
            delete SavedImage;
        }
    }else{
        QMessageBox::warning(this,tr("Save As Error!"),tr("Illegal path/file name"));
        return;
    }

}

/*
 * zoomAny function
 * Zoom all layers and images and shapes in canva
 */
void Canva::zoomAny(qreal factor){
    if(zoomFactor>=4.0 && factor > 1){
        zoomFactor=4.0;
        return;
    }else if(zoomFactor<=0.25 && factor < 1){
        zoomFactor=0.25;
        return;
    }else{
        zoomFactor*=factor;
        qDebug()<<"zoom"<<layers.size();
        for(layer *zoomLayer:layers){
            qDebug()<<"index";
            for(int i=0;i<zoomLayer->images->size();i++){
                ImageItem* zoomImage=zoomLayer->images->at(i);
                *zoomImage=zoomImage->transformed(QTransform::fromScale(factor,factor));
                update();
            }
            for(int i=0;i<zoomLayer->shapes->size();i++){
                zoomLayer->shapes->at(i)->scale(factor);
            }
        }
        resize((this->size().width())*factor,(this->size().height())*factor);
        update();
        return;
    }
}

/*
 * zoom in and zoom out functon for zoom all layers
 */
void Canva::zoomIn(){
    zoomAny(2);
}

void Canva::zoomOut(){
    zoomAny(0.5);
}


/*
 * rotate functons for rotate all layers
 */
void Canva::rotateClockWise(){
    QTransform rotation;
    rotation.rotate(90);
    //rotate for shapes
    for(layer *rotateLayer:layers){
        for(int i=0;i<rotateLayer->images->size();i++){
            ImageItem* rotateImage=rotateLayer->images->at(i);
            *rotateImage=rotateImage->transformed(rotation);
        }
    }
    update();
}

void Canva::rotateCounterClockWise(){
    QTransform rotation;
    rotation.rotate(-90);
    for(layer *rotateLayer:layers){
        for(int i=0;i<rotateLayer->images->size();i++){
            ImageItem* rotateImage=rotateLayer->images->at(i);
            *rotateImage=rotateImage->transformed(rotation);
        }
    }
    resize(this->rect().height(),this->rect().width());
    update();
}

/*
 * mouse events for paint
 */
void Canva::mouseDoubleClickEvent(QMouseEvent *event){
    qDebug()<<"clc"<<lass;
    if(lass && event->button() == Qt::LeftButton){
        qDebug()<<"doub";
        QRectF bound=classo.controlPointRect();
        int pixTx=bound.topLeft().rx();
        int pixTy=bound.topLeft().ry();
        int height=-bound.topLeft().x()+bound.bottomRight().x();
        int width=-bound.topLeft().y()+bound.bottomRight().y();
        ImageItem* newImageItem=new ImageItem(height,width,ImageItem::Format_ARGB32_Premultiplied);
        qDebug()<<newImageItem->size();
        for(int i=0;i<newImageItem->width();i++){
            for(int y=0;y<newImageItem->height();y++){
                if(classo.contains(QPoint(i,y)+ActiveImage->getPosition()+QPoint(pixTx,pixTy))){
                    newImageItem->setPixelColor(QPoint(i,y),ActiveImage->pixelColor(QPoint(i,y)+ActiveImage->getPosition()+QPoint(pixTx,pixTy)));
                }else{
                    newImageItem->setPixelColor(QPoint(i,y),QColor(254,254,254,0));
                }
            }
        }
        //newImageItem->save("classo.png");
        //load("classo.png");
        ActiveImages->append(newImageItem);
        update();
        lass = false;
    }

    if(wireOn){
        wireDraw=false;
        ShapeItem* shape=new ShapeItem;
        shape->setPath(lastWire);
        shape->setColor(globalColor);
        shape->setPenWidth(globalWidth);
        shape->setShow();
        shape->scale(zoomFactor);
        activeShapeItems->append(shape);
        qDebug()<<shape->path().boundingRect();
        lastWire=QPainterPath();
        wire=QPainterPath();

    }
}

void Canva::mousePressEvent(QMouseEvent *event){
    if(lass && event->buttons()==Qt::LeftButton){
        classo.moveTo(event->pos());
    }
    if(wireOn && event->button() == Qt::LeftButton){
        if (wire.isEmpty()) {
            lastWire.moveTo(event->pos());
        } else{
            lastWire.lineTo(event->pos());
        }
        previousPosition=event->pos();
        wireExist=true;
        wireStart=event->pos();
        wireCurrent=event->pos();
        wire.moveTo(wireStart);
        wireDraw = true;
        previousPosition=event->pos();
        update();
        return;
    }
    if(selectionOn){
        basicLasso->mousePressEvent(event, *this);
        return;
    }
    //    if(needPaint){
    //        previousPosition=event->pos();
    //        return;
    //    }
    if(needPaint){
        //myPencil=solidPen(globalColor, globalWidth);
        penMousePressEvent(event, *this, myPencil);
    }
    if (isNormal&& event->button() == Qt::LeftButton) {
        setCursor(Qt::SizeAllCursor);
        int index = itemAt(event->pos());
        previousPosition=event->pos();
        if (index != -1) {
            itemInMotion=activeShapeItems->at(index);
            update();
        }else{
            itemInMotion=NULL;
            index=imageAt(event->pos());
            if(index!=-1){
                qDebug()<<index;
                imageInMotion=ActiveImages->at(index);
                moveImageTo(event->pos());
            }
        }
    }
    qDebug()<<"mouse Press End";
}

void Canva::mouseMoveEvent(QMouseEvent *event){

    if(lass && event->buttons()==Qt::LeftButton){
        classo.lineTo(event->pos());
        classo.lineTo(event->pos());
        // path.insert(event->pos().x(),event->pos().y());
        update();
        return;
    }

    if(wireOn){
        wireCurrent=event->pos();
        if (wireDraw){
            wire=lastWire;
            wire.moveTo(wireStart);
            wire.lineTo(wireCurrent);
        }
        update();
        return;
    }
    //    update();
    qDebug()<<"Mouse Move Begin";
    if(selectionOn){
        basicLasso->mouseMoveEvent(event, *this);
        return;
    }
    if(needPaint){
        penMouseMoveEvent(event, *this, myPencil);
        return;
    }


    if (isNormal && (event->buttons()== Qt::LeftButton) && itemInMotion){
        moveItemTo(event->pos());
        qDebug()<<"item begin move";
        return;
    }else if(isNormal){
        if((event->buttons()==Qt::LeftButton && imageInMotion)){
            qDebug()<<"Image Move to Begin";
            moveImageTo(event->pos());
            return;
        }
    }

    qDebug()<<"mouse Move End";
}

void Canva::mouseReleaseEvent(QMouseEvent *event){
    if(selectionOn){
        basicLasso->mouseReleaseEvent(event, *this);
        return;
    }
    if(needPaint){
        penMouseReleaseEvent(event, *this, myPencil);
        update();
        return;
    }
    if (isNormal && event->button() == Qt::LeftButton && itemInMotion){
        moveItemTo(event->pos());
        //itemInMotion = 0;
    }else if(isNormal){
        moveImageTo(event->pos());
    }


    qDebug()<<"mouse Release End";
    setCursor(Qt::ArrowCursor);
}


/*
 * showGrid in canva
 * Notic that all shapes will fit to grid points if Gird is on;
 */

void Canva::showGrid(){
    gridOn=!gridOn;
    update();
}

/*
 * save with grid
 * Gird will be saved in the images if saveWithGrid is true
 */
void Canva::saveWithGrid(){
    saveGridOn=!saveGridOn;
}

/*
 * get & set function for zoom
 */
qreal Canva::getZoomFactor(){
    return zoomFactor;
}

/*
 * hide/show layer
 */
void Canva::layerShow(int index){
    qDebug()<<"layer show";
    layers.at(index)->show=!layers.at(index)->show;
    qDebug()<<layers.at(index)->show;
    update();
}

/*
 * active/inactive of layer
 * Notice that only one can be actived
 */
void Canva::layerActive(int index){
    activeLayer=layers[index];
    ActiveImage=activeLayer->images->at(0);
    activeShapeItems=activeLayer->shapes;
    ActiveImages=activeLayer->images;
    imageInMotion=ActiveImage;
}

/*
 * decide the item on which your mouse clicking
 */
int Canva::itemAt(const QPoint &pos){
    for(int i=0;i<activeShapeItems->size();i++){
        ShapeItem* item=activeShapeItems->at(i);
        if(item->path().boundingRect().contains(pos-item->position())){
            emit(ShapeItemOn());
            return i;
        }
    }
    return -1;
}

/*
 * decide the image on which your mouse clicking
 */
int Canva::imageAt(const QPoint &pos){
    for(int i=ActiveImages->size()-1;i>=0;i--){
        ImageItem* item=ActiveImages->at(i);
        if(item->rect().contains(pos-item->getPosition())){
            qDebug()<<"getImage";
            imageInMotion=item;
            emit(ImageItemOn());
            return i;
        }
    }
    return -1;
}

/*
 * move image to position
 */

void Canva::moveItemTo(const QPoint &pos){
    QPoint offset = pos - previousPosition;
    QPoint newPosition=itemInMotion->position() + offset;
    if(gridOn){
        int x=newPosition.x();
        int y=newPosition.y();
        int intZoomFactor=zoomFactor;
        x=x-x%(intZoomFactor*10);
        y=y-y%(intZoomFactor*10);
        newPosition=QPoint(x,y);
    }
    previousPosition=previousPosition+newPosition-itemInMotion->position();
    itemInMotion->setPosition(newPosition);
    update();
}


void Canva::moveImageTo(const QPoint &pos){
    qDebug()<<"image move begin"<<(imageInMotion==NULL);
    if(imageInMotion!=NULL){
        qDebug()<<"image move begin";
        QPoint offset = pos - previousPosition;
        qDebug()<<"Offset"<<offset;
        imageInMotion->moveTo(offset);
        previousPosition = pos;
        if(this->rect().bottomRight().rx()<imageInMotion->rect().bottomRight().rx()+imageInMotion->getPosition().rx()){
            resize(imageInMotion->rect().bottomRight().rx()+imageInMotion->getPosition().rx(),rect().bottomRight().ry());
        }
        if(this->rect().bottomRight().ry()<imageInMotion->rect().bottomRight().ry()+imageInMotion->getPosition().ry()){
            resize(rect().bottomRight().rx(),imageInMotion->rect().bottomRight().ry()+imageInMotion->getPosition().ry());
        }
    }

    update();
    qDebug()<<"Image Move end";
}

/*
 * function for create different shapeitems
 */

void Canva::createShapeItem(shapeType ShapeName)
{
    ShapeItem* shape=new ShapeItem;
    switch (ShapeName) {
    case 0:
        shape->drawAmmeter();
        break;
    case 1:
        shape->drawAndGate();
        break;
    case 2:
        shape->drawBuffer();
        break;
    case 3:
        shape->drawCapacity();
        break;
    case 4:
        shape->drawCopperline();
        break;
    case 5:
        shape->drawCurrentSource();
        break;
    case 6:
        shape->drawDiode();
        break;
    case 7:
        shape->drawGround();
        break;
    case 8:
        shape->drawInductor();
        break;
    case 9:
        shape->drawNandGate();
        break;
    case 10:
        shape->drawNorGate();
        break;
    case 11:
        shape->drawNotGate();
        break;
    case 12:
        shape->drawOrGate();
        break;
    case 13:
        shape->drawResistance();
        break;
    case 14:
        shape->drawTransistor();
        break;
    case 15:
        shape->drawVoltmeter();
        break;
    case 16:
        shape->drawXNORGate();
        break;
    case 17:
        shape->drawXORGate();
        break;
    default:
        break;
    }
    shape->setColor(globalColor);
    shape->setPenWidth(globalWidth);
    qDebug()<<globalColor;
    shape->setShow();
    shape->scale(zoomFactor);
    activeShapeItems->append(shape);
    qDebug()<<"add item";
    update();
}

/*
 * apply different filter activeImage
 */

void Canva::setGrayFilter() { //JWJ
    filterappli = new GrayFilter(this);
    filterappli->setFilter(*this);
}

void Canva::setNegativeFilter() { //JWJ
    filterappli = new NegativeFilter(this);
    filterappli->setFilter(*this);
}
void Canva::setPenColor(QColor color){
    this->globalColor=color;
}

/*
 * set & get method for global pen, color ,width data
 */
void Canva::setPenWidth(int width){
    this->globalWidth=width;
}

QColor Canva::getColor(){
    return globalColor;
}

int Canva::getWidth(){
    return globalWidth;
}

/*
 * zoom item
 * only the item you choose will be zoomed;
 * shape has higher priority than images
 */
void Canva::zoomItem(float factor){
    qDebug()<<(itemInMotion==NULL);
    if(itemInMotion!=NULL){
        itemInMotion->scale(factor);
    }else{
        if(imageInMotion!=NULL){
            if(imageInMotion->getZoomFactor()>=4.0 && factor>1){
                imageInMotion->setZoomFactor(4.0);
                return;
            }else if(imageInMotion->getZoomFactor()<=0.25 && factor<1){
                imageInMotion->setZoomFactor(1.0);
                return;
            }else{
                qDebug()<<"image zoom item";
                *imageInMotion=imageInMotion->transformed(QTransform::fromScale(factor,factor));
                imageInMotion->setZoomFactor(imageInMotion->getZoomFactor()*factor);
            }
        }
    }
    update();
}

/*
 * rotate item
 * only the item you choose will be rotated;
 * shape has higher priority than images
 */
void Canva::rotateItem(float angle){
    if(itemInMotion!=NULL){
        itemInMotion->rotate(angle);
    }else if(imageInMotion!=NULL){
        QTransform rotation;
        rotation.rotate(angle);
        *imageInMotion=imageInMotion->transformed(rotation);
    }
    update();
}

/*
 * delete item
 * only the item you choose will be deleted;
 * shape has higher priority than images
 */
void Canva::deleteItem(){
    if(itemInMotion!=NULL){
        for(int i=0;i<activeShapeItems->size();i++){
            if(itemInMotion==activeShapeItems->at(i)){
                activeShapeItems->removeAt(i);
            }
        }
    }else if(imageInMotion!=NULL){
        for(int i=0;i<ActiveImages->size();i++){
            if(imageInMotion==ActiveImages->at(i)){
                ActiveImages->removeAt(i);
            }
        }
    }
    update();
}
/*
 * copy item
 * only the item you choose will be cpoied;
 * shape has higher priority than images
 */
void Canva::Copy(){
    if(imageInMotion!=NULL){
        QApplication::clipboard()->setImage(*imageInMotion);
    }
}

/*
 * delete item
 * only the item you choose will be pasted;
 * shape has higher priority than images
 */
void Canva::Paste(){
    if(copyImage!=NULL){
        load(*copyImage);
    }
}

/*
 * set mouseevent enviornment
 */
void Canva::setNroaml(){
    isNormal=true;
    selectionOn=false;
    needPaint=false;
    wireOn=false;
    lass=false;
}
void Canva::activeSlection(){
    isNormal=false;
    selectionOn=true;
    needPaint=false;
    wireOn=false;
    lass=false;
}

void Canva::setPaintOn(){
    isNormal=false;
    selectionOn=false;
    needPaint=true;
    wireOn=false;
    lass=false;
}

void Canva::setWireOn(){
    isNormal=false;
    selectionOn=false;
    needPaint=false;
    wireOn=true;
    lass=false;
}

void Canva::lassOn(){
    isNormal=false;
    selectionOn=false;
    needPaint=false;
    wireOn=false;
    lass=true;
    qDebug()<<lass;
}


void Canva::setSolidPencil(){
    myPencil=solidPen(globalColor,globalWidth);
    qDebug()<<"pen";

}

void Canva::setDotPencil(){
    myPencil=dotPen(globalColor,globalWidth);
}
void Canva::setDashPecil(){
    myPencil=dashPen(globalColor,globalWidth);

}
