#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include <QObject>
#include "canva.h"

class Canva;
/*
 * Class: AbstractFilter
 * ---------------------
 * This class defines the root of the AbtractFilter hierarchy. AbstractFilter is
 * an abstract class, which contains methods that can be overridden by its subclasses.
 */

class AbstractFilter : public QObject {

    Q_OBJECT

public:
    explicit AbstractFilter(QObject *parent = 0);
    virtual ~AbstractFilter(){}

    virtual void setFilter(Canva & canva) = 0;


};

#endif // ABSTRACTFILTER_H
