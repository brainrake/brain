#include "brain.hxx"

void Brain::input(){

    static int selected_layer=0;

    sf::Event Event;
    while (window->GetEvent(Event))
    {
        // Close window : exit
        if (Event.Type == sf::Event::Closed)
            this->_stop=true;

        // Escape key : exit
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)){
            this->_stop=true;
        }
        // Resize event : adjust viewport
        if (Event.Type == sf::Event::Resized){
            window->SetActive();
            glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        }
        if (Event.Type == sf::Event::KeyPressed){
            if ( !Event.Key.Shift ){
                switch(Event.Key.Code){
                    case sf::Key::F1: if(this->layers[0]){selected_layer=0;} break;
                    case sf::Key::F2: if(this->layers[1]){selected_layer=1;} break;
                    case sf::Key::F3: if(this->layers[2]){selected_layer=2;} break;
                    case sf::Key::F4: if(this->layers[3]){selected_layer=3;} break;
                    case sf::Key::F5: if(this->layers[4]){selected_layer=4;} break;
                    case sf::Key::F6: if(this->layers[5]){selected_layer=5;} break;
                    case sf::Key::F7: if(this->layers[6]){selected_layer=6;} break;
                    case sf::Key::F8: if(this->layers[7]){selected_layer=7;} break;

                    case sf::Key::Left:  this->layers[selected_layer]->info.tx-=0.2;break;
                    case sf::Key::Right: this->layers[selected_layer]->info.tx+=0.2;break;
                    case sf::Key::Down:  this->layers[selected_layer]->info.ty-=0.2;break;
                    case sf::Key::Up:    this->layers[selected_layer]->info.ty+=0.2;break;

                    case sf::Key::PageUp:   this->layers[selected_layer]->info.a+=0.2;break;
                    case sf::Key::PageDown: this->layers[selected_layer]->info.a-=0.2;break;

                    case sf::Key::Q:  this->layers[selected_layer]->set_source(this->sources[0]);break;
                    case sf::Key::W:  this->layers[selected_layer]->set_source(this->sources[1]);break;
                    case sf::Key::E:  this->layers[selected_layer]->set_source(this->sources[2]);break;
                    case sf::Key::R:  this->layers[selected_layer]->set_source(this->sources[3]);break;
                    case sf::Key::T:  this->layers[selected_layer]->set_source(this->sources[4]);break;
                }
            } else if ( Event.Key.Shift ){ 
                switch(Event.Key.Code){
                    case sf::Key::Left:  this->layers[selected_layer]->info.sx-=0.1;break;
                    case sf::Key::Right: this->layers[selected_layer]->info.sx+=0.1;break;
                    case sf::Key::Down:  this->layers[selected_layer]->info.sy-=0.1;break;
                    case sf::Key::Up:    this->layers[selected_layer]->info.sy+=0.1;break;
                }
            }
        }
    }
}
