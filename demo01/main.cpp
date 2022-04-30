#include "videoplayer.h"

#include <QApplication>

//程序主进入文件
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayer w;//主窗口
    w.show();//运行展示
    return a.exec();
}

//videoshow.h 用于视频解码获得图片数据
//videoitem.h 用于在UI中绘图
//videoplayer.h主类,connect videoshow和videoitem两者的信号和槽
