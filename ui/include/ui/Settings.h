#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>

namespace UI {

    class Settings : public QSettings {
      Q_OBJECT
    public:
      Settings(QObject *parent = 0);
      virtual ~Settings();

      Q_INVOKABLE
      void setValue(const QString &key, const QVariant &value);

      Q_INVOKABLE
      void setValueIfNotSet(const QString &key, const QVariant &value);

      Q_INVOKABLE
      QVariant value(const QString &key, const QVariant &defaultValue);

      Q_INVOKABLE
      bool boolValue(const QString &key, const bool defaultValue);


    signals:
      void settingChanged(const QString& key);
    };


}
#endif // SETTINGS_H
