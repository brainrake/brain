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
    this->set_title(_filename);

    //start thread
    if ( ! pthread_create(&(this->thread), NULL, Source::thread_start, (void *)this) ){
        printf("[Source::Source] Created source thread: %s\n",info.title);
    } else {
        printf("[Source::Source] Error creating source thread: %s\n",_filename);
    }
}

Source::~Source(){
}


void Source::set_title(char* _filename){
    char str[strlen(_filename)+1];
    char* dotpos = strrchr(_filename,'.');
    strncpy(str,_filename,dotpos-_filename);
    if(strrchr(str,'\\')){strncat(info.title,strrchr(str,'\\')+1,63);}
    else if(strrchr(str,'/')){strncat(info.title,strrchr(str,'/')+1,63);}
    else if(strlen(str)>63){strncat(info.title,&(_filename[strlen(str)-63]),63);}
    else{strncat(info.title, str, 63);}
}


void* Source::thread_start(void* _source){
    Source* source=(Source*) _source;
    source->run();
    printf("[Source::thread_start] Thread finished\n");
}


void Source::run(){
    if( !this->ffmpeg_init()){
    } else {
        printf("[Source::Source] Error initializing ffmpeg\n");
    }
    
    
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
