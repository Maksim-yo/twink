#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H
#include <QObject>
#include "utils/Image.h"

class ImageObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QByteArray* data READ data NOTIFY dataChanged)
    Q_PROPERTY(QString base64 READ base64 NOTIFY base64Changed)

public:
    ImageObject(const ImageObject&) = delete;
    ImageObject& operator=(const ImageObject&) = delete;
    ImageObject(std::unique_ptr<Image::Image> img);
    void        resize(QSize);
    QSize       getSize();
    bool        isNull();
    QImage&     get();
    Image::Image* getImg();
    Image::Type type();
    bool        isValid() const;
    QByteArray* data() const;
    QString     base64() const;

signals:

    void dataChanged();
    void base64Changed();

private:
    std::unique_ptr<Image::Image> img;

};

#endif // IMAGEOBJECT_H
