#pragma once

#include "entity.h"


// Class to represent a brick
// Inherits from entity
class brick :
    public entity
{
private:
    static sf::Texture texture;

public:
    // Interface of the class

    // Constructor
    // Arguments are the initial coordinates of the brick
    // SFML uses the computer graphics convention where
    // (0, 0) is the top left corner of the screen
    // x increases to the right
    // y increases downwards
    brick(float x, float y);

    // Implement pure virtual functions
    void update() override;
    void draw(sf::RenderWindow& rw) override;
};

