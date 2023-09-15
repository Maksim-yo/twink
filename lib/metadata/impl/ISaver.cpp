#include "metadata/ISaver.h"
#include "metadata/TagLib.h"


namespace Metadata {

    std::unique_ptr<ISaver> createSaver(ParserType type, ParserSpeed speed){

        switch(type){

            case ParserType::Taglib:
                return std::make_unique<TaglibSaver>(speed);
            default:
                return {};
        }
    }
}
