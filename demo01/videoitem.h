#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>

namespace Ui{
class VideoItem;
}

class VideoItem : public QWidget
{
    Q_OBJECT
public:
    explicit VideoItem(QWidget *parent = nullptr);
//    ~VideoItem();
public slots:
    void slot_setImage(const QImage image);
    void paintEvent(QPaintEvent *event);

private:
    Ui::VideoItem *ui;
    QImage m_image;

};

#endif // VIDEOITEM_H
