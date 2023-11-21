#include "interactions.h"

#include <cmath>


// Determine wether two entities overlap
bool is_interacting(const entity& e1, const entity& e2)
{
	auto box1 = e1.get_bounding_box();
	auto box2 = e2.get_bounding_box();
	return box1.intersects(box2);
}


// Resolve potential collision between the ball and the paddle
void handle_collision(ball& b, paddle& p)
{
	if (is_interacting(b, p))
	{
		// Make the ball bounce upwards
		b.move_up();

		// Make the new direction depend on where the collision occurs on the paddle
		// If the collision is on the left of the paddle, make the ball bounce to the left
		// Otherwise, make the ball bounce to the right
		if (b.x() <= p.x())
		{
			b.move_left();
		}
		else
		{
			b.move_right();
		}
	}
}


// Resolve potential collision between the ball and a brick
void handle_collision(ball& b, brick& p)
{
	if (is_interacting(b, p))
	{
		// Update the brick's strength
		p.weaken();

		// The brick is destroyed if its too weak
		if (p.is_too_weak())
		{
			p.destroy();
		}

		// Make the new direction depend on where the collision occures on the brick
		// If the ball collides on the side of the brick, make the ball bounce to the side
		// If the ball collides on the top/bottom of the brick, make the ball bounce to the top/bottom

		// First, we find the amount of overlap in each direction, for example:
		// The smaller the left overlap, the closer the ball is to the left side of the brick
		// And similarly for the other sides of the brick
		float left_overlap = b.right() - p.left();
		float right_overlap = b.left() - p.right();
		float top_overlap = b.bottom() - p.top();
		float bottom_overlap = b.top() - p.bottom();

		// If the left overlap is smaller than the right overlap, the ball hit the left side of the brick
		bool from_left = std::abs(left_overlap) < std::abs(right_overlap);
		bool from_top = std::abs(top_overlap) < std::abs(bottom_overlap);

		// Use the right or left overlap as appropriate
		float min_x_overlap = from_left ? left_overlap : right_overlap;
		float min_y_overlap = from_top ? top_overlap : bottom_overlap;

		// If the ball hit the left or right side of the brick, change its horizontal direction
		// If the ball hit the top or bottom of the brick, change its vertical direction
		if (std::abs(min_x_overlap) < std::abs(min_y_overlap))
		{
			if (from_left)
			{
				b.move_left();
			}
			else
			{
				b.move_right();
			}
		}
		else
		{
			if (from_top)
			{
				b.move_up();
			}
			else
			{
				b.move_down();
			}
		}
	}
}
