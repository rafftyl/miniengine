#pragma once
#include "Animation.h"
#include "SpriteRenderer.h"
#include <memory>
#include <vector>

namespace mini
{
	class SpritesheetAnimation : public Animation
	{
	private:
		std::vector<std::pair<float, std::shared_ptr<sf::Sprite>>> spritesheet;
		std::shared_ptr<SpriteRenderer> renderer;
	public:
		SpritesheetAnimation(std::vector<std::pair<float, std::shared_ptr<sf::Sprite>>>&& sprites, bool shouldLoop = true);
		~SpritesheetAnimation();
		void update(float deltaTime) override;
		void setRenderer(GameObject& rendererOwner) override;
	};
}
