#include "MovementComponent.h"

MovementComponent::MovementComponent()
	: speed(0.f), direction(0.f),
	velocity(0.f, 0.f), sprite(nullptr)
{

}

MovementState MovementComponent::getState() const
{
	if (velocity.x == 0.0 && velocity.y == 0.0)
		return MovementState::IDLE;
	if (velocity.y > 0.0)
		return MovementState::FALL;
	if (velocity.y < 0.0)
		return MovementState::JUMP;

	return MovementState::RUN;
}

void MovementComponent::update(float dt)
{
	velocity.x = speed * direction * dt;


	sprite->move(velocity);
}
