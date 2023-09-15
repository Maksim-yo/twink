#include "metadata/IParser.h"
#include "metadata/TagLib.h"

namespace Metadata {

    std::unique_ptr<IParser> createParser(ParserType type, ParserSpeed speed){

        switch(type){

            case ParserType::Taglib:
                return std::make_unique<TaglibParser>(speed);
            default:
                return {};
        }
    }

    // Format: type/png
    QString getMimyType(const std::string& str){

        auto _start = std::find(str.cbegin(),str.cend(), '/');
        return QString(std::string(_start + 1, str.cend()).c_str());
    }

    // Format: type/png
    bool validateMimeType(const std::string &str)
    {
        auto _start = std::find(str.cbegin(),str.cend(), '/');
        if (_start == str.end())
            return false;
        return true;
    }

}
