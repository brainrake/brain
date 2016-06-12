#include "brain.hxx"


Brain::Brain() {
    _stop = false;

    this->clock.restart();

    for (unsigned int i=0; i<MAX_LAYERS; i++) {
        this->layers[i] = 0;
    }

    for (unsigned int i=0; i<MAX_SOURCES; i++) {
        this->sources[i] = 0;
    }

    this->init_render();
}


Brain::~Brain() {
    this->close_render();
    //TODO
}


void Brain::run() {
    while ( ! this->_stop ) {
        this->step();
    }
}


void Brain::step() {
    sf::Int64 t = clock.getElapsedTime().asMicroseconds();
    this->delta = t - this->time;
    this->time = t;

    this->input();
    this->render();

    for (unsigned int i=0; i < MAX_SOURCES; i++) {
        if (this->sources[i]) {
            this->sources[i]->next_frame();
        }
    }

}


void Brain::add_source(Source* source) {
    //set up reference to self
    source->brain = this;

    //find end of sources array
    unsigned int i;
    for (i=0; i<MAX_SOURCES; i++) {
        if (this->sources[i] == 0) {
            break;
        }
    }

    //add source to sources array
    if (i<MAX_SOURCES) {
        this->sources[i] = source;
        source->info.id = i;
    }
}


void Brain::add_layer(Layer* layer) {
    //set up reference to self
    layer->brain = this;

    //find end of layers array
    unsigned int i;
    for (i=0; i<MAX_LAYERS; i++) {
        if (this->layers[i] == 0) {
            break;
        }
    }

    //add layer to layers array
    if (i<MAX_LAYERS) {
        this->layers[i] = layer;
        layer->info.id = i;
    }
}
