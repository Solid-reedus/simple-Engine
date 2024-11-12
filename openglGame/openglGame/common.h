#pragma once

#include <vector>
#include "glm/glm.hpp"


struct Instance
{
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scl;
	glm::mat4 trans;

	Instance()
	{
		pos = glm::vec3(0.0f);
		rot = glm::vec3(0.0f);
		scl = glm::vec3(0.0f);
		trans = glm::mat4(1.0f);
	}

	Instance(glm::vec3 p_pos, glm::vec3 p_rot, glm::vec3 p_scl)
	{

		pos = p_pos;
		rot = p_rot;
		scl = p_scl;

		trans = glm::mat4(1.0f);

		trans = glm::scale(trans, scl);

		trans = glm::rotate(trans, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X-axis
		trans = glm::rotate(trans, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
		trans = glm::rotate(trans, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z-axis

		trans = glm::translate(trans, pos);
	}

	/*
	 InstanceArray[i + j * 10].trans = glm::translate(InstanceArray[i + j * 10].trans, InstanceArray[i + j * 10].pos);
	*/

};