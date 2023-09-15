#include <map>

#include "metadata/TagLib.h"
#include "utils/Log.h"
#include "utils/Services.h"
#include "utils/Utils.h"

#include <taglib/apetag.h>
#include <taglib/asffile.h>
#include <taglib/fileref.h>
#include <taglib/flacfile.h>
#include <taglib/mp4file.h>
#include <taglib/mpcfile.h>
#include <taglib/mpegfile.h>
#include <taglib/opusfile.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>
#include <taglib/vorbisfile.h>
#include <taglib/wavpackfile.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/id3v2tag.h>

namespace Metadata {

using namespace TagLib;

    using TagMap = std::map<std::string, std::vector<std::string>>;

    TagMap
    constructTagMap(const TagLib::PropertyMap& properties)
    {
        TagMap tagMap;

        for (const auto& [propertyName, propertyValues] : properties)
        {
            std::vector<std::string>& values {tagMap[propertyName.upper().to8Bit(true)]};
            for (const TagLib::String& propertyValue : propertyValues)
            {
                std::string trimedValue {(propertyValue.to8Bit(true))};
                values.emplace_back(std::move(trimedValue));
            }
        }

        return tagMap;
    }


    QString convertMP4Format(TagLib::MP4::CoverArt::Format format){

        switch (format) {


        case TagLib::MP4::CoverArt::PNG:
            return "png";
        case TagLib::MP4::CoverArt::JPEG:
            return "jpeg";
        case TagLib::MP4::CoverArt::GIF:
            return "gif";
        case TagLib::MP4::CoverArt::BMP:
            return "bmp";
        default:
            return "";

        }

    }
    static void mergeTagMaps(TagMap& dst, TagMap&& src)
    {
        for (auto&& [tag, values] : src)
        {
            if (dst.find(tag) == std::cend(dst))
                dst[tag] = std::move(values);
        }
    }

    //RVO
    static TagLib::String convertString(QString string) {


        return {string.toStdString()};
    }

    static TagLib::StringList convertStringList(std::vector<QString> data){

        TagLib::StringList res;
        for(const QString& elm: data)
            res.append(convertString(elm));
        return res;
    }

    static TagLib::ByteVector convertByteVector(QByteArray* data){

        return TagLib::ByteVector::fromCString(data->data(),data->size());
    }



    std::vector<std::string> getFirstMatch(const TagMap& tags, std::initializer_list<std::string> keys){

        std::vector<std::string> res;
        for (std::string key : keys){

            const auto it{tags.find(key)};
            if (it == std::cend(tags))
                continue;

            if (it->second.empty())
                continue;

            for (auto& elm : it->second){


                res.emplace_back(std::move(elm));
            }
            break;
        }

        return res;

    }

    std::vector<Artist> getArtists(const TagMap& map, std::initializer_list<std::string> artistTagNames){

        std::vector<Artist> res;

        const auto artistNames{getFirstMatch(map, artistTagNames)};

          std::transform(artistNames.cbegin(), artistNames.cend(), std::back_inserter(res), [&](std::string name) {
              qDebug() << "Artist: " << name.c_str();
              return Artist{QString(name.c_str())};});


        return res;

    }
    
    bool isImageSupported(QString mimeType){
        
        return mimeType == "jpeg" || mimeType == "png" || mimeType == "jpg";
    }

    void getImage(TagLib::ByteVector img_data, QString format, Track& track){

        Image track_img;
        track_img.data = new QByteArray(img_data.data(), img_data.size());
        track_img.mimeType = format;


        if (!validateMimeType(track_img.mimeType.toStdString())) {
            qDebug() << "Cannot get image. Incorrect image type:" << track_img.mimeType.toStdString().c_str();
            return;
        }
        track.image = track_img;

        return;


    }

    std::optional<Track> TaglibParser::parse(std::filesystem::path path)
    {

        LOG(DEBUG) << "WHY YOU ARE NOT WORKING";
        QString mimeType = Utils::getExtension(path).c_str();
        if(Metadata::convertType(mimeType) == Metadata::UNDEFINED )
            return std::nullopt;

        TagLib::FileRef file  = TagLib::FileRef(path.c_str(), true, parsingSpeed);
        if(file.isNull())
            return std::nullopt;

        const auto audio_properties = file.audioProperties();
        if(!audio_properties)
            return std::nullopt;

        Track track;
        track.bitrate = audio_properties->bitrate();
        track.sampleRate = audio_properties->sampleRate();
        track.channels = audio_properties->channels();
        track.duration = audio_properties->lengthInSeconds();
        track.path = path.make_preferred().string().c_str();
        auto properties = constructTagMap(file.file()->properties());


        auto getAPETags = [&](const TagLib::APE::Tag* apeTag)
        {
            if (!apeTag)
                return;

            mergeTagMaps(properties, constructTagMap(apeTag->properties()));
        };



        if (TagLib::MPEG::File* mp3File {dynamic_cast<TagLib::MPEG::File*>(file.file())}){

            if (mp3File->ID3v2Tag())
            {
                const auto& frameListMap {mp3File->ID3v2Tag()->frameListMap()};

                if (!frameListMap["APIC"].isEmpty()){
                    TagLib::ID3v2::AttachedPictureFrame* _img = (TagLib::ID3v2::AttachedPictureFrame*)(frameListMap["APIC"].front());

                    getImage(_img->picture(), _img->mimeType().toCString(), track);
                }
            }
            getAPETags(mp3File->APETag());
        }


        else if (TagLib::MP4::File* mp4File {dynamic_cast<TagLib::MP4::File*>(file.file())})
        {
            auto& coverItem {mp4File->tag()->itemMap()["covr"]};
            TagLib::MP4::CoverArtList coverArtList {coverItem.toCoverArtList()};

            if (!coverArtList.isEmpty()) {
                auto _img = coverArtList.front();
                getImage(_img.data(), convertMP4Format(_img.format()),track);
            }
        }

        else if (TagLib::FLAC::File* flacFile {dynamic_cast<TagLib::FLAC::File*>(file.file())})
        {
            if (!flacFile->pictureList().isEmpty()){
                auto _img = flacFile->pictureList().front();
                getImage(_img->data(), _img->mimeType().toCString(), track);
            }
        }
        track.artists = getArtists(properties, {"ARTISTS", "ARTIST"});

        for (auto[tag, values] : properties){

            if (!values.empty())
                processTag(track, tag, values);
        }

        return track;
    }


