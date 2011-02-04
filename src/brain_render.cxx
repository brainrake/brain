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
    
    window->SetFramerateLimit(100);

    // Set color and depth clear value
    glClearDepth(1.0f);
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

    //Enable Z-buffer read and write
    //glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);

    // Enable blending
    glEnable (GL_BLEND);


    //set up projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,WIDTH/(double)HEIGHT,0.2,100);
    gluLookAt( 0,0,1,
               0,0,0,
               0,1,0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    window->Display();
}

void Brain::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(unsigned int i=0; i<MAX_LAYERS;i++){
        if(this->layers[i]){
            this->layers[i]->render();
        }
    }

    this->render_fps();

    window->Display();
}

void Brain::render_fps(){
    static sf::Clock Clock;
    static double time=0;
    static double fps=0;

    static int cnt=0;
    cnt++;

    if(cnt==10){
        cnt=0;
        double time2=Clock.GetElapsedTime();
        double dif=time2-time;
        time=time2;
        fps=10/dif;
    }


    char str[255];
    sprintf(str,"%03.2f fps",fps);
    sf::String Text;
    Text.SetText(str);
    Text.SetColor(sf::Color(255, 255, 255));
    window->Draw(Text);
}


void Brain::close_render(){
    //TODO
}
