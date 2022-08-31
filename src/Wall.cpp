#include <Wall.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

// Temporário
#include <iostream>

Wall::Wall(int height, int width){
    this->win_height = height;
    this->win_width = width;
}

Wall::~Wall(){}

void Wall::set_block_size(int height, int width){
    this->sq_width = width;
    this->sq_height = height;
}

void Wall::draw(){

    for (int i = 0; i < this->win_height; i += this->sq_height){
        for (int j = 0; j < this->win_width; j += this->sq_width){

            int x_coord = (i * this->win_width) / (this->sq_width * this->sq_width);
            int y_coord = (j) / this->sq_width;
            unsigned int value = map1[0][x_coord + y_coord];

            if (value == 0xff000000) continue;
            sf::RectangleShape block;
            block.setSize(sf::Vector2f(this->sq_width, this->sq_height));
            sf::Vector2f blockPosition(i, j);
            block.setPosition(blockPosition); 
            block.setFillColor(sf::Color(100, 100, 100));
            this->blocks_list.push_back(block);
        }
    }
}

std::vector<sf::RectangleShape> &Wall::get_block_list(){
    return this->blocks_list;
}
