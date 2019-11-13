#pragma once
#include "DisplayableObject.h"
#include "Animation.h"

class Gun :
	public DisplayableObject,
	public Animation
{
public:
	Gun(int magsize);
	~Gun();

	virtual void Display() override;
	void Update(const double& deltaTime);

	//User prompt to move animation on
	void ActionGiven();
	bool Running();
	int GetState();

private:

	//Texture vars
	GLuint DarkGreyMaterial;
	GLuint GreyMaterial;
	GLuint MediumGreyMaterial;
	GLuint GreenPlastic;
	GLuint Glass;

	GLUquadric *quad;

	//State variable, and var for if animation running
	bool running = false;
	int state = 0;
	//Magazine size
	int magsize = 1;
	int magsizeMax = 1;

	//Draw Barrel
	void Barrel();
	//Draw Bolt
	void Bolt();
	//Draw the frame which hold the gun together
	void Frame();
	//Helper function for the frame and stock (Drawing rounded sides cuboids)
	void DrawFrameSide(float length, float height);
	//Draw Rail holding the scope
	void ScopeRail();
	//Draw Scope
	void Scope();
	//Draw trigger and trigger guard
	void Trigger();
	//Draw Butt stock of the gun
	void Stock();

	//Draw a cuboid, dynamic x, y, z with texture to draw
	void DrawCuboid(float length, float width, float height, GLuint texture);

	//Increment state
	void IncState();
	//Initialise animation vars for new state
	void InitState();

	//Barrel, scope, bolt and frame vars
	float gun_bore_exit = 0.75;
	float gun_bore_start = 1.5;
	float barrel_width = 2;
	float barrel_length = 130;

	float scope_rail_length = 30;
	float scope_rail_width = 2.25;

	float bolt_length = 22.5;
	float bolt_handle_radius = 0.5;

	float frame_width = 0.5;

	//Animation
	int keyframe = -1;
	float animation_time = 0;
	float animation_rotation = 0;
	float animation_translation = 0;
	float animation_bolt_translation = 0;

	//Interp for bolt
	float interp_bolt_start = 0;
	float interp_bolt_finish = 0;
	float interp_bolt_time = 1;

	//Interp for trigger
	float interp_trigger_time = 1;
	float interp_trigger_start = 0;
	float interp_trigger_finish = 0;
};

