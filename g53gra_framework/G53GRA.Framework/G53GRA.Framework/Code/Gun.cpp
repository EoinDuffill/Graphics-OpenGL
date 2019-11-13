#include "Gun.h"

Gun::Gun(int magazinesize)
{
	//Store mag size
	magsize = magazinesize;
	magsizeMax = magazinesize;

	//Load in textures
	DarkGreyMaterial = Scene::GetTexture("./Textures/dark-grey-material.bmp");
	GreyMaterial = Scene::GetTexture("./Textures/light_grey.bmp");
	GreenPlastic = Scene::GetTexture("./Textures/dark-olive-green.bmp");
	MediumGreyMaterial = Scene::GetTexture("./Textures/grey.bmp");
	Glass = Scene::GetTexture("./Textures/glass.bmp");

	quad = gluNewQuadric();
	gluQuadricTexture(quad, GLU_TRUE);
	gluQuadricNormals(quad, GLU_FLAT);
}


Gun::~Gun()
{
}

void Gun::IncState() {
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

//User prompt to move animation along, only done so if ready
void Gun::ActionGiven() {
	if (!running) {
		IncState();
		running = true;
	}
}

//initialise variables for a new state
void Gun::InitState() {
	keyframe = -1;
	animation_time = 0;
	animation_rotation = 0;
	animation_translation = 0;
	if (state == 2) {
		printf("Firing gun, bullets left = %d\n", magsize - 1);
	}
}

//Return if animation currently running
bool Gun::Running() {
	return running;
}

//Return current state
int Gun::GetState() {
	return state;
}

void Gun::Display() {

	glPushMatrix();
	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_TEXTURE_2D);
	
	//Move to pos and scale
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	
	//Rotate all the barrel
	//glRotatef(30, 0, 0, 1.0);

	glColor3f(0.5f, 0.5f, 0.5f);
	Barrel();
	glColor3f(0.75f, 0.75f, 0.75f);

	glPushMatrix();
	ScopeRail();
	Scope();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	Frame();
	glPushMatrix();
	Trigger();
	glPopMatrix();
	Stock();
	glPopMatrix();

	
	glTranslatef(0, 0, barrel_length);
	glRotatef((interp_bolt_start + animation_rotation*((interp_bolt_finish - interp_bolt_start) / interp_bolt_time)), 0, 0, 1.0);
	glTranslatef(0, 0, animation_bolt_translation);
	Bolt();

	glDisable (GL_TEXTURE_2D);
	//Revert style attributes
	glPopAttrib();

	glPopMatrix();
}

