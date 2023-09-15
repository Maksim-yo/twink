#include "utils/String.h"

namespace Utils {

    String::String(std::string_view str) {
        default_data = str;
        data = QString(std::string(str.begin(), str.end()).c_str());
    }
    String::String(const char* str) {
        default_data = str;
        data = str;

    }

    String::String(const QString& str){data = str;}
    String::String(QString&& str){data = str;}
    QString& String::operator=(const QString& str) { data = str; return data;}
    QString& String::operator=(QString&& str) { data = str; return data;}


    String::String(const String& str){
        data = str.get_data();
        default_data = str.get_default();
    }
    String::String(String&& str){
        data = str.get_data();
        default_data = str.get_default();
    }
    String& String::operator=(const String& str) {
        data = str.get_data();
        default_data = str.get_default();
        return *this;
    }
    String& String::operator=(String&& str) {
        data = str.get_data();

        return *this;
    }

    bool String::isDefault(){ return data == default_data.data();}

    std::string_view String::get_default() const {return default_data;}

    QString String::get_data() const {return data ==  default_data.data() ? default_data.data() : data ;}


    QString& String::operator+= (const QString& str) {

        data += str;
        return *this;
    }

    bool operator== (const String& str1, const String& str2)
    {
        return str1.data == str2.data;
    }

    bool operator!= (const String& str1, const String& str2)
    {
        return str1.data != str2.data;
    }

    bool operator> (const String& str1, const String& str2)
    {
        return str1.data > str2.data;
    }

    bool operator< (const String& str1, const String& str2)
    {
        return str1.data < str2.data;
    }

    bool operator<= (const String& str1, const String& str2)
    {
        return str1.data <= str2.data;
    }

    bool operator>= (const String& str1, const String& str2)
    {
        return str1.data >= str2.data;
    }
}
