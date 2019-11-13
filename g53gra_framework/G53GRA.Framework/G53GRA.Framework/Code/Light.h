#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

#include <cmath>

class Light :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Light();
	~Light();

	// Could use to represent light source with sphere (optional)
	virtual void Display() override;

	void Update(const double& deltaTime);

private:

	// reflectance model parameters for LIGHT
	GLfloat *_ambient, *_diffuse, *_specular;

	// flag for indicating positional or directional light source
	// 0.0f for directional, 1.0f for positional
	GLfloat _positionalLight;
};

