#include "videoitem.h"


VideoItem::VideoItem(QWidget *parent)
    : QWidget{parent}
{

}

//获取得到的图片进行绘图
void VideoItem::slot_setImage(const QImage  image)
{
    m_image = image;
    this->update();//立即刷新绘图
}

//绘图事件
void VideoItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //先画黑色背景
    painter.setBrush( Qt::black );
    painter.drawRect( 0,0, this->width() , this->height() );
    //等比例缩放图片  等比例变成控件这么大
    if( m_image.size().width()<= 0 ) return;

    QPixmap img = QPixmap::fromImage(m_image.scaled(this->size(), Qt::KeepAspectRatio));

    //调整贴图位置，使其居中
    //x = （widget_show的宽 - 图片宽） / 2
    //y = （widget_show的高 - 图片高） / 2
    int x =  this->width() - img.width() ;
    int y =  this->height() - img.height();
    x = x/2;
    y = y/2;
    painter.drawPixmap(x,y,img);

}
