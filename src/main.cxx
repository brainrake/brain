#include "brain.hxx"

int main (int argc, char**argv) {
    Brain* brain = new Brain();

    //create layers
    for (int i=0; i < 4; i++) {
        Layer* layer = new Layer(brain);
        brain->add_layer(layer);
    }

    //create a source for each command line argument
    for (int i=1; i < argc; i++) {
        Source* source = new Source(argv[i]);
        brain->add_source(source);
    }

    //start the main loop
    brain->run();
    
    delete brain;
    return 0;
}
