#pragma once
#include "Component.h"

namespace mini
{
	class Camera : public Component
	{
	public:
		Camera(GameObject& owner);
		virtual ~Camera();

		void update(float deltaTime) override;
	};
}
