#ifndef ISAVER_H
#define ISAVER_H
#include "IParser.h"

namespace Metadata {

    class ISaver
    {
    public:
        virtual ~ISaver() {};
        virtual bool save(Track track, std::filesystem::path file) = 0;

    };

    std::unique_ptr<ISaver> createSaver(ParserType type, ParserSpeed speed);
}
#endif // ISAVER_H
