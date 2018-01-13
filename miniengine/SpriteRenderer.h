#pragma once
#include "Renderer.h"
#include <memory>

namespace sf { class Sprite; }
namespace mini
{
	class SpriteRenderer : public Renderer
	{
	private:
		std::shared_ptr<sf::Sprite> sprite;
	public:
		SpriteRenderer(GameObject& owner);
		virtual ~SpriteRenderer();

		void setSprite(const std::shared_ptr<sf::Sprite>& sharedSprite);		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
