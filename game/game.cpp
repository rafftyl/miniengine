// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Miniengine.h"
#include "GameObject.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SpritesheetAnimation.h"
#include "Animator.h"
#include "MouseFollower.h"
#include "DraggableObject.h"
#include "BoxCollider.h"
#include "LayoutElement.h"
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

	auto otherSprite = std::make_shared<sf::Sprite>();
	otherSprite->setTexture(texture);
	otherSprite->setTextureRect(sf::IntRect(0, 0, texture.getSize().x / 2, texture.getSize().y / 2));

	auto sharedShape = std::make_shared<sf::CircleShape>(80.f);
	sharedShape->setOrigin({ 80, 80 });

	std::vector<std::pair<float, std::shared_ptr<sf::Sprite>>> spritesheet =
	{
		{3.0f, sharedSprite},
		{1.0f, otherSprite}
	};
	auto animation = std::make_shared<mini::SpritesheetAnimation>(std::move(spritesheet), true);

	mini::Scene defaultScene("default_scene", [&](mini::Scene& scene)
	{
		auto& obj_1 = scene.addObject("obj_1");
		obj_1.setScreenSpace(true);
		obj_1.setPosition({ 320, 240 });
		auto& ren = obj_1.addComponent<mini::SpriteRenderer>();
		ren.setColor(sf::Color::White);
		ren.setLayer(1);
		ren.setSprite(sharedSprite);
		auto& animator = obj_1.addComponent<mini::Animator>();
		animator.setAnimations({ {"idle", animation} });
		animator.setDefaultAnimation("idle");
		obj_1.addComponent<SceneChanger>().currentScene = "default_scene";
		obj_1.addComponent<mini::BoxCollider>();
		obj_1.addComponent<DraggableObject>();
		auto& layoutEl = obj_1.addComponent<mini::LayoutElement>();
		layoutEl.setPivotPosition({ 0, 0 });
		layoutEl.setPosition({ 0,0 });
		layoutEl.setSize({ 0.3f, 0.3f });
		layoutEl.applySettings({ true, true, false, false });

		auto& obj_2 = scene.addObject("obj_2");
		obj_2.setPosition({ 900, 200 });
		auto& shapeRen_2 = obj_2.addComponent<mini::ShapeRenderer>();
		shapeRen_2.setColor(sf::Color::Red);
		shapeRen_2.setShape(sharedShape);
		shapeRen_2.setLayer(3);

		auto& obj_3 = scene.addObject("obj_3");
		obj_3.setPosition({ 200, 200 });
		auto& shapeRen_3 = obj_3.addComponent<mini::ShapeRenderer>();
		shapeRen_3.setColor(sf::Color::Red);
		shapeRen_3.setShape(sharedShape);
		shapeRen_3.setLayer(2);
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

