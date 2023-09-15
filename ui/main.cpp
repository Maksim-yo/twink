#include <QApplication>
#include <QQmlApplicationEngine>
#include <memory>
#include <QDir>
#include <QQuickItem>
#include <filesystem>
#include <QQmlContext>
#include <QtQml/qqmlregistration.h>
#include <QAbstractListModel>
#include <QPainter>
#include <QTimer>
#include <QVector>

#include "utils/Services.h"
#include "utils/Image.h"
#include "metadata/ISaver.h"
#include "include/ui/MusicObject.h"
#include "include/ui/MetadataPageHandler.h"
#include "include/ui/SettingsPageHandler.h"
#include "include/ui/ParsingHandler.h"
#include "include/ui/Settings.h"
#include "include/ui/Search.h"
#include "utils/QtLogger.h"

class SearchHandler: public QObject {

    Q_OBJECT

public:
    SearchHandler(MusicObjectModel*& model): model(model) {
        UI::Search* search = new UI::Search(model->getList());
        search->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, search, &QObject::deleteLater);
        connect(this, &SearchHandler::edit, this, &SearchHandler::onWrite);
        connect(model, &MusicObjectModel::modelChanged, search, &UI::Search::updateData);
        connect(this, &SearchHandler::send, search, &UI::Search::onMessage);
        connect(search, &UI::Search::send, this, &SearchHandler::onHandleData);
        workerThread.start();

    }
    ~SearchHandler(){
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void onWrite(QString message){

        emit send(1, message);
    }

    void onHandleData(QVector<MusicItem> data){

        QVector<MusicItem>& model_data = model->getList();
        model->update(data);


    }
signals:
    void edit(QString message);
    void send(int c, QString message);


private:
    QThread workerThread;
    MusicObjectModel*& model;
};

using namespace std::chrono_literals;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/twink/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QCoreApplication::setOrganizationName("MyTwink");
    QCoreApplication::setOrganizationDomain("examples.com");
    QCoreApplication::setApplicationName("Twink");

    Service<Logger> logger = {std::make_unique<QtLogger>()};

    UI::MetadataPageHandler* metadata_handler = new UI::MetadataPageHandler();
    Service<Metadata::IParser> parser;
    QQmlContext* context = engine.rootContext();
    MusicObjectModel* model = new MusicObjectModel;
    UI::Settings* settings = new UI::Settings();
    UI::SettingsPageHanlder settingsHandler(settings);

    Metadata::ParserSpeed parseSpeedType = Metadata::convertParserSpeed(settings->value("parsingSpeed", "Average").toString());
    parser.assign(Metadata::createParser(Metadata::ParserType::Taglib, parseSpeedType));
    Service<Metadata::ISaver> saver = Metadata::createSaver(Metadata::ParserType::Taglib, parseSpeedType);
    ParsingHandler* parsingHandler =  new ParsingHandler(model);
    SearchHandler* searchHandler = new SearchHandler(model);

    context->setContextProperty("trackList", model);
    context->setContextProperty("settings", settings);
    context->setContextProperty("parsingHandler", parsingHandler);
    context->setContextProperty("metadata_handler",metadata_handler);
    context->setContextProperty("searchHandler", searchHandler);

    emit parsingHandler->changedPath("C:/Users/lyzlo/Music");
    engine.load(url);

    return app.exec();
}


#include "main.moc"
