// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Miniengine.h>
#include "GameObject.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "MouseFollower.h"
#include "DraggableObject.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

int main()
{
	mini::EngineSettings settings;
	settings.windowHeight = 480;
	settings.windowWidth = 640;
	settings.windowName = "Example Game";

	auto sharedShape = std::make_shared<sf::CircleShape>(80.f);
	sharedShape->setOrigin({ 80, 80 });

	mini::Scene scene("default_scene");
	/*auto& obj_1 = scene.addObject("obj_1");	
	auto& shapeRen = obj_1.addComponent<mini::ShapeRenderer>();
	shapeRen.setColor(sf::Color::Green);
	shapeRen.setShape(sharedShape);
	shapeRen.setLayer(1);
	auto& follower_1 = obj_1.addComponent<MouseFollower>();
	follower_1.offset = sf::Vector2f(-50, 0);

	auto& obj_2 = scene.addObject("obj_2");
	auto& shapeRen_2 = obj_2.addComponent<mini::ShapeRenderer>();
	shapeRen_2.setColor(sf::Color::Red);
	shapeRen_2.setShape(sharedShape);
	auto& follower_2 = obj_2.addComponent<MouseFollower>();
	follower_2.offset = sf::Vector2f(50, 0);*/

	auto& obj_3 = scene.addObject("obj_3");
	obj_3.setPosition({ 200, 200 });
	auto& shapeRen_3 = obj_3.addComponent<mini::ShapeRenderer>();
	shapeRen_3.setColor(sf::Color::Red);
	shapeRen_3.setShape(sharedShape);
	obj_3.addComponent<mini::CircleCollider>();
	auto& draggable = obj_3.addComponent<DraggableObject>();

	mini::Miniengine engine(settings, { std::move(scene) });
	engine.Run();
	return 0;
}

