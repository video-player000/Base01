/********************************************************************************
** Form generated from reading UI file 'videoplayer.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYER_H
#define UI_VIDEOPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <videoitem.h>

QT_BEGIN_NAMESPACE

class Ui_VideoPlayer
{
public:
    VideoItem *wdg_show;
    QWidget *wdg_ctrl;
    QPushButton *pb_play;

    void setupUi(QWidget *VideoPlayer)
    {
        if (VideoPlayer->objectName().isEmpty())
            VideoPlayer->setObjectName(QString::fromUtf8("VideoPlayer"));
        VideoPlayer->resize(800, 600);
        VideoPlayer->setMinimumSize(QSize(800, 600));
        wdg_show = new VideoItem(VideoPlayer);
        wdg_show->setObjectName(QString::fromUtf8("wdg_show"));
        wdg_show->setGeometry(QRect(9, 9, 781, 511));
        wdg_ctrl = new QWidget(VideoPlayer);
        wdg_ctrl->setObjectName(QString::fromUtf8("wdg_ctrl"));
        wdg_ctrl->setGeometry(QRect(10, 540, 120, 80));
        pb_play = new QPushButton(wdg_ctrl);
        pb_play->setObjectName(QString::fromUtf8("pb_play"));
        pb_play->setGeometry(QRect(10, 10, 93, 29));

        retranslateUi(VideoPlayer);

        QMetaObject::connectSlotsByName(VideoPlayer);
    } // setupUi

    void retranslateUi(QWidget *VideoPlayer)
    {
        VideoPlayer->setWindowTitle(QCoreApplication::translate("VideoPlayer", "VideoPlayerDemo", nullptr));
        pb_play->setText(QCoreApplication::translate("VideoPlayer", "Play", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoPlayer: public Ui_VideoPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYER_H
