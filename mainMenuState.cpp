//
// Created by Nina on 2022/1/10.
//

#include "MainMenuState.h"

// constructor
mainMenuState::mainMenuState(sf::RenderWindow* window, std:: stack<State*>* states) : State(window, states)  // constructor
{
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Black);
    this->initBanner();
    this->initFont();  // load  font
    this->initButton();  // create button
    this->initDecoration();  // create AC_girl at top-right corner
    this->initMusic();
    std::cout << "a mainMenuState is create" << std::endl;
}

// destructor
mainMenuState::~mainMenuState(){

    auto it = this -> button.begin();
    for(it = this->button.begin(); it != this->button.end(); ++it){

        delete it->second;
    }


}

// functions
void mainMenuState::initMusic() {

    if(!this->music.openFromFile("/Users/nina/Desktop/C++practice/Game/pickachu.ogg")){
        std::cout << "BGM failed to open" << "\n";
    }
    music.setVolume(40);
    this->music.play();

}

void mainMenuState::initBanner() {
    this->Banner.setPosition(700, 400);
    this->Banner.setSize(sf::Vector2f(1100, 200));  // width , length
    this->Banner.setFillColor(sf::Color::Blue);

    this->banner_text.setFont(font);
    this->banner_text.setString(" PROFESSOR ! LET'S PLAY VOLLEYBALL !");
    this->banner_text.setFillColor(sf::Color::Yellow);
    this->banner_text.setCharacterSize(50);
    this->banner_text.setPosition(
            this->Banner.getPosition().x +(this->Banner.getGlobalBounds().width / 2.f) - this->Banner.getGlobalBounds().width / 2.f,
            this->Banner.getPosition().y + (this->Banner.getGlobalBounds().height / 2.f) - this->Banner.getGlobalBounds().height / 4.f
    );

}

void mainMenuState::initDecoration() {
    if(!this->decoration_t1.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/ACgirl.png")){
        std:: cout << "AC_girl.png loading issue !!!" << "\n";
    }
    decoration_s1.setTexture(decoration_t1);
    decoration_s1.setPosition(1840, 250);

    if(!this->decoration_t2.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/ywTsai.png")){
        std:: cout << "ywTsai.png loading issue !!!" << "\n";
    }
    decoration_s2.setTexture(decoration_t2);
    decoration_s2.setPosition(100, 230);
    decoration_s2.scale(0.2f, 0.2f);
    this->decoDir = 1.f;

    if(!this->decoration_t3.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/pdogs.png")){
        std:: cout << "pdogs.png loading issue !!!" << "\n";
    }
    decoration_s3.setTexture(decoration_t3);
    decoration_s3.setPosition(0, 2000);
    decoration_s3.scale(.15f, .15f);
    this->ballDirX = 1.f;
    this->ballDirY = 1.f;
    this->ballGravity = .1f;
    this->ballVelocity = sf::Vector2f(4.f, 2.f);


}


void mainMenuState::initButton() {
    // start button

    this->button["Game_STATE"] = new Button(1150, 1000, 100, 200, "PRESS START", &this->font,
                                            sf::Color(70,70,70,200),
                                            sf::Color(150,150,150,255),
                                            sf::Color(20,20,20,200) );

    // config
    this->button["setting_btn"] = new Button(1150, 1150, 100, 200, "OPTION", &this->font,
                                             sf::Color(70,70,70,200),
                                             sf::Color(150,150,150,255),
                                             sf::Color(20,20,20,200) );


    // end button
    this->button["EXIT_STATE"] = new Button(1150, 1300, 100, 200, "PRESS EXIT", &this->font,
                                            sf::Color(70,70,70,200),
                                            sf::Color(150,150,150,255),
                                            sf::Color(20,20,20,200) );
}

