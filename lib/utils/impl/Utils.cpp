#include <stdexcept>
#include "utils/Utils.h"

namespace Utils {

    QString convertTime(int time){

       int sec =  time % 60;

       int mins = time / 60;

       QString secs = QString("%1").arg(sec, 2, 'g', -1, '0');
       return QString("%1").arg(mins) + ":" + secs;

    }

    // TODO: REIMPLEMENT
    int convertTime(QString str) {

        std::string temp = str.toStdString();
        auto it = std::find(temp.begin(), temp.end(), ':' );
        if (it == temp.end() || std::distance(temp.begin(), it) <= 0 || std::distance(it + 1, temp.end()) != 2)
            throw std::runtime_error("Incorrect format");
        int mins = QString(std::string(temp.begin(), it).c_str()).toInt();
        int secs = QString(std::string(it+ 1, temp.end()).c_str()).toInt();
        return mins * 60 + secs;


    }

    std::string getExtension(std::filesystem::path filename){

        filename = filename.filename();
        std::string str = filename.string();
        auto start = std::find(str.rbegin(), str.rend(), '.');
        if(start == str.rend())
            return "";
        return std::string(start.base() , str.end());
    }


    std::string stringTrim(std::string_view str, std::string_view whitespaces)
    {
        std::string_view res;

        const auto strBegin = str.find_first_not_of(whitespaces);
        if (strBegin != std::string_view::npos)
        {
            const auto strEnd {str.find_last_not_of(whitespaces)};
            const auto strRange {strEnd - strBegin + 1};

            res = str.substr(strBegin, strRange);
        }

        return std::string(res);
    }


}
