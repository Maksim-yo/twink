#include "utils/Utils.h"
#include <QTest>
#include <QObject>


class TestUtils: public QObject {

    Q_OBJECT

private slots:
    void convertTime(){

        QString timeStr1 = Utils::convertTime(60);
        QString timeStr2 = Utils::convertTime(142);
        QString timeStr3 = Utils::convertTime(64);
        int     timeInt1 = Utils::convertTime("1:00");
        int     timeInt2 = Utils::convertTime("2:22");


        QVERIFY(timeInt1 == 60);
        QVERIFY(timeInt2 == 142);
        QVERIFY(timeStr1 == "1:00");
        QVERIFY(timeStr2 == "2:22");
        QVERIFY(timeStr3 == "1:04");

    }

    void getExtension(){


        auto res1 = Utils::getExtension("file.f");
        auto res2 = Utils::getExtension("file.f.png");
        auto res3 = Utils::getExtension("file.");
        auto res4 = Utils::getExtension("file");

        QVERIFY(res1 == "f");
        QVERIFY(res2 == "png");
        QVERIFY(res3 == "");
        QVERIFY(res4 == "");

    }
private:

};

QTEST_MAIN(TestUtils)
#include "utls_test.moc"
