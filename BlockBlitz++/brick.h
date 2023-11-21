#pragma once

#include "entity.h"
#include "constants.h"


// Class to represent a brick
// Inherits from entity
class brick :
    public entity
{
private:
    static sf::Texture texture;

    // How many times the brick can be hit before destroying it
    int strength{ constants::brick_strength };

public:
    // Interface of the class

    // Constructor
    // Arguments are the initial coordinates of the brick
    // SFML uses the computer graphics convention where
    // (0, 0) is the top left corner of the screen
    // x increases to the right
    // y increases downwards
    brick(float x, float y);

    // Helper functions for brick strength
    void set_strength(int s) noexcept;
    void weaken() noexcept;
    bool is_too_weak() noexcept;

    // Implement pure virtual functions
    void update() override;
    void draw(sf::RenderWindow& rw) override;
};