    void TaglibParser::processTag(Track& track, std::string tag, std::vector<std::string> values)
    {

        QString value{values.front().c_str()};

        if (tag == "TITLE")
            track.title = value;
        else if (tag == "DATE")
            track.date = QDateTime::fromString(value);
        else if (tag == "YEAR" && !track.date.isValid())
            track.date = QDateTime::fromString(value);
        else if (tag == "ORIGINALDATE")
            track.date = QDateTime::fromString(value);
        else if (tag == "ORIGINALYEAR" && !track.date.isValid())
            track.date = QDateTime::fromString(value);
        else if (tag == "ALBUM")
            track.album.title = value;

    }

    static
    TagLib::AudioProperties::ReadStyle
    ParserSpeedToTagLibReadStyle(ParserSpeed readStyle)
    {
        switch (readStyle)
        {
            case ParserSpeed::Fast: return TagLib::AudioProperties::ReadStyle::Fast;
            case ParserSpeed::Average: return TagLib::AudioProperties::ReadStyle::Average;
            case ParserSpeed::Low: return TagLib::AudioProperties::ReadStyle::Accurate;
            default:
                throw std::runtime_error("unsupported read style");
        }
    }

    TaglibParser::TaglibParser(ParserSpeed speed)
    {
        parsingSpeed = ParserSpeedToTagLibReadStyle(speed);
    }

    TaglibSaver::TaglibSaver(ParserSpeed speed)
    {
        _parser = TaglibParser(speed);
        parsingSpeed = ParserSpeedToTagLibReadStyle(speed);
    }


    // TODO: Add support for MP4
    bool TaglibSaver::save(Track track, std::filesystem::path path)
    {

        std::optional<Track> track_src = _parser.parse(path);

        if (!track_src.has_value())
            return false;

        TagLib::FileRef file  = TagLib::FileRef(path.c_str(), true, parsingSpeed);
        if(file.isNull())
            return false;

        TagLib::File* _file = file.file();
        auto properties = _file->properties();

        auto artistReplace = [&track, &properties]()->bool{
            TagLib::StringList data;
            std::for_each(track.artists.begin(), track.artists.end(),[&data](Artist artist){
                qDebug() << "Aritst: " << artist.name;
                data.append(convertString(artist.name));});
                return properties.replace("ARTISTS", data);
        };

        auto createImageMPEG = [&track](QByteArray* image, QString mimeType)->TagLib::ID3v2::Frame*{

            if (!isImageSupported(getMimyType(track.image->mimeType.toStdString()))) {

                qDebug() << "Couldn't load image. Unsuported image type: " << track.image->mimeType.toStdString().c_str();
                return nullptr;
            }

            auto img = new TagLib::ID3v2::AttachedPictureFrame();
            img->setPicture(convertByteVector(image));
            img->setMimeType(convertString(mimeType));
            img->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);

            return img;
        };

        if(track_src->title != track.title)
            properties.replace("TITLE", convertString(track.title));
        if(track_src->album.title != track.album.title)
            properties.replace("ALBUM", convertString(track.album.title));

        if(track_src->artists != track.artists) {

            bool res = artistReplace();
            if (res == false)
                return false;
        }
        
        if (TagLib::MPEG::File* mp3File {dynamic_cast<TagLib::MPEG::File*>(file.file())}){


            qDebug() << "Is image: " << track.image.has_value();
                if (mp3File->ID3v2Tag() && track.image.has_value())
                {
                    auto tag = mp3File->ID3v2Tag();
                    auto frame = createImageMPEG(track.image->data, track.image->mimeType);
                    if (frame != nullptr) {
                        tag->removeFrames("APIC");
                        tag->addFrame(frame);
                    }
                }

                auto res = mp3File->setProperties(properties);
                if (res.size() > 0)
                    return false;
                if (!mp3File->save())
                    return false;
        }
        else if (TagLib::FLAC::File* flacFile {dynamic_cast<TagLib::FLAC::File*>(file.file())}) {

            flacFile->removePictures();
            TagLib::FLAC::Picture* _img = new TagLib::FLAC::Picture(convertByteVector(track.image->data));
            _img->setMimeType(convertString(track.image->mimeType));
            flacFile->addPicture(_img);

        }

        return true;
    }
}
