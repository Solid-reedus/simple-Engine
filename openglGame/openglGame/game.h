#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "baseRenderable.h"
#include "baseActor.h"

#include "box.h"

class Game
{
	public:
	Game();
	~Game();
	bool Init();
	bool InitActors();
	void Update();
	void Render();
	void Exit();

	private:
	GLFWwindow* window = nullptr;
	glm::mat4 camPos = glm::mat4(0);
	float deltaTime = 0.0f;	
	float lastFrame = 0.0f;

	std::vector<BaseRenderable*> renderedRenderable;
	std::vector<BaseActor*> renderedActors;

};

