#pragma once
#include "Component.h"
#include "SpriteRenderer.h"
#include <vector>
#include <utility>
#include <memory>

namespace mini
{
	class Animator : public Component
	{
	
	public:
		Animator(GameObject& owner);
		virtual ~Animator();
	};
}
