#ifndef NEGATIVEFILTER_H
#define NEGATIVEFILTER_H

#include "abstractfilter.h"
#include <QObject>

/*
 * Subclasses: NegativeFilter
 * --------------------------
 * This class can be used to paint an obtained image processed by
 * negtive filter.
 */

class NegativeFilter : public AbstractFilter {

    Q_OBJECT

public:
    NegativeFilter(QObject *parent = 0);
    void setFilter(Canva & canva);

};


#endif // NEGATIVEFILTER_H
