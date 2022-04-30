#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>

//绘图类

//需要：
//将VideoItem类与ui界面中的控件wdg_show关联起来
//在videoPlayer.ui中，将wdg_show提升为VideoItem（继承VideoItem）
//这样就可以在wdg_show上进行绘图了

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
