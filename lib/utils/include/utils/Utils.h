#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <filesystem>
namespace Utils {
    QString convertTime(int time);
    // FORMAT: mins:sec
    int     convertTime(QString str);
    std::string getExtension(std::filesystem::path filename);
    std::string stringTrim(std::string_view str, std::string_view whitespaces);

}
#endif // UTILS_H
