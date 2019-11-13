#pragma once
#include "DisplayableObject.h"

#include "Animation.h"

class Magazine :
	public DisplayableObject,
	public Animation
{
public:
	Magazine(int magazinesize);
	~Magazine();

	virtual void Display() override;
	void Update(const double& deltaTime);

	//User prompt to advance animation
	void ActionGiven();

private:

	//Texture var
	GLuint DarkGreyMaterial;

	//Animation state
	int state = 0;
	int keyframe = -1;
	//Animation running
	bool running = false;
	//Magazine size
	int magsize = 1;
	int magsizeMax = 1;

	//Animation vars for translation
	float animation_time = 0;
	float animation_translation = 0;
	float animation_translation_mag = 0;

	//increment state
	void IncState();
	//initialise state vars
	void InitState();

	//Draw magazine
	void Mag();

	//Draw Cuboid, as before however with top side not drawn and insides drawn
	void DrawCuboid(bool mag, float length, float width, float height, GLuint texture);
};

