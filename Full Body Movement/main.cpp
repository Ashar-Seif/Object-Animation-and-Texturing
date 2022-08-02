#include <GL/glut.h>
#include <stdlib.h>


static int elbow[] = {0, 0};
static int arm[] = {0, 0};
static int armZ[] = {0, 0};
static int legX[] = {0, 0};
static int legZ[] = {0, 0};
static int knee[] = {0, 0};
static int fingers[] = {0, 0};
static int flang[] = {0, 0};




int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);



    // START OF RIGHT LEG
    glPushMatrix();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef((GLfloat)legZ[0], 0.0, 0.0, 1.0);
    glTranslatef(-0.5, 0.0, 0.0);

    glRotatef((GLfloat)legX[0], 1.0, 0.0, 0.0);
    glTranslatef(0.5, -0.5, 0.0);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef (0.5, 1.0, 0.5);
    glutSolidCube (1.0);
    glPopMatrix();


    glTranslatef(0.0, -0.5, 0.0);
    glRotatef(GLfloat (knee[0]), 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glScalef (0.5, 1.0, 0.5);
    glutSolidCube (1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.625, 0.0);
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef (0.75, 0.25, 0.75);
    glutSolidCube (1.0);
    glPopMatrix();

    glPopMatrix();
    // END OF RIGHT LEG


    // START OF LEFT LEG
    glPushMatrix();

    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef((GLfloat)legZ[1], 0.0, 0.0, 1.0);
    glTranslatef(+0.5, 0.0, 0.0);

    glRotatef((GLfloat)legX[1], 1.0, 0.0, 0.0);
    glTranslatef(-0.5, -0.5, 0.0);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef (0.5, 1.0, 0.5);
    glutSolidCube (1.0);
    glPopMatrix();


    glTranslatef(0.0, -0.5, 0.0);
    glRotatef(GLfloat (knee[1]), 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();
    glColor3f(0.71, 0.4, 0.12);
    glScalef (0.5, 1.0, 0.5);
    glutSolidCube (1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.625, 0.0);
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef (0.75, 0.25, 0.75);
    glutSolidCube (1.0);
    glPopMatrix();

    glPopMatrix();
    // END OF LEFT LEG


    // START OF TRUNK
    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0);
    glScalef(1.5, 0.5, 0.5);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
    // END OF TRUNK

    // START OF STOMACH
    glPushMatrix();
    glTranslatef(0.0, 1.25, 0.0);
    glScalef(1.5, 1.5, 0.5);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    // END OF STOMACH

    // START OF HEAD
    glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glColor3f(0.71, 0.4, 0.12);
    glutSolidSphere(0.35, 16, 16);
    glPopMatrix();
    // END OF HEAD


    // START OF RIGHT ARM

    glPushMatrix();



    glTranslatef(1.25, 1.85, 0.3);


    glRotatef((GLfloat)armZ[0], 1.0, 0.0, 0.0);


    glTranslatef(-0.375, 0, 0);
    glRotatef(arm[0], 0.0, 0.0, 1.0);
    glTranslatef(0.375, 0, 0);

    // Draw the limb
    // The shoulder is centered in origin and has 1, 1, 1 dimensions
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef (0.75, 0.3, 0.3);
    glutSolidCube (1.0);
    glPopMatrix();




    glTranslatef(0.75, 0, 0);

    glTranslatef(-0.375, 0, 0.0);
    glRotatef((GLfloat)elbow[0], 0.0, 0.0, 1.0);
    glTranslatef(0.375, 0, 0.0);
    glPushMatrix();
    glColor3f(0.71, 0.4, 0.12);
    glScalef (0.75, 0.3, 0.3);
    glutSolidCube (1.0);
    glPopMatrix();



    // START OF FINGER 1
    glPushMatrix();

    glTranslatef(0.475, 0.05, 0.1125);
    glColor3f(1, 0, 0);

    glTranslatef(-0.1 , 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 1


    // START OF FINGER 2
    glPushMatrix();

    glTranslatef(0.475, 0.05, 0.0375);
    glColor3f(1, 0, 0);

    glTranslatef(-0.1 , 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 2

    // START OF FINGER 3
    glPushMatrix();

    glTranslatef(0.475, 0.05, -0.0375);
    glColor3f(1, 0, 0);

    glTranslatef(-0.1 , 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 3


    // START OF FINGER 4
    glPushMatrix();

    glTranslatef(0.475, 0.05, -0.1125);
    glColor3f(1, 0, 0);

    glTranslatef(-0.1 , 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 4


    // START OF FINGER 5
    glPushMatrix();

    glTranslatef(0.475, -0.1, 0);
    glColor3f(1, 0, 0);

    glTranslatef(-0.1 , 0, 0);
    glRotatef(- flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glRotatef(-fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 5


    glPopMatrix();


    // END OF RIGHT ARM


    // START OF LEFT ARM

    glPushMatrix();



    glTranslatef(-1.25, 1.85, 0.3);
    glRotatef((GLfloat)armZ[1], 1.0, 0.0, 0.0);
    glTranslatef(0.375, 0, 0);
    glRotatef(arm[1], 0.0, 0.0, 1.0);
    glTranslatef(-0.375, 0, 0);

    // Draw the limb
    // The shoulder is centered in origin and has 1, 1, 1 dimensions
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef (0.75, 0.3, 0.3);
    glutSolidCube (1.0);
    glPopMatrix();



    glTranslatef(-0.75, 0, 0);

    glTranslatef(0.375, 0, 0.0);
    glRotatef((GLfloat)elbow[1], 0.0, 0.0, 1.0);
    glTranslatef(-0.375, 0, 0.0);
    glPushMatrix();
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glScalef (0.75, 0.3, 0.3);
    glutSolidCube (1.0);
    glPopMatrix();

// START OF FINGER 1
    glPushMatrix();

    glTranslatef(-0.475, 0.05, 0.1125);
    glColor3f(1, 0, 0);

    glTranslatef(0.1 , 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 1


    // START OF FINGER 2
    glPushMatrix();

    glTranslatef(-0.475, 0.05, 0.0375);
    glColor3f(1, 0, 0);

    glTranslatef(0.1 , 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 2

    // START OF FINGER 3
    glPushMatrix();

    glTranslatef(-0.475, 0.05, -0.0375);
    glColor3f(1, 0, 0);

    glTranslatef(0.1 , 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 3


    // START OF FINGER 4
    glPushMatrix();

    glTranslatef(-0.475, 0.05, -0.1125);
    glColor3f(1, 0, 0);

    glTranslatef(0.1 , 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 4


    // START OF FINGER 5
    glPushMatrix();

    glTranslatef(-0.475, -0.1, 0);
    glColor3f(1, 0, 0);

    glTranslatef(0.1 , 0, 0);
    glRotatef(- flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(-fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 5




    glPopMatrix();




    // END OF LEFT ARM





    glPopMatrix();
    glutSwapBuffers();






//    glTranslatef(1.5, 0.25, 0.0);
//    glPushMatrix();
//    glColor3f(1.0, 0.0, 0.0);
//    glScalef (1, 0.5, 1);
//    glutWireCube (1.0);
//    glPopMatrix();
//    glTranslatef(0.0, 1.25, 0.0);
//    glPushMatrix();
//    glColor3f(0.0, 1.0, 0.0);
//    glScalef (0.5, 2.0, 0.5);
//    glutWireCube (1.0);
//    glPopMatrix();
//    glTranslatef(0.0, 2, 0.0);
//    glPushMatrix();
//    glColor3f(0.0, 0.0, 1.0);
//    glScalef (0.5, 2.0, 0.5);
//    glutWireCube (1.0);
//    glPopMatrix();



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

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        // LEGS MOVEMENT
        case 'x':
            if (legX[1] >= -70) {
                legX[1] = (legX[1] - 5) % 360;
                glutPostRedisplay();


            }
            break;

        case 'X':
            if (legX[1] <= 70) {
                legX[1] = (legX[1] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'z':
            if (legZ[1] >= -70) {
                legZ[1] = (legZ[1] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'Z':
            if (legZ[1] <= 70) {
                legZ[1] = (legZ[1] + 5) % 360;
                glutPostRedisplay();
            }

            break;


        case 'n':
            if (legX[0] >= -50) {
                legX[0] = (legX[0] - 5) % 360;
                glutPostRedisplay();


            }
            break;

        case 'N':
            if (legX[0] <= 50) {
                legX[0] = (legX[0] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'm':
            if (legZ[0] >= -30) {
                legZ[0] = (legZ[0] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'M':
            if (legZ[0] <= 30) {
                legZ[0] = (legZ[0] + 5) % 360;
                glutPostRedisplay();
            }

            break;

            // KNEES MOVEMENT
        case 'k':
            if (knee[0] >= -30) {
                knee[0] = (knee[0] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'K':
            if (knee[0] <= 30) {
                knee[0] = (knee[0] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 's':
            if (knee[1] >= -30) {
                knee[1] = (knee[1] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'S':
            if (knee[1] <= 30) {
                knee[1] = (knee[1] + 5) % 360;
                glutPostRedisplay();
            }
            break;

            // ARMS MOVEMENT
        case 'c':
            if (arm[1] < 90) {
                arm[1] = (arm[1] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'C':
            if (arm[1] > -90) {
                arm[1] = (arm[1] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'j':
            if (arm[0] < 90) {
                arm[0] = (arm[0] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'J':
            if (arm[0] > -90) {
                arm[0] = (arm[0] - 5) % 360;
                glutPostRedisplay();
            }
            break;


            // ELBOWS MOVEMENT
        case 'v':
            if (elbow[1] < 130) {
                elbow[1] = (elbow[1] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'V':
            if (elbow[1] > -120) {
                elbow[1] = (elbow[1] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'b':
            if (elbow[0] < 130) {
                elbow[0] = (elbow[0] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'B':
            if (elbow[0] > -120) {
                elbow[0] = (elbow[0] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'U':
            if (armZ[0] < 90) {
                armZ[0] = (armZ[0] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'u':
            if (armZ[0] > -90) {
                armZ[0] = (armZ[0] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'D':
            if (armZ[1] < 90) {
                armZ[1] = (armZ[1] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'd':
            if (armZ[1] > -90) {
                armZ[1] = (armZ[1] - 5) % 360;
                glutPostRedisplay();
            }
            break;


        case 'q':
            if (flang[1] < 20) {
                flang[1] = (flang[1] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'Q':
            if (flang[1] > -20) {
                flang[1] = (flang[1] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'w':
            if (fingers[1] < 20) {
                fingers[1] = (fingers[1] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'W':
            if (fingers[1] > -20) {
                fingers[1] = (fingers[1] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'i':
            if (flang[0] < 20) {
                flang[0] = (flang[0] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'I':
            if (flang[0] > -20) {
                flang[0] = (flang[0] - 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'o':
            if (fingers[0] < 20) {
                fingers[0] = (fingers[0] + 5) % 360;
                glutPostRedisplay();
            }
            break;

        case 'O':
            if (fingers[0] > -20) {
                fingers[0] = (fingers[0] - 5) % 360;
                glutPostRedisplay();
            }
            break;






        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}


static void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}