#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include<QWidget>
#include "videoshow.h"

//播放类

//ffmpeg是采用c语言实现的 因此在c++工程中导入c语言
extern "C" {
//avcodec:用于编解码(最重要的库)
#include "libavcodec/avcodec.h"
//avformat:封装格式处理
#include "libavformat/avformat.h"
//swscale:视频像素数据格式转换
#include "libswscale/swscale.h"
//avdevice:各种设备的输入输出
#include "libavdevice/avdevice.h"
}


//为了使 ui 布局控制和其他的控制代码分离
namespace Ui{//namespace用于解决命名冲突,不同namespcae::下的类可以同名
class VideoPlayer;
}

class VideoPlayer : public QWidget
{
    Q_OBJECT//宏，只有加入了Q_OBJECT，你才能使用QT中的signal和slot机制

public:
    explicit VideoPlayer(QWidget *parent = nullptr); //explicit表明该类只能显示构造，不能通过类型转换操作符隐式转换使用。
    ~VideoPlayer();

private slots://槽函数
    void on_pb_play_clicked();//相应接受到的信号，执行展示页面

private:
    Ui::VideoPlayer *ui;//Ui界面对象
    VideoShow* m_videoShow;//用于下一步，展示画面对象

};

#endif // VIDEOPLAYER_H














