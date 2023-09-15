#ifndef METADATAPAGEHANDLER_H
#define METADATAPAGEHANDLER_H

#include <QObject>
#include <QVariant>


namespace UI {

    class Validator {

    public:
        friend class MetadataPageHandler;

        Validator(int indx);
        int getIndex();
        QString validate(QString message, QString item_type);
        bool isValid();
    private:
        QVector<QString> unvalidatedItems{};
        int index;
    };
    class MetadataPageHandler: public QObject {

        Q_OBJECT

    public:
        MetadataPageHandler() {};
    public slots:

        bool onSaved(QVariant itm);
        QString onEdited(QString message, QString item_type, int index);

    private:
        Validator validator{0};

    };
}
#endif // METADATAPAGEHANDLER_H
