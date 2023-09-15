#include "include/ui/Search.h"
#include "utils/Services.h"
#include <QTimer>
#include <QDebug>

namespace UI {

    Search::Search( const QVector<MusicItem> init_data): init_data(init_data)
    {

    }

    void Search::updateData(QVector<MusicItem> new_data)
    {
        init_data = new_data;
    }

    void Search::onMessage(int c, QString message)
    {

        if (message == "") {
            for(MusicItem item : init_data)
                item.setVisible(true);
             emit send(init_data);
        }
        for(MusicItem& item : init_data){

            if (item.title().get_data().toLower().contains(message.toLower()) || item.pretiffyArtists().toLower().contains(message.toLower()))
                item.setVisible(true);
            else
                item.setVisible(false);

        }

        emit send(init_data);
    }
}