void Gun::Update(const double& deltaTime) {

	if (running) {
		animation_time += static_cast<float>(deltaTime);
		animation_rotation += static_cast<float>(deltaTime);
		animation_translation += static_cast<float>(deltaTime);
	}

	//State 1, Load the ammo into the gun
	if (state == 1) {
		if (animation_time >= 4.5) {
			
			running = false;
		}
		//Pull bolt back
		if (animation_time < 0.5) {
			if (keyframe != 0) {
				keyframe = 0;
				interp_bolt_time = 0.5;
				interp_bolt_start = 0;
				interp_bolt_finish = 0;
			}
			animation_bolt_translation = (1.2 * bolt_length * (animation_time));
		}
		//Pull bolt Up
		else if (animation_time < 1.0) {
			if (keyframe != 1) {
				keyframe = 1;
				animation_rotation = 0;
				interp_bolt_start = 0;
				interp_bolt_finish = 80;
			}
			
			
		}
		//Wait for magazine
		else if (animation_time < 3) {
			if (keyframe != 2) {
				keyframe = 2;
				interp_bolt_start = 80;
				interp_bolt_finish = 80;
			}
			
		}
		//Push bolt down
		else if (animation_time < 3.5) {
			if (keyframe != 3) {
				keyframe = 3;
				animation_rotation = 0;
				interp_bolt_start = 80;
				interp_bolt_finish = 0;
			}
			

		}
		//push bolt back
		else if (animation_time < 4) {
			if (keyframe != 4) {
				keyframe = 4;
				animation_rotation = 0;
				interp_bolt_start = 0;
				interp_bolt_finish = 0;
				
			}
			animation_bolt_translation = -(1.2 * bolt_length * (animation_time - 4));
		}
		else if (animation_time < 4.5) {
			if (keyframe != 5) {
				keyframe = 5;
				
			}
			animation_bolt_translation = 0;

		}

	}
	//State 2, Shoot the gun of all ammo
	else if (state == 2) {
		if (animation_time >= 3) {
			//animation_time = 0;
			running = false;

		}
		//Pull trigger
		if (animation_time < 0.25) {
			if (keyframe != 0) {
				keyframe = 0;
				animation_rotation = 0;
				interp_bolt_time = 0.5;
				interp_bolt_start = 0;
				interp_bolt_finish = 0;
				interp_trigger_time = 0.25;
				interp_trigger_start = 0;
				interp_trigger_finish = -25;
			}

		}
		//Trigger release
		else if (animation_time < 0.5) {
			if (keyframe != 1) {
				keyframe = 1;
				animation_rotation = 0;
				interp_bolt_time = 0.5;
				interp_bolt_start = 0;
				interp_bolt_finish = 0;
				interp_trigger_time = 0.5;
				interp_trigger_start = -25;
				interp_trigger_finish = 0;
			}


		}
		else if (animation_time < 1) {
			if (keyframe != 2) {
				keyframe = 2;
				interp_bolt_time = 0.5;
				interp_bolt_start = 0;
				interp_bolt_finish = 0;
				interp_trigger_time = 0.5;
				interp_trigger_start = 0;
				interp_trigger_finish = 0;
			}
			//Wait for .5s
		}
		else if (animation_time < 1.5) {
			if (keyframe != 3) {
				keyframe = 3;
				animation_rotation = 0.0f;
				interp_bolt_time = 0.5;
				interp_bolt_start = 0;
				interp_bolt_finish = 0;
			}
			//Bolt pull
			animation_bolt_translation = 1.2 * bolt_length * (animation_time - 1);
		}
		else if (animation_time < 2) {
			if (keyframe != 4) {
				animation_rotation = 0.0f;
				keyframe = 4;
				interp_bolt_time = 0.5;
				interp_bolt_start = 0;
				interp_bolt_finish = 80;
			}
			//Bolt pull up

		}
		else if (animation_time < 2.5) {
			if (keyframe != 5) {
				animation_rotation = 0.0f;
				keyframe = 5;
				interp_bolt_time = 0.5;
				interp_bolt_start = 80;
				interp_bolt_finish = 0;
			}
			//Bolt push down

		}
		else if (animation_time < 3) {
			if (keyframe != 6) {
				keyframe = 6;
				interp_bolt_time = 1;
				interp_bolt_start = 0;
				interp_bolt_finish = 0;
			}
			//Bolt push back
			animation_bolt_translation = -(1.2 * bolt_length * (animation_time - 3));
		}
	}
	//state3, magazine removal (done in magazine class)
	else if (state == 3) {
		if (animation_time >= 1.5) {

			running = false;
		}
	}
	else if (state == 4) {
		//Waiting stage
		running = false;
	}
	
}

