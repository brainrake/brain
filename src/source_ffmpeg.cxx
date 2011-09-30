#include "source.hxx"

int Source::ffmpeg_init() {

//ffmpeg init mutex
    static pthread_mutex_t init_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock (&init_mutex);
////
    
    av_register_all();

    // Open video file
    if (av_open_input_file(&pFormatCtx, this->filename, NULL, 0, NULL)!=0)
    return -1; // Couldn't open file

    // Retrieve stream information
    if (av_find_stream_info(pFormatCtx)<0)
    return -1; // Couldn't find stream information

    // Dump information about file onto standard error
    //printf("source %d \n",info.id);
    //dump_format(pFormatCtx, 0, filename, 0);

    // Find the first video stream
    videoStream=-1;
    for (i=0; i<pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO) {
            videoStream=i;
            break;
        }
    }
    if (videoStream==-1)
        return -1; // Didn't find a video stream

    // Get a pointer to the codec context for the video stream
    pCodecCtx=pFormatCtx->streams[videoStream]->codec;

    // Find the decoder for the video stream
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec==NULL) {
    fprintf(stderr, "Unsupported codec!\n");
        return -1; // Codec not found
    }

    // Open codec
    if (avcodec_open(pCodecCtx, pCodec)<0)
        return -1; // Could not open codec


    this->info.width=pCodecCtx->width;
    this->info.height=pCodecCtx->height;

    // Allocate video frame
    pFrame=avcodec_alloc_frame();
    





    buf_front=(void*)malloc(4*this->info.width*this->info.height);
    buf_back=(void*)malloc(4*this->info.width*this->info.height);
    


    pthread_mutex_unlock (&init_mutex);



    // Set up colorspace conversion
    int w = pCodecCtx->width;
    int h = pCodecCtx->height;
    img_convert_ctx = sws_getContext(w, h,
        //is->video_st->codec->pix_fmt,
        pCodecCtx->pix_fmt,
        w, h,
        PIX_FMT_RGBA,
        //PIX_FMT_YUV420P,
        SWS_BICUBIC,
        NULL, NULL, NULL);

    if (img_convert_ctx == NULL) {
        fprintf(stderr, "[Source::ffmpeg_init] Cannot initialize the image conversion context!\n");
        return 1;
    }



    return 0;
}



int Source::ffmpeg_decode_frame() {

    i=0;
    while(av_read_frame(pFormatCtx, &packet)>=0) {
        // Is this a packet from the video stream?
        if (packet.stream_index==videoStream) {
            // Decode video frame
            avcodec_decode_video(pCodecCtx, pFrame, &frameFinished,
            packet.data, packet.size);

            
            // Did we get a video frame?
            if (frameFinished) {




                int line=pCodecCtx->width*4;
                sws_scale(img_convert_ctx, pFrame->data,
                    pFrame->linesize, 0,
                    pCodecCtx->height,
                    (uint8_t**)&(this->buf_back),
                    &line);


                // Free the packet that was allocated by av_read_frame
                av_free_packet(&packet);


                return 0;

            }
        }
    }

    av_seek_frame(pFormatCtx, -1, 0, 0);
    return 0;
    //return 1;
}
