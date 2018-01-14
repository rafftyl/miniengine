#pragma once
#include "Component.h"

namespace mini
{
	class Camera : public Component
	{
	public:
		Camera(GameObject& owner);
		virtual ~Camera();
	protected:
		void update() override;
	};
}
