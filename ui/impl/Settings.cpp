#include "include/ui/Settings.h"


namespace UI {

    Settings::Settings(QObject* parent) :
      QSettings(parent) {
    }

    Settings::~Settings() {
    }

    QVariant Settings::value(const QString &key, const QVariant &defaultValue = QVariant()) {
      return QSettings::value(key, defaultValue);
    }

    bool Settings::boolValue(const QString &key, bool defaultValue) {
      return QSettings::value(key, defaultValue).toBool();
    }

    void Settings::setValue(const QString &key, const QVariant &value) {

      QSettings::setValue(key, value);
      emit settingChanged(key);
    }

    void Settings::setValueIfNotSet(const QString &key, const QVariant &value) {

      if( !QSettings::contains(key) ) {
        QSettings::setValue(key, value);
        emit settingChanged(key);
      }
    }
}
