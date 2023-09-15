#include <QTest>
#include <QObject>

#include "utils/String.h"

class StringUtils: public QObject {


    Q_OBJECT

private slots:
    // TODO: ADD TESTS WITH MOVE AND COPY OPERATORS OF UTILS::STRING
    void string_test(){

        Utils::String str = Utils::String("hllo");
        str = QString("Hello");
        Utils::String str2 = Utils::String("test");
        Utils::String str3 = Utils::String("");
        str3 = QString("");

        Q_ASSERT(str3.isDefault() == true);
        Q_ASSERT(str3.get_data() == "");
        Q_ASSERT(str3.get_default() == "");
        Q_ASSERT(str2.isDefault() == true);
        Q_ASSERT(str2.get_default() == "test");
        Q_ASSERT(str2.get_data()== "test");
        Q_ASSERT(str.isDefault() == false);
        Q_ASSERT(str.get_default() == "hllo");
        Q_ASSERT(str.get_data()== "Hello");

    }
};

QTEST_MAIN(StringUtils)
#include "string_test.moc"
