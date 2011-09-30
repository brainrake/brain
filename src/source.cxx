#include "source.hxx"

#include <string.h>
#include <stdio.h>


Source::Source() {
    this->_stop = false;
    info.height = 0;
    info.width = 0;
    info.title[0] = 0;
    this->buf_front=0;
    this->buf_back=0;
    this->filename = NULL;

    //fps
    time=0;
    fps=0;
    cnt=0;
}


Source::Source(char* _filename) {
    this->_stop = false;
    info.height=0;
    info.width=0;
    info.title[0] = 0;
    this->buf_front=0;
    this->buf_back=0;
    
    this->filename = new char[strlen(_filename)+1];
    strcpy(this->filename, _filename);
    
    //set title
    this->set_title(_filename);


    if (!this->ffmpeg_init()) {
    } else {
        printf("[Source::Source] Error initializing ffmpeg\n");
    }

    //start thread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    sched_param schedparam;
    schedparam.sched_priority = -10;
    int ret = pthread_attr_setschedparam(&attr, &schedparam);
    printf("ret %d\n",ret);

    if ( ! pthread_create(&(this->thread), &attr, Source::thread_start, (void *)this) ) {
        printf("[Source::Source] Created source thread: %s\n",info.title);
    } else {
        printf("[Source::Source] Error creating source thread: %s\n",_filename);
    }
}


/*
       int pthread_create(pthread_t *restrict thread,
              const pthread_attr_t *restrict attr,
              void *(*start_routine)(void*), void *restrict arg);
*/


Source::~Source() {
}


void Source::set_title(char* _filename) {
    char str[strlen(_filename)+1];
    char* dotpos = strrchr(_filename,'.');
    strncpy(str,_filename,dotpos-_filename);
    str[dotpos-_filename]=0;
    if (strrchr(str,'\\')) {strncat(info.title,strrchr(str,'\\')+1,63);}
    else if (strrchr(str,'/')) {strncat(info.title,strrchr(str,'/')+1,63);}
    else if (strlen(str)>63) {strncat(info.title,&(_filename[strlen(str)-63]),63);}
    else {strncat(info.title, str, 63);}
}


void* Source::thread_start(void* _source) {
    Source* source=(Source*) _source;
    source->run();
    printf("[Source::thread_start] Thread finished\n");
}


void Source::run() {
    while(!this->_stop) {
        this->step();
    }
}


void Source::step() {
    if (!this->ffmpeg_decode_frame()) {
    } else {
        this->_stop = true;
    }
    this->swap_buffers();



///fps
    cnt++;

    if (cnt>=50) {
        cnt=0;
        double time2=Clock.GetElapsedTime();
        double dif=time2-time;
        time=time2;
        fps=50.0/dif;
        printf("%03.2f fps  %s\n",fps,this->info.title);
    }

}


void Source::swap_buffers() {
    void* buf;
    buf = this->buf_back;
    this->buf_back = this->buf_front;
    this->buf_front = buf;
}
