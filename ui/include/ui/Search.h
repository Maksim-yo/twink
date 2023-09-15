#ifndef SEARCH_H
#define SEARCH_H
#include <QThread>
#include "include/ui/MusicObject.h"


namespace UI{
class Search: public QObject
{
    Q_OBJECT

public:

    Search(const QVector<MusicItem> init_data);
public slots:
    void onMessage(int c, QString message);
    void updateData(QVector<MusicItem> new_data);
signals:
    void send(QVector<MusicItem> data);
private:
    QVector<MusicItem> init_data;

};
}
#endif // SEARCH_H
