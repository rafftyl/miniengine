#include "Animator.h"
#include "Timer.h"

namespace mini
{
	Animator::Animator(GameObject& owner) : Component(owner)
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::start()
	{
		playAnimation(defaultAnimationName);
	}

	void Animator::update()
	{
		if (currentAnimation != nullptr)
		{
			currentAnimation->update(Time::getDeltaTime() * playbackSpeed);
			if (currentAnimation->isFinished())
			{
				playAnimation(defaultAnimationName);
			}
		}
	}

	void Animator::setDefaultAnimation(const std::string& name)
	{
		defaultAnimationName = name;
	}

	void Animator::setAnimations(const std::map<std::string, std::shared_ptr<Animation>>& animationMap)
	{
		animations = animationMap;
	}

	void Animator::playAnimation(const std::string& name)
	{
		currentAnimation = animations.find(name)->second;
		if (currentAnimation != nullptr)
		{
			currentAnimation->reset();
			currentAnimation->setRenderer(owner);
		}
	}

	void Animator::setPlaybackSpeed(float speed)
	{
		playbackSpeed = speed;
	}
}