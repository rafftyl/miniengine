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
#include "LayoutElement.h"
#include "CircleCollider.h"
#include "Screen.h"
#include "Pawn.h"
#include "PositionInterpolator.h"
#include "Field.h"
#include "Camera.h"
#include "UIButton.h"
#include "GameplaySystem.h"
#include "GameManager.h"
#include "Prefab.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

int main()
{
	mini::EngineSettings settings;
	settings.windowHeight = 960;
	settings.windowWidth = 1280;

	sf::Texture texture;
	texture.loadFromFile("Assets/img_1.png");
	texture.setSmooth(true);
	auto sharedSprite = std::make_shared<sf::Sprite>();
	sharedSprite->setTexture(texture);
	sharedSprite->setOrigin({ texture.getSize().x * 0.5f, texture.getSize().y * 0.5f });

	auto rectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(1.0f, 1.0f));
	rectShape->setOrigin({ .5f , .5f});

	auto font = std::make_shared<sf::Font>();
	font->loadFromFile("Assets/die_hard.ttf");

	mini::Prefab buttonPrefab("button",
		[&](mini::GameObject& object) 
	{
		object.setScreenSpace(true);
		auto ren = object.addComponent<mini::ShapeRenderer>();
		ren->setColor(sf::Color::Blue);
		ren->setShape(rectShape);
		
		object.addComponent<mini::BoxCollider>();		
		auto layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->applySettings({ false, false, false, false });
		layoutEl->setPosition({ 0.5f, 0.5f });
		layoutEl->setPivotPosition({ 0.5f, 0.5f });
		layoutEl->setSize({ 0.8f, 0.2f });
		object.addComponent<UIButton>();
	});

	mini::Prefab pawnPrefab("pawn",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setSprite(sharedSprite);
		ren->setLayer(2);
		object.addComponent<mini::BoxCollider>();
		object.addComponent<Pawn>()->setColors(sf::Color::Green, sf::Color::White);
		object.addComponent<PositionInterpolator>();
		object.setScale({ 0.33f, 0.33f });
	});

	mini::Prefab slotPrefab("slot",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::ShapeRenderer>();
		ren->setShape(rectShape);
		ren->setColor(sf::Color::Cyan);
		ren->setLayer(1);
		object.setScale({ 80, 80 });
	});

	mini::Prefab fieldPrefab("field",
		[&](mini::GameObject& object)
	{
		auto ren = object.addComponent<mini::ShapeRenderer>();
		ren->setShape(rectShape);
		object.addComponent<mini::BoxCollider>();
		auto fieldComp = object.addComponent<Field>();
		fieldComp->setColors(sf::Color::Yellow, sf::Color::White);
		fieldComp->setSlotCount(3);
		fieldComp->setSlotPrefab(slotPrefab);
		object.setScale({ 200, 200 });
	});

	mini::Prefab textPrefab("label", 
		[&](mini::GameObject& object)
	{
		object.setScreenSpace(true);
		auto text = object.addComponent<mini::TextRenderer>();
		text->setFont(font);
		text->setText("Dupa");
		text->setCharacterSize(45);
		text->setLayer(1);
		text->setColor(sf::Color::Red);
	});

	mini::Scene menu("menu", [&](mini::Scene& scene)
	{
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

		GameManager::getInstance().setupGame(0);
	});	

	mini::Scene game("game", [&](mini::Scene& scene)
	{
		auto& menu = buttonPrefab.instantiate(scene);
		menu.getComponent<UIButton>()->onClicked().addCallback(
			[&](UIButton& button) 
		{
			button.getGameplaySystem().loadScene("menu");
			GameEvents::getInstance().clearEvents();
			Pawn::selectedPawn = nullptr; 
		});
		auto layoutEl = menu.getComponent<mini::LayoutElement>();
		layoutEl->setPivotPosition({ 0.0f, 0.0f });
		layoutEl->setPosition({ 0.0f, 0.0f });	
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setSize({ 100.0f, 100.0f });

		auto& endTurn = buttonPrefab.instantiate(scene);
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
				GameManager::getInstance().endTurn(); 
			} 
		});
		layoutEl = endTurn.getComponent<mini::LayoutElement>();
		layoutEl->setPivotPosition({ 1.0f, 1.0f });
		layoutEl->setPosition({ 1.0f, 1.0f });
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setSize({ 100.0f, 100.0f });

		auto& pawn_1 = pawnPrefab.instantiate(scene);
		pawn_1.setPosition({ 200, 200 });

		auto& pawn_2 = pawnPrefab.instantiate(scene);
		pawn_2.setPosition({ 500, 200 });

		auto& field_1 = fieldPrefab.instantiate(scene);
		field_1.setPosition({ 500, 500 });

		auto& field_2 = fieldPrefab.instantiate(scene);
		field_2.setPosition({ 200, 500 });
		field_2.getComponent<Field>()->setSlotCount(1);

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 200, 200 });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize({ static_cast<float>(settings.windowWidth), static_cast<float>(settings.windowHeight) });
	});

	mini::Scene howTo("how_to", [&](mini::Scene& scene)
	{
		auto& menu = buttonPrefab.instantiate(scene);
		menu.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {button.getGameplaySystem().loadScene("menu"); });
		auto layoutEl = menu.getComponent<mini::LayoutElement>();
		layoutEl->setPivotPosition({ 0.0f, 0.0f });
		layoutEl->setPosition({ 0.0f, 0.0f });
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setSize({ 100.0f, 100.0f });

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 0.5f * settings.windowWidth, 0.5f * settings.windowHeight });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize({ static_cast<float>(settings.windowWidth), static_cast<float>(settings.windowHeight) });
	});

	settings.windowName = "Example Game";
	mini::Miniengine engine(settings, { std::move(menu), std::move(howTo), std::move(game) });
	engine.Run();

	return 0;
}

