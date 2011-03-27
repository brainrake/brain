#include "layer.hxx"


void Layer::init_render(){
    glGenTextures( 1, &texture );
    glActiveTexture(texture);
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    this->_ready = true;
}


void Layer::render(){
    if (!this->_ready) { return; }
    
    glPushMatrix();

    //apply translation, rotation and scaling
    glTranslatef(info.tx,info.ty,info.tz);
    glRotatef(info.ry,0,1,0);
    glRotatef(info.rx,1,0,0);
    glRotatef(info.rz,0,0,1);
    glScalef(info.sx,info.sy,info.sz);


    //TODO: set blending mode
    switch (info.blending){
        case 1: //inverse alpha
            glBlendFunc (GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA); break;
        case 0:
        default://alpha
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
    }

    //texture
    if (this->source and this->source->buf_front){
        glActiveTexture(this->texture);
        //if(!this->_texture_ready){
        //    this->_texture_ready = true;
            glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, this->source->info.width, this->source->info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->source->buf_front);
        //} else {
        //    glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, this->source->info.width, this->source->info.height, GL_RGBA, GL_UNSIGNED_BYTE, this->source->buf_front);
        //}
        glEnable(GL_TEXTURE_2D);
    }

    //TODO: store this
    float aspect = this->source->info.width / (float) this->source->info.height;

    //draw rectangle
    glColor4f(info.r,info.g,info.b,info.a);
    glBegin( GL_QUADS );
        //TODO: use aspect ratio info from source
        glTexCoord2d(0,1); glVertex3d(-aspect,-1,0);
        glTexCoord2d(1,1); glVertex3d( aspect,-1,0);
        glTexCoord2d(1,0); glVertex3d( aspect, 1,0);
        glTexCoord2d(0,0); glVertex3d(-aspect, 1,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void Layer::close_render(){
    this->_ready = false;
    glDeleteTextures(1,&texture);
}
