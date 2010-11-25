#ifndef __SOURCE_HXX__
#define __SOURCE_HXX__

#include <pthread.h>

struct SourceInfo{
    char* filename;
    unsigned int width;
    unsigned int height;
    
};


class Source{
private:
    SourceInfo info;

    void step();

public:
    Source();
    ~Source();
    
    void play();
    void pause();
    void seek(unsigned long int frame);

    friend class Brain;
    friend class Layer;
};

#endif
