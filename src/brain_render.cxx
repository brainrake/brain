#include "brain.hxx"

#define WIDTH 800
#define HEIGHT 600


void Brain::init_render() {
    //display settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    //Settings.AntialiasingLevel = 2;

    //create window
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT, 32), "brain::output",sf::Style::Close, settings);

    glewInit();
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        printf("glewInit failed, aborting.\n");
        exit (1);
    }
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("OpenGL version %s supported\n", glGetString(GL_VERSION));


    //preserve state when drawing via SFML
    //window->preserveOpenGLStates(true);

    window->setFramerateLimit(200);

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

    window->display();
}


void Brain::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i=0; i<MAX_LAYERS; i++) {
        if (this->layers[i]) {
            this->layers[i]->render();
        }
    }

    this->render_fps();

    window->display();
}


void Brain::render_fps() {
    static int i = 0;
    static sf::Int64 d = 0;
    static double fps = 0;
    if (i == 100) { fps = 100 * 1000000/((double) d); d = 0; i = 0; }
    d += this->delta;
    i++;

    char str[255];
    sprintf(str, "%03.2f fps", fps);
    //sf::Font font;
    //font.loadFromFile("arial.ttf");
    //sf::Text text = sf::Text();
    //text.setString(str);//, font);
    //text.setColor(sf::Color(255, 255, 255));
    //window->draw(text);
}


void Brain::close_render() {
    //TODO
}
