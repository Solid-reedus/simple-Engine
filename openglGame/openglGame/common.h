#pragma once

#include <vector>
#include "glm/glm.hpp"


struct Instance
{
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scl;
	glm::mat4 trans;
};