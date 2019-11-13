#pragma once
#include "DisplayableObject.h"

#include "Animation.h"

#define GL_CLAMP_TO_EDGE 0x812f

class SkyBox :
	public DisplayableObject
{
public:
	SkyBox();
	~SkyBox();

	virtual void Display() override;
	void Update(const double& deltaTime);

private:

	GLuint up, down, left, right, back, forward;
	//Size
	float height = 1024, width = 1024, length = 1024;

};

