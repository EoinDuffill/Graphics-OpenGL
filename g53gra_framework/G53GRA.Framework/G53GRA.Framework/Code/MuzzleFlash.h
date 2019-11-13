#pragma once
#include "DisplayableObject.h"

#include "Animation.h"

class MuzzleFlash :
	public DisplayableObject,
	public Animation
{
public:
	MuzzleFlash();
	~MuzzleFlash();

	void Display();

	void Update(const double& deltaTime);

	void SetFlash(bool b);
	bool GetFlash();

private:

	bool Flash = false;
	//Delay between call to flash and actually flashing (allowing bullet to exit barrel)
	float FlashDelay = 0.25;

	//Length of time to flash for
	float FlashLength = 0.1 + FlashDelay;

	float runtime;

	GLfloat *_ambient, *_diffuse, *_specular;
};

