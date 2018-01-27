#pragma once

class GameManager
{
private:
	const int playerCount = 2;
	int currentPlayerIndex = -1;
	int humanPlayerIndex = -1;
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	
	int getCurrentPlayerIndex() const;
	int getHumanPlayerIndex() const;
	bool isCurrentPlayerHuman() const;
	void setupGame(int humanPlayer);
	void endTurn();
private:
	GameManager();
	~GameManager();
};

