#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "model.h"

struct Camera;

class BaseRenderable
{
	public:
	BaseRenderable(Camera& p_cameraRef) : m_cameraRef(p_cameraRef) {}
	virtual void Render() = 0;
	virtual void AddInstance(Instance newInstance) { m_intances.push_back(newInstance); };
	virtual ~BaseRenderable() = default;

	protected:
	Shader* m_shader = nullptr;
	Model*  m_model = nullptr;

	std::vector<Instance> m_intances;
	Camera& m_cameraRef;

};

