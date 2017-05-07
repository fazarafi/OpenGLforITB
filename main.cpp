/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
//#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include "parser.h"
#include <iostream>
/* Global variables */
char title[] = "3D Shapes";
std::vector< std::vector<Point> > listBuilding;
Parser parse;

/* Load Texture from file */
GLuint LoadTexture( const char *filename )
{

   GLuint texture;

   int width, height;

   unsigned char * data;

   FILE * file;

   file = fopen( filename, "rb" );
   cout<<filename<<endl;
   if ( file == NULL ) return 0;
   width = 1024;
   height = 512;
   cout<<"DISINI"<<endl;
   data = (unsigned char *)malloc( width * height * 3 );
   //int size = fseek(file,);
   fread( data, width * height * 3, 1, file );
   fclose( file );

   for(int i = 0; i < width * height ; ++i)
   {
      int index = i*3;
      unsigned char B,R;
      B = data[index];
      R = data[index+2];

      data[index] = R;
      data[index+2] = B;

   }


   glGenTextures( 1, &texture );
   glBindTexture( GL_TEXTURE_2D, texture );
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
   gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
   free( data );

   return texture;
}
 
/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 10.0f); // Set background color to black and opaque
   	glClearDepth(10.0f);                   // Set background depth to farthest
   	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   	glShadeModel(GL_SMOOTH);   // Enable smooth shading
   	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Drawing building without bottom from vector of point */