void Gun::Stock() {

	glPushMatrix();

	//Stock straight block from stock
	glTranslatef(0.5, -0.5, 6);
	DrawCuboid(6, 3, 3, GreenPlastic);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	glPushMatrix();
	glRotatef(180, 0, 0, 1.0);
	glTranslatef(-4, -2.5, 0);
	DrawFrameSide(6, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	DrawFrameSide(6, 2);
	glPopMatrix();

	//Stock straight block from stock
	glTranslatef(0, 1.1, 2);
	glRotatef(65, 1.0, 0, 0);
	DrawCuboid(8, 3, 4, GreenPlastic);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	glPushMatrix();
	glTranslatef(4, 3.5, 0);
	glRotatef(180, 0, 0, 1.0);
	
	DrawFrameSide(8, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	DrawFrameSide(8, 3);
	glPopMatrix();
	glTranslatef(0, 0, 6);


	//Main Stock 
	glTranslatef(0, 0, 1.75);
	glRotatef(-65, 1.0, 0, 0);
	DrawCuboid(22, 3, 6, GreenPlastic);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	glPushMatrix();
	glTranslatef(4, 5.5, 0);
	glRotatef(180, 0, 0, 1.0);

	DrawFrameSide(22, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	DrawFrameSide(22, 5);
	glPopMatrix();
	glTranslatef(0, -3, 9.25);

	glPushMatrix();
	//Main Stock Top
	glTranslatef(0, 0, 1.75);
	DrawCuboid(11, 3, 6, GreenPlastic);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	glPushMatrix();
	glTranslatef(4, 5.5, 0);
	glRotatef(180, 0, 0, 1.0);

	DrawFrameSide(11, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	DrawFrameSide(11, 5);
	glPopMatrix();
	glTranslatef(0, 3.3, -9);

	//Main Stock Bottom Connector
	glTranslatef(0, 0, 1.75);
	glRotatef(25, 1.0, 0, 0);
	DrawCuboid(8, 3, 6, GreenPlastic);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	glPushMatrix();
	glTranslatef(4, 5.5, 0);
	glRotatef(180, 0, 0, 1.0);

	DrawFrameSide(8, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	DrawFrameSide(8, 5);
	glPopMatrix();

	

	//Main Stock Top
	
	glRotatef(-25, 1.0, 0, 0);
	glTranslatef(0, 2.5, 12.25);
	DrawCuboid(6, 3, 6, GreenPlastic);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	glPushMatrix();
	glTranslatef(4, 5.5, 0);
	glRotatef(180, 0, 0, 1.0);

	DrawFrameSide(6, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	DrawFrameSide(6, 5);
	glPopMatrix();
	glTranslatef(0, -2.88, -11.75);

	//Main Stock Top Connector
	glTranslatef(0, 0, 1.75);
	glRotatef(-15, 1.0, 0, 0);
	DrawCuboid(12, 3, 6, GreenPlastic);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	glPushMatrix();
	glTranslatef(4, 5.5, 0);
	glRotatef(180, 0, 0, 1.0);

	DrawFrameSide(12, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	DrawFrameSide(12, 5);
	glPopMatrix();
	

	glPopMatrix();

	
	

	glPopMatrix();
}

void Gun::Barrel() {
	
	glPushMatrix();

	glDisable(GL_CULL_FACE);
	
	//Inner cylinder for barrel
	glBindTexture(GL_TEXTURE_2D, MediumGreyMaterial);
	gluCylinder(quad, gun_bore_exit, gun_bore_start, barrel_length, 32, 6);
	//Disk for gap between cylinders at bullet exit
	gluDisk(quad, gun_bore_exit, barrel_width, 32, 1);

	glPushMatrix();
	glTranslatef(0, 0, barrel_length);
	//Disk for gap between cylinders at bullet entry
	gluDisk(quad, gun_bore_start, barrel_width, 32, 1);
	glTranslatef(0, 0, bolt_length*0.75);
	//Cylinders for barrel end (behind bullet entry point)
	gluCylinder(quad, gun_bore_start, gun_bore_start, 4, 32, 1);
	gluCylinder(quad, barrel_width, barrel_width, 4, 32, 1);
	//Disks between cylinders
	gluDisk(quad, gun_bore_start, barrel_width, 32, 1);
	glTranslatef(0, 0, 4);
	gluDisk(quad, gun_bore_start, barrel_width, 32, 1);

	glPopMatrix();
	glEnable(GL_CULL_FACE);
	//outer cylinder for barrel
	gluCylinder(quad, barrel_width, barrel_width, barrel_length, 32, 1);
	
	glPopMatrix();
}

void Gun::Bolt() {

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);
	//Bolt
	gluCylinder(quad, gun_bore_start, gun_bore_start, bolt_length, 32, 1);
	glPushMatrix();
	glRotatef(180, 1.0, 0, 0);
	gluDisk(quad, 0, gun_bore_start, 32, 1);
	glPopMatrix();
	glTranslatef(0, 0, bolt_length);
	gluDisk(quad, 0, gun_bore_start, 32, 1);

	//Bolt Handle
	glTranslatef(0,0,-1);
	glRotatef(90, 0, 1.0, 0);
	glRotatef(50, 1.0, 0, 0);
	glTranslatef(-0.5, 1, -0.3);
	DrawCuboid(6.5, 1, 0.5, DarkGreyMaterial);
	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);
	glTranslatef(.5, .25, 4.5);
	gluCylinder(quad, 0.25, 0.75, 1.5, 32, 1);
	glTranslatef(0, 0, 1.5);
	gluCylinder(quad, 0.75, 0.75, .5, 32, 1);
	glTranslatef(0, 0, .5);
	gluDisk(quad, 0, 0.75, 16, 1);

	glPopMatrix();

}

void Gun::ScopeRail() {

	
	//Rail
	glTranslatef(-scope_rail_width/2, barrel_width + 0.2, barrel_length - 10);
	DrawCuboid(scope_rail_length, scope_rail_width, 0.5, DarkGreyMaterial);
	//Rail Supports
	glPushMatrix();
	glTranslatef(scope_rail_width / 3, - 0.2, 2);
	DrawCuboid(6.5, scope_rail_width* 0.75, 0.2, DarkGreyMaterial);
	glTranslatef(0, 0, scope_rail_length* 0.85);
	DrawCuboid(2, scope_rail_width * 0.75, 0.2, DarkGreyMaterial);
	glPopMatrix();

}

void Gun::Scope() {

	glTranslatef(scope_rail_width / 2, 4, -5);

	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);
	//Scope tube widest
	gluCylinder(quad, 3.5, 3.5, 4, 32, 1);

	glPushMatrix();

	//Scope inner tube widest
	glDisable(GL_CULL_FACE);
	gluCylinder(quad, 3.3, 3.3, 4, 32, 1);
	glEnable(GL_CULL_FACE);
	
	//Exit Lens Rim
	glRotatef(180, 0, 1.0, 0);
	gluDisk(quad, 3.3, 3.5, 32, 1);
	glTranslatef(0, 0, -1);
	//Exit Lens
	glBindTexture(GL_TEXTURE_2D, Glass);
	glColor3f(0.4, 0.4, 0.4);
	gluDisk(quad, 0, 3.5, 32, 1);
	glPopMatrix();
	glColor3f(0.75, 0.75, 0.75);
	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);

	//Lense Cap clamp
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	gluCylinder(quad, 3.6, 3.6, 0.5, 32, 1);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 3.5, 3.6, 32, 1);
	glRotatef(180, 0, 1.0, 0);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 3.5, 3.6, 32, 1);
	glRotatef(180, 0, 1.0, 0);

	//Hinge
	glTranslatef(-0.75,3.5,0);
	DrawCuboid(0.5, 1.5, 0.5, DarkGreyMaterial);
	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);

	//Lens Cap
	glTranslatef(0.75, 1.6, 3.8);
	glRotatef(80, 1.0, 0, 0);
	glTranslatef(0, 0, 0.5);
	gluCylinder(quad, 3.6, 3.6, 0.5, 32, 1);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 0, 3.6, 32, 1);
	glRotatef(180, 0, 1.0, 0);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 0, 3.6, 32, 1);
	
	glPopMatrix();
	
	//Scope Tube Large to Small
	glTranslatef(0, 0, 4);
	gluCylinder(quad, 3.5, 1.75, 10, 32, 1);

	//Scope central tube
	glTranslatef(0, 0, 10);
	gluCylinder(quad, 1.75, 1.75, 20, 32, 1);

	//Scope to rail clamp
	glPushMatrix();	
	glRotatef(90, 1.0, 0, 0);
	glTranslatef(1.5, 2, -1);
	DrawCuboid(5, 0.5, 2.5, DarkGreyMaterial);

	glTranslatef(-3.25, 0, 0);
	DrawCuboid(5, 0.5, 2.5, DarkGreyMaterial);

	glRotatef(90, 0, 1.0, 0);
	glTranslatef(-4.5, 0, 0);
	DrawCuboid(3.5, 0.5, 2.5, DarkGreyMaterial);
	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);
	glPopMatrix();

	//Central sphere
	glTranslatef(0, 0, 8);
	glutSolidSphere(2.85, 50, 50);

	//Three scope adjustment cyliders (attached to the ball)
	//
	glPushMatrix();
	glRotatef(-90, 1.0, 0, 0);
	gluCylinder(quad, 1.75, 1.75, 3.5, 32, 1);
	glTranslatef(0, 0, 3.5);
	gluDisk(quad, 0, 1.75, 32, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1.0, 0);
	gluCylinder(quad, 1.75, 1.75, 3.5, 32, 1);
	glTranslatef(0, 0, 3.5);
	gluDisk(quad, 0, 1.75, 32, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1.0, 0);
	gluCylinder(quad, 1.75, 1.75, 3.5, 32, 1);
	glTranslatef(0, 0, 3.5);
	gluDisk(quad, 0, 1.75, 32, 1);
	glPopMatrix();
	//

	//Scope to rail clamp
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0);
	glTranslatef(1.5, 6, -1);
	DrawCuboid(5, 0.5, 2.5, DarkGreyMaterial);

	glTranslatef(-3.25, 0, 0);
	DrawCuboid(5, 0.5, 2.5, DarkGreyMaterial);

	glRotatef(90, 0, 1.0, 0);
	glTranslatef(-4.5, 0, 0);
	DrawCuboid(3.5, 0.5, 2.5, DarkGreyMaterial);
	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);
	glPopMatrix();

	//Scope Tube central to Medium 
	glTranslatef(0, 0, 12);
	gluCylinder(quad, 1.75, 2.5, 3, 32, 1);

	//Scope Tube medium
	glTranslatef(0, 0, 3);
	gluCylinder(quad, 2.5, 2.5, 6, 32, 1);
	glDisable(GL_CULL_FACE);
	gluCylinder(quad, 2.3, 2.3, 6, 32, 1);
	glEnable(GL_CULL_FACE);
	
	//Front Rim
	glTranslatef(0, 0, 6);
	gluDisk(quad, 2.3, 2.5, 32, 1);
	//Front Lens
	glBindTexture(GL_TEXTURE_2D, Glass);
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0, 0, -1);
	gluDisk(quad, 0, 2.5, 16, 1);
	glColor3f(0.75, 0.75, 0.75);
	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);


	glPushMatrix();
	//Lens cap Clamp
	glTranslatef(0, 0, 0);
	gluCylinder(quad, 2.6, 2.6, 0.5, 32, 1);
	glRotatef(180, 0, 1, 0);
	gluDisk(quad, 2.5, 2.6, 32, 1);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 2.5, 2.6, 32, 1);

	//Hinge
	glTranslatef(-0.75, 2.5, -0.5);
	DrawCuboid(0.5, 1.5, 0.5, DarkGreyMaterial);
	glBindTexture(GL_TEXTURE_2D, DarkGreyMaterial);

	//Lens Cap
	glTranslatef(0.75, 0.9, -2.4);
	glRotatef(-60, 1.0, 0, 0);
	glTranslatef(0, 0, 0.5);
	gluCylinder(quad, 2.6, 2.6, 0.5, 32, 1);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 0, 2.6, 32, 1);
	glRotatef(180, 0, 1.0, 0);
	glTranslatef(0, 0, 0.5);
	gluDisk(quad, 0, 2.6, 32, 1);

	glPopMatrix();

}

