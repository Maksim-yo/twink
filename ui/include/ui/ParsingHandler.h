#ifndef PARSINGHANDLER_H
#define PARSINGHANDLER_H
#include <QObject>
#include "metadata/IParser.h"
#include "include/ui/MusicObject.h"

class ParsingHandler : public QObject
{
    Q_OBJECT
public:
    ParsingHandler(MusicObjectModel*& obj);
public slots:
    void onChangedPath(QString path);
    void onShowPathChanged(bool state);
signals:
    void changedPath(QString path);
private:
    std::vector<Metadata::Track> proccess(std::filesystem::path directory);
    void converter(std::vector<Metadata::Track> tracks);
    MusicObjectModel*& model;
    std::filesystem::path path;
    bool path_state;
};

#endif // PARSINGHANDLER_H