void mainMenuState::initFont(){  // loadFont
    if(!this->font.loadFromFile("/Users/nina/Desktop/C++practice/Game/font/VCR_OSD_MONO_1.001.ttf")){
        throw("ERROR::MAINMENUSTATE::COUNLD NOT LOAD FONT.");
    }
}

void mainMenuState::endstate(){  // close MainMenu for debug
    std::cout << "end the MainMenuState." << std::endl;
}

void mainMenuState::updateInput(const float &dt) {  // end state ?
    this->checkForEnd();
}

// update all the button and deal with their functionality
void mainMenuState::updateButton() {
    for(auto &it : this->button){  // in the button map
        it.second->update(this->mousePosView);  // update button status
    }

    // new game
    if(this->button["Game_STATE"]->isPressed()){
        this->music.pause();
        std::cout << "go to game state" << "\n";
        this-> states->push(new GameState(this->window, this-> states));

    }

    //QUIT GAME
    if(this->button["EXIT_STATE"]->isPressed()){
        this->music.pause();
        this-> wantEnd = true;
    }

}

void mainMenuState:: updateImageAnimation()
{
    imageAnimation();
    imageMove();
}

void mainMenuState:: imageMove()
{
    this-> decoration_s1.move(0.f, this->decoDir);
    this->decoration_s2.move(0.f, this->decoDir);
}

void mainMenuState::imageAnimation() {
    if(this->decoration_s1.getGlobalBounds().top < 230.f)
    {
        this->decoDir = 1.f;
    }
    else if(this->decoration_s1.getGlobalBounds().top > 250.f)
    {
        this->decoDir = -1.f;
    }
}

void mainMenuState::ballmove() {
    this->decoration_s3.move(this->ballVelocity.x * this-> ballDirX, this->ballVelocity.y * this->ballDirY);
}

void mainMenuState:: ballVelocityChange()
{
    this-> ballVelocity.y += ballGravity;
    if(this->decoration_s3.getPosition().y < 2000 * 2/3 && this->ballDirY == -1.f)
        this->ballVelocity.y +=  -2 * ballGravity;
//    else if(this->decoration_s3.getPosition().y > 2000 * 2/3 && this->ballDirY == 1.f)
//        this-> ballVelocity.y += 2 * ballGravity;
}

void mainMenuState::ballCollision() {
    if(this->decoration_s3.getGlobalBounds().left <= 0.f)
    {
        this->ballDirX = 1.f;
        this->decoration_s3.setPosition(0, this->decoration_s3.getPosition().y);
    }
    else if(this->decoration_s3.getGlobalBounds().left + this->decoration_s3.getGlobalBounds().width >= 2500)
    {
        this->ballDirX = -1.f;
        this->decoration_s3.setPosition(2500 - this->decoration_s3.getGlobalBounds().width, this->decoration_s3.getPosition().y);
    }
    else if(this->decoration_s3.getGlobalBounds().top + this->decoration_s3.getGlobalBounds().height >= 2000.f)
    {
        this-> ballDirY = -1.f;
        this->decoration_s3.setPosition(this->decoration_s3.getPosition().x, 2000 - this->decoration_s3.getGlobalBounds().height);
    }

}

void mainMenuState:: updateBall()
{
    this->ballVelocityChange();
    this->ballCollision();
    this->ballmove();
}

void mainMenuState::update(const float& dt){  //
    this->updateImageAnimation();
    this->updateBall();
    this->updateMousePosition();
    this-> updateInput(dt);  // weather ESC is pressed
    this->updateButton();  // update buttons status
}

void mainMenuState::renderButtons(sf::RenderTarget *target) {
    for (auto &it : this->button)
    {
        it.second->render(target);
    }

}

void mainMenuState:: render(sf::RenderTarget* target){

    if (!target)
        target = window;

    target->draw(this->background);
    target->draw(this->Banner);
    target->draw(this->banner_text);
    target->draw(this->decoration_s1);
    target->draw(this->decoration_s2);
    target->draw(this->decoration_s3);
    this->renderButtons(target);

}
