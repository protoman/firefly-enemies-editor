#include "mapareawidget.h"

#include <QPainter>
#include <QColor>
#include <iostream>

MapAreaWidget::MapAreaWidget(QWidget *parent)
    : QWidget{parent}
{
    myParent = parent;
    myParent->resize(QSize(999, 200));
    loadMapData();
}

void MapAreaWidget::loadMapData()
{
    std::string mapFilename = "/home/iuri/Desenvolvimento/firefly/build/games/FireFly/data/tiled/swamp.tmx";
    worldLoader.loadMap(mapFilename);
    layers = worldLoader.getMapLayers();
    imageLayers = worldLoader.getMapImageLayers();
    tilesetLayers = worldLoader.getMapTilesetLayers();
    tilesetsInfo = worldLoader.getTilesetsInfo();
    loadMapImages();
}

void MapAreaWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QLineF line;

    // DRAW TILES //
    std::cout << "### BEGIN #####################################################" << std::endl;
    for (auto const& tileLayer : tilesetLayers) {
        for (auto const& tile : tileLayer.second) {
            int tilesetNumber = findTilesetByTileNumber(tile.tile_pos);
            if (tilesetNumber < tilesetImages.size() && !tilesetImages.empty()) {
                std::cout << "tileset dest[" << tile.dest_x << "][" << tile.dest_y << "], origin[" << tile.origin_x << "][" << tile.origin_y << "], tilesetNumber[" << tilesetNumber << "]" << std::endl;
                QRectF target(QPoint(tile.dest_x * zoom, tile.dest_y * zoom), QSize(tile.w * zoom, tile.h * zoom));
                QRectF source(QPoint(tile.origin_x, tile.origin_y), QSize(tile.w, tile.h));
                painter.drawPixmap(target, tilesetImages.at(tilesetNumber), source);
            } else {
                std::cout << "ERROR: tilesetNumber[" << tilesetNumber << "] is greater than the total number of tilesets images [" << tilesetImages.size() << "]" << std::endl;
            }
        }
    }
    std::cout << "### END #####################################################" << std::endl;

    // DRAW GRID //
    QPen pen(QColor(160, 160, 160), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_red(QColor(255, 0, 255), 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_white(QColor(250, 250, 250), 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    // linhas verticais
    for (unsigned int i=1; i<200; i++) {
        int pos = i*TILESIZE*zoom;
        line = QLineF(pos, 0, pos,200 * TILESIZE * zoom);
        painter.drawLine(line);
    }
    // linhas horizontais
    for (unsigned int i=1; i<200; i++) {
        int pos = i * TILESIZE*zoom;
        //QLineF line(0, 800, 16, 800);
        line = QLineF(0, pos, 200*TILESIZE*zoom, pos);
        painter.drawLine(line);
    }

    QSize resizeMe(MAP_W*TILESIZE*zoom, MAP_H*TILESIZE*zoom);
    this->resize(resizeMe);
    if (myParent != nullptr) {
        myParent->adjustSize();
    }


}

void MapAreaWidget::loadMapImages()
{
    // TODO
    //std::string FILEPATH =
    for (tiled_world_tileset_data tileset_data : tilesetsInfo) {
        //std::string filename = FILEPATH + "/images/sprites/objects/" + Mediator::get_instance()->object_list.at(obj_id).graphic_filename;

        QPixmap temp_image(tileset_data.filename.c_str());
        if (temp_image.isNull()) {
            std::cout << "Could not open image [" << tileset_data.filename << "]" << std::endl;
            // TODO - quit
            return;
        }
        tilesetImages.emplace_back(temp_image);
    }
}

int MapAreaWidget::findTilesetByTileNumber(int tileNumber) const
{
    for (unsigned i=0; i<tilesetsInfo.size(); i++) {
        if (tileNumber - 1 <= tilesetsInfo.at(i).size) {
            return i;
        }
    }
    return tilesetsInfo.size()-1;
}
