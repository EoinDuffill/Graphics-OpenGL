#include "Bullet.h"

Bullet::Bullet()
{
	brass = Scene::GetTexture("./Textures/brass2.bmp");
	lead = Scene::GetTexture("./Textures/grey-plastic.bmp");
	quad = gluNewQuadric();
	gluQuadricTexture(quad, GLU_TRUE);
	gluQuadricNormals(quad, GLU_FLAT);
}


Bullet::~Bullet()
{
}

void Bullet::SetBulletNumber(int n) {
	//Set bullet number
	bullet_number = n;
	bullet_number_init = n;

	//Random vars for casing ejection earlier
	srand(time(0)*n);
	//rand_rotation = 1 + (((float)rand() )/ (float)RAND_MAX) * (45 - 1);
	casing_ejection_speed *= 1 + (((float)rand()) / (float)RAND_MAX) * (1.66 - 1);
}

void Bullet::IncState() {
	//State incrementation
	if (state != 2) {
		state += 1;
		InitState();
	}
	else {
		bullet_number--;
		if (bullet_number >= 0) {
			InitState();
		}
		
	}
	printf("state = %d, bul num = %d\n", state, bullet_number);
	
}

void Bullet::ActionGiven() {

	IncState();

}

void Bullet::InitState() {
	//Initialise a new state
	keyframe = -1;
	animation_time = 0;
	animation_rotation = 0;
}

void Bullet::Display() {

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	
	//Move to pos and scale
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	//Apply bullet animation translations
	glTranslatef(0 , -60 + animation_translation + animation_bullet_from_mag_up, -animation_bullet_load_translation - animation_bullet_from_mag_along);


	glRotatef(-90, 1.0, 0, 0);
	glRotatef(90, 0, 1.0, 0);
	//Draw Bullet
	glColor3f(0.8f, 0.8f, 0.8f);
	Payload(15, M_PI / 7, M_PI / 32);

	glRotatef(-90, 0, 1.0, 0);
	glRotatef(90, 1.0, 0, 0);
	

	//Draw Casing
	glColor3f(0.75f, 0.75f, 0.75f);
	Casing();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}

void Bullet::Update(const double& deltaTime) {

	//Animation counters, based on delta time
	animation_time += static_cast<float>(deltaTime);
	animation_rotation += static_cast<float>(deltaTime);
	
	//Translation into the gun
	if (state == 1) {
		
		if (animation_time < 1) {
			if (keyframe != 0) {
				keyframe = 0;
			}
		}
		else if (animation_time < 2.5) {
			if (keyframe != 1) {
				keyframe = 1;
			}
			animation_translation = 40 * (animation_time - 1);
		}
		else if (animation_time < 3.5) {
			if (keyframe != 2) {
				keyframe = 2;
			}
		}
		else if (animation_time < 4 && bullet_number == 0) {
			if (keyframe != 3) {
				keyframe = 3;
			}
			animation_bullet_load_translation = 140 * (animation_time - 3.5);
		}
	}
	//Bullet is to be shot (i.e. state = 2, shooting state, bullet_number = 0, this bullets turn to shoot)
	else if (state == 2 && bullet_number == 0) {

		if (animation_time < 0.25) {
			if (keyframe != 0) {
				keyframe = 0;
			}
			
		}
		else if (animation_time < 0.75) {
			if (keyframe != 1) {
				keyframe = 1;
			}
			//Bullet in flight tranlation
			animation_bullet_translation = bullet_speed * (animation_time - 0.25);
		}
		else if (animation_time < 1) {
			if (keyframe != 2) {
				keyframe = 2;
			}
			//Bullet in flight tranlation
			animation_bullet_translation = bullet_speed * (animation_time - 0.25);
		}
		else if (animation_time < 1.5) {
			if (keyframe != 3) {
				keyframe = 3;
			}
			//pull back from the chamber
			animation_casing_translation = 140 * (animation_time - 1);
			//Bullet in flight tranlation
			animation_bullet_translation = bullet_speed * (animation_time - 0.25);
		}
		else if (animation_time < 10) {
			if (keyframe != 4) {
				keyframe = 4;
				animation_rotation = 0;
			}
			//Bullet in flight tranlation
			animation_bullet_translation = bullet_speed * (animation_time - 0.25);
			//Casing physics, via suvat
			if (animation_casing_ejection_down > -100) {
				//displacement vertically
				animation_casing_ejection_down = (casing_ejection_speed*sin(casing_ejection_angle * (M_PI / 180)))*(animation_time - 1.5) + ((0.5 * (GRAVITY*(1 / scale[0])))*((animation_time - 1.5)*(animation_time - 1.5)));
				//displacement sideways
				animation_casing_ejection_side = (casing_ejection_speed*cos(casing_ejection_angle * (M_PI / 180)))*(animation_time - 1.5);
				//spinning the cartridge
				animation_casing_rotation = 180 * (sin( casing_ejection_rotational_velocity * animation_rotation* (M_PI / 180)));

			}
		}
	}
	//Move bullet up the magazine
	else if (state == 2 && bullet_number > 0) {
		if (animation_time > 2 && animation_time < 2.5) {
			animation_bullet_from_mag_up = ( (bullet_number_init - bullet_number + 1) * bullet_radius * 1.25 * 2 * 2* (animation_time - 2));
		}
		else if (animation_time > 2.5 && animation_time < 3 && bullet_number == 1) {
			animation_bullet_from_mag_along = 140 * (animation_time - 2.5);
		}
	}
	//Suvat calculations after bullet shot
	else if(state == 2){
		//Bullet in flight tranlation
		animation_bullet_translation = bullet_speed * (animation_time - 0.25);
		if (animation_casing_ejection_down > -100) {
			//displacement vertically
			animation_casing_ejection_down = (casing_ejection_speed*sin(casing_ejection_angle * (M_PI / 180)))*(animation_time - 1.5) + ((0.5 * (GRAVITY*(1 / scale[0])))*((animation_time - 1.5)*(animation_time - 1.5)));
			//displacement sideways
			animation_casing_ejection_side = (casing_ejection_speed*cos(casing_ejection_angle * (M_PI / 180)))*(animation_time - 1.5);
			//spinning the cartridge
			animation_casing_rotation = 180 * (sin( casing_ejection_rotational_velocity * animation_rotation* (M_PI / 180)));


		}
	}

	

}

