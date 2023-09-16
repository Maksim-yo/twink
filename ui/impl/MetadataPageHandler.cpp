#include <QRegularExpressionValidator>

#include "include/ui/MetadataPageHandler.h"
#include "include/ui/MusicObject.h"
#include "metadata/ISaver.h"
#include "utils/Services.h"
#include "utils/QtLogger.h"
#include "utils/Utils.h"

namespace UI {

    const std::string_view album_name = "album_name";
    const std::string_view track_year = "track_year";
    const std::string_view  artist_name = "artist_name";
    const std::string_view track_title = "track_title";


    Validator::Validator(int indx): index(indx) { }

    int Validator::getIndex()
    {
        return index;
    }

    QString Validator::validate(QString message, QString item_type)
    {
        QRegularExpression rx;
        std::string item_name = item_type.toStdString();
        int pos = 0;
        if (item_name == track_year){

            rx = QRegularExpression(R"(\d+|^\s*$)");
        }
        else {
            rx = QRegularExpression(R"([\p{L}\(\)\.\,\ \d]+|^\s*$)");
        }

        QRegularExpressionValidator v(rx);
        auto res = v.validate(message, pos);
        if (res == QValidator::Acceptable) {
            if (unvalidatedItems.contains(item_type)) {
                bool res = unvalidatedItems.removeOne(item_type);
                Q_ASSERT(res == true);
            }
            return {};
        }

        if (!unvalidatedItems.contains(item_type))
        {
            unvalidatedItems.emplaceBack(item_type);
        }
        return "Unsuported symbols";
    }

    bool Validator::isValid()
    {
        return !(unvalidatedItems.size() > 0);
    }

    bool MetadataPageHandler::onSaved(QVariant itm)
    {
        if (!validator.isValid()) {
            LOG(DEBUG) << "Couldn't save data because data is not valid";
            return false;
        }
        MusicItem item = itm.value<MusicItem>();
        Metadata::Track track;
        Metadata::Image image;

        auto img_data = Image::encodeImage(item.image()->getImg());
        if (img_data != nullptr && item.image()->isValid()){


            image.data = img_data;
            image.mimeType = "image/jpeg";
            track.image = image;
        }
        else
            LOG(DEBUG) << "Image is not valid";

        track.title = item.title().isDefault() ? "" : item.title().get_data();
        track.duration = Utils::convertTime(item.duration().get_data());
        track.album.title = item.album().album().isDefault() ? "" : item.album().album().get_data();

        track.path = item.path();

        QVector<QString> artists = item.artist();

        std::transform(artists.begin(), artists.end(), std::back_inserter(track.artists), [](QString artist){return Metadata::Artist{artist};} );
        bool res = Service<Metadata::ISaver>::get()->save(track, track.path.toStdString());


        LOG(DEBUG) << "Saving file..." << (res ? "Success" : "Failure");
        return true;

    }

    QString MetadataPageHandler::onEdited(QString message, QString item_type, int index)
    {
//        qDebug() << message;
        if (index != validator.getIndex())
            validator = Validator(index);

        QString err_msg = validator.validate(message,item_type);
        return err_msg;

    }



}
