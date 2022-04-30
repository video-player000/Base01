#ifndef VIDEOSHOW_H
#define VIDEOSHOW_H

#include <QThread>
#include <QImage>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
//avutil:工具库（大部分库都需要这个库的支持）
#include "libavutil/avutil.h"
#include "libavutil/imgutils.h"
#include "libavutil/frame.h"
#include "libavutil/mem.h"
#include "libavutil/time.h"//获取时间基函数的头文件
}

//开启线程进行解码
class VideoShow : public QThread
{
    Q_OBJECT
public:
    explicit VideoShow();
    void run();//解码，发送数据

//信号
signals:
    void SIG_GetOneImage(const QImage image);

public:
    QString m_fileName;//文件路径

};

#endif // VIDEOSHOW_H
