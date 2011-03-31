#include "brain.hxx"

int main (int argc, char**argv){
    Brain* brain = new Brain();


    for (int i=0; i < 4; i++) {
        Layer* layer = new Layer();
        brain->add_layer(layer);
    }

    for (int i=1; i < argc; i++) {
        Source* source = new Source(argv[i]);
        brain->add_source(source);
    }
    
    brain->run();
    
    delete brain;
    return 0;
}