void Gun::Trigger() {

	//Trigger Guard
	glTranslatef(1.5-0.125, -3.5, -1.5);
	glPushMatrix();
	DrawCuboid(0.25, 1.5, 3, DarkGreyMaterial);
	glPopMatrix();

	glTranslatef(0, 0, 6);
	glPushMatrix();
	glRotatef(15, 1.0, 0, 0);
	DrawCuboid(0.25, 1.5, 3, DarkGreyMaterial);
	glPopMatrix();

	glTranslatef(0, 0, 0.1);
	glRotatef(-90, 1.0, 0, 0);
	DrawCuboid(0.25, 1.5, 5.9, DarkGreyMaterial);

	//Trigger
	glTranslatef(0, 1, 3.75);
	glRotatef(-100, 1.0, 0, 0);
	glRotatef((interp_trigger_start + animation_rotation*((interp_trigger_finish - interp_trigger_start) / interp_trigger_time)), 1.0, 0, 0);
	DrawCuboid(0.25, 1.5, 1.25, DarkGreyMaterial);
	
	glTranslatef(0, 1.25, 0);
	glRotatef(20, 1.0, 0, 0);	
	DrawCuboid(0.25, 1.5, 1, DarkGreyMaterial);

	glTranslatef(0, 1, 0);
	glRotatef(45, 1.0, 0, 0);	
	DrawCuboid(0.25, 1.5, 1.25, DarkGreyMaterial);

}

