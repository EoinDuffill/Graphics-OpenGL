#include "Light.h"


Light::Light()
	:  _positionalLight(1.0f)
{
	// Set ambient colour of the light (off-grey)
	static GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };

	// white diffuse
	static GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// Set specular colour (white)
	static GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}


Light::~Light()
{
}

void Light::Display()
{
	
}

void Light::Update(const double& deltaTime)
{
	
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, _ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _specular);

	GLfloat lPosition[4] = { pos[0], pos[1], pos[2], _positionalLight };
	glLightfv(GL_LIGHT0, GL_POSITION, lPosition);

	// enable GL_LIGHT0 with these defined properties
	glEnable(GL_LIGHT0); 
}

