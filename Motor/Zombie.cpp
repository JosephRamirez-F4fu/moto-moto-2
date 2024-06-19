#include "Zombie.h"
#include <random>
#include <ctime>
#include<glm/gtx/rotate_vector.hpp>
#include "Human.h"
Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	this->speed = speed;
	//color green
	color.set(0, 185, 0, 255);
	this->position = position;
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}
	//direction = glm::vec2(direction);
}

void Zombie::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies)
{
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randRotate(-40.0f, 40.0f);
	Human* closestHuman = getNearestHuman(humans);
	if (closestHuman != nullptr) {
		glm::vec2 direction = glm::normalize(closestHuman->getPosition() - position);
		position += direction * speed;
	}
	if (collideWithLevel(levelData)) {
		direction = glm::rotate(direction, randRotate(randomEngine));
	}
}


Human* Zombie::getNearestHuman(vector<Human*>& humans)
{
	Human* closestHuman = nullptr;
	float smallestDistance = 9999999.0f;

	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVec = humans[i]->getPosition() - position;
		float distance = glm::length(distVec);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	return closestHuman;
}