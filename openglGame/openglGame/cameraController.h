#pragma once

#include <camera.h>
#include <GLFW/glfw3.h>

class CameraController
{
	public:

    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    CameraController(Camera& p_camera);
    ~CameraController(){};

    void ProcessKeyboard(Camera_Movement p_direction, float p_deltaTime);
    void ProcessMouseMovement(glm::vec2 p_newPos, GLboolean p_constrainPitch = true);

	private:
    Camera& m_camera;
    // default camera options
    float m_movementSpeed = 5.0f;
    float m_mouseSensitivity = 0.07f;

    glm::vec2 m_lastMousePos = glm::vec2(0, 0);
    bool m_firstMouseInput = false;
};

