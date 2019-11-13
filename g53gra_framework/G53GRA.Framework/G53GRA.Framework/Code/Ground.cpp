#include "Ground.h"



Ground::Ground()
{
}


Ground::~Ground()
{
}

void Ground::Display() {

	glBegin(GL_QUADS);

	glColor3f(0.5f, 0.5f, 0.5f);

	glVertex3f(-size, -50, -size);
	glVertex3f(-size, -50, size);
	glVertex3f(size, -50, size);
	glVertex3f(size, -50, -size);
	glEnd();




}
