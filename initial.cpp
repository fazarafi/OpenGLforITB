/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
 
/* Global variables */
char title[] = "3D Shapes";
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 10.0f); // Set background color to black and opaque
   glClearDepth(10.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
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
 
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
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
