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
	static constexpr int brick_columns{ 10 };
	static constexpr int brick_rows{ 4 };
	static constexpr int brick_strength{ 3 };
	static constexpr int player_lives{ 3 };
	static constexpr float text_state_position_x{ window_width / 2.0f - 100.0f };
	static constexpr float text_state_position_y{ window_width / 2.0f - 100.0f };
	static constexpr int text_state_size{ 35 };
	static constexpr float text_lives_position_x{ window_width / 2.0f - 65.0f };
	static constexpr float text_lives_position_y{ window_width / 2.0f - 50.0f };
	static constexpr int text_lives_size{ 35 };
};
