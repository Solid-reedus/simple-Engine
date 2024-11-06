#pragma once

#include "baseRenderable.h"


class BaseActor : public BaseRenderable
{
	public:
	virtual void Update(float p_deltaTime) = 0;
	virtual ~BaseActor() = 0;

	protected:

	//transform

};

