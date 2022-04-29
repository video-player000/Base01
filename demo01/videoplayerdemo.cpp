#include "videoplayerdemo.h"
#include "ui_videoplayerdemo.h"

VideoPlayerDemo::VideoPlayerDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoPlayerDemo)
{
    ui->setupUi(this);
}

VideoPlayerDemo::~VideoPlayerDemo()
{
    delete ui;
}

