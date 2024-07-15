#include "shapepath.h"

QPainterPath circlepath(){
    QPainterPath  circlePath;
    circlePath.addEllipse(QRect(0, 0, 100, 100));
    return  circlePath;
}
