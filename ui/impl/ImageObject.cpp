#include "include/ui/ImageObject.h"
#include <QtDebug>

ImageObject::ImageObject(std::unique_ptr<Image::Image> img): img(std::move(img)) { }

void ImageObject::resize(QSize size)
{
    img->resize(size);
    emit dataChanged();
    emit base64Changed();
}

QSize ImageObject::getSize()
{
    return img->getSize();
}

bool ImageObject::isNull()
{
    return img->isNull();
}

QImage& ImageObject::get()
{
    return img->get();
}

Image::Image* ImageObject::getImg()
{
    return img.get();
}

Image::Type ImageObject::type()
{
    return img->type();
}

bool ImageObject::isValid() const
{
    return img->isValid();
}

QByteArray* ImageObject::data() const
{
    auto res = Image::encodeImage(img.get());
    Q_ASSERT(res->size() > 0);
    return res;
}

QString ImageObject::base64() const
{
    return data()->toBase64();
}

