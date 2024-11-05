#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "model.h"

class BaseRenderable
{
	public:
	//BaseRenderable();
	virtual void Render() = 0;
	virtual void AddInstance(Instance newInstance) { intances.push_back(newInstance); };
	virtual ~BaseRenderable() = default;

	protected:
	Shader* shader;
	Model* model;

	std::vector<Instance> intances;


};

