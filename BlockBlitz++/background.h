#pragma once


#include "constants.h"
#include "entity.h"


// Class to represent the background
// Inherits from entity
class background :
    public entity
{
private:
    sf::Texture texture;

public:
    // Interface of the class

    // Constructor
    // Arguments are the initial coordinates of the center of the background
    // SFML uses the computer graphics convention where
    // (0, 0) is the top left corner of the screen
    // x increases to the right
    // y increases downwards
    background(float x, float y);

    // Implement pure virtual functions
    void update() override;
    void draw(sf::RenderWindow& rw) override;
};

