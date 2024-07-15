#include "grayfilter.h"
#include "canva.h"

/* Implementation of constructor */
GrayFilter::GrayFilter(QObject *parent) : AbstractFilter(parent) {

}

/* Implementation: setFilter
 * -------------------------
 * This method realize the gray filter by considering RGB of each pixel,
 * and calculate a new rgb, to show the gray scale of each pixel
 */

void GrayFilter::setFilter(Canva & canva) {
    for (int x = 0; x < canva.getImage()->width(); x++) {
        for (int y = 0; y < canva.getImage()->height(); y++) {
            QRgb pixel = canva.getImage()->pixel(x, y);
            int rgb = (0.3 * qRed(pixel) + 0.6 * qGreen(pixel) + 0.1 * qBlue(pixel));
            pixel = qRgb(rgb, rgb, rgb);
            canva.getImage()->setPixel(x, y, pixel);
        }
    }
    canva.update();
}
