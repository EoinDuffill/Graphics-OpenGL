#pragma once

#include <Scene.h>

#include "Gun.h"

#include "Ground.h"

#include "Bullet.h"

#include "Light.h"

#include "MuzzleFlash.h"

#include "SkyBox.h"

#include "Magazine.h"

#define MAG_SIZE 5

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

	void HandleMouse(int button, int state, int x, int y);

private:
	void Initialise();
	void Projection();

	void NewBullets();

	bool EarlyRunningCheck = false;
	//Vars for objs
	Bullet **bullets;
	Gun *g;
	Magazine *mag;
	MuzzleFlash *f;
	Ground *ground;
	SkyBox *skybox;

};