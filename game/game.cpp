// game.cpp : Defines the entry point for the console application.
//
#include "Miniengine.h"
#include "GameObject.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "DraggableObject.h"
#include "BoxCollider.h"
#include "LayoutElement.h"
#include "CircleCollider.h"
#include "Screen.h"
#include "Camera.h"
#include "UIButton.h"
#include "GameplaySystem.h"
#include "Prefab.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

int main()
{
	mini::EngineSettings settings;
	settings.windowHeight = 480;
	settings.windowWidth = 640;

	/*sf::Texture texture;
	texture.loadFromFile("Assets/img_1.png");
	texture.setSmooth(true);
	auto sharedSprite = std::make_shared<sf::Sprite>();
	sharedSprite->setTexture(texture);
	sharedSprite->setOrigin({ texture.getSize().x * 0.5f, texture.getSize().y * 0.5f });*/
	auto rectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(10.0f, 10.0f));
	rectShape->setOrigin({ 5.0f , 5.0f});

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
		startGame.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {button.getGameplaySystem().loadScene("game"); });
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
		auto& menu = buttonPrefab.instantiate(scene);
		menu.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {button.getGameplaySystem().loadScene("menu"); });
		auto layoutEl = menu.getComponent<mini::LayoutElement>();
		layoutEl->setPivotPosition({ 0.0f, 0.0f });
		layoutEl->setPosition({ 0.0f, 0.0f });	
		layoutEl->applySettings({ false, false, true, true });
		layoutEl->setSize({ 100.0f, 100.0f });

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 200, 200 });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize({ 1280, 960});
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

