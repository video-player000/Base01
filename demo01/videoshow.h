#ifndef VIDEOSHOW_H
#define VIDEOSHOW_H

#include <QThread>
#include <QImage>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/avutil.h"
#include "libavutil/imgutils.h"
#include "libavutil/frame.h"
#include "libavutil/mem.h"
}

class VideoShow : public QThread
{
    Q_OBJECT
public:
    explicit VideoShow();
    void run();
signals:
    void SIG_GetOneImage(const QImage image);
public slots:
public:
    QString m_fileName;

};

#endif // VIDEOSHOW_H
