#ifndef _TAGLIB_H
#define _TAGLIB_H

#include <taglib/audioproperties.h>
#include "metadata/IParser.h"
#include "metadata/ISaver.h"

namespace Database::Model{

    class Track;
}

namespace Metadata {

    class TaglibParser: public IParser {

    public:
          TaglibParser(ParserSpeed speed);
          std::optional<Track> parse(std::filesystem::path file) override;

    private:
          void processTag(Track& track, std::string tag, std::vector<std::string> values) override;
          TagLib::AudioProperties::ReadStyle parsingSpeed;
        };

    class TaglibSaver: public ISaver {

      public:
        TaglibSaver(ParserSpeed speed);
        // TODO: reimplement
        bool save(Track track, std::filesystem::path) override;
    private:
        TagLib::AudioProperties::ReadStyle parsingSpeed;
        TaglibParser _parser{ParserSpeed::Average};

    };
}

#endif
