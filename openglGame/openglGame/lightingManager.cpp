#include <lightingManager.h>
#include <glad/glad.h>


LightingManager::LightingManager()
	: m_suns(), m_spotlights(), m_areaLights(), lightingUBO()
{
	InitUBO();
	UpdateUBO();
}

LightingManager::LightingManager(const std::vector<Sun>& p_suns, const std::vector<SpotLight>& p_spotlights, const std::vector<AreaLight>& p_areaLights)
	: m_suns(p_suns), m_spotlights(p_spotlights), m_areaLights(p_areaLights), lightingUBO()
{
	InitUBO();
	UpdateUBO();
}

void LightingManager::AddSun(const Sun & p_sun) {m_suns.push_back(p_sun);}
void LightingManager::AddSpotLight(const SpotLight& p_spotLight) {m_spotlights.push_back(p_spotLight);}
void LightingManager::AddAreaLight(const AreaLight& p_areaLight) {m_areaLights.push_back(p_areaLight);}

void LightingManager::SubtractSun(int p_index)
{
	if (p_index < 0 || p_index >= m_suns.size())
	{
		printf("error: p_index in LightingManager::SubtractSun is out of bounds \n");
		return;
	}
	m_suns.erase(m_suns.begin() + p_index);
	UpdateUBO();
}

void LightingManager::SubtractSpotLight(int p_index)
{
	if (p_index < 0 || p_index >= m_spotlights.size())
	{
		printf("error: p_index in LightingManager::SubtractSpotLight is out of bounds \n");
		return;
	}
	m_spotlights.erase(m_spotlights.begin() + p_index);
	UpdateUBO();
}

void LightingManager::SubtractAreaLight(int p_index)
{
	if (p_index < 0 || p_index >= m_areaLights.size())
	{
		printf("error: p_index in LightingManager::SubtractAreaLight is out of bounds \n");
		return;
	}
	m_areaLights.erase(m_areaLights.begin() + p_index);
	UpdateUBO();
}

const LightingManager::Sun* LightingManager::LookAtSun(int p_index) const
{
	if (p_index < 0 || p_index >= m_suns.size())
	{
		printf("error: p_index in LightingManager::LookAtSun is out of bounds \n");
		return nullptr;
	}
	return &m_suns[p_index];
}

const LightingManager::SpotLight* LightingManager::LookAtSpotLight(int p_index) const
{
	if (p_index < 0 || p_index >= m_spotlights.size())
	{
		printf("error: p_index in LightingManager::SubtractSpotLight is out of bounds \n");
		return nullptr;
	}
	return &m_spotlights[p_index];
}

const LightingManager::AreaLight* LightingManager::LookAtAreaLight(int p_index) const
{
	if (p_index < 0 || p_index >= m_areaLights.size())
	{
		printf("error: p_index in LightingManager::SubtractAreaLight is out of bounds \n");
		return nullptr;
	}
	return &m_areaLights[p_index];
}

