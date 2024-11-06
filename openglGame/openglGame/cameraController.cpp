#include "cameraController.h"
#include <camera.h>

CameraController::CameraController(Camera& p_camera) : m_camera(p_camera) {}

void CameraController::ProcessKeyboard(Camera_Movement p_direction, float p_deltaTime)
{
    float velocity = m_movementSpeed * p_deltaTime;

    switch (p_direction)
    {
        case FORWARD:  m_camera.position += m_camera.front * velocity; break;
        case BACKWARD: m_camera.position -= m_camera.front * velocity; break;
        case LEFT:     m_camera.position -= m_camera.right * velocity; break;
        case RIGHT:    m_camera.position += m_camera.right * velocity; break;
        case UP:       m_camera.position += m_camera.WORLD_UP * velocity; break;
        case DOWN:     m_camera.position -= m_camera.WORLD_UP * velocity; break;
        default:
        break;
    }
}

void CameraController::ProcessMouseMovement(glm::vec2 p_newPos, GLboolean p_constrainPitch)
{
    glm::vec2 offset;
    offset.x = p_newPos.x - m_lastMousePos.x;
    offset.y = m_lastMousePos.y - p_newPos.y;
    offset *= m_mouseSensitivity;

    m_lastMousePos = p_newPos;

    m_camera.yaw += offset.x;
    m_camera.pitch += offset.y;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (p_constrainPitch)
    {
        if (m_camera.pitch > 89.0f)  m_camera.pitch = 89.0f;
        if (m_camera.pitch < -89.0f) m_camera.pitch = -89.0f;
    }

    m_camera.UpdateCamVecs();
}