void drawBuilding(vector<Point> points) {
	int x1, z1, x2, z2, i = 0;
	glBegin(GL_QUADS); 
	for (i = 0; i < points.size(); i++) {
		int x1 = points[i].getX();
    	int z1 = points[i].getY();
    	if (i == points.size() - 1) {
			x2 = points[0].getX();
		 	z2 = points[0].getY();  
      	}
      	else {
      		x2 = points[i+1].getX();
      	 	z2 = points[i+1].getY();
      	}
      
  

      	if ((i + 4)/ 4 == 0) {
      		glColor3f(10.0f, 0.0f, 0.0f);     // Red
      	}
      	else if ((i + 4)/ 5 == 0) {
      		glColor3f(175.0f, 10.0f, 0.0f);     // Yellow
      	}
      	else if ((i + 4)/ 5 == 0) {
      		glColor3f(0.0f, 0.0f, 10.0f);     // Blue
      	}
      	else { // (div (i + 1, ) == 0
      		glColor3f(175.0f, 0.0f, 10.0f);     // Magenta
      	}
		glVertex3f((float)x1-175, 20.0f, (float)(z1*(-175)/360));
      	glVertex3f((float)x2-175, 20.0f, (float)(z2*(-175)/360));
      	glVertex3f((float)x2-175, 10.0f,  (float)(z2*(-175)/360));
      	glVertex3f((float)x1-175, 10.0f,  (float)(z1*(-175)/360));
   }
   glEnd();
   
   glBegin(GL_POLYGON);
   glColor3f(10.0f, 0.5f, 0.0f);     // Orange 
   for (i = 0; i < points.size(); i++) {
   	  glVertex3f((float)points[i].getX()-175, 20.0f, (float)(points[i].getY()*(-175)/360));
   }
   glEnd();
   
}
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	
   	parse.parseAdi("bangunan.txt");
   	listBuilding = parse.getPoints();
	cout << listBuilding.size() << endl;
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   
   	glFrustum(-250.0, 350.0, -50.0, 450.0, 240.0, 600.0);         
   	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	
   	// Render a color-cube consisting of 6 quads with different colors
   	glLoadIdentity();
    // Reset the model-view matrix
 
   	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      	// Top face (y = 10.0f)
      	// Define vertices in counter-clockwise (CCW) order with normal pointing out
      	glColor3f(0.0f, 10.0f, 0.0f);     // Green
      	glVertex3f(175.0f, 10.0f, -175.0f);
      	glVertex3f(-175.0f, 10.0f, -175.0f);
      	glVertex3f(-175.0f, 10.0f,  175.0f);
      	glVertex3f( 175.0f, 10.0f,  175.0f);
 	
      	// Bottom face (y = -10.0f)
      	glColor3f(10.0f, 0.5f, 0.0f);     // Orange
      	glVertex3f( 175.0f, -10.0f,  175.0f);
      	glVertex3f(-175.0f, -10.0f,  175.0f);
      	glVertex3f(-175.0f, -10.0f, -175.0f);
      	glVertex3f( 175.0f, -10.0f, -175.0f);
 
      	// Front face  (z = 10.0f)
      	glColor3f(10.0f, 0.0f, 0.0f);     // Red
      	glVertex3f( 175.0f,  10.0f, 175.0f);
      	glVertex3f(-175.0f,  10.0f, 175.0f);
      	glVertex3f(-175.0f, -10.0f, 175.0f);
      	glVertex3f( 175.0f, -10.0f, 175.0f);
 
      	// Back face (z = -10.0f)
      	glColor3f(175.0f, 10.0f, 0.0f);     // Yellow
      	glVertex3f( 175.0f, -10.0f, -175.0f);
      	glVertex3f(-175.0f, -10.0f, -175.0f);
      	glVertex3f(-175.0f,  10.0f, -175.0f);
      	glVertex3f( 175.0f,  10.0f, -175.0f);
 
      	// Left face (x = -10.0f)
      	glColor3f(0.0f, 0.0f, 10.0f);     // Blue
      	glVertex3f(-175.0f,  10.0f,  175.0f);
      	glVertex3f(-175.0f,  10.0f, -175.0f);
      	glVertex3f(-175.0f, -10.0f, -175.0f);
      	glVertex3f(-175.0f, -10.0f,  175.0f);
 
      	// Right face (x = 10.0f)
      	glColor3f(175.0f, 0.0f, 10.0f);     // Magenta
      	glVertex3f(175.0f,  10.0f, -175.0f);
      	glVertex3f(175.0f,  10.0f,  175.0f);
      	glVertex3f(175.0f, -10.0f,  175.0f);
      	glVertex3f(175.0f, -10.0f, -175.0f);
   	glEnd();  // End of drawing color-cube
   
   	// Render a color-cube consisting of 6 quads with different colors
   	glLoadIdentity();
        // Reset the model-view matrix
 	
   	for (int i = 0; i < listBuilding.size(); i++) {
    	drawBuilding(listBuilding[i]);
   	}
   /*glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 10.0f)
      //Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 10.0f, 0.0f);     // Green
      glVertex3f(-144.0f, 20.0f, -19.0f);
      glVertex3f(-118.0f, 20.0f, -19.0f);
      glVertex3f(-118.0f, 20.0f, -4.0f);
      glVertex3f(-144.0f, 20.0f, -4.0f);
 
      // Bottom face (y = -10.0f)
      glColor3f(10.0f, 0.5f, 0.0f);     // Orange
      glVertex3f(-144.0f, 10.0f, -19.0f);
      glVertex3f(-118.0f, 10.0f, -19.0f);
      glVertex3f(-118.0f, 10.0f, -4.0f);
      glVertex3f(-144.0f, 10.0f, -4.0f);
 
      //Front face  (z = 10.0f)
      glColor3f(10.0f, 0.0f, 0.0f);     // Red
	  glVertex3f(-144.0f, 20.0f, -4.0f);
      glVertex3f(-118.0f, 20.0f, -4.0f);
      glVertex3f(-118.0f, 10.0f,  -4.0f);
      glVertex3f(-144.0f, 10.0f,  -4.0f);
 
      // Back face (z = -10.0f)
      glColor3f(175.0f, 10.0f, 0.0f);     // Yellow
	  glVertex3f(-144.0f, 10.0f, -19.0f);
      glVertex3f(-118.0f, 10.0f, -19.0f);
      glVertex3f(-118.0f, 20.0f,  -19.0f);
      glVertex3f(-144.0f, 20.0f,  -19.0f);
 
      // Left face (x = -10.0f)
      glColor3f(0.0f, 0.0f, 10.0f);     // Blue
	  glVertex3f(-118.0f, 20.0f, -19.0f);
      glVertex3f(-118.0f, 20.0f, -4.0f);
      glVertex3f(-118.0f, 10.0f,  -4.0f);
      glVertex3f(-118.0f, 10.0f,  -19.0f);
 
      // Right face (x = 10.0f)
      glColor3f(175.0f, 0.0f, 10.0f);     // Magenta
	  glVertex3f(-144.0f, 20.0f, -19.0f);
      glVertex3f(-144.0f, 20.0f, -4.0f);
      glVertex3f(-144.0f, 10.0f,  -4.0f);
      glVertex3f(-144.0f, 10.0f,  -19.0f);
   glEnd();  // End of drawing color-cube
    */
   	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   	// Compute aspect ratio of the new window
   	if (height == 0) height = 1;                // To prevent divide by 0
   	GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   	// Set the viewport to cover the new window
   	glViewport(0, 0, width, height);
 
   	// Set the aspect ratio of the clipping volume to match the viewport
   	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   	glLoadIdentity();             // Reset
   	// Enable perspective projection with fovy, aspect, zNear and zFar
   	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   	glutInit(&argc, argv);            // Initialize GLUT
   	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
  	glutInitWindowSize(640, 480);   // Set the window's initial width & height
   	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   	glutCreateWindow(title);          // Create window with the given title
   	glutDisplayFunc(display);       // Register callback handler for window re-paint event
   	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   	initGL();                       // Our own OpenGL initialization
   	glutMainLoop();                 // Enter the infinite event-processing loop
   	return 0;
}
