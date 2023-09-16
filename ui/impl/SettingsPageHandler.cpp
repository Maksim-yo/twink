#include "include/ui/SettingsPageHandler.h"
#include "include/ui/Settings.h"
#include "metadata/IParser.h"
#include "utils/Services.h"
#include "utils/QtLogger.h"
#include "include/ui/MusicObject.h"



namespace UI{


    SettingsPageHanlder::SettingsPageHanlder(UI::Settings*& _settings): settings(_settings) {

        connect(settings, &UI::Settings::settingChanged, this, &SettingsPageHanlder::handleChange);
    }

    Settings& SettingsPageHanlder::get()
    {
        return *settings;
    }

    void SettingsPageHanlder::handleChange(const QString& key){

        LOG(DEBUG) << "Changing settings...";
        if(key == "parsingSpeed"){
            QString value = settings->value(key, "Average").toString();
            Metadata::ParserSpeed speed = Metadata::convertParserSpeed(value);
            Service<Metadata::IParser>::reset(Metadata::createParser(Metadata::ParserType::Taglib, speed));

            LOG(DEBUG) << "Setting " << key.toStdString() << " to " << value.toStdString();
        }
        if (key == "showPath")
        {
            setShowPath();
        }
    }

    void SettingsPageHanlder::setShowPath(){

        bool show_path_state = settings->value("showPath", Qt::Unchecked) == Qt::Unchecked ? false : true;
        qDebug() << "sfdaf "  << show_path_state;
        MusicObjectModel* model = Service<MusicObjectModel>::get();
        model->modifyData([show_path_state](MusicItem& item) {item.setPath(show_path_state);});
        emit pathShowChanged(show_path_state);

    }
}