void Gun::Frame() {

	glPushMatrix();
	glRotatef(0.4, 1.0, 0, 0);
	glTranslatef(-2.5, -4.5, barrel_length*0.49);
	//Left side
	DrawFrameSide(barrel_length * 0.67, 4.5);

	glPopMatrix();
	glRotatef(0.4, 1.0, 0, 0);
	glTranslatef(2.5, 0, barrel_length*0.49);
	glRotatef(180, 0, 0, 1.0);
	//Right side
	DrawFrameSide(barrel_length * 0.67, 4.5);

	glRotatef(90, 1.0, 0, 0);
	glTranslatef(0,0,-5);
	//Frame underneath
	DrawCuboid(4, 4, barrel_length*0.55, GreenPlastic);
	glTranslatef(0, barrel_length*0.632, 0);
	//Under Bolt
	DrawCuboid(4, 4, 5, GreenPlastic);

	//Connector pieces to stock
	glTranslatef( 0, 4, 1.75);
	glPushMatrix();
	glRotatef(-14.5, 1.0, 0, 0);
	DrawCuboid(3, 4, 7, GreenPlastic);
	glTranslatef(-0.5, 7, 0.5);
	glRotatef(90, 1.0, 0, 0);
	DrawFrameSide(7, 2);

	glTranslatef(4.5, 2, 0);
	glRotatef(180, 0, 0, 1.0);
	DrawFrameSide(7, 2);

	glPopMatrix();
	glTranslatef(0, 0, -1.75);
	
	DrawCuboid(3, 4, 7, GreenPlastic);
	glTranslatef(-0.5, 7, .5);
	glRotatef(90, 1.0, 0, 0);
	
	DrawFrameSide(7, 2);

	glTranslatef(4.5, 0, 7);
	glRotatef(180, 0, 1.0, 0);
	DrawFrameSide(7, 2);
	//
}

