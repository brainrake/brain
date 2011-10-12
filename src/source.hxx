#ifndef __SOURCE_HXX__
#define __SOURCE_HXX__

#include "brain.hxx"

#include <string>
#include <pthread.h>

#include <SFML/Window.hpp>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}



class Brain;


struct SourceInfo{
    GLuint id;
    char title[64];
    
    GLuint width;
    GLuint height;

    double fps;
    
    unsigned long int position;
};


class Source{
private:
    Brain* brain;

    SourceInfo info;
    char* filename;

    void init();
    void set_title(char* _filename);

    bool _stop;
    void run();
    void step();
    void swap_buffers();

    void* buf_front;
    void* buf_back;

    //thread stuff
    pthread_t thread;
    static void* thread_start(void* _source);

    //buffer swap mutex and cv
    pthread_mutex_t buf_mutex;
    pthread_cond_t buf_cv;

    //ffmpeg stuff
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

//fps
    double _last_frame_time;

    sf::Clock Clock;
    double time;
    double fps;
    int cnt;
    void log_fps();
  
public:
    Source(char* _filename);
    ~Source();
    
    void play();
    void pause();
    void seek(unsigned long int _position);
    void set_play_mode(unsigned char play_mode);

    void next_frame();

    friend class Brain;
    friend class Layer;
};

#endif
