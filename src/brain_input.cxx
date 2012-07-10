#include "brain.hxx"

void Brain::input(){

    static int selected_layer=0;

    sf::Event event;
    while (window->pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed)
            this->_stop=true;

        // Escape key : exit
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
            this->_stop=true;
        }
        // Resize event : adjust viewport
        if (event.type == sf::Event::Resized){
            window->setActive();
            glViewport(0, 0, event.size.width, event.size.height);
        }
        if (event.type == sf::Event::KeyPressed){
            if ( !event.key.shift and !event.key.control){
                switch(event.key.code){
                    case sf::Keyboard::F1: if(this->layers[0]){selected_layer=0;} break;
                    case sf::Keyboard::F2: if(this->layers[1]){selected_layer=1;} break;
                    case sf::Keyboard::F3: if(this->layers[2]){selected_layer=2;} break;
                    case sf::Keyboard::F4: if(this->layers[3]){selected_layer=3;} break;
                    case sf::Keyboard::F5: if(this->layers[4]){selected_layer=4;} break;
                    case sf::Keyboard::F6: if(this->layers[5]){selected_layer=5;} break;
                    case sf::Keyboard::F7: if(this->layers[6]){selected_layer=6;} break;
                    case sf::Keyboard::F8: if(this->layers[7]){selected_layer=7;} break;

                    case sf::Keyboard::Left:  this->layers[selected_layer]->info.tx-=0.2;break;
                    case sf::Keyboard::Right: this->layers[selected_layer]->info.tx+=0.2;break;
                    case sf::Keyboard::Down:  this->layers[selected_layer]->info.ty-=0.2;break;
                    case sf::Keyboard::Up:    this->layers[selected_layer]->info.ty+=0.2;break;

                    case sf::Keyboard::PageUp:   this->layers[selected_layer]->info.a+=0.2;break;
                    case sf::Keyboard::PageDown: this->layers[selected_layer]->info.a-=0.2;break;

                    case sf::Keyboard::Q:  if(this->sources[0]){this->layers[selected_layer]->set_source(this->sources[0]);} break;
                    case sf::Keyboard::W:  if(this->sources[1]){this->layers[selected_layer]->set_source(this->sources[1]);} break;
                    case sf::Keyboard::E:  if(this->sources[2]){this->layers[selected_layer]->set_source(this->sources[2]);} break;
                    case sf::Keyboard::R:  if(this->sources[3]){this->layers[selected_layer]->set_source(this->sources[3]);} break;
                    case sf::Keyboard::T:  if(this->sources[4]){this->layers[selected_layer]->set_source(this->sources[4]);} break;
                    case sf::Keyboard::A:  if(this->sources[5]){this->layers[selected_layer]->set_source(this->sources[5]);} break;
                    case sf::Keyboard::S:  if(this->sources[6]){this->layers[selected_layer]->set_source(this->sources[6]);} break;
                    case sf::Keyboard::D:  if(this->sources[7]){this->layers[selected_layer]->set_source(this->sources[7]);} break;
                    case sf::Keyboard::F:  if(this->sources[8]){this->layers[selected_layer]->set_source(this->sources[8]);} break;
                    case sf::Keyboard::G:  if(this->sources[9]){this->layers[selected_layer]->set_source(this->sources[9]);} break;
                }
            } else if ( event.key.shift and !event.key.control){
                switch(event.key.code){
                    case sf::Keyboard::Left:  this->layers[selected_layer]->info.sx-=0.1;break;
                    case sf::Keyboard::Right: this->layers[selected_layer]->info.sx+=0.1;break;
                    case sf::Keyboard::Down:  this->layers[selected_layer]->info.sy-=0.1;break;
                    case sf::Keyboard::Up:    this->layers[selected_layer]->info.sy+=0.1;break;
                }
            } else if ( !event.key.shift and event.key.control ){
                switch(event.key.code){
                    case sf::Keyboard::Left:  this->layers[selected_layer]->info.rz+=1;break;
                    case sf::Keyboard::Right: this->layers[selected_layer]->info.rz-=1;break;
                    case sf::Keyboard::Down:  this->layers[selected_layer]->info.rx+=1;break;
                    case sf::Keyboard::Up:    this->layers[selected_layer]->info.rx-=1;break;
                }
            } else if ( event.key.shift and event.key.control){
                switch(event.key.code){
                    case sf::Keyboard::Left:  this->layers[selected_layer]->info.ry+=1;break;
                    case sf::Keyboard::Right: this->layers[selected_layer]->info.ry-=1;break;
                    case sf::Keyboard::Up:    this->layers[selected_layer]->info.tz+=1;break;
                    case sf::Keyboard::Down:  this->layers[selected_layer]->info.tz-=1;break;
                }
            }
        }
    }
}


//TODO
/*
void set_active_layer() {
}

void set_source() {
}
*/