void Bullet::Casing() {

	glPushMatrix();

	//Apply translations and rotations to the bullet casing
	glTranslatef(animation_casing_ejection_side, animation_casing_ejection_down, animation_casing_translation);
	glRotatef(animation_casing_rotation, 0, 1.0, 0);

	glDisable(GL_CULL_FACE);
	//Brass Texture
	glBindTexture(GL_TEXTURE_2D, brass);
	//Casing and bullet contact patch

	gluCylinder(quad, bullet_radius*1.01, bullet_radius*1.01, bullet_radius, 32, 1);
	glTranslatef(0, 0, bullet_radius );

	//Casing widening
	gluCylinder(quad, bullet_radius*1.01, bullet_radius*1.25, bullet_radius, 32, 1);
	glTranslatef(0, 0, bullet_radius );

	//Casing length
	gluCylinder(quad, bullet_radius*1.25, bullet_radius*1.25, bullet_radius * 7, 32, 1);
	glTranslatef(0, 0, bullet_radius * 7);

	//Casing indent
	gluDisk(quad, 0, bullet_radius*1.25, 32, 1);
	gluCylinder(quad, bullet_radius*1.2, bullet_radius*1.2, 0.5, 32, 1);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 0, bullet_radius*1.25, 32, 1);
	gluCylinder(quad, bullet_radius*1.25, bullet_radius*1.25, 1, 32, 1);
	glTranslatef(0, 0, 1);
	gluDisk(quad, 0, bullet_radius*1.25, 32, 1);
	glEnable(GL_CULL_FACE);

	glPopMatrix();
}

void Bullet::Payload(float cone_height, float cone_angle, float res) {

	glPushMatrix();

	glTranslatef(0, animation_bullet_translation, 0);

	//Nose length 
	float nose_length = cone_height;
	float r_res = res;
	float temp_r = 0;

	float conical_radius = 3 * nose_length;
	float conical_angle = cone_angle;
	float conical_res = conical_angle * res;

	//Angles for calculations
	float phi = conical_angle;
	float theta = 0.f;

	float x = 0.f, y = 0.f, z = 0.f;


	while (theta < ((2 * M_PI) )) {
		//Set initial values of radius and phi
		temp_r = 0;
		phi = conical_angle;

		glBindTexture(GL_TEXTURE_2D, lead);

		do {
			glBegin(GL_QUADS);
			

			glTexCoord2d(0,0);

			x = temp_r * cos(theta);
			y = conical_radius * sin(phi);
			z = temp_r * sin(theta);
			glVertex3f(x, y, z);

			//Increase theta by resolution
			theta += r_res;

			glTexCoord2d(0, 1);

			x = temp_r * cos(theta);
			z = temp_r * sin(theta);
			glVertex3f(x, y, z);

			//Decrement phi by resolution
			phi -= conical_res;
			//Update temp radius as phi has been decreased
			temp_r = abs((conical_radius * cos(phi)) - (conical_radius * cos(conical_angle)));
			
			//Store max value for bullet radius
			if(temp_r > bullet_radius) bullet_radius = temp_r;

			glTexCoord2d(1, 1);

			y = conical_radius * sin(phi);
			x = temp_r * cos(theta);
			z = temp_r * sin(theta);
			glVertex3f(x, y, z);

			//Reset theta
			theta -= r_res;

			glTexCoord2d(1, 0);

			x = temp_r * cos(theta);
			z = temp_r * sin(theta);
			glVertex3f(x, y, z);

			glEnd();
		} while (phi > -6*conical_res);

		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -y);
		gluDisk(quad, 0, temp_r, 24, 1);
		glPopMatrix();

		//Increment theta by resolution for a new strip down the cone
		theta += r_res;
	}

	glPopMatrix();

}
