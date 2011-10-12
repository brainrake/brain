#ifndef __BRAIN_HXX__
#define __BRAIN_HXX__

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include "layer.hxx"
#include "source.hxx"

class Layer;
class Source;


#define MAX_LAYERS 16
#define MAX_SOURCES 16





struct BrainInfo{
};


class Brain{
private:

    BrainInfo info; 

    Layer* layers[MAX_LAYERS];
    Source* sources[MAX_SOURCES];

    sf::RenderWindow* window;

    bool _stop;

    void init_render();
    void render();
    void close_render();
    void render_fps();

    void step();

    sf::Clock clock;

public:

    Brain();
    ~Brain();

    void run();
    void add_source(Source* source);
    void add_layer(Layer* layer);

    void input();

    double time;
    double delta;

    friend class Layer;
    friend class Source;
};


#endif
