#pragma once
#include "Renderer.h"
#include <memory>

namespace sf { class Shape; }
namespace mini
{
	class ShapeRenderer : public Renderer
	{
	private:
		std::shared_ptr<sf::Shape> shape;
	public:
		ShapeRenderer(GameObject& owner);
		virtual ~ShapeRenderer();
		void setShape(const std::shared_ptr<sf::Shape>& sharedShape);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		void tempUglyHack() const;
	};
}
