#pragma once

#include "baseRenderable.h"

class Monkey : public BaseRenderable
{
	public:
	Monkey(Camera& p_cameraRef, Shader* p_shader);
	void Render() override;
	private:

};

