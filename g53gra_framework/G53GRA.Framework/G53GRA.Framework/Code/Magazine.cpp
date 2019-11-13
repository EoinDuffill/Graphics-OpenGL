#include "Magazine.h"

Magazine::Magazine(int magazinesize)
{
	magsize = magazinesize;
	magsizeMax = magazinesize;

	DarkGreyMaterial = Scene::GetTexture("./Textures/dark-grey-material.bmp");
}


Magazine::~Magazine()
{
}

void Magazine::IncState() {
	//Decrement magsize until empty, then increment to next state
	if (state != 2) {
		state += 1;
	}
	else {
		magsize--;
		if (magsize <= 0) {
			state++;
		}
	}
	//If ended, set state to init state
	if (state == 5) {
		magsize = magsizeMax;
		state = 1;
	}
	InitState();
	printf("%d\n", state);
}

//User prompt to advance animation, only done if animation currently not running
void Magazine::ActionGiven() {
	if (!running) {
		IncState();
		running = true;
	}
}

//initialise vars for new state
void Magazine::InitState() {
	keyframe = -1;
	animation_time = 0;
	animation_translation = 0;
	if (state == 2) {

	}
}

void Magazine::Display() {

	glPushMatrix();
	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_TEXTURE_2D);

	//Move to pos and scale
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	//Translate mag according to animation
	glTranslatef(0, animation_translation_mag, 0);
	//Draw magazine
	Mag();

	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glPopMatrix();

}

void Magazine::Update(const double& deltaTime) {

	if (running) {
		animation_time += static_cast<float>(deltaTime);
		animation_translation += static_cast<float>(deltaTime);
	}

	//Raise mag
	if (state == 1) {
		if (animation_time >= 4.5) {

			running = false;
		}

		if (animation_time < 1) {
			if (keyframe != 0) {
				keyframe = 0;
			}
		}
		else if (animation_time < 2.5) {
			if (keyframe != 1) {
				keyframe = 1;
			}
			animation_translation_mag = 6.5 * (animation_time - 1);
		}
	}
	//Waiting while shooting
	else if (state == 2) {
		if (animation_time >= 3) {

			running = false;
		}
	}
	//Magazine exit
	else if (state == 3) {
		if (animation_time >= 1.5) {

			running = false;
		}
		if (animation_time < 1.5) {
			if (keyframe != 0) {
				keyframe = 0;
			}
			animation_translation_mag = -6.5 * (animation_time - 1.5);
		}
	}
	else if (state == 4) {
		//Waiting state
		running = false;
	}

}

void Magazine::Mag() {
	DrawCuboid(true, 12, 3, 10, DarkGreyMaterial);
}

void Magazine::DrawCuboid(bool mag, float length, float width, float height, GLuint texture) {
	glDisable(GL_CULL_FACE);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);

	// Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0, 0, length);
	glTexCoord2d(0, 1);
	glVertex3f(width, 0, length);
	glTexCoord2d(1, 1);
	glVertex3f(width, height, length);
	glTexCoord2d(1, 0);
	glVertex3f(0, height, length);

	// Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3f(0, height, 0);
	glTexCoord2d(1, 1);
	glVertex3f(width, height, 0);
	glTexCoord2d(1, 0);
	glVertex3f(width, 0, 0);
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3f(0, 0, length);
	glTexCoord2d(1, 1);
	glVertex3f(0, height, length);
	glTexCoord2d(1, 0);
	glVertex3f(0, height, 0);
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(width, 0, length);
	glTexCoord2d(0, 1);
	glVertex3f(width, 0, 0);
	glTexCoord2d(1, 1);
	glVertex3f(width, height, 0);
	glTexCoord2d(1, 0);
	glVertex3f(width, height, length);
	// Top
	if (!mag) {
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0, 0);
		glVertex3f(0, height, length);
		glTexCoord2d(0, 1);
		glVertex3f(width, height, length);
		glTexCoord2d(1, 1);
		glVertex3f(width, height, 0);
		glTexCoord2d(1, 0);
		glVertex3f(0, height, 0);
	}
	// Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0, 0, length);
	glTexCoord2d(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2d(1, 1);
	glVertex3f(width, 0, 0);
	glTexCoord2d(1, 0);
	glVertex3f(width, 0, length);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_CULL_FACE);
}
