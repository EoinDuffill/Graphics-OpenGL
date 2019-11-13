#pragma once
#include <DisplayableObject.h>
#include <Animation.h>

#include <ctime>


#define M_PI 3.14159265358979323846
#define GRAVITY -9.81f

class Bullet :
	public DisplayableObject,
	public Animation
{
public:
	Bullet();
	~Bullet();

	virtual void Display() override;
	void Update(const double& deltaTime);

	void SetBulletNumber(int n);
	void IncState();
	//User prompt to advance
	void ActionGiven();

private:

	//Texture vars..
	GLuint brass;
	GLuint lead;
	GLUquadric *quad;

	//initial bullet number and bullet number, determines whether to shoot or not
	int bullet_number_init = 0;
	int bullet_number = 0;
	int state = 0;
	float rand_rotation = 0;
	float rand_speed = 0;

	//Draw Bullet
	void Payload(float cone_height, float cone_angle, float res);
	//Draw Bullet Casing
	void Casing();
	
	//Initialise new animation state
	void InitState();

	//Bullet radius, is determined later on
	float bullet_radius = 0;

	//Bullet speed
	float bullet_speed = 3000;

	//Animation keyframe
	int keyframe = -1;

	//Animation translation variables, for various states in bullet animation
	float animation_time = 0;
	float animation_rotation = 0;
	float animation_translation = 0;

	//Bullet fire
	float animation_bullet_translation = 0;

	//Move up in magazine
	float animation_bullet_load_translation = 0;
	//From magazine into chamber
	float animation_bullet_from_mag_along = 0;
	float animation_bullet_from_mag_up = 0;

	//Bullet casing translations, post shot
	float animation_casing_translation = 0;
	float animation_casing_rotation = 0;
	float animation_casing_ejection_down = 0;
	float animation_casing_ejection_side = 0;

	//speeds and angles for casing ejection
	float casing_ejection_rotational_velocity = 40;
	float casing_ejection_angle = 60;
	float casing_ejection_speed = 65;

};

