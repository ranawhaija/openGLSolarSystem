#include <stdlib.h>
#include <windows.h>
#include <gl\glaux.h>
#include <GL\glut.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
//#pragma comment(lib, "OPENGL32.LIB")
//#pragma comment(lib, "GLU32.LIB")
#pragma comment(lib, "GLAUX.LIB")

float		xrot;
float		yrot;
float		zrot;
unsigned int	texture[2];
float LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
float LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
float LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };
AUX_RGBImageRec *LoadBMP(char *Filename)
{
	FILE *File=NULL;
	if (!Filename)
		return NULL;

	File=fopen(Filename,"r");
	if (File)
	{
		fclose(File);
		return auxDIBImageLoad(Filename);
	}
	return NULL;
}

int LoadTextures(char *filename, unsigned int *texture)
{
	int Status=FALSE;
	AUX_RGBImageRec *TextureImage[1];
	memset(TextureImage,0,sizeof(void *)*1);
	if (TextureImage[0]=LoadBMP(filename))
	{
		Status=TRUE;
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	}
	if (TextureImage[0])
	{
		if (TextureImage[0]->data)	
			free(TextureImage[0]->data);
		free(TextureImage[0]);
	}
	return Status;
}


void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	gluPerspective(45.0, (float)w/(float)h, 1.0, 100.0);
	//gluLookAt(0,0,6,0,0,0,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void) 
{
	
	GLUquadricObj* pObj; //the object which will use it to drow the pictures
	// Clear the window 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Save the matrix state and do the rotations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	pObj = gluNewQuadric(); //creates new quadric for pObj
    gluQuadricTexture(pObj,GL_TRUE);
    glEnable(GL_TEXTURE_2D);
	// Store the current matrix
    glPushMatrix();
 
    // Enable/Disable features
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
 
    // Just in case we set all vertices to white.,color for screen
    glColor4f(1,1,1,1);
	GLfloat val = 300.0f;
 
	//Earth
	glPushMatrix();
	pObj = gluNewQuadric();//prepare the variable which will use it in drawing process
    gluQuadricTexture(pObj,GL_TRUE);//enable drawing for picture
    glEnable(GL_TEXTURE_2D);//automatically activate the generation of texture coordinates on the axis
    glBindTexture(GL_TEXTURE_2D, texture[0]);//select the type of texture

	glTranslatef(0.0f,0.0f,-100.0f); //position of the earth
	glRotatef(-90.0, 1.0f, 0.0f, 0.0f); //Rotates the Earth on its spot, fixing the texture display
	glRotatef(xrot*2 , 0.0f, 0.0f, 1.0f); //Rotates the Earth on its spot, simulating the planet spinning
	gluSphere(pObj, 16.0f, 30, 17); //draws the sphere for the earth
    glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(pObj); 
	// Restore the matrix state
	glPopMatrix();	// Modelview matrix
	// Step earth orbit 0.5 degrees
	xrot += 0.5f;
	//resets the rotation value
	if(xrot >= 360.0f)
		xrot = 0.0f;
	// Restore the matrix state
	glPopMatrix();	// Modelview matrix
	//glTranslatef(0.0f,0.0f,-5.0f);
	//glRotatef(xrot,1.0f,0.0f,0.0f);
	//glRotatef(yrot,0.0f,1.0f,0.0f);
	//glRotatef(zrot,0.0f,0.0f,1.0f);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glBegin(GL_QUADS);
	//	// Front Face
	//	glNormal3f( 0.0f, 0.0f, 1.0f); 
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	//	// Back Face
	//	glNormal3f( 0.0f, 0.0f,-1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	//	// Top Face
	//	glNormal3f( 0.0f, 1.0f, 0.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	//glEnd();
	////glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glBegin(GL_QUADS);
	//	// Bottom Face
	//	glNormal3f( 0.0f,-1.0f, 0.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	//	// Right face
	//	glNormal3f( 1.0f, 0.0f, 0.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	//	// Left Face
	//	glNormal3f(-1.0f, 0.0f, 0.0f);
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	//glEnd();
	xrot+=0.3f;
	/*yrot+=0.2f;
	zrot+=0.4f;*/
 	glutSwapBuffers();
}

void Key(unsigned char key, int x, int y )
{
	if(key ==  27 )	exit(0);
}


void action(void)
{
	Display();;
}

bool init(void)
{
	if (!LoadTextures("wall.bmp", &texture[0]))
		return FALSE;
	if (!LoadTextures("star.bmp", &texture[1]))
		return FALSE;
	glEnable(GL_TEXTURE_2D);
	//glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	//glDepthFunc(GL_LEQUAL);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glColor4f(1.0f,1.0f,1.0f,0.5f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	return TRUE;
}


void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition (0,0);
	glutCreateWindow("Texture");
	if(!init())
	{
		//MessageBox(NULL, "Initializing Error", "Error", 0);
		exit(1);
	}
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutIdleFunc(action);
	glutFullScreen();
	glutMainLoop();
}


