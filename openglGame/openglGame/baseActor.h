#pragma once

#include "baseRenderable.h"


class BaseActor : public BaseRenderable
{
	public:
	virtual void Update(float deltaTime) = 0;
	virtual ~BaseActor() = 0;

	protected:

	//transform

};

