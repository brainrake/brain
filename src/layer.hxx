#ifndef __LAYER_HXX__
#define __LAYER_HXX__

#include <pthread.h>
#include <GL/gl.h>

#include "source.hxx"

struct LayerInfo{
    GLuint width;
    GLuint height;
    GLfloat r,g,b,a;    //color, alpha
    GLfloat tx,ty,tz;   //translation
    GLfloat rx,ry,rz;   //rotation
    GLfloat sx,sy,sz;   //scaling
    
    unsigned char blending;
};


class Layer{
private:

    Source* source;

    bool _ready;
    bool _texture_ready;
    
    GLuint texture;
    
    //front and back buffers
    GLbyte* buffer0;
    GLbyte* buffer1;

    pthread_mutex_t buffer_mutex;

    void init_render();
    void close_render();


public:

    Layer();
    ~Layer();

    LayerInfo info;
    
    void set_source(Source* source);
    void render();
    
    friend class Brain;
    friend class Source;
};


#endif
