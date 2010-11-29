#ifndef __SOURCE_HXX__
#define __SOURCE_HXX__

#include <string>
#include <GL/gl.h>
#include <pthread.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


struct SourceInfo{
    char title[64];
    GLuint width;
    GLuint height;
    unsigned long int position;
};


class Source{
private:
    SourceInfo info;
    char* filename;

    void set_title(char* _filename);

    bool _stop;
    void run();
    void step();
    void swap_buffers();

    void* buf_front;
    void* buf_back;

    pthread_t thread;
    static void* thread_start(void* _source);
    
    int ffmpeg_init();
    int ffmpeg_decode_frame();
    AVFormatContext *pFormatCtx;
    int             i, videoStream;
    AVCodecContext  *pCodecCtx;
    AVCodec         *pCodec;
    AVFrame         *pFrame;
    AVPacket        packet;
    int             frameFinished;
    float           aspect_ratio;
    struct SwsContext *img_convert_ctx;
  
public:
    Source();
    Source(char* _filename);
    ~Source();
    
    void play();
    void pause();
    void seek(unsigned long int _position);
    void set_play_mode(unsigned char play_mode);

    friend class Brain;
    friend class Layer;
};

#endif
