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
            switch(Event.Key.Code){
            case sf::Key::F1: selected_layer=0; break;
            case sf::Key::F2: selected_layer=1; break;
            case sf::Key::F3: selected_layer=2; break;
            case sf::Key::F4: selected_layer=3; break;

            case sf::Key::A: this->layers[selected_layer]->info.tx-=0.2;break;
            case sf::Key::D: this->layers[selected_layer]->info.tx+=0.2;break;
            case sf::Key::S: this->layers[selected_layer]->info.ty-=0.2;break;
            case sf::Key::W: this->layers[selected_layer]->info.ty+=0.2;break;

            case sf::Key::R: this->layers[selected_layer]->info.a+=0.2;break;
            case sf::Key::F: this->layers[selected_layer]->info.a-=0.2;break;
            }
        }
    }
}
