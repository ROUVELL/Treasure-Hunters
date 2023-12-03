#include "Player.h"

Player::Player()
{
	animationComponent.load("player");
	animationComponent.setSprite(&sprite);
	animationComponent.change("idle");

	movementComponent.setSprite(&sprite);
	movementComponent.setSpeed(200.f);
	//movementComponent.setGravity(10.f);

	sprite.setScale(2.0, 2.0);
	sprite.setPosition(200, 200);
	auto [w, h] = sprite.getLocalBounds().getSize();
	sprite.setOrigin(w / 2.f, h / 2.f);

	shape.setSize(sprite.getLocalBounds().getSize());
	shape.setPosition(sprite.getPosition());
	shape.setScale(2.0, 2.0);
	shape.setOrigin(w / 2.f, h / 2.f);
	shape.setOutlineThickness(-0.5f);
	shape.setOutlineColor(sf::Color::Cyan);
	shape.setFillColor(sf::Color::Transparent);
}

void Player::processEvents(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Num1:
			animationComponent.change("idle sword");
			break;
		case sf::Keyboard::Num2:
			animationComponent.change("run sword");
			break;
		case sf::Keyboard::Num3:
			animationComponent.change("jump sword");
			break;
		case sf::Keyboard::Num4:
			animationComponent.change("air attack 1");
			break;
		case sf::Keyboard::Num5:
			animationComponent.change("ground sword");
			break;
		case sf::Keyboard::Num6:
			animationComponent.change("hit sword");
			break;
		case sf::Keyboard::Num7:
			animationComponent.change("attack 1");
			break;
		case sf::Keyboard::Num8:
			animationComponent.change("attack 2");
			break;
		case sf::Keyboard::Num9:
			animationComponent.change("attack 3");
			break;
		case sf::Keyboard::Num0:
			animationComponent.change("air attack 2");
			break;
		default:
			break;
		}
	}
}

void Player::movement()
{
	movementComponent.setDirection(Direction::NONE);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movementComponent.setDirection(Direction::LEFT);
		sprite.setScale(-2.0, 2.0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementComponent.setDirection(Direction::RIGHT);
		sprite.setScale(2.0, 2.0);
	}
}

void Player::checkState()
{
	switch (movementComponent.getState())
	{
	case MovementState::IDLE:
		animationComponent.change("idle");
		break;

	case MovementState::RUN:
		animationComponent.change("run");
		break;

	case MovementState::JUMP:
		animationComponent.change("jump");
		break;

	case MovementState::FALL:
		animationComponent.change("fall");
		break;

	default:
		break;
	}
}

void Player::update(float dt)
{
	movement();
	movementComponent.update(dt);
	shape.setPosition(sprite.getPosition());

	checkState();
	animationComponent.update();
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
	window.draw(shape);
}
