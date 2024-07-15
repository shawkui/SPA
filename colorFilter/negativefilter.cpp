#include "negativefilter.h"
#include "canva.h"

/* Implementation of constructor */
NegativeFilter::NegativeFilter(QObject *parent) : AbstractFilter(parent) {

}

/* Implementation: setFilter
 * -------------------------
 * This method realize the negative filter by reverse all pixels
 * of the image.
 */
void NegativeFilter::setFilter(Canva & canva) {
    canva.getImage()->invertPixels(QImage::InvertRgb);
    canva.update();
}
