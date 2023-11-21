#pragma once


struct constants
{
	static constexpr int window_width{ 520 };
	static constexpr int window_height{ 450 };
	static constexpr int framerate_limit{ 60 };
	static constexpr float ball_speed{ 6.0f };
	static constexpr float paddle_width{ 90.0f };
	static constexpr float paddle_height{ 20.0f };
	static constexpr float paddle_speed{ 8.0f };
	static constexpr float brick_width{ 43.0f };
	static constexpr float brick_height{ 20.0f };
	static constexpr float brick_offset{ brick_width / 2.0f };
	static constexpr float brick_columns{ 10 };
	static constexpr float brick_rows{ 4 };
};
