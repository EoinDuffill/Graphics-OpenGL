#include "MuzzleFlash.h"

MuzzleFlash::MuzzleFlash()
{
	// Set ambient colour of the light (redish)
	static GLfloat ambient[] = { 0.05f, 0.0075f, 0.005f, 1.0f };

	static GLfloat diffuse[] = { 1.0f, 0.5, 0.25, 1.0f };

	// Set specular colour (white)
	static GLfloat specular[] = { 0.15f, 0.075f, 0.05f, 1.0f };

	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}


MuzzleFlash::~MuzzleFlash()
{
}


void MuzzleFlash::Display() {

}

void MuzzleFlash::Update(const double& deltaTime) {

	//Reset as has run for long enough
	if (runtime > FlashLength) {
		Flash = false;
		glDisable(GL_LIGHT1);
	}
	runtime += deltaTime;

	//Enable lights if flash is true and it hasnt been running too long
	if (Flash && runtime - FlashDelay > 0) {


		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT1, GL_AMBIENT, _ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, _diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, _specular);

		GLfloat lPosition[4] = { pos[0], pos[1], pos[2], 1 };
		glLightfv(GL_LIGHT1, GL_POSITION, lPosition);

		// enable GL_LIGHT0 with these defined properties
		glEnable(GL_LIGHT1);
		
	}
}

void MuzzleFlash::SetFlash(bool b) {
	Flash = b;
	runtime = -FlashDelay;

}

bool MuzzleFlash::GetFlash() {
	return Flash;
}
