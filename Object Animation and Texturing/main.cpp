#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "glm.h"
#include <iostream> 
#include <math.h>
#include "imageloader.h"

#define PI 3.14

static int body = 0, head = 0, shoulderl1 = 0, shoulderl2 = 0, shoulderr1 = 0, shoulderr2 = 0, elbowl1 = 0, elbowr1 = 0, llegup1 = 0, llegup2 = 0, llegdown = 0, leftfoot = 0, rightfoot = 0, rlegup1 = 0, rlegup2 = 0, rlegdown = 0;
double eye[] = { 0, 0, 10 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
const char *modelname = "objects/birch.obj";
const char *modelname2 = "objects/bench.obj";
double speed = 0.2;
int pressed = 0;
int limitForwardBackward = 0, limitUpDown=0 , limitRightLeft = 0;
int i;
int moving, startx, starty;
GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

// RGBA
GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0.0};
GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
// x , y, z, w
GLfloat light_position[] = {0.5, 5.0, 0.0, 1.0};
GLfloat lightPos1[] = {-0.5, -5.0, -2.0, 1.0};
GLuint _textureId; //The id of the basic texture
GLuint _textureId0; //The id of the texture GreenBronze
GLuint _textureId1; //The id of the texture gray
GLuint _textureId2; //The id of the texture grass
GLuint _textureId3; //The id of the texture MattoniBasamento
GLuint _textureId4; //The id of the texture Pavimentazione


  

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId);			 //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
        0,							  //0 for now
        GL_RGB,					  //Format OpenGL uses for image
        image->width, image->height, //Width and height
        0,							  //The border of the image
        GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
        GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
                                     //as unsigned numbers
        image->pixels);			  //The actual pixel data
    return textureId;						  //Returns the id of the texture
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
    gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 0.2, 5.0);
}
void drawmodel(char *filename)
{
	GLMmodel *model = glmReadOBJ(filename);
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90.0);
	glmScale(model, 2);
	glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
}