void LightingManager::UpdateLight(int p_index, LightType p_lightType, LightAtr p_lightAtr, glm::vec3 p_val)
{
	// sun starts at 0
	int offset = 0;

	switch (p_lightType)
	{
		case LightingManager::LightType::sun:
		{
			if (p_index >= m_suns.size())
			{
				printf("error: p_index is out of bounds of sun size in LightingManager::UpdateLight \n");
				return;
			}

			switch (p_lightAtr)
			{
				case LightingManager::LightAtr::pos:
				{
					printf("error: sun doesnt have a attribute pos, in LightingManager::UpdateLight \n");
					return;
				}
				case LightingManager::LightAtr::dir:
				{
					offset += p_index * sizeof(Sun);
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::color:
				{
					offset += p_index * sizeof(Sun) + 16;
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::intensity:
				{
					return;
				}
				default:
				return;
			}
			break;
		}
		case LightingManager::LightType::spotlight:
		{
			if (p_index >= m_spotlights.size())
			{
				printf("error: p_index is out of bounds of spotlight size in LightingManager::UpdateLight \n");
				return;
			}

			offset = SPOT_LIGHT_BUFFER_START;

			switch (p_lightAtr)
			{
				case LightingManager::LightAtr::pos:
				{
					offset += p_index * sizeof(SpotLight);
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::dir:
				{
					offset += p_index * sizeof(SpotLight) + 16;
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::color:
				{
					offset += p_index * sizeof(SpotLight) + (16 * 2);
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::intensity:
				{
					return;
				}
				default:
				break;
			}

			break;
		}
		case LightingManager::LightType::areaLight:
		{
			if (p_index >= m_areaLights.size())
			{
				printf("error: p_index is out of bounds of area lights size in LightingManager::UpdateLight \n");
				return;
			}

			offset = AREA_LIGHT_BUFFER_START;

			switch (p_lightAtr)
			{
				case LightingManager::LightAtr::pos:
				{
					offset += p_index * sizeof(SpotLight);
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::dir:
				{
					offset += p_index * sizeof(SpotLight) + 16;
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::color:
				{
					offset += p_index * sizeof(SpotLight) + (16 * 2);
					SetSubBufferVal(offset, p_val);
					return;
				}
				case LightingManager::LightAtr::intensity:
				{
					return;
				}
				default:
				break;
			}


			break;
		}
		default:
		printf("error:type in LightingManager::UpdateLight is invalid \n");
		break;
	}
}

void LightingManager::SetSubBufferVal(int p_offset, const glm::vec3& p_val)
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightingUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, p_offset, sizeof(glm::vec3), &p_val);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void LightingManager::InitUBO()
{
	int maxSize = LIGHTS_SIZE_BUFFER_START + 16; // For the 3 padded ints (numSuns, numSpotlights, numAreaLights) and padding_

	glGenBuffers(1, &lightingUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lightingUBO);
	glBufferData(GL_UNIFORM_BUFFER, maxSize, NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightingUBO);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, lightingUBO, 0, maxSize);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);


}

void LightingManager::UpdateUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightingUBO);

	// Calculate the total size for the UBO
	int uboSize = LIGHTS_SIZE_BUFFER_START + 16; // 3 integers (numSuns, numSpotlights, numAreaLights) each aligned to 16 bytes

	// Allocate buffer space
	//glBufferData(GL_UNIFORM_BUFFER, uboSize, nullptr, GL_STATIC_DRAW);

	int offset = 0;

	// Upload `Sun` data
	for (int i = 0; i < m_suns.size(); i++) 
	{
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &m_suns[i].dir);
		offset += 16;

		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &m_suns[i].color);
		offset += 12;

		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &m_suns[i].intensity);
		offset += 4; 
	}

	// 96
	// Move offset for the next block of lights
	offset = SPOT_LIGHT_BUFFER_START;
	// Upload `SpotLight` data
	for (int i = 0; i < m_spotlights.size(); i++) 
	{
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &m_spotlights[i].pos);
		offset += 16;

		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &m_spotlights[i].dir);
		offset += 16;

		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &m_spotlights[i].color);
		offset += 12;

		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &m_spotlights[i].intensity);
		offset += 4;
	}

	// Move offset for the next block of lights
	offset = AREA_LIGHT_BUFFER_START;

	// Upload `AreaLight` data
	for (int i = 0; i < m_areaLights.size(); i++) 
	{
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &m_areaLights[i].pos);
		offset += 16;

		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &m_areaLights[i].color);
		offset += 12;

		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &m_areaLights[i].intensity);
		offset += 4;
	}

	offset = LIGHTS_SIZE_BUFFER_START;

	float sunSize = m_suns.size();
	float spotLightSize = m_spotlights.size();
	float areaLightSize = m_areaLights.size();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(int), &sunSize);
	glBufferSubData(GL_UNIFORM_BUFFER, offset + 4, sizeof(int), &spotLightSize);
	glBufferSubData(GL_UNIFORM_BUFFER, offset + 8, sizeof(int), &areaLightSize);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
