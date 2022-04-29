#include "videoshow.h"
#include <QDebug>
# include<iostream>
using namespace std;

VideoShow::VideoShow()
{
    m_fileName = "H:/DesktopD/427.mp4";

}

void VideoShow::run()
{


        AVFormatContext* pFormatCtx;
        AVCodecContext* pCodecCtx;
        AVCodecParameters* pCodecPar;
        const AVCodec* pCodec;
        AVFrame* pFrame, * pFrameRGB;
        int videoStream, numBytes;
        static struct SwsContext* img_convert_ctx;
        uint8_t* out_buffer;
        AVPacket* packet;

        pFormatCtx = avformat_alloc_context();
        std:string path = m_fileName.toStdString();
        const char* file_path = path.str();
        if (avformat_open_input(&pFormatCtx, file_path, NULL, NULL) != 0){
            qDebug()<<"File opened unsuccessfully.\n";
            return;
        }
        if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
        {
            qDebug()<<"find video stream failed ";
        }

        //循环查找视频中包含的流信息，直到找到视频类型的流
        //便将其记录下来,保存到videoStream变量中
        //这里我们现在只处理视频流,音频流先不管他
        videoStream = -1;
        for (int i = 0; i < pFormatCtx->nb_streams; i++) {
            enum AVMediaType mediaType = pFormatCtx->streams[i]->codecpar->codec_type;
            if (mediaType == AVMEDIA_TYPE_VIDEO) {
                videoStream = i;
            }
            else if (mediaType == AVMEDIA_TYPE_AUDIO)
            {
                //音频流
            }
            else {

            }
        }
        if (videoStream == -1) {
            printf("Find video stream unsuccessfully.\n");
            return;
        }

        //查找解码器
        pCodecPar = pFormatCtx->streams[videoStream]->codecpar;
        //pCodec = avcodec_find_decoder(pCodecPar->codec_id);
        pCodec = avcodec_find_decoder(pCodecPar->codec_id);
        if (pCodec == NULL) {
            printf( "Find Codec unsuccessfully.\n");
            return;
        }

        pCodecCtx = avcodec_alloc_context3(NULL);
        if (pCodecCtx == NULL)
        {
            printf("Could not allocate AVCodecContext\n");
            return;
        }
        avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStream]->codecpar);

        //打开解码器
        if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
            printf("Open codec unsuccessfully.\n");
            return;
        }

        pFrame = av_frame_alloc();
        pFrameRGB = av_frame_alloc();

        img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
            pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

        numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

        out_buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

        av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

        int y_size = pCodecPar->width * pCodecPar->height;
        packet = (AVPacket*)malloc(sizeof(AVPacket)); //分配一个packet
        av_new_packet(packet, y_size); //分配packet的数据

        av_dump_format(pFormatCtx, 0, file_path, 0); //输出视频信息
        int index = 0;
        while (1)
        {
            if (av_read_frame(pFormatCtx, packet) < 0)
            {
                break; //这里认为视频读取完了
            }
            if (packet->stream_index == videoStream)
            {

                if (avcodec_send_packet(pCodecCtx, packet) != 0) {
                    printf("decode error.\n");
                    return;
                }
                if (avcodec_receive_frame(pCodecCtx, pFrame) != 0) {//got_picture = 0 success, a frame was returned
                    printf( "decode error.\n");
                    return;
                }
                else{
                    sws_scale(img_convert_ctx,
                        (uint8_t const* const*)pFrame->data,
                        pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                        pFrameRGB->linesize);
                        printf("index");
                    //out_buffer 与 pFrameRGB 是捆绑的，将 out_buffer 里面的数据存在 QImage 里面
                    QImage tmpImg((uchar*)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                    //把图像复制一份 传递给界面显示
                    QImage image = tmpImg.copy();
                    //显示到控件 多线程 无法控制控件 所以要发射信号
                    emit SIG_GetOneImage( image );

                    //if (index > 50) return; //这里我们就保存50张图片
                }
            }
            av_packet_unref(packet);
            msleep(5); // 停一停
        }

        av_free(out_buffer);
        av_free(pFrame);
        av_free(pFrameRGB);
        avcodec_close(pCodecCtx);
        avformat_close_input(&pFormatCtx);

        return;

}
