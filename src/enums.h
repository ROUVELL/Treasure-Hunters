#pragma once

enum class Direction
{
	NONE = 0,
	LEFT = -1,
	RIGHT = 1
};

enum class MovementState
{
	IDLE = 0,
	RUN,
	JUMP,
	FALL,
};

enum class PlayerState
{
	IDLE = 0,
	RUN,
	JUMP,
	FALL,
	GROUND,
	HIT,
	ATTACK,
	AIR_ATTACK,
	DEAD
};