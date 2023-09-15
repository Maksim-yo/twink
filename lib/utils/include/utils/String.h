#ifndef STRING_H
#define STRING_H
#include <QString>

// TODO: implement explicit cast converstation between QString and String
namespace Utils {

    class String: private QString {

    public:

        String() = delete;
        String(std::string_view str);
        String(const char* str);

        String(const QString& str);
        String(QString&& str);
        QString& operator=(const QString& str);
        QString& operator=(QString&& str);

        String(const String& str);
        String(String&& str);
        String& operator=(const String& str);
        String& operator=(String&& str);

        bool isDefault();

        std::string_view get_default() const;

        QString get_data() const;

        friend bool operator== (const String& str1, const String& str2);

        friend bool operator!= (const String& str1, const String& str2);

        friend bool operator> (const String& str1, const String& str2);

        friend bool operator< (const String& str1, const String& str2);

        friend bool operator<= (const String& str1, const String& str2);

        friend bool operator>= (const String& str1, const String& str2);

        QString& operator+= (const QString& str);

    private:
        QString data;
        std::string_view default_data;

    };
}
#endif // STRING_H
