#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Player.hpp>
#include <Wall.hpp>

//  Player(double WINDOW_WIDTH, double WINDOW_HEIGHT, float GRID_SIZE) {
//      this->GRID_SIZE = GRID_SIZE;
//      this->movement_speed = GRID_SIZE;
//      this->player_position = new sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
//      body.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE));
//      body.setPosition(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2)); 

//  }


Player::Player(){}
Player:: Player(sf::Vector2f position, float GRID_SIZE, float WINDOW_WIDTH, float WINDOW_HEIGHT, Wall wall) {
    this->GRID_SIZE = GRID_SIZE;
    this->WINDOW_HEIGHT = WINDOW_HEIGHT;
    this->WINDOW_WIDTH = WINDOW_WIDTH;
    this->movement_speed = GRID_SIZE;
    this->position = position;
    this->wall = wall;

    this->velocity = sf::Vector2f(0, 0);

    this->body.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE));
    this->body.setPosition(sf::Vector2f(position)); 

}


void Player::move(sf::Event event){

    bool moving_left = false;
    bool moving_down = false;
    bool moving_up = false;
    bool moving_right = false;   

    velocity.x = 0;
    velocity.y = 0;
    switch(event.type){
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Right){
                moving_right = true;
                velocity.x = movement_speed;
            }
            if(event.key.code == sf::Keyboard::Down){
                moving_down = true;
                velocity.y = movement_speed;                        
            }
            if(event.key.code == sf::Keyboard::Up){
                moving_up = true;
                velocity.y = -movement_speed;
            }
            if(event.key.code == sf::Keyboard::Left){
                moving_left = true;
                velocity.x = -movement_speed;
            }

            break;

        case sf::Event::KeyReleased:
            if(event.key.code == sf::Keyboard::Right){
                moving_right = false;
            }
            if(event.key.code == sf::Keyboard::Down){
                moving_down = false;
            }
            if(event.key.code == sf::Keyboard::Up){
                moving_up = false;
            }
            if(event.key.code == sf::Keyboard::Left){
                moving_left = false;
            }
            break;

            default:
            break;
    }

    // Colisão bordas.
    sf::Vector2f nextPosition = body.getPosition() + body.getSize() + velocity;
    // Calisão paredes

    bool can = true;
    for (auto w: wall.get_block_list()){
        auto pos = w.getPosition();
        if (abs(pos.x - nextPosition.x + 10) + abs(pos.y - nextPosition.y + 10) < 10) {
            can = false;
        }
            
    }
    if(can and nextPosition.x > 0 and nextPosition.x <= WINDOW_WIDTH and nextPosition.y > 0 and nextPosition.y <= WINDOW_HEIGHT)
        body.move(velocity);


}
