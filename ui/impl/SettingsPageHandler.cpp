#include "include/ui/SettingsPageHandler.h"
#include "include/ui/Settings.h"
#include "metadata/IParser.h"
#include "utils/Services.h"
#include "utils/QtLogger.h"


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
        QString value = settings->value(key, "Average").toString();
        if(key == "parsingSpeed"){
            Metadata::ParserSpeed speed = Metadata::convertParserSpeed(value);
            Service<Metadata::IParser>::reset(Metadata::createParser(Metadata::ParserType::Taglib, speed));

            LOG(DEBUG) << "Setting " << key.toStdString() << " to " << value.toStdString();
        }
    }
}
