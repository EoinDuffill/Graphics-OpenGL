#include "SkyBox.h"

SkyBox::SkyBox()
{

	//Load in skybox
	up = Scene::GetTexture("./Textures/nightsky_up.bmp");
	down = Scene::GetTexture("./Textures/nightsky_dn.bmp");
	forward = Scene::GetTexture("./Textures/nightsky_ft.bmp");
	back = Scene::GetTexture("./Textures/nightsky_bk.bmp");
	left = Scene::GetTexture("./Textures/nightsky_lf.bmp");
	right = Scene::GetTexture("./Textures/nightsky_rt.bmp");

}


SkyBox::~SkyBox()
{
}

void SkyBox::Display() {

	glColor3f(1, 1, 1);

	glDisable(GL_CULL_FACE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, forward);
	//Removing line on skybox edge (for each skybox panel)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	
	

	// Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(-width, -height, length);
	glTexCoord2d(0, 0);
	glVertex3f(width, -height, length);
	glTexCoord2d(0, 1);
	glVertex3f(width, height, length);
	glTexCoord2d(1, 1);
	glVertex3f(-width, height, length);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, back);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	
	// Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-width, -height, -length);
	glTexCoord2d(0, 1);
	glVertex3f(-width, height, -length);
	glTexCoord2d(1, 1);
	glVertex3f(width, height, -length);
	glTexCoord2d(1, 0);
	glVertex3f(width, -height, -length);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, left);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(1, 0);
	glVertex3f(-width, -height, -length);
	glTexCoord2d(0, 0);
	glVertex3f(-width, -height, length);
	glTexCoord2d(0, 1);
	glVertex3f(-width, height, length);

	glTexCoord2d(1, 1);
	glVertex3f(-width, height, -length);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, right);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(1, 0);
	glVertex3f(width, -height, length);
	glTexCoord2d(0, 0);
	glVertex3f(width, -height, -length);
	glTexCoord2d(0, 1);
	glVertex3f(width, height, -length);
	glTexCoord2d(1, 1);
	glVertex3f(width, height, length);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, up);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	

	// Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1, 1);
	glVertex3f(-width, height, length);
	glTexCoord2d(1, 0);
	glVertex3f(width, height, length);
	glTexCoord2d(0, 0);
	glVertex3f(width, height, -length);
	glTexCoord2d(0, 1);
	glVertex3f(-width, height, -length);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, down);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	

	// Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-width, -height, length);
	glTexCoord2d(0, 1);
	glVertex3f(-width, -height, -length);
	glTexCoord2d(1, 1);
	glVertex3f(width, -height, -length);
	glTexCoord2d(1, 0);
	glVertex3f(width, -height, length);
	
	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_CULL_FACE);

	

}

void SkyBox::Update(const double & deltaTime)
{
}
