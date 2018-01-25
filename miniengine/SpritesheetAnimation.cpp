#include "SpritesheetAnimation.h"
#include "GameObject.h"
#include <algorithm>

namespace mini
{
	SpritesheetAnimation::SpritesheetAnimation(std::vector<std::pair<float, std::shared_ptr<sf::Sprite>>>&& sprites, bool shouldLoop) : Animation(shouldLoop), spritesheet(std::move(sprites))
	{
		float duration = 0;
		for (const auto& spritePair : spritesheet)
		{
			duration += spritePair.first;
		}
		setLoopDuration(duration);
	}

	SpritesheetAnimation::~SpritesheetAnimation()
	{
	}

	void SpritesheetAnimation::update(float deltaTime)
	{
		Animation::update(deltaTime);
		float accumulatedTime = 0;
		for (const auto& spritePair : spritesheet)
		{
			accumulatedTime += spritePair.first;
			if (timer < accumulatedTime)
			{
				renderer->setSprite(spritePair.second);
				break;
			}
		}
	}

	void SpritesheetAnimation::setRenderer(GameObject& rendererOwner)
	{
		renderer = rendererOwner.getComponent<SpriteRenderer>();
	}
}