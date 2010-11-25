#include "layer.hxx"


Layer::Layer(){
    this->_ready = false;
    
    this->info.r=0;
    this->info.g=0;
    this->info.b=0;
    this->info.a=1;
    this->info.width=0;
    this->info.height=0;
    this->info.tx=0;
    this->info.ty=0;
    this->info.tz=0;
    this->info.rx=0;
    this->info.ry=0;
    this->info.rz=0;
    this->info.sx=1;
    this->info.sy=1;
    this->info.sz=1;
}


Layer::~Layer(){
    this->close_render();
}


void Layer::set_source(Source* _source){
    this->close_render();
    
    this->source = _source;
    this->info.height = this->source->info.height;
    this->info.width  = this->source->info.width;
    
    this->init_render();
}
