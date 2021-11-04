#include "qcustomgraphicseffect.h"

void QCustomGraphicsEffect::draw(QPainter *t_painter)
{
    QImage image;
    image = sourcePixmap().toImage();
    image = image.convertToFormat(QImage::Format_Grayscale8);
    for (int i = 0; i < image.sizeInBytes(); ++i)
        image.bits()[i] = image.bits()[i] < 100 ? 0 : 255;
    t_painter->drawPixmap(0, 0, QPixmap::fromImage(image));
}
