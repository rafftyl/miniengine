#pragma once
namespace mini
{
	class Animation
	{
	protected:
		float timer = 0;
	private:		
		float loopDuration;
		bool loop;	
	public:
		virtual void update(float deltaTime);
		void reset();
		virtual void setRenderer(class GameObject& rendererOwner) = 0;
		bool isFinished() const;
	protected:
		Animation(bool shouldLoop);
		~Animation();
		void setLoopDuration(float duration);
	};
}
