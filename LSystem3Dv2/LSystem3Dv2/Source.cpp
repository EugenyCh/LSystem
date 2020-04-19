#include	<GL/glut.h>
#include	<stdio.h>
#include	"LSystem.h"

Vector3D	eye(5, 0, 0);			// camera position
Vector3D	rot(0, -90, 0);
int			mouseOldX = 0;
int			mouseOldY = 0;
LSystem		lsystem;
unsigned	systemList = 0;			// display list to draw system
int			numIterations = 0;			// current # of iterations to draw system

/////////////////////////////////////////////////////////////////////////////////

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(rot.x, 1, 0, 0);
	glRotatef(rot.y, 0, 1, 0);
	glRotatef(rot.z, 0, 0, 1);

	if (systemList == 0)					// no display list yet, build it )
	{
		systemList = glGenLists(1);

		glNewList(systemList, GL_COMPILE);
		lsystem.buildSystem(numIterations);
		lsystem.draw();
		glEndList();
	}

	Vector3D	center = -lsystem.getBounds().getCenter();
	Vector3D	size = lsystem.getBounds().getSize();

	glScalef(4 / size.x, 4 / size.y, 1);
	glTranslatef(center.x, center.y, center.z);

	glCallList(systemList);

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	// factor all camera ops into projection matrix
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 60.0);
	gluLookAt(eye.x, eye.y, eye.z,	// eye
		0, 0, 0,				// center
		0.0, 0.0, 1.0);		// up

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

void key(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q')	//	quit requested
		exit(0);

	if (key == '+')				// increment # of iterations
	{
		glDeleteLists(systemList, 1);
		systemList = 0;
		numIterations++;
		glutPostRedisplay();
	}
	else
		if (key == '-')				// decrement # of iterations
		{
			glDeleteLists(systemList, 1);
			systemList = 0;

			if (numIterations > 0)
				numIterations--;

			glutPostRedisplay();
		}
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
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
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


	//lsystem.setInitialString ( "X" );
	//lsystem.addRule ( 'X', "F-[[X]+X]+F[+FX]-X" );
	//lsystem.addRule ( 'F', "FF"          );


	//lsystem.addRule ( 'F', "F[-&<F][<++&F]||F[--&>F]" );
	//lsystem.setDistScale     ( 0.75 );


	//lsystem.addRule ( 'F', "F[&+F][F][->F][->F][&F]" );
	//lsystem.setDistScale     ( 0.75 );

	//lsystem.addRule('F', "F[-F]<[F]>[+F][F]");
	//lsystem.setDistScale(0.75);

	
							// very nice
	/*	lsystem.setInitialString (  "A" );
		lsystem.addRule ( 'A', " [+cBFA][-cBFA][>cBFA][<cBFA]" );
		lsystem.setDistScale     ( 0.75 );*/
	
	
		lsystem.setInitialString ( "AB" );
		lsystem.addRule          ( 'A', "[F[+FCA][-FCA]]"  );
		lsystem.addRule          ( 'B', " [F[>FCB][<FCB]]" );
		lsystem.setDistScale     ( 0.75 );
	
	/*
		lsystem.setInitialString ( "X" );
		lsystem.addRule          ( 'X',  "F[++X]-F[--X]X" );
		lsystem.setDistScale     ( 0.75 );
	*/
	
										// Koch island
		/*lsystem.setInitialString ( "F+F+F+F" );
		lsystem.addRule          ( 'F', "F+F-F-FF+F+F-F" );
		lsystem.setDistScale     ( 1 );
		lsystem.setAngle         ( M_PI / 2 );*/
	
	
		//lsystem.setInitialString ( "F" );
		//lsystem.addRule          ( 'F', "F[-F]F[+F][F]" );
		//lsystem.setAngle         ( M_PI / 6 );
	
	//	lsystem.buildSystem ( numIterations );

	glutMainLoop();

	return 0;
}
