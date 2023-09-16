#ifndef SETTINGSPAGEHANDLER_H
#define SETTINGSPAGEHANDLER_H

#include <QObject>

namespace UI{

    class Settings;

    class SettingsPageHanlder: public QObject{

        Q_OBJECT
    public:
        SettingsPageHanlder(UI::Settings*& _settings);
        void setShowPath();
        Q_INVOKABLE
        UI::Settings& get();

    private slots:
        void handleChange(const QString& key);
    signals:
        void pathShowChanged(bool state);

    private:
        UI::Settings* settings;

    };
}
#endif // SETTINGSPAGEHANDLER_H
