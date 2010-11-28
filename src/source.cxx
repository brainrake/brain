#include "source.hxx"

#include <string.h>
#include <stdio.h>

Source::Source(){
    this->_stop = false;
    info.height = 0;
    info.width = 0;
    info.title[0] = 0;
    this->buf_front=0;
    this->buf_back=0;
    this->filename = NULL;
}

Source::Source(char* _filename){
    this->_stop = false;
    info.height=0;
    info.width=0;
    info.title[0] = 0;
    this->buf_front=0;
    this->buf_back=0;
    
    this->filename = new char[strlen(_filename)];
    strcpy(this->filename, _filename);
    
    //set title
    if(strrchr(_filename,'\\')){strncat(info.title,strrchr(_filename,'\\'),63);}
    else if(strrchr(_filename,'/')){strncat(info.title,strrchr(_filename,'/'),63);}
    else if(strlen(_filename)>63){strncat(info.title,&(_filename[strlen(_filename)-63]),63);}
    else{strncat(info.title, _filename, 63);}
    
    
    if( !this->ffmpeg_init()){
    } else {
        printf("[Source::Source] Error initializing ffmpeg\n");
    }
    
    buf_front=(void*)malloc(4*this->info.width*this->info.height);
    buf_back=(void*)malloc(4*this->info.width*this->info.height);
    
    //start thread
    if ( ! pthread_create(&(this->thread), NULL, Source::thread_start, (void *)this) ){
        printf("[Source::Source] Created source thread: %s\n",_filename);
    } else {
        printf("[Source::Source] Error creating source thread: %s\n",_filename);
    }
}

Source::~Source(){
}


void* Source::thread_start(void* _source){
    Source* source=(Source*) _source;
    source->run();
    printf("[Source::thread_start] Thread finished\n");
}


void Source::run(){
    while(!this->_stop){
        this->step();
    }
}

void Source::step(){
    if(!this->ffmpeg_decode_frame()){
    } else {
        this->_stop = true;
    }
    this->swap_buffers();
}

void Source::swap_buffers(){
    void* buf;
    buf=this->buf_back;
    this->buf_back=this->buf_front;
    this->buf_front=buf;
}
