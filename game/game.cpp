// game.cpp : Defines the entry point for the console application.
//
#include "Miniengine.h"
#include "GameObject.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "DraggableObject.h"
#include "BoxCollider.h"
#include "LayoutElement.h"
#include "CircleCollider.h"
#include "KeyMover.h"
#include "Camera.h"
#include "UIButton.h"
#include "SceneChanger.h"
#include "Prefab.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

int main()
{
	sf::Texture texture;
	texture.loadFromFile("img_1.png");
	texture.setSmooth(true);
	auto sharedSprite = std::make_shared<sf::Sprite>();
	sharedSprite->setTexture(texture);
	sharedSprite->setOrigin({ texture.getSize().x * 0.5f, texture.getSize().y * 0.5f });

	auto sharedShape = std::make_shared<sf::CircleShape>(80.f);
	sharedShape->setOrigin({ 80, 80 });

	mini::Prefab prefab_1("duda",
		[&](mini::GameObject& object) 
	{
		object.setScreenSpace(true);
		auto ren = object.addComponent<mini::SpriteRenderer>();
		ren->setColor(sf::Color::Green);
		ren->setSprite(sharedSprite);
		ren->setLayer(1);
		object.addComponent<SceneChanger>()->currentScene = "default_scene";
		object.addComponent<mini::BoxCollider>();
		auto& layoutEl = object.addComponent<mini::LayoutElement>();
		layoutEl->setPivotPosition({ 0, 0 });
		layoutEl->setPosition({ 0,0 });
		layoutEl->setSize({ 0.3f, 0.3f });
		layoutEl->applySettings({ true, true, false, false });
		object.addComponent<UIButton>();
	});

	mini::Scene defaultScene("default_scene", [&](mini::Scene& scene)
	{
		auto& obj_1 = prefab_1.instantiate(scene);
		obj_1.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {std::cout << "clicked!" << std::endl; });

		auto& testObj = prefab_1.instantiate(scene);
		testObj.getComponent<mini::LayoutElement>()->setPosition({ 320.0f, 0.0f });

		auto& obj_2 = scene.addObject("obj_2");
		obj_2.setPosition({ 900, 200 });
		auto& shapeRen_2 = obj_2.addComponent<mini::ShapeRenderer>();
		shapeRen_2->setColor(sf::Color::Red);
		shapeRen_2->setShape(sharedShape);

		auto& obj_3 = scene.addObject("obj_3");
		obj_3.setPosition({ 200, 200 });
		auto& shapeRen_3 = obj_3.addComponent<mini::ShapeRenderer>();
		shapeRen_3->setColor(sf::Color::Red);
		shapeRen_3->setShape(sharedShape);
		obj_3.addComponent<mini::CircleCollider>();

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 200, 200 });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize({ 1280, 960});
		cam.addComponent<KeyMover>();
	});	

	mini::Scene otherScene("other_scene", [&](mini::Scene& scene)
	{
		auto& obj_1 = scene.addObject("obj_1");
		obj_1.setPosition({ 400, 500 });
		auto& ren = obj_1.addComponent<mini::SpriteRenderer>();
		ren->setColor(sf::Color::Green);
		ren->setSprite(sharedSprite);
		ren->setLayer(1);
		obj_1.addComponent<SceneChanger>()->currentScene = "other_scene";

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 200, 200 });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp->setOrthoSize({ 1280, 960});
		cam.addComponent<KeyMover>();
	});

	mini::EngineSettings settings;
	settings.windowHeight = 480;
	settings.windowWidth = 640;
	settings.windowName = "Example Game";
	mini::Miniengine engine(settings, { std::move(defaultScene), std::move(otherScene) });
	engine.Run();

	return 0;
}

