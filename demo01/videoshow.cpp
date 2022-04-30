#include "videoshow.h"
#include <QDebug>//用于打印到控制台  若用printf的话只有程序结束才会从缓冲区显示到控制台
# include<iostream>
using namespace std;

//构造函数 获取文件路径
VideoShow::VideoShow()
{
    m_fileName = "./media/222.mp4";
     //m_fileName = "H://Project//media//media-file//aaa.mp4";

}

//解码、发送图片内容
void VideoShow::run()
{


    AVFormatContext* pFormatCtx;//文件指针
    AVCodecContext* pCodecCtx;
    AVCodecParameters* pCodecPar;
    const AVCodec* pCodec;


//2.需要分配一个 AVFormatContext，视频文件指针，用于FFMPEG所有的操作
    pFormatCtx = avformat_alloc_context();
    //获取文件路径，同时兼容中文
    std::string path = m_fileName.toStdString();
    const char* file_path = path.c_str();//转为c语言能处理的字符串

//3.打开视频文件  打开url中输入流并传递给指针
    if (avformat_open_input(&pFormatCtx, file_path, NULL, NULL) != 0){
        qDebug()<<"File opened from url unsuccessfully!";
        return;
    }
    else{
        qDebug()<<"File opened from url successfully.";
    }
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)//判断是否获取到流信息
    {
        qDebug()<<"find video stream failed ";
        return;
    }

//4.读取视频流
    int videoStream = -1;
    unsigned int i;
    //循环查找视频中包含的流信息，直到找到视频类型的流和音频类型的流
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        //AVMediaType 编解码器信息类型
        enum AVMediaType mediaType = pFormatCtx->streams[i]->codecpar->codec_type;
        if (mediaType == AVMEDIA_TYPE_VIDEO) {
            //视频流
            videoStream = i;//用于索引视频流
        }
        else if (mediaType == AVMEDIA_TYPE_AUDIO)
        {
            //音频流
        }
    }
    //找不到视频流
    if (videoStream == -1) {
        qDebug()<<"Find video stream unsuccessfully";
        return;
    }

//5.查找解码器
    pCodecPar = pFormatCtx->streams[videoStream]->codecpar;
    //avcodec_find_decoder()用于查找具有匹配 编解码器ID 的已注册解码器
    pCodec = avcodec_find_decoder(pCodecPar->codec_id);
    if (pCodec == NULL) {
        qDebug()<< "Find Codec unsuccessfully";
        return;
    }
    //打开解码器
    pCodecCtx = avcodec_alloc_context3(NULL);
    if (pCodecCtx == NULL)
    {
        qDebug()<< "Could not allocate AVCodecContext";
        return;
    }

    //类型转换，将AVCodecParameters结构体中码流参数拷贝到AVCodecContext结构体中
    avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStream]->codecpar);

    //用于 初始化 一个视音频编解码器的AVCodecContext
    //参数:（需要初始化的AVCodecContext，输入的AVCodec，一些选项）
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        qDebug()<<"Open decode codec unsuccessfully";
        return;
    }

//6.申请解码需要的结构体 AVFrame 视频缓存的结构体
    //(pFrame:描述了解码后的（原始）音频或视频数据)
    AVFrame * pFrame = av_frame_alloc();
    AVFrame * pFrameRGB = av_frame_alloc();

    //分配一个packet
    AVPacket* packet = (AVPacket*)malloc(sizeof(AVPacket));

//7.这里我们将解码后的 YUV 数据转换成 RGB32 YUV420p 格式视频数据-->RGB32--> 图片显示出来
    static struct SwsContext* img_convert_ctx;
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
        pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

    //过指定像素格式、图像宽、图像高来计算所需的内存大小 这里YUV420P
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height, 1);

    //申请RGB一帧画面大小对应的空间
    uint8_t* out_buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

    //pFrameRGB与out_buffer绑定 瓜分所分配的内存
    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, out_buffer, AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height, 1);

    //为packet分配内存
    int y_size = pCodecPar->width * pCodecPar->height;
    av_new_packet(packet, y_size); //分配packet的数据
    av_dump_format(pFormatCtx, 0, file_path, 0); //输出视频信息

//8.循环读取视频帧, 转换为 RGB 格式, 抛出信号去控件显示
    //以微妙为单位记录时间
    int64_t start_time =av_gettime();
    int64_t pts_us = 0;
    while (1)
    {
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //视频全部读完了
        }
        //计算实际时间，比较显示时间与已播放时间戳，做出同步
        int64_t realTime =av_gettime()-start_time;//实际播放时间
        while(pts_us>realTime)
        {
            msleep(5);
            realTime = av_gettime()-start_time;
        }
        if (packet->stream_index == videoStream)
        {

            //将分组数据包发送给解码器
            if (avcodec_send_packet(pCodecCtx, packet) != 0) {
                qDebug()<<"send_packet error";
                return;
            }
            if (avcodec_receive_frame(pCodecCtx, pFrame) != 0) {
                //若为0则成功，a frame was returned
                qDebug()<<"receive_frame error";
                return;
            }
            else{
             //PTS与DTS——显示时间戳与解码时间戳
             //pts *av_q2d(time_base)计算得到的单位是 秒 乘以1000000得到的微妙单位，为了与avgettime的时间比较
             //时间戳值乘以时间基=实际的时刻值(秒单位)

                //显示的时刻
                pts_us=1000000 * pFrame->pts *av_q2d(pFormatCtx->streams[videoStream]->time_base);//绝对时间
                //获取解码的帧数据
                //YUV420转换RGB
                sws_scale(img_convert_ctx,
                    (uint8_t const* const*)pFrame->data,
                    pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                    pFrameRGB->linesize);
                    printf("index");
                //out_buffer 与 pFrameRGB 是捆绑的，将 out_buffer 里面的数据存在 QImage 里面
                QImage tmpImg((uchar*)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                //把图像复制一份 传递给界面显示
                QImage image = tmpImg.copy();
                //将得到的图片数据 通过发射信号 显示到控件，
                emit SIG_GetOneImage( image );
            }
        }

        //清理AVPacket中的所有空间数据
        av_packet_unref(packet);
        //msleep(6); // 停一停,关系到播放速度
    }

    //析构
    av_free(out_buffer);
    av_free(pFrame);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);

    return;

}
