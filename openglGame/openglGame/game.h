#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <baseRenderable.h>
#include <baseActor.h>
#include <camera.h>
#include <cameraController.h>
#include <monkey.h>

class LightingManager;

class Game
{
	public:
	Game(){};
	~Game(){};
	bool Init();
	bool InitActors();
	void Update();

	void UpdateKeyInputs();
	void Render();
	void Exit();

	float GetDeltaTime() const { return m_deltaTime; };
	CameraController* m_camController = nullptr;
	Camera* m_currentCamera = nullptr;
	LightingManager* lightingManager = nullptr;

	private:

	// OnKeyInput should be used for non continuous input
	static void OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void OnMouseInput(GLFWwindow* window, double xposIn, double yposIn);
	static void OnScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void OnResize(GLFWwindow* window, int width, int height);

	GLFWwindow* m_window = nullptr;
	float m_deltaTime = 0.0f;	
	float m_lastFrame = 0.0f;

	std::vector<BaseRenderable*> m_renderedRenderable;
	std::vector<BaseActor*> m_renderedActors;
	std::vector<Camera> m_sceneCameras;
	std::vector<Shader> m_shaders;

};

