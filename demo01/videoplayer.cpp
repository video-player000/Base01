#include "videoplayer.h"
#include "ui_videoplayer.h"
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>

//构造函数
VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent},ui(new Ui::VideoPlayer)//构造函数赋值
{
    ui->setupUi(this);//.ui文件生成的类的构造函数，进行初始化(窗体，信号和槽)
    m_videoShow =new VideoShow;
   //连接信号和槽
   //参数:（发送者，发送信号，接收者，接收槽函数）
    connect(m_videoShow,SIGNAL(SIG_GetOneImage(QImage)),//连接videoshow解码和videoitem展示类
            ui->wdg_show,SLOT(slot_setImage(QImage)));
}

//析构函数
VideoPlayer::~VideoPlayer()
{

    if(m_videoShow)
    {
        m_videoShow->quit();
        m_videoShow->wait();
        delete m_videoShow;
        m_videoShow = nullptr;
    }
    delete ui;
}

//槽函数
void VideoPlayer::on_pb_play_clicked()
{
    m_videoShow->start();
}

