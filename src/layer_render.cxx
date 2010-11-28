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
    glActiveTexture(texture);
    
    glPushMatrix();

    //apply translation, rotation and scaling
    glTranslatef(info.tx,info.ty,info.tz);
    glRotatef(0,1,0,info.ry);
    glRotatef(1,0,0,info.rx);
    glRotatef(0,0,1,info.rz);
    glScalef(info.sx,info.sy,info.sz);


    //NOTE: NTSC luminosity color scaling: red 0.299; green 0.587; blue 0.114;
    //TODO: set blending mode
    switch (info.blending){
        case 1: //luma key
        case 0:
        default://alpha blending
        ;
    }


    
    if (this->source and this->source->buf_front){
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, this->source->info.width, this->source->info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->source->buf_front);
        glEnable(GL_TEXTURE_2D);
    }

    //draw rectangle
    glBegin( GL_QUADS );
        glColor4f(info.r,info.g,info.b,info.a);
        //TODO: use aspect ratio info from source
        glTexCoord2d(0,1); glVertex3d(-1,-1,0);
        glTexCoord2d(1,1); glVertex3d( 1,-1,0);
        glTexCoord2d(1,0); glVertex3d( 1, 1,0);
        glTexCoord2d(0,0); glVertex3d(-1, 1,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void Layer::close_render(){
    this->_ready = false;
    glDeleteTextures(1,&texture);
}
