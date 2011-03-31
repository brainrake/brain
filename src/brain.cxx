#include "brain.hxx"


Brain::Brain(){
    _stop = false;
    
    for (unsigned int i=0;i<MAX_LAYERS;i++){
        this->layers[i] = 0;
    }
    
    for (unsigned int i=0;i<MAX_SOURCES;i++){
        this->sources[i] = 0;
    }
    
    this->init_render();
}


Brain::~Brain(){
    this->close_render();
    //TODO
}


void Brain::run(){
    while ( ! this->_stop ){
        this->step();
    }
}


void Brain::step(){
    this->input();
    this->render();
}


void Brain::add_source(Source* source){
    unsigned int i;
    for(i=0; i<MAX_SOURCES;i++){
        if (this->sources[i] == 0){
            break;
        }
    }

    if (i<MAX_SOURCES){
        this->sources[i] = source;
        source->info.id = i;
    }
}


void Brain::add_layer(Layer* layer){
    unsigned int i;
    for(i=0; i<MAX_LAYERS;i++){
        if (this->layers[i] == 0){
            break;
        }
    }

    if (i<MAX_LAYERS){
        this->layers[i] = layer;
        layer->info.id = i;
    }
}
