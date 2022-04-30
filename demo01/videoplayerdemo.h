#ifndef VIDEOPLAYERDEMO_H
#define VIDEOPLAYERDEMO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class VideoPlayerDemo; }
QT_END_NAMESPACE

class VideoPlayerDemo : public QWidget
{
    Q_OBJECT

public:
    VideoPlayerDemo(QWidget *parent = nullptr);
    ~VideoPlayerDemo();

private:
    Ui::VideoPlayerDemo *ui;
};
#endif // VIDEOPLAYERDEMO_H
