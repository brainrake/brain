#include "brain.hxx"

int main (int argc, char**argv){
    Brain* brain = new Brain();
    
    
    Source* source1 = new Source();
    brain->add_source(source1);
    
    Layer* layer1 = new Layer();
    layer1->set_source(source1);
    
    brain->add_layer(layer1);
    
    

    Source* source2 = new Source();
    brain->add_source(source2);
    
    Layer* layer2 = new Layer();
    layer2->set_source(source2);

    brain->add_layer(layer2);


    brain->run();
    
    delete brain;
    return 0;
}
