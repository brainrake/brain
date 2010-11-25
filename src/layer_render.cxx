#include "layer.hxx"


void Layer::init_render(){

    this->_ready = true;
}


void Layer::render(){
    glPushMatrix();

    //apply layer properties
    glTranslatef(info.tx,info.ty,info.tz);
    glRotatef(0,1,0,info.ry);
    glRotatef(1,0,0,info.rx);
    glRotatef(0,0,1,info.rz);
    glScalef(info.sx,info.sy,info.sz);

    //draw rectangle
    glBegin( GL_QUADS );
        glColor4f(info.r,info.g,info.b,info.a);
        glVertex3d(-1.3333333f,-1,0);
        glVertex3d( 1.3333333f,-1,0);
        glVertex3d( 1.3333333f, 1,0);
        glVertex3d(-1.3333333f, 1,0);
    glEnd();

    glPopMatrix();
}

void Layer::close_render(){
    this->_ready = false;
}
