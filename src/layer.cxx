#include "layer.hxx"

Layer::Layer(Brain* _brain) {
    this->brain = _brain;
    
    this->_ready = false;
    this->_texture_ready = false;

    this->info.id=-1;
    
    this->info.r=1; this->info.g=1; this->info.b=1; this->info.a=1;
    
    this->info.width=0; this->info.height=0;
    
    this->info.tx=0; this->info.ty=0; this->info.tz=0;
    this->info.rx=0; this->info.ry=0; this->info.rz=0;
    this->info.sx=1; this->info.sy=1; this->info.sz=1;
    
    this->info.blending=0;

    this->info.fps = 25;
    
    this->source=0;
}


Layer::~Layer() {
    this->close_render();
}


void Layer::set_source(Source* _source) {
    this->close_render();
    this->source = _source;

    if (this->source) {
        this->info.height = this->source->info.height;
        this->info.width  = this->source->info.width;

        printf("Layer %d: set_source: %s\n", this->info.id, source->info.title);
        
        this->init_render();
    }
}

