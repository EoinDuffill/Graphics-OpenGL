#include "MyScene.h"


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Skybox and textures
	skybox = new SkyBox();
	AddObjectToScene(skybox);

	//Ground object, all ground pieces
	ground = new Ground();
	AddObjectToScene(ground);

	//Create bullet array and add new bullets
	bullets = new Bullet*[MAG_SIZE];
	NewBullets();
	
	//Create the gun
	g = new Gun(MAG_SIZE);
	g->size(1);
	AddObjectToScene(g);

	//Create the magazine
	mag = new Magazine(MAG_SIZE);
	mag->position(-1.25, -20.5, 131.5);
	AddObjectToScene(mag);

	//Standard light, for scene light source
	Light *l = new Light();
	l->position(50, 100, 0);
	AddObjectToScene(l);

	//Light source for muzzle flashes, after shots are fired
	f = new MuzzleFlash();
	f->position(0, 10, 0);
	AddObjectToScene(f);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 10000.0);
}

//Function to spawn in new bullets, 1 magazine of them
void MyScene::NewBullets() {
	for (int i = 0; i < MAG_SIZE; i++) {
		bullets[i] = new Bullet();
		bullets[i]->size(0.175);
		bullets[i]->position(0, -i * 2, 136);
		bullets[i]->SetBulletNumber(i);
		AddObjectToScene(bullets[i]);
	}
}


void MyScene::HandleMouse(int button, int state, int x, int y) {
	Scene::HandleMouse(button, state, x, y);

	//Right button to advance animation and shots
	if (state == 1 && button == GLUT_RIGHT_BUTTON) {
		
		//Bullet Action
		if (!g->Running()) {
			for (int i = 0; i < MAG_SIZE; i++) {
				bullets[i]->ActionGiven();
			}
		}
		printf("Action given\n");
		
		//Muzzle Flash Checks
		//
		if (!g->Running()) {
			EarlyRunningCheck = true;
		}
		//Gun Action
		g->ActionGiven();
		if (g->GetState() == 2 && EarlyRunningCheck && !f->GetFlash()) {
			printf("flash\n");
			f->SetFlash(true);
		}
		EarlyRunningCheck = false;
		//

		//If state is 4, then create new bullets, animation will start to repeat now
		if (g->GetState() == 4) {
			NewBullets();
		}

		//Mag action
		mag->ActionGiven();
	}

}
