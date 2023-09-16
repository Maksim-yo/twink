#ifndef IPARSER_H
#define IPARSER_H


#include <filesystem>
#include <QString>
#include <QDateTime>
#include <optional>
#include <vector>
#include <QByteArray>


namespace Metadata {



    struct Artist {

      friend bool operator==(const Artist &artist, const Artist &other){
        return artist.name== other.name;
      }

      QString name;

    };

    enum SupportedTypes{

        MP4,
        MPEG,
        FLAC,
        UNDEFINED,
    };


    struct Image {

        QByteArray* data{nullptr};
        QString mimeType;
    };

    struct Album {

        QString title;
    };


    struct Track{

        qint64 duration;
        QString title;
        qint64 bitrate;
        qint64 sampleRate;
        qint64 channels;
        QDateTime date;
        Album album;
        std::vector<Artist> artists{};
        std::optional<Image> image;
        QString path;
    };

    enum ParserSpeed{

        Fast,
        Average,
        Low
    };

    enum ParserType{

        Taglib
    };


    static SupportedTypes convertType(const QString& type) {

        if( type == "mp3")
            return MPEG;
        if ( type == "mp4")
            return MP4;
        if (type == "flac")
            return FLAC;
        return UNDEFINED;

    }



    static ParserSpeed convertParserSpeed(const QString& type) {

        if( type == "Fast")
            return Fast;
        if(type == "Low")
            return Low;
        return Average;

    }

    QString getMimyType(const std::string& str);
    bool validateMimeType(const std::string& str);

    class IParser {

    public:
        virtual ~IParser() {}
        virtual std::optional<Track> parse(std::filesystem::path file) = 0;
        virtual void processTag(Track& track, std::string tag, std::vector<std::string> values) = 0;

    };


    std::unique_ptr<IParser> createParser(ParserType type, ParserSpeed speed);
}

#endif
