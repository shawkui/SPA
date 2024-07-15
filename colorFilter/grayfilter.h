#ifndef GRAYFILTER_H
#define GRAYFILTER_H

#include "abstractfilter.h"
#include <QObject>

/*
 * Subclasses: GrayFilter
 * --------------------------
 * This class can be used to paint an obtained image processed by
 * gray filter.
 */

class GrayFilter : public AbstractFilter {

    Q_OBJECT

public:
    GrayFilter(QObject *parent = 0);
    void setFilter(Canva & canva);

};

#endif // GRAYFILTER_H