//Initializes 3D rendering
void initRendering(const char* bmbImg, GLuint & textureID)
{
    Image *image = loadBMP(bmbImg);
	//Image *image = loadBMP("grass.bmp");
	_textureId = loadTexture(image);
	delete image;
	// Turn on the power
	glEnable(GL_LIGHTING);
	// Flip light switch
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	// assign light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	// Material Properties
	GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glEnable(GL_NORMALIZE);
	//Enable smooth shading
	glShadeModel(GL_SMOOTH);
	// Enable Depth buffer
	glEnable(GL_DEPTH_TEST);
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
void turnLeft()
{
	double theta = -PI/100;
    rotatePoint(up, theta, eye);
}

void turnRight()
{
	double theta = PI/100;
    rotatePoint(up, theta, eye);
}

void moveUp()
{
	double horizontal [3];
    double look [] = {center[0] -eye[0], center[1] -eye[1], center[2] -eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI/100, eye);
    rotatePoint(horizontal, PI/100, up);
}


void moveDown()
{

	double horizontal [3];
    double look [] = {center[0] -eye[0], center[1] -eye[1], center[2] -eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI/100, eye);
    rotatePoint(horizontal, -PI/100, up);
}

void moveForward()
{

	double speed = 0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{

	double speed = -0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void display(void)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Clear Depth and Color buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);


	glTranslatef(0.0, 0.0, -2.0);
	glTranslatef(0.0, 1.25, 0.0);
	glRotatef(body, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);

	//Head

	glPushMatrix();
	glTranslatef(0.0, 4, 0.0);
	glRotatef(head, 0.0, 1.0, 0.0);
	glScalef(1.75, 1.75, 1.75);
	glutWireSphere(0.35, 16, 16);
	glPopMatrix();

	//Body
	glPushMatrix();
	glScalef(2.0, 6.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	/////////////////////////////////////////////////////////////////////////
	//start left arm
	glPushMatrix();

	//left shoulder

	//1st movement
	glTranslatef(1.4, 2.75, 0.0);
	glRotatef(shoulderl1, 0.0, 0.0, 1.0);
	glTranslatef(-1.4, -2.75, 0.0);

	//2nd movement
	glTranslatef(1.4, 2.75, 0.0);
	glRotatef(shoulderl2, 0.0, 1.0, 0.0);
	glTranslatef(-1.4, -2.75, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(1.4, 2, 0.0);
	glScalef(0.3, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();

	//left elbow

	//1st movement
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(elbowl1, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(1.4, 0.5, 0.0);
	glScalef(0.3, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();

	//left hand

	glPushMatrix();
	//finger1
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(1.4, -0.42, -0.1);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);


	glPopMatrix();
	//finger2
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(1.4, -0.42, 0.0);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);


	glPopMatrix();
	//finger3
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(1.4, -0.42, 0.1);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);


	glPopMatrix();
	//finger4
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(1.4, -0.42, 0.2);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//end left arm
	//start right arm
	glPushMatrix();

	//right shoulder

	//1st movement
	glTranslatef(-1.4, 2.75, 0.0);
	glRotatef(shoulderr1, 0.0, 0.0, 1.0);
	glTranslatef(1.4, -2.75, 0.0);

	//2nd movement
	glTranslatef(-1.4, 2.75, 0.0);
	glRotatef(shoulderr2, 0.0, 1.0, 0.0);
	glTranslatef(1.4, -2.75, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(-1.4, 2, 0.0);
	glScalef(0.3, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();

	//right elbow

	//1st movement
	glTranslatef(-1.4, 1.25, 0.0);
	glRotatef(elbowr1, 1.0, 0.0, 0.0);
	glTranslatef(1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(-1.4, 0.5, 0.0);
	glScalef(0.3, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();
	//left hand

	glPushMatrix();
	//finger1
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(-1.4, -0.42, -0.1);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);


	glPopMatrix();
	//finger2
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(-1.4, -0.42, 0.0);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);


	glPopMatrix();
	//finger3
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(-1.4, -0.42, 0.1);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);


	glPopMatrix();
	//finger4
	glTranslatef(1.4, 1.25, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glTranslatef(-1.4, -1.25, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(-1.4, -0.42, 0.2);
	glScalef(0.1, 0.3, 0.2);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//end right arm

	////left leg

	//upper_left_leg
	glPushMatrix();

	//first move
	glTranslatef(-1.4, -2.75, 0.0);
	glRotatef(llegup1, 1.0, 0.0, 0.0);
	glTranslatef(1.4, 2.75, 0.0);

	//second move
	glTranslatef(-1.4, -2.75, 0.0);
	glRotatef(llegup2, 0.0, 0.0, 1.0);
	glTranslatef(1.4, 2.75, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(0.75, -4.5, 0.0);
	glScalef(0.5, 3.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//lower_left_leg
	glTranslatef(-1.4, -5.75, 0.0);
	glRotatef(llegdown, 1.0, 0.0, 0.0);
	glTranslatef(1.4, 5.75, 0.0);
	glPushMatrix();
	glTranslatef(0.75, -7.5, 0.0);
	glScalef(0.5, 3.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//left foot
	glTranslatef(-1.4, -2.75, 0.0);
	glRotatef(leftfoot, 1.0, 0.0, 0.0);
	glTranslatef(1.4, 2.75, 0.1);
	glPushMatrix();
	glTranslatef(0.75, -9.0, 0.1);
	glScalef(0.7, 0.7, 1.7);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();

	///////////////////////////////////////////////////right_leg
	//upper_right_leg
	glPushMatrix();

	//first move
	glTranslatef(-1.4, -2.75, 0.0);
	glRotatef(rlegup1, 1.0, 0.0, 0.0);
	glTranslatef(1.4, 2.75, 0.0);

	//second move
	glTranslatef(-1.4, -2.75, 0.0);
	glRotatef(rlegup2, 0.0, 0.0, 1.0);
	glTranslatef(1.4, 2.75, 0.0);

	//draw
	glPushMatrix();
	glTranslatef(-0.75, -4.5, 0.0);
	glScalef(0.5, 3.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//lower_right_leg
	glTranslatef(-1.4, -5.75, 0.0);
	glRotatef(rlegdown, 1.0, 0.0, 0.0);
	glTranslatef(1.4, 5.75, 0.0);
	glPushMatrix();
	glTranslatef(-0.75, -7.5, 0.0);
	glScalef(0.5, 3.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//right foot
	glTranslatef(-1.4, -2.75, 0.0);
	glRotatef(rightfoot, 1.0, 0.0, 0.0);
	glTranslatef(1.4, 2.75, 0.1);
	glPushMatrix();
	glTranslatef(-0.75, -9.0, 0.1);
	glScalef(0.7, 0.7, 1.7);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(11, -1.5, 14.0);
	glScalef(5, 4, 1);
	drawmodel((char *)modelname);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11, -6.6, 4.0);
	glRotatef(270.0, 0.0, 1.0, 0.0);
	glScalef(3, 3, 3);
	drawmodel((char *)modelname2);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15, -9.5,  15);
	glTexCoord2f(5.0f, 0.0f); glVertex3f( 15, -9.5,  15);
	glTexCoord2f(5.0f, 5.0f); glVertex3f( 15, -9.5, -15);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-15, -9.5, -15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		turnLeft();
		break;
	case GLUT_KEY_RIGHT:
		turnRight();
		break;
	case GLUT_KEY_UP:
		if (center[1] <= 1.5)
			moveUp();
		break;
	case GLUT_KEY_DOWN:
		if (center[1] >= -1.5)
			moveDown();
		break;
	}
	glutPostRedisplay();
}
void reset ()
{ 
	double e[] = { 0, 0, 10 };
	double c[] = {0.0, 0.0, 1};
	double u[] = {0.0, 1.0, 0.0};
	for (int i = 0; i < 3; i++)
	{
		eye[i] = e[i];
		center[i] = c[i];
		up[i] = u[i];
	}

    glutPostRedisplay();
}


void Keyboard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case '1':
       reset();
       break;
	case 'f':
		moveForward();
		break;
	case 'b':
		moveBack();
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
	
}
void floorMenu(int id)
{
  
    switch(id)
    {
        case 0:
            initRendering("images/GreenBronze.bmp",_textureId);
            break;

        case 1:
            initRendering("images/MattoniBasamento.bmp",_textureId);
            break;

        case 2:
            initRendering("images/grass.bmp",_textureId);
            break;

        case 3:
            initRendering("images/gray.bmp",_textureId);
            break;
		case 4:
            initRendering("images/Pavimentazione.bmp",_textureId);
            break;
		

        default:
            break;
    }

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitWindowSize(1500, 1500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Garden");
	initRendering("images/grass.bmp",_textureId);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1.0, 0.1, 10);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    int subMenu = glutCreateMenu(floorMenu);
    glutAddMenuEntry("GreenBronze", 0);
    glutAddMenuEntry("MattoniBasamento", 1);
    glutAddMenuEntry("grass", 2);
    glutAddMenuEntry("gray",3);
	glutAddMenuEntry("Pavimentazione",4);
    glutCreateMenu(floorMenu);
    glutAddSubMenu("Change Floor", subMenu);
    glutAddMenuEntry("Reset", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
