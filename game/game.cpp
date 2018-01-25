// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Miniengine.h>
#include "GameObject.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "MouseFollower.h"
#include "DraggableObject.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "KeyMover.h"
#include "Camera.h"
#include "SceneChanger.h"
#include <SFML/Graphics.hpp>
#include <memory>

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

	mini::Scene defaultScene("default_scene", [&](mini::Scene& scene)
	{
		auto& obj_1 = scene.addObject("obj_1");
		obj_1.setPosition({ 400, 500 });
		auto& ren = obj_1.addComponent<mini::SpriteRenderer>();
		ren.setColor(sf::Color::Green);
		ren.setSprite(sharedSprite);
		ren.setLayer(1);
		obj_1.addComponent<SceneChanger>().currentScene = "default_scene";

		auto& obj_2 = scene.addObject("obj_2");
		obj_1.setPosition({ 900, 200 });
		auto& shapeRen_2 = obj_2.addComponent<mini::ShapeRenderer>();
		shapeRen_2.setColor(sf::Color::Red);
		shapeRen_2.setShape(sharedShape);

		auto& obj_3 = scene.addObject("obj_3");
		obj_3.setPosition({ 200, 200 });
		auto& shapeRen_3 = obj_3.addComponent<mini::ShapeRenderer>();
		shapeRen_3.setColor(sf::Color::Red);
		shapeRen_3.setShape(sharedShape);
		obj_3.addComponent<mini::CircleCollider>();
		obj_3.addComponent<DraggableObject>();

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 200, 200 });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp.setOrthoSize({ 1280, 960});
		cam.addComponent<KeyMover>();
	});	

	mini::Scene otherScene("other_scene", [&](mini::Scene& scene)
	{
		auto& obj_1 = scene.addObject("obj_1");
		obj_1.setPosition({ 400, 500 });
		auto& ren = obj_1.addComponent<mini::SpriteRenderer>();
		ren.setColor(sf::Color::Green);
		ren.setSprite(sharedSprite);
		ren.setLayer(1);
		obj_1.addComponent<SceneChanger>().currentScene = "other_scene";

		auto& cam = scene.addObject("camera");
		cam.setPosition({ 200, 200 });
		auto& camComp = cam.addComponent<mini::Camera>();
		camComp.setOrthoSize({ 1280, 960});
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

