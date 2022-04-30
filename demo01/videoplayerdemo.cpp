#include "videoplayerdemo.h"
#include "ui_videoplayer.h"

VideoPlayerDemo::VideoPlayerDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
}

VideoPlayerDemo::~VideoPlayerDemo()
{
    delete ui;
}

