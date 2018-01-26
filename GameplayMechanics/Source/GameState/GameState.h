#pragma once
#include <unordered_map>
#include <GameState.h>
#include <Move.h>


namespace Game
{
	class DefaultMove;

	class GameState : public grailMCTS::GameState
	{
		public:
			std::unique_ptr<grailMCTS::GameState> clone() const override;
			bool equals(const grailMCTS::GameState& other) const override;
			std::size_t playersCount() const override;
			grailMCTS::Result getResult() const override;
			int whoPlay() const override;
			std::vector<std::unique_ptr<const grailMCTS::Move>> getMoves() const override;
			void applyMove(const grailMCTS::Move& move) override;
			void applyMove(const DefaultMove& move);

		private:
	};
}