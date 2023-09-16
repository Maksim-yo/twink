#include <QUrl>

#include "include/ui/ParsingHandler.h"
#include "utils/Services.h"
#include "utils/QtLogger.h"
#include "utils/Utils.h"
#include "metadata/ISaver.h"
ParsingHandler::ParsingHandler(MusicObjectModel*& obj) : model(obj)
{
    connect(this, &ParsingHandler::changedPath, this, &ParsingHandler::onChangedPath);
}

void ParsingHandler::onChangedPath(QString path)
{
    model->clear();
    QString resolve_path = QUrl(path).isLocalFile() == true ? QUrl(path).toLocalFile() : path;
    std::vector<Metadata::Track> tracks = proccess(resolve_path.toStdString());
    converter(tracks);
}

void ParsingHandler::onShowPathChanged(bool state)
{
    qDebug() << "onShowPathChanged " << state;
    path_state = state;
}

std::vector<Metadata::Track> ParsingHandler::proccess(std::filesystem::path directory)  {

    std::vector<Metadata::Track> tracks;

    for (const auto& file : std::filesystem::recursive_directory_iterator(directory)){

        if (file.is_directory())
            continue;

        if (Metadata::convertType(Utils::getExtension(file.path()).c_str()) == Metadata::SupportedTypes::UNDEFINED)
            continue;

        auto track = Service<Metadata::IParser>::get()->parse(std::filesystem::canonical(file));
        LOG(DEBUG) << "Parsing file: " << track->path.toStdString() << "..." << (track.has_value() ? "Success" : "Failure");;
        if(track.has_value())
            tracks.emplace_back(track.value());

    }

    return tracks;
}

void ParsingHandler::converter(std::vector<Metadata::Track> tracks) {


    for(auto& track: tracks){

        MusicItem item;
        AlbumItem album;
        album.setAlbum(track.album.title);
        item.setYear(track.date.toString());
        item.setAlbum(album);
        item.setDuration(Utils::convertTime(track.duration));

        item.setTitle(track.title);
        item.setPath(track.path);
        item.setPath(path_state);

        Metadata::Image image;
        if (track.image.has_value() && track.image->data) {

            std::unique_ptr<Image::Image> image;
            image = Image::decodeImage(track.image.value().data, Image::convertString(track.image->mimeType));
            if (image && image->isValid()) {
                auto image_heap = new ImageObject(std::move(image));
                item.setImage(std::move(image_heap));
            }
        }


        QVector<QString> _artists;
        std::transform(track.artists.begin(), track.artists.end(), std::back_inserter(_artists), [](Metadata::Artist artist){return artist.name;});
        item.setArtist(_artists);

        model->addItem(item);
    }
    emit model->modelChanged(model->getList());
    emit model->modelUpdate();
}
