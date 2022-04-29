#include "videoplayer.h"
#include "ui_videoplayer.h"
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>


VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent},
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    m_videoShow =new VideoShow;
    connect(m_videoShow,SIGNAL(SIG_GetOneImage(QImage)),
            ui->wdg_show,SLOT(slot_setImage(QImage)));
}

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

void VideoPlayer::on_pb_play_clicked()
{
    m_videoShow->start();
}
