#include "brain.hxx"

#define WIDTH 800
#define HEIGHT 600


void Brain::init_render(){
    //display settings
    sf::WindowSettings Settings;
    Settings.DepthBits = 24;
    Settings.StencilBits = 8;
    //Settings.AntialiasingLevel = 2;
    
    //create window
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT, 32), "brain::output",sf::Style::Close, Settings);

    //preserve state when drawing via SFML
    window->PreserveOpenGLStates(true);
    
    window->SetFramerateLimit(60);

    // Set color and depth clear value
    glClearDepth(1.0f);
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

    //Enable Z-buffer read and write
    //glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);

    // Enable blending
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    window->Display();
}

void Brain::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(unsigned int i=0; i<MAX_LAYERS;i++){
        if(this->layers[i]){
            this->layers[i]->render();
        }
    }

    window->Display();
}

void Brain::close_render(){
    //TODO
}
