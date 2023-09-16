#include "include/ui/MusicObject.h"
#include "ui/cmake_data.h"
#include "utils/Image.h"
#include "utils/Utils.h"
#include <QString>
#include <QUrl>


static QString makeArtists(QVector<QString> artists){

    QString res;

    for(int i = 0; i < artists.size(); i++){

        res += artists[i];

        if (i != artists.size() - 1)
            res += ", ";
    }
    return res;

}

static QVector<QString> makeArtists(QString str){

    QVector<QString> res;
    auto artitsts = str.split(",");

    for (auto & elm : artitsts){

        std::string trimed_str = Utils::stringTrim(elm.toStdString(), " ");

        res.emplace_back(QString::fromStdString(trimed_str));
    }
    return res;
}

MusicItem::MusicItem()
{
    std::unique_ptr<Image::Image> image = Image::create(UNKNOWN_IMAGE_PATH);
    _image = new ImageObject(std::move(image));
}


void MusicItem::setArtist(QVector<QString> artists)
{
    QVector<QString> data;
    data.reserve(artists.size());

    for(auto& elm : artists)
        data.emplace_back(QString(elm));

    _artist = data;
}

QString MusicItem::pretiffyArtists() const
{

    return makeArtists(_artist);
}


QHash<int, QByteArray> MusicObjectModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ArtistRole] = "artist";
    roles[DurationRole] = "duration";
    roles[ImageRole] = "image";
    roles[AlbumNameRole] = "album_name";
    roles[ItemRole] = "item";
    roles[PathRole] = "path";
    roles[AlbumYearRole] = "album_year";
    roles[VisibleRole] = "visible";
    roles[YearRole] = "year";
    roles[YearRoleisDefault] = "year_is_default";
    roles[NameRoleisDefault] = "name_is_default";
    roles[ArtistRoleisDefault] = "artist_is_default";
    roles[AlbumNameRoleisDefault] = "album_name_is_default";
    return roles;
}


int MusicObjectModel::rowCount(const QModelIndex & parent) const {
    if (parent.isValid())
        return 0;
    return musicList.count();
}


bool MusicObjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;


    MusicItem &item = musicList[index.row()];
    if (role == NameRole) item.setTitle(value.toString());
    else if (role == ArtistRole) {
        auto _artists = makeArtists(value.toString());
        item._artist = _artists;
    }
    else if (role == DurationRole) item.setDuration(value.toString());
    else if (role == PathRole) item.setPath(value.toString());
    else if (role == VisibleRole) {
        item.setVisible(value.toBool()) ;
    }
    else if (role == ImageRole) {

        std::unique_ptr<Image::Image> image  = Image::create(value.toUrl().toLocalFile());
        if (image == nullptr){
            return false;
        }
        auto image_heap = new ImageObject(std::move(image));
        item.setImage(std::move(image_heap));
    }
    else if (role == AlbumNameRole) {
        AlbumItem album = item.album();
        album.setAlbum(value.toString());
        item.setAlbum(album);
    }

    else if (role == YearRole) {
        item.setYear(value.toString());
    }
    else
        return false;

    emit dataChanged(index, index, { role } );

    return true;

}

void MusicObjectModel::setList(QVector<MusicItem> items)
{
    beginResetModel();
    musicList = items;
    endResetModel();
    emit modelChanged(musicList);
    emit modelUpdate();
}

QVector<MusicItem>& MusicObjectModel::getList()
{
    return musicList;
}

void MusicObjectModel::update(QVector<MusicItem> data)
{
    for(int i= 0; i < data.size(); ++i){
        if (data[i].visible() != musicList[i].visible()){
            musicList[i].setVisible(data[i].visible());
            emit dataChanged(index(i), index(i));

        }
    }
}

void MusicObjectModel::modifyData(std::function<void (MusicItem &)> function)
{
    for(int i= 0; i < musicList.size(); ++i){
        function(musicList[i]);
        emit dataChanged(index(i), index(i));
    }
}

void MusicObjectModel::clear()
{
    beginResetModel();
    musicList.clear();
    endResetModel();

}

QVariant MusicObjectModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= musicList.count())
        return QVariant();
    const MusicItem& item = musicList.at(index.row());
    if (role == ArtistRole) {

        QString _artists = item.pretiffyArtists();
        return _artists.isEmpty()  ? item._artist_default.get_data() : _artists;
    };
    if (role == NameRole) return item.title().get_data();
    if (role == DurationRole) return item.duration().get_data();
    if (role == PathRole) {
        return item.path();}
    if (role == ItemRole ) {
        return       QVariant::fromValue(item);}
    if (role == YearRole) {
        return item.year().get_data();}
    if (role == AlbumNameRole) return item.album().album().get_data();
    if (role == VisibleRole) return item.visible();
    if (role == NameRoleisDefault) return item.title().isDefault();
    if (role == ArtistRoleisDefault) return item.artist().size() <= 0;
    if (role == YearRoleisDefault) return item.year().isDefault();
    if (role == AlbumNameRoleisDefault) {
        return item.album().album().isDefault();}
    if (role == ImageRole)  {

        if (item.image())
            return QVariant::fromValue(item.image());
        return {};
    }

    return {};
}

void MusicObjectModel::addItem(MusicItem item)
{
    beginInsertRows(QModelIndex(), musicList.size(),musicList.size());
    musicList <<  item;
    endInsertRows();
}


