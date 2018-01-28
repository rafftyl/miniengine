#pragma once
#include "Component.h"
#include "TextRenderer.h"

class PawnStats : public mini::Component
{
private:
	std::shared_ptr<mini::TextRenderer> textRen;
public:
	PawnStats(mini::GameObject& owner);
	~PawnStats();
	void start() override;
};