void Gun::DrawFrameSide(float length, float height) {

	
	//Main stock side
	DrawCuboid(length, frame_width+0.5, height, GreenPlastic);

	glPushMatrix();

	glTranslatef(frame_width, height, 0);
	//Cylinder, round off top
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	gluCylinder(quad, .5, .5, length, 32, 1);
	glPopMatrix();


	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, -height, length - 0.00000002);
	//Cylinder end, back
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	gluDisk(quad, 0, 0.5, 32, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, length - 0.00000002);
	//Cylinder end, back
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	gluDisk(quad, 0, 0.5, 32, 1);
	glPopMatrix();

	glPopMatrix();


	//Stock top
	DrawCuboid(length, frame_width, frame_width, GreenPlastic);

	glPopMatrix();

	glTranslatef(frame_width, -frame_width, 0);
	DrawCuboid(length, frame_width, frame_width, GreenPlastic);
	glTranslatef(0, frame_width, 0);
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	gluCylinder(quad, .5, .5, length, 32, 1);

	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.00000001);
	glRotatef(180, 1.0, 0, 0);

	//Cylinder end, front
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	gluDisk(quad, 0, 0.5, 32, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, height, - 0.00000002);
	glRotatef(180, 1.0, 0, 0);
	//Cylinder end, back
	glBindTexture(GL_TEXTURE_2D, GreenPlastic);
	gluDisk(quad, 0, 0.5, 32, 1);
	glPopMatrix();

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Gun::DrawCuboid(float length, float width, float height, GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	
	// Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0, 0, length);
	glTexCoord2d(0, 1 );
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
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0, height, length);
	glTexCoord2d(0, 1);
	glVertex3f(width, height, length);
	glTexCoord2d(1, 1);
	glVertex3f(width, height, 0);
	glTexCoord2d(1, 0);
	glVertex3f(0, height, 0);
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
}
