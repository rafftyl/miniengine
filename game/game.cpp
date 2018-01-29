// game.cpp : Defines the entry point for the console application.
//
#include "Miniengine.h"
#include "GameObject.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "BoxCollider.h"
#include "GameEvents.h"
#include "PawnStats.h"
#include "LayoutElement.h"
#include "CircleCollider.h"
#include "Screen.h"
#include "Pawn.h"
#include "PositionInterpolator.h"
#include "Field.h"
#include "Camera.h"
#include "UIButton.h"
#include "Moves/EndTurn.h"
#include "GameplaySystem.h"
#include "OrderPanel.h"
#include "GameState/Pawn.h"
#include "GameplayManager.h"
#include "GameManager.h"
#include "Prefab.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <sstream>


int main()
{
	mini::EngineSettings settings;
	settings.windowHeight = 1000;
	settings.windowWidth = 1920;

	sf::Texture texture_thug;
	texture_thug.loadFromFile("Assets/thug.png");
	texture_thug.setSmooth(true);
	auto thugSprite = std::make_shared<sf::Sprite>();
	thugSprite->setTexture(texture_thug);
	thugSprite->setOrigin({ texture_thug.getSize().x * 0.5f, texture_thug.getSize().y * 0.5f });

	sf::Texture texture_sentinel;
	texture_sentinel.loadFromFile("Assets/sentinel.png");
	texture_sentinel.setSmooth(true);
	auto sentinelSprite = std::make_shared<sf::Sprite>();
	sentinelSprite->setTexture(texture_sentinel);
	sentinelSprite->setOrigin({ texture_sentinel.getSize().x * 0.5f, texture_sentinel.getSize().y * 0.5f });

	sf::Texture texture_brawler;
	texture_brawler.loadFromFile("Assets/brawler.png");
	texture_brawler.setSmooth(true);
	auto brawlerSprite = std::make_shared<sf::Sprite>();
	brawlerSprite->setTexture(texture_brawler);
	brawlerSprite->setOrigin({ texture_brawler.getSize().x * 0.5f, texture_brawler.getSize().y * 0.5f });

	sf::Texture texture_stop;
	texture_stop.loadFromFile("Assets/stop.png");
	texture_stop.setSmooth(true);
	auto stopSprite = std::make_shared<sf::Sprite>();
	stopSprite->setTexture(texture_stop);
	stopSprite->setOrigin({ texture_stop.getSize().x * 0.5f, texture_stop.getSize().y * 0.5f });

	sf::Texture texture_2;
	texture_2.loadFromFile("Assets/back.png");
	texture_2.setSmooth(true);
	auto backButtonSprite = std::make_shared<sf::Sprite>();
	backButtonSprite->setTexture(texture_2);
	backButtonSprite->setOrigin({ texture_2.getSize().x * 0.5f, texture_2.getSize().y * 0.5f });

	sf::Texture texture_endTurn;
	texture_endTurn.loadFromFile("Assets/end_turn.png");
	texture_endTurn.setSmooth(true);
	auto endTurnButtonSprite = std::make_shared<sf::Sprite>();
	endTurnButtonSprite->setTexture(texture_endTurn);
	endTurnButtonSprite->setOrigin({ texture_endTurn.getSize().x * 0.5f, texture_endTurn.getSize().y * 0.5f });

	sf::Texture texture_3;
	texture_3.loadFromFile("Assets/up_arrow.png");
	texture_3.setSmooth(true);
	auto upArrowSprite = std::make_shared<sf::Sprite>();
	upArrowSprite->setTexture(texture_3);
	upArrowSprite->setOrigin({ texture_3.getSize().x * 0.5f, texture_3.getSize().y * 0.5f });

	sf::Texture texture_4;
	texture_4.loadFromFile("Assets/radio.png");
	texture_4.setSmooth(true);
	auto radioSprite = std::make_shared<sf::Sprite>();
	radioSprite->setTexture(texture_4);
	radioSprite->setOrigin({ texture_4.getSize().x * 0.5f, texture_4.getSize().y * 0.5f });

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/camo.png");
	backgroundTexture.setSmooth(true);
	backgroundTexture.setRepeated(true);
	auto backgroundSprite = std::make_shared<sf::Sprite>();
	backgroundSprite->setTexture(backgroundTexture);
	backgroundSprite->setOrigin({ backgroundTexture.getSize().x * 1.0f, backgroundTexture.getSize().y * 1.0f});
	sf::IntRect rect(-7000, -7000, 3000, 3000);
	backgroundSprite->setTextureRect(rect);
	auto rectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(1.0f, 1.0f));
	rectShape->setOrigin({ .5f , .5f});

	auto font = std::make_shared<sf::Font>();
	font->loadFromFile("Assets/die_hard.ttf");

	mini::Prefab textPrefab("label",
		[&](mini::GameObject& object)
	{
		object.setScreenSpace(true);
		auto text = object.addComponent<mini::TextRenderer>();
		text->setFont(font);
		text->setText("Dupa");
		text->setCharacterSize(45);
		text->setLayer(1);
		text->setColor(sf::Color::Black);
	});

	mini::Prefab backgroundPrefab("background",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(backgroundSprite);
		ren->setLayer(-1);
		object.setPosition({ 0.5f * settings.windowWidth, 0.5f * settings.windowHeight });
	});

	mini::Prefab buttonPrefab("button",
		[&](mini::GameObject& object) 
	{
		object.setScreenSpace(true);
		auto ren = object.addComponent<mini::ShapeRenderer>();
		ren->setColor(sf::Color(100, 100, 100, 180));
		ren->setShape(rectShape);
		
		object.addComponent<mini::BoxCollider>();		
		auto layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->applySettings({ false, false, false, false });
		layoutEl->setPosition({ 0.5f, 0.5f });
		layoutEl->setPivotPosition({ 0.5f, 0.5f });
		layoutEl->setSize({ 0.8f, 0.2f });
		object.addComponent<UIButton>();
	});

	mini::Prefab backButtonPrefab("backButton",
		[&](mini::GameObject& object)
	{
		object.setScreenSpace(true);
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(backButtonSprite);
		ren->setColor(sf::Color::White);

		object.addComponent<mini::BoxCollider>();
		auto layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setPosition({ 0.0f, 0.0f });
		layoutEl->setPivotPosition({ 0.0f, 0.0f });
		layoutEl->setSize({ 100.0f, 100.0f});
		object.addComponent<UIButton>();
	});

	mini::Prefab endTurnButtonPrefab("endTurnButton",
		[&](mini::GameObject& object)
	{
		object.setScreenSpace(true);
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(endTurnButtonSprite);
		ren->setColor(sf::Color::White);

		object.addComponent<mini::BoxCollider>();
		auto layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setPosition({ 0.0f, 0.0f });
		layoutEl->setPivotPosition({ 0.0f, 0.0f });
		layoutEl->setSize({ 100.0f, 100.0f });
		object.addComponent<UIButton>();
	});

	mini::Prefab thugPrefab("thug",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(thugSprite);
		ren->setLayer(2);
		object.addComponent<mini::BoxCollider>();
		object.addComponent<Pawn>()->setColors(sf::Color::Green, sf::Color::White);
		object.getComponent<Pawn>()->labelPrefab = textPrefab;
		object.addComponent<PositionInterpolator>();
		object.setScale({ 1.3f, 1.3f });
	});

	mini::Prefab sentinelPrefab("sentinel",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(sentinelSprite);
		ren->setLayer(2);
		object.addComponent<mini::BoxCollider>();
		object.addComponent<Pawn>()->setColors(sf::Color::Green, sf::Color::White);
		object.getComponent<Pawn>()->labelPrefab = textPrefab;
		object.addComponent<PositionInterpolator>();
		object.setScale({ 1.3f, 1.3f });
	});

	mini::Prefab brawlerPrefab("brawler",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(brawlerSprite);
		ren->setLayer(2);
		object.addComponent<mini::BoxCollider>();
		object.addComponent<Pawn>()->setColors(sf::Color::Green, sf::Color::White);
		object.getComponent<Pawn>()->labelPrefab = textPrefab;
		object.addComponent<PositionInterpolator>();
		object.setScale({ 1.3f, 1.3f });
	});

	mini::Prefab slotPrefab("slot",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::ShapeRenderer>();
		ren->setShape(rectShape);
		ren->setColor(sf::Color(0, 255, 255, 100));
		ren->setLayer(1);
		object.setScale({ 80, 80 });
	});

	mini::Prefab fieldPrefab("field",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::ShapeRenderer>();
		ren->setShape(rectShape);
		ren->setColor(sf::Color(120, 120, 120, 100));
		object.addComponent<mini::BoxCollider>();
		auto fieldComp = object.addComponent<Field>();
		fieldComp->setColors(sf::Color(0, 255, 255, 100), sf::Color(120,120,120,100));
		fieldComp->setSlotCount(3);
		fieldComp->setSlotPrefab(slotPrefab);
		object.setScale({ 200, 200 });
	});

	mini::Prefab orderButtonPrefab("orderButton",
		[&](mini::GameObject& object)
	{
		object.setScreenSpace(true);
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(upArrowSprite);
		ren->setLayer(5);
		
		auto layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setPivotPosition({ 0.5f, 0.5f });
		layoutEl->setSize({ 85.0f, 85.0f });
		object.addComponent<mini::BoxCollider>();

		object.addComponent<UIButton>();
	});

	mini::Prefab stopButtonPrefab("stopButton",
		[&](mini::GameObject& object)
	{
		object.setScreenSpace(true);
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(stopSprite);
		ren->setLayer(5);

		auto layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setPivotPosition({ 0.5f, 0.5f });
		layoutEl->setSize({ 85.0f, 85.0f });
		object.addComponent<mini::BoxCollider>();

		object.addComponent<UIButton>();
	});

	mini::Prefab orderPanelPrefab("orderPanel",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(radioSprite);

		auto layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setPosition({ 0.95f, 0.2f });
		layoutEl->setPivotPosition({ 1.0f, 0.5f });
		layoutEl->setSize({ 350, 600 });

		object.addComponent<OrderPanel>()->setParams({ 0, 320 }, { 2, 2 }, 100, orderButtonPrefab, stopButtonPrefab);
	});


	std::map<Game::PawnType, mini::Prefab> prefabMap = { { Game::PawnType::Thug, thugPrefab},{ Game::PawnType::Sentinel, sentinelPrefab },{ Game::PawnType::Brawler, brawlerPrefab } };
	mini::Scene menu("menu", [&](mini::Scene& scene)
	{
		backgroundPrefab.instantiate(scene).move({ -400, 0 });

		auto& startGame = buttonPrefab.instantiate(scene);
		startGame.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {button.getGameplaySystem().loadScene("game");  });
		sf::Vector2f buttonPos{ 0.5f, 0.25f };
		startGame.getComponent<mini::LayoutElement>()->setPosition(buttonPos);

		auto& startText = textPrefab.instantiate(scene);
		startText.setPosition({ buttonPos.x * mini::Screen::width, buttonPos.y * mini::Screen::height});
		startText.getComponent<mini::TextRenderer>()->setText("START GAME");

		auto& howTo = buttonPrefab.instantiate(scene);
		howTo.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {button.getGameplaySystem().loadScene("how_to"); });
		buttonPos = { 0.5f, 0.5f };
		howTo.getComponent<mini::LayoutElement>()->setPosition(buttonPos);

		auto& howToText = textPrefab.instantiate(scene);
		howToText.setPosition({ buttonPos.x * mini::Screen::width, buttonPos.y * mini::Screen::height });
		howToText.getComponent<mini::TextRenderer>()->setText("GAME RULES");

		auto& quit = buttonPrefab.instantiate(scene);
		quit.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {button.getGameplaySystem().closeApplication(); });
		buttonPos = { 0.5f, 0.75f };
		quit.getComponent<mini::LayoutElement>()->setPosition(buttonPos);

		auto& quitText = textPrefab.instantiate(scene);
		quitText.setPosition({ buttonPos.x * mini::Screen::width, buttonPos.y * mini::Screen::height });
		quitText.getComponent<mini::TextRenderer>()->setText("QUIT");

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 0.5f * settings.windowWidth, 0.5f * settings.windowHeight });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize({ static_cast<float>(settings.windowWidth), static_cast<float>(settings.windowHeight)});		
	});	

	mini::Scene game("game", [&](mini::Scene& scene)
	{
		Game::GameplayManager::GetInstance().RestartGame();
		backgroundPrefab.instantiate(scene).move({ -500, 0 });
		auto& menu = backButtonPrefab.instantiate(scene);
		menu.getComponent<UIButton>()->onClicked().addCallback(
			[&](UIButton& button) 
		{
			button.getGameplaySystem().loadScene("menu");
			GameEvents::getInstance().clearEvents();
			Pawn::selectedPawn = nullptr; 
		});

		auto& endTurn = endTurnButtonPrefab.instantiate(scene);
		endTurn.getComponent<UIButton>()->onClicked().addCallback(
			[&](UIButton& button) 
		{
			if (GameManager::getInstance().isCurrentPlayerHuman()) 
			{ 
				if (Pawn::selectedPawn != nullptr)
				{
					Pawn::selectedPawn->setHighlighted(false);
					Pawn::selectedPawn = nullptr;
				}
				Game::GameplayManager::GetInstance().GetCurrentGameState().PerformMove(Game::EndTurn());
				GameManager::getInstance().endTurn(); 
			} 
		});
		auto layoutEl = endTurn.getComponent<mini::LayoutElement>();
		layoutEl->setPivotPosition({ 1.0f, 1.0f });
		layoutEl->setPosition({ 1.0f, 1.0f });
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setSize({ 100.0f, 100.0f });

		auto& unitStats = textPrefab.instantiate(scene);
		unitStats.getComponent<mini::TextRenderer>()->setColor(sf::Color::White);
		unitStats.setScreenSpace(true);
		unitStats.setPosition({ 200, 780 });
		unitStats.addComponent<PawnStats>();

		auto& aiBusy = textPrefab.instantiate(scene);
		aiBusy.getComponent<mini::TextRenderer>()->setColor(sf::Color::White);
		aiBusy.setScreenSpace(true);
		aiBusy.setPosition({ 950, 140 });
		aiBusy.getComponent<mini::TextRenderer>()->setText("Plotting to crush you...");
		aiBusy.setActive(false);

		GameManager::getInstance().aiBusyText = &aiBusy;
		orderPanelPrefab.instantiate(scene);

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 0.5f * settings.windowWidth, 0.5f * settings.windowHeight });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize(sf::Vector2f(static_cast<float>(settings.windowWidth), static_cast<float>(settings.windowHeight)));
		cam.move({ 0, -200 });

		GameManager::getInstance().setupGame({ 0 }, scene, prefabMap, fieldPrefab, sf::Vector2f(0.5f * settings.windowWidth, 130), 220);

		Game::GameplayManager::GetInstance().onNewGameStateFound = [&](Game::GameState& state) {GameManager::getInstance().endTurn(); };
	});

	mini::Scene howTo("how_to", [&](mini::Scene& scene)
	{
		auto& back = scene.addObject("background");
		back.addComponent<mini::ShapeRenderer>()->setShape(rectShape);
		back.getComponent<mini::ShapeRenderer>()->setColor(sf::Color(100, 100, 100, 255));
		back.getComponent<mini::ShapeRenderer>()->setLayer(-1);
		auto lel = back.addComponent<mini::LayoutElement>();
		lel->setPivotPosition({ 0.5f, 0.5f });
		lel->setPosition({ 0.5f, 0.5f });
		lel->applySettings({ false, false, false, false });
		lel->setSize({ 1.0f, 1.0f });

		auto& menu = backButtonPrefab.instantiate(scene);
		menu.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {button.getGameplaySystem().loadScene("menu"); });

		auto& howToText = textPrefab.instantiate(scene);

		auto layoutEl = howToText.addComponent<mini::LayoutElement>();
		layoutEl->setPivotPosition({ 0.5f, 0.5f });
		layoutEl->setPosition({ 0.5f, 0.5f });
		layoutEl->applySettings({ false, false, false, false });
		layoutEl->setSize({ 0.9f, 0.6f });

		std::stringstream stream;
		stream << "How to Play: \n";
		stream << "You can assign one order per turn, units continue to execute last given order until given a new one.\n";
		stream << "Units will not move if enemy is present. They will continue fight until one side wins. \n";
		stream << "You win when last enemy unit is killed, or you have the most units at the last turn.\n";
		stream << "\n";
		stream << "Orders: \n";
		stream << "Advance- unit moves in given direction. If enemy is encountered unit stops to fight. Move will be continued once enemy is dead.\n";
		stream << "Stop- stops unit in place, it will still engage in combat with the enemy\n";
		stream << "\n";
		stream << "Unit stats: \n";
		stream << "health- when reaches 0 the unit is dead.\n";
		stream << "speed- how many fields the unit can traverse in turn.\n";
		stream << "attack- damage dealt when attacking enemy.\n";
		stream << "counter- damage dealt in response to enemy attack.\n";
		stream << "\n";
		stream << "Credits: \n";
		stream << "Piotr Lukaszewicz\n";
		stream << "Rafal Tyl\n";
		howToText.getComponent<mini::TextRenderer>()->setText(stream.str().c_str());
		howToText.getComponent<mini::TextRenderer>()->setColor(sf::Color::Black);
		howToText.getComponent<mini::TextRenderer>()->setCharacterSize(25);

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 0.5f * settings.windowWidth, 0.5f * settings.windowHeight });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize({ static_cast<float>(settings.windowWidth), static_cast<float>(settings.windowHeight) });
	});

	settings.windowName = "Radio Commander";
	mini::Miniengine engine(settings, { std::move(menu), std::move(howTo), std::move(game) });
	engine.Run();

	return 0;
}

