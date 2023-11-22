#include "Player.h"

Player::Player()
{
	animationComponent.load("player");
	animationComponent.setSprite(&sprite);

	sprite.setScale(2.0, 2.0);
	sprite.setPosition(200, 200);
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

void Player::update()
{
	animationComponent.update();
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}
