#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H
#include <QString>
#include <QObject>
#include <QVector>
#include <QAbstractListModel>
#include <QList>

#include "ImageObject.h"
#include "utils/String.h"

//using Utils::String;
static const std::string_view default_value{"Unknown"};
static const std::string_view default_time_value{"??:??"};
static const std::string_view default_year_value{"????"};

struct AlbumItem {

    Utils::String album() const {return _album;}

    void setAlbum(QString album) {if (album.length()) _album = album;}

private :
    Utils::String _album{default_value};

};

struct pathStruct {


    QString none_path{""};
    QString path;

};
struct MusicItem {


//    Q_OBJECT
//    Q_PROPERTY(QString artist READ artist WRITE setArtist)
//    Q_PROPERTY(QString title READ title WRITE setTitle)
//    Q_PROPERTY(QString album READ album WRITE setAlbum)
//    Q_PROPERTY(QString duration READ duration WRITE setDuration)
//    Q_PROPERTY(ImageObjcect* ianm READ artist WRITE setArtist)
    MusicItem();
    QVector<QString> artist() const noexcept {return _artist;}
    Utils::String title() const noexcept {return _name;}
    Utils::String duration() const noexcept {return _duration;}
    Utils::String year() const noexcept {return _year;}
    QString path() const {return _current_path;}
    pathStruct pathData() const {return _path;}
    ImageObject* image() const noexcept {return _image;}
    qint64 bitrate() const {return _bitrate;}
    qint64 sampleRate() const {return _sampleRate;}
    qint64 channels() const {return _channels;}
    AlbumItem album() const {return _album;}
    bool    visible() const {return _visible;}

    void setArtist(QVector<QString> artists);
    void setTitle(QString title) {if (!title.isEmpty()) _name = title;}
    void setDuration(QString duration) { _duration = duration; }
    void setPath(QString path){
        _path.path = path;
    }
    void setPath(bool state) {
        qDebug() << state;
        if(state)
            _current_path = _path.path;
        else
            _current_path = _path.none_path;
    }
    void setImage(ImageObject* image){_image = image;}
    void setBitrate(qint64 bitrate) {_bitrate = bitrate; }
    void setSampleRate(qint64 rate) {_sampleRate = rate;}
    void setChannles(qint64 channels) {_channels = channels;}
    void setAlbum(AlbumItem album) {_album = album;}
    void setVisible(bool visible) {_visible = visible;}
    void setYear(QString year) { if(!year.isEmpty())_year = year;}
    QString pretiffyArtists() const ;

    Utils::String  _name{default_value};
    QVector<QString> _artist;
    Utils::String _artist_default{default_value};
    Utils::String _duration{default_time_value};
    Utils::String _year{default_year_value};

    pathStruct _path;
    QString _current_path;
    qint64 _bitrate;
    qint64 _sampleRate;
    qint64 _channels;
    AlbumItem _album;
    bool _visible{true};
    ImageObject* _image{nullptr};

};
Q_DECLARE_METATYPE(MusicItem)

class MusicObjectModel : public  QAbstractListModel
{


    Q_OBJECT
    Q_ENUMS(MusicRoles)


public:

    using QAbstractListModel::QAbstractListModel;

    enum MusicRoles {
        NameRole = Qt::UserRole + 1,
        ArtistRole,
        DurationRole,
        ImageRole,
        PathRole,
        ItemRole,
        YearRole,
        AlbumYearRole,
        AlbumNameRole,
        VisibleRole,
        NameRoleisDefault,
        YearRoleisDefault,
        ArtistRoleisDefault,
        AlbumNameRoleisDefault,
    };

    ~MusicObjectModel(){}
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role) const override;
//    Q_INVOKABLE MusicItem getItem(int index);
    void addItem(MusicItem item);
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVector<MusicItem>& getList();
    void clear();
    void update(QVector<MusicItem> data);
    void modifyData(std::function<void(MusicItem& item)> function);
    void setList(QVector<MusicItem> items);
    QHash<int, QByteArray> roleNames() const override;
signals:
    void nameClicked(int index);
    void nameChanged();
    void durationChanged();
    void artistChanged();
    void listenersChanged();
    void imageChanged();
    void modelChanged(QVector<MusicItem> temp);
    // USED IN QML as onModelUpdate()
    void modelUpdate();

private:
    QVector<MusicItem> musicList;

};

#endif // MUSICOBJECT_H
