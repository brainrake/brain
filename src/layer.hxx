#ifndef __LAYER_HXX__
#define __LAYER_HXX__

#include <pthread.h>

#include "brain.hxx"
#include "source.hxx"

class Brain;
class Source;

struct LayerInfo{
    GLuint id;
    
    GLuint width;
    GLuint height;
    GLfloat r,g,b,a;    //color, alpha
    GLfloat tx,ty,tz;   //translation
    GLfloat rx,ry,rz;   //rotation
    GLfloat sx,sy,sz;   //scaling
    
    unsigned char blending;

    double fps;
};


class Layer{
private:
    Brain* brain;

    Source* source;

    bool _ready;
    bool _texture_ready;

    double _last_frame_time;

    void step_frame();

    GLuint texture;
    
    void init_render();
    void close_render();

public:

    Layer(Brain* brain);
    ~Layer();

    LayerInfo info;
    
    void set_source(Source* source);
    void render();
    
    friend class Brain;
    friend class Source;
};


#endif
