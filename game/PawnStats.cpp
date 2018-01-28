#include "PawnStats.h"
#include "GameObject.h"
#include "GameEvents.h"
#include "LayoutElement.h"
#include "Pawn.h"
#include <sstream>

PawnStats::PawnStats(mini::GameObject& owner) : mini::Component(owner)
{
}

PawnStats::~PawnStats()
{
}

void PawnStats::start()
{
	textRen = owner.getComponent<mini::TextRenderer>();
	GameEvents::getInstance().onPawnHoverStart.addCallback(
		[&](Pawn& pawn) 
		{
		std::shared_ptr<Game::Pawn> pwn = pawn.getGameStatePawn().lock();
		std::string pawnTypeName;
		switch (pwn->GetUnitType())
		{
		case Game::PawnType::Thug:
			pawnTypeName = "Thug";
			break;
		case Game::PawnType::Brawler:
			pawnTypeName = "Brawler";
			break;
		case Game::PawnType::Sentinel:
			pawnTypeName = "Sentinel";
			break;
		default:
			break;
		}
		std::string lastOrderName = "Stop";
		if (pwn->lastOrder == Game::OrderType::Advance)
		{
			lastOrderName = "Go";
			switch (pwn->direction)
			{
			case Game::Directions::North:
				lastOrderName.append(" north");
				break;
			case Game::Directions::South:
				lastOrderName.append(" south");
				break;
			case Game::Directions::East:
				lastOrderName.append(" east");
				break;
			case Game::Directions::West:
				lastOrderName.append(" west");
				break;
			default:
				break;
			}
		}
		
		std::stringstream ss;
			
		ss << "Type: " << pawnTypeName << std::endl
			<< "Health: " << pwn->GetHealth() << "/" << pwn->GetMaxHealth() << std::endl
			<< "Damage: " << pwn->GetMeeleAttack() << std::endl
			<< "Speed: " << pwn->GetSpeed() << std::endl
			<< "Last order: " << lastOrderName;
		textRen->setText(ss.str());
		owner.setActive(true);
		//owner.getComponent<mini::LayoutElement>()->refresh();
		}
	);
	GameEvents::getInstance().onPawnHoverEnd.addCallback([&](Pawn& pawn) {owner.setActive(false); });
	owner.setActive(false);
}
