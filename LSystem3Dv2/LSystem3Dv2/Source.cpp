#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <FreeImage.h>
#include <stdio.h>
#include "LSystem.h"

Vector3D rot(0, -90, 0);
Vector3D camSh(0, 0, 0); // camera shift
int mouseOldX = 0;
int mouseOldY = 0;
LSystem lsystem;
unsigned systemList = 0; // display list to draw system
int numIterations = 3;	 // current # of iterations to draw system
float zoom = 1.0f;
int winWidth, winHeight;
bool saving = false;
float lookAngleH = 0.0f;
float lookAngleV = 0.0f;

/////////////////////////////////////////////////////////////////////////////////

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void reshape(int, int);
void saveImage();
void display()
{
    reshape(winWidth, winHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRotatef(rot.x, 1, 0, 0);
    glRotatef(rot.y, 0, 1, 0);
    glRotatef(rot.z, 0, 0, 1);
    glScalef(zoom, zoom, zoom);

    if (systemList == 0) // no display list yet, build it )
    {
        systemList = glGenLists(1);

        glNewList(systemList, GL_COMPILE);
        lsystem.buildSystem(numIterations);
        lsystem.draw();
        glEndList();
    }

    Vector3D center = -lsystem.getBounds().getCenter();
    Vector3D size = lsystem.getBounds().getSize();

    glScalef(4 / size.x, 4 / size.y, 1);
    glTranslatef(center.x, center.y, center.z);

    glCallList(systemList);

    glPopMatrix();
    glutSwapBuffers();
    if (saving)
    {
        saving = false;
        saveImage();
    }
}

void reshape(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    // factor all camera ops into projection matrix
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 60.0);
    Vector3D eye;
    eye.x = (cosf(lookAngleH) + sinf(lookAngleH)) * cosf(lookAngleV);
    eye.y = (cosf(lookAngleH) - sinf(lookAngleH)) * cosf(lookAngleV);
    eye.z = sqrtf(2) * sinf(lookAngleV);
    eye *= 5.f;
    gluLookAt(eye.x, eye.y, eye.z, // eye
        0.0, 0.0, 0.0, // center
        0.0, 0.0, 1.0);	// up

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void motion(int x, int y)
{
    rot.y -= ((mouseOldY - y) * 180.0f) / 200.0f;
    rot.z -= ((mouseOldX - x) * 180.0f) / 200.0f;
    rot.x = 0;

    if (rot.z > 360)
        rot.z -= 360;

    if (rot.z < -360)
        rot.z += 360;

    if (rot.y > 360)
        rot.y -= 360;

    if (rot.y < -360)
        rot.y += 360;

    mouseOldX = x;
    mouseOldY = y;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        mouseOldX = x;
        mouseOldY = y;
    }
}

void mouseWheel(int wheel, int direction, int x, int y)
{
    wheel = 0;
    if (direction == -1 && zoom > 0.1f)
    {
        zoom -= 0.1f;

    }
    else if (direction == +1)
    {
        zoom += 0.1f;
    }

    glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        camSh.z += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        camSh.z -= 0.1f;
        break;
    case GLUT_KEY_LEFT:
        camSh.x -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        camSh.x += 0.1f;
        break;
    }

    glutPostRedisplay();
}

void processKey(unsigned char key, int x, int y)
{
    if (key == 27 || key == 'q' || key == 'Q') //	quit requested
        exit(0);

    switch (key)
    {
    case '+': // increment # of iterations
        glDeleteLists(systemList, 1);
        systemList = 0;
        numIterations++;
        break;
    case '-': // decrement # of iterations
        glDeleteLists(systemList, 1);
        systemList = 0;
        if (numIterations > 0)
            numIterations--;
        break;
    case '=':
        camSh = Vector3D(0, 0, 0);
        break;
    case 'S':
    case 's':
        saving = true;
        break;
    case '8':
        lookAngleV += M_PI / 32;
        break;
    case '2':
        lookAngleV -= M_PI / 32;
        break;
    case '4':
        lookAngleH -= M_PI / 32;
        break;
    case '6':
        lookAngleH += M_PI / 32;
        break;
    }

    glutPostRedisplay();
}

void saveImage()
{
    size_t width = winWidth;
    size_t height = winHeight;
    BYTE* pixels = new BYTE[3 * width * height];

    glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

    // Convert to FreeImage format & save to file
    FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);
    FreeImage_Save(FIF_PNG, image, "image.png", 0);

    // Free resources
    FreeImage_Unload(image);
    delete[] pixels;
}

int main(int argc, char* argv[])
{
    // initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);

    // create window
    glutCreateWindow("L-system demo");

    // register handlers
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKey);
    glutMouseFunc(mouse);
    glutMouseWheelFunc(mouseWheel);
    glutMotionFunc(motion);

    init();

    // initialize l-system

    //lsystem.setInitialString ( "++++++++++X" );
    //lsystem.setAngle ( 7.2 * M_PI / 180.0 );
    //lsystem.setDistScale     ( 0.7 );
    //lsystem.addRule  ( 'X', "F[+++++++++X]-F[---------!X]X" );

    //	lsystem.addRule ( 'F', "F[+F]F[-F]F" );

    //	lsystem.addRule ( 'F', "F[+F]F[-F][F]" );

    //lsystem.addRule ( 'F', "F[-F]F[+F][F]" );

    //lsystem.addRule ( 'F', "F[>-F<]F[+F][<F>]" );

    //	lsystem.addRule ( 'F', "FF-[-F+F+F]+[+F-F-F]" );

    //lsystem.setInitialString ( "X" );
    //lsystem.addRule          ( 'X', "F[+X]F[-X]+X" );
    //lsystem.addRule          ( 'F', "FF"           );

    //lsystem.setInitialString ( "X" );
    //lsystem.addRule ( 'X', "F[+X][-X]FX" );
    //lsystem.addRule ( 'F', "FF"          );

    //lsystem.setInitialString("X");
    //lsystem.addRule('X', "F-[[X]+X]+F[+FX]-X");
    //lsystem.addRule('F', "FF");

    //lsystem.addRule ( 'F', "F[-&<F][<++&F]||F[--&>F]" );
    //lsystem.setDistScale     ( 0.75 );

    //lsystem.addRule ( 'F', "F[&+F][F][->F][->F][&F]" );
    //lsystem.setDistScale     ( 0.75 );

    //lsystem.addRule('F', "F[-F]<[F]>[+F][F]");
    //lsystem.setDistScale(0.75);

    //lsystem.setInitialString("A");
    //lsystem.addRule('A', " [+FA][-FA][>FA][<FA]");
    //lsystem.setDistScale(0.75);

    lsystem.setInitialString("AB");
    lsystem.addRule('A', "[F[+FA][-FA]]");
    lsystem.addRule('B', " [F[>FB][<FB]]");
    lsystem.setDistScale(0.75);

    //lsystem.setInitialString ( "X" );
    //lsystem.addRule          ( 'X',  "F[++X]-F[--X]X" );
    //lsystem.setDistScale     ( 0.75 );

    // Koch island
    //lsystem.setInitialString ( "F+F+F+F" );
    //lsystem.addRule          ( 'F', "F+F-F-FF+F+F-F" );
    //lsystem.setDistScale     ( 1 );
    //lsystem.setAngle         ( M_PI / 2 );

    //lsystem.setInitialString ( "F" );
    //lsystem.addRule          ( 'F', "F[-F]F[+F][F]" );
    //lsystem.setAngle         ( M_PI / 6 );

    glutMainLoop();

    return 0;
}
