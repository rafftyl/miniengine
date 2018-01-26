#pragma once
#include "Component.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include <map>
#include <string>
#include <memory>

namespace mini
{
	class Animator : public Component
	{
	private:
		std::string defaultAnimationName;
		std::shared_ptr<Animation> currentAnimation;
		std::map<std::string, std::shared_ptr<Animation>> animations;
		float playbackSpeed = 1;
	public:
		Animator(GameObject& owner);
		virtual ~Animator();
		void start() override;
		void update() override;
		void setDefaultAnimation(const std::string& name);
		void setAnimations(const std::map<std::string, std::shared_ptr<Animation>>& animationMap);
		void playAnimation(const std::string& name);
		void setPlaybackSpeed(float speed);
	};
}
