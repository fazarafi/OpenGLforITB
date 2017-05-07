/* compile with: gcc -lGL -lglut -Wall -o texture texture.c */
 
 #include <GL/gl.h>
 #include <GL/glut.h>
 
 /* This program does not feature some physical simulation screaming
    for continuous updates, disable that waste of resources */
 #define STUFF_IS_MOVING 0
 
 #if STUFF_IS_MOVING
     #include <unistd.h>
 #endif
 
 #include <stdlib.h>
 #include <math.h>
 #include <time.h>
 
 /* using the routine above - replace this declaration with the snippet above */
 GLuint raw_texture_load(const char *filename, int width, int height);
 
 static GLuint texture;
 
 void render()
 {
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     /* fov, aspect, near, far */
     gluPerspective(60, 1, 1, 10);
     gluLookAt(0, 0, -2, /* eye */
               0, 0, 2, /* center */
               0, 1, 0); /* up */
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glEnable(GL_TEXTURE_2D);
         
         /* create a square on the XY
            note that OpenGL origin is at the lower left
            but texture origin is at upper left
            => it has to be mirrored
            (gasman knows why i have to mirror X as well) */
         glBegin(GL_QUADS);
         glNormal3f(0.0, 0.0, 1.0);
         glTexCoord2d(1, 1); glVertex3f(0.0, 0.0, 0.0);
         glTexCoord2d(1, 0); glVertex3f(0.0, 1.0, 0.0);
         glTexCoord2d(0, 0); glVertex3f(1.0, 1.0, 0.0);
         glTexCoord2d(0, 1); glVertex3f(1.0, 0.0, 0.0);
         glEnd();
         
         glDisable(GL_TEXTURE_2D);
     glPopAttrib();
     
     glFlush();
     
     glutSwapBuffers();
 }
 
 void init()
 {
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glShadeModel(GL_SMOOTH);
     
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_DEPTH_TEST);
     
     // glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[]){2.0, 2.0, 2.0, 0.0});
     // glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat[]){1.0, 1.0, 1.0, 0.0});
     
     texture = raw_texture_load("texture.raw", 200, 256);
 }
 
 #if STUFF_IS_MOVING
 void idle()
 {
     render();
     usleep((1 / 50.0) * 1000000);
 }
 #endif
 
 void resize(int w, int h)
 {
     glViewport(0, 0, (GLsizei) w, (GLsizei) h);
 }
 
 void key(unsigned char key, int x, int y)
 {
     if (key == 'q') exit(0);
 }
 
 int main(int argc, char *argv[])
 {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
     glutInitWindowSize(640, 480);
     glutCreateWindow("Texture demo - [q]uit");
     
     init();
     glutDisplayFunc(render);
     glutReshapeFunc(resize);
     #if STUFF_IS_MOVING
         glutIdleFunc(idle);
     #endif
     glutKeyboardFunc(key);
     
     glutMainLoop();
     
     return 0;
 }

// /*
//  * OGL01Shape3D.cpp: 3D Shapes
//  */
// #include <windows.h>  // for MS Windows
// #include <GL/glut.h>  // GLUT, include glu.h and gl.h
// #include <stdio.h>
// #include <iostream>
 
// using namespace std;
// /* Global variables */
// char title[] = "3D Shapes";

// GLfloat texCoords[] = {
//     0.0f, 0.0f,  // Lower-left corner  
//     1.0f, 0.0f,  // Lower-right corner
//     0.5f, 1.0f   // Top-center corner
// };

// GLuint LoadTexture( const char *filename )
// {

//    GLuint texture;

//    int width, height;

//    unsigned char * data;

//    FILE * file;

//    file = fopen( filename, "rb" );
//    cout<<filename<<endl;
//    if ( file == NULL ) return 0;
//    width = 1024;
//    height = 512;
//    cout<<"DISINI"<<endl;
//    data = (unsigned char *)malloc( width * height * 3 );
//    //int size = fseek(file,);
//    fread( data, width * height * 3, 1, file );
//    fclose( file );

//    for(int i = 0; i < width * height ; ++i)
//    {
//       int index = i*3;
//       unsigned char B,R;
//       B = data[index];
//       R = data[index+2];

//       data[index] = R;
//       data[index+2] = B;

//    }


//    glGenTextures( 1, &texture );
//    glBindTexture( GL_TEXTURE_2D, texture );
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
//    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
//    free( data );

//    return texture;
// }

// /* Initialize OpenGL Graphics */
// void initGL() {
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
//    glClearDepth(1.0f);                   // Set background depth to farthest
//    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
//    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
//    glShadeModel(GL_SMOOTH);   // Enable smooth shading
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
// }
 
// /* Handler for window-repaint event. Called back when the window first appears and
//    whenever the window needs to be re-painted. */
// void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
//    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
//    // Render a color-cube consisting of 6 quads with different colors
//    glLoadIdentity();                 // Reset the model-view matrix
//    glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
 
//    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
//       // Top face (y = 1.0f)
//       // Define vertices in counter-clockwise (CCW) order with normal pointing out
//       glColor3f(0.0f, 1.0f, 0.0f);     // Green
//       glVertex3f( 1.0f, 1.0f, -1.0f);
//       glVertex3f(-1.0f, 1.0f, -1.0f);
//       glVertex3f(-1.0f, 1.0f,  1.0f);
//       glVertex3f( 1.0f, 1.0f,  1.0f);
 
//       // Bottom face (y = -1.0f)
//       glColor3f(1.0f, 0.5f, 0.0f);     // Orange
//       glVertex3f( 1.0f, -1.0f,  1.0f);
//       glVertex3f(-1.0f, -1.0f,  1.0f);
//       glVertex3f(-1.0f, -1.0f, -1.0f);
//       glVertex3f( 1.0f, -1.0f, -1.0f);
 
//       // Front face  (z = 1.0f)
//       glColor3f(1.0f, 0.0f, 0.0f);     // Red
//       glVertex3f( 1.0f,  1.0f, 1.0f);
//       glVertex3f(-1.0f,  1.0f, 1.0f);
//       glVertex3f(-1.0f, -1.0f, 1.0f);
//       glVertex3f( 1.0f, -1.0f, 1.0f);
 
//       // Back face (z = -1.0f)
//       glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
//       glVertex3f( 1.0f, -1.0f, -1.0f);
//       glVertex3f(-1.0f, -1.0f, -1.0f);
//       glVertex3f(-1.0f,  1.0f, -1.0f);
//       glVertex3f( 1.0f,  1.0f, -1.0f);
 
//       // Left face (x = -1.0f)
//       glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//       glVertex3f(-1.0f,  1.0f,  1.0f);
//       glVertex3f(-1.0f,  1.0f, -1.0f);
//       glVertex3f(-1.0f, -1.0f, -1.0f);
//       glVertex3f(-1.0f, -1.0f,  1.0f);
 
//       // Right face (x = 1.0f)
//       glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
//       glVertex3f(1.0f,  1.0f, -1.0f);
//       glVertex3f(1.0f,  1.0f,  1.0f);
//       glVertex3f(1.0f, -1.0f,  1.0f);
//       glVertex3f(1.0f, -1.0f, -1.0f);
//    glEnd();  // End of drawing color-cube
 
//    // Render a pyramid consists of 4 triangles
//    glLoadIdentity();                  // Reset the model-view matrix
//    glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
 
//    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
//       // Front
//       glColor3f(1.0f, 0.0f, 0.0f);     // Red
//       glVertex3f( 0.0f, 1.0f, 0.0f);
//       glColor3f(0.0f, 1.0f, 0.0f);     // Green
//       glVertex3f(-1.0f, -1.0f, 1.0f);
//       glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//       glVertex3f(1.0f, -1.0f, 1.0f);
 
//       // Right
//       glColor3f(1.0f, 0.0f, 0.0f);     // Red
//       glVertex3f(0.0f, 1.0f, 0.0f);
//       glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//       glVertex3f(1.0f, -1.0f, 1.0f);
//       glColor3f(0.0f, 1.0f, 0.0f);     // Green
//       glVertex3f(1.0f, -1.0f, -1.0f);
 
//       // Back
//       glColor3f(1.0f, 0.0f, 0.0f);     // Red
//       glVertex3f(0.0f, 1.0f, 0.0f);
//       glColor3f(0.0f, 1.0f, 0.0f);     // Green
//       glVertex3f(1.0f, -1.0f, -1.0f);
//       glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//       glVertex3f(-1.0f, -1.0f, -1.0f);
 
//       // Left
//       glColor3f(1.0f,0.0f,0.0f);       // Red
//       glVertex3f( 0.0f, 1.0f, 0.0f);
//       glColor3f(0.0f,0.0f,1.0f);       // Blue
//       glVertex3f(-1.0f,-1.0f,-1.0f);
//       glColor3f(0.0f,1.0f,0.0f);       // Green
//       glVertex3f(-1.0f,-1.0f, 1.0f);
//    glEnd();   // Done drawing the pyramid
   
//    GLuint ImageTex = LoadTexture("vtr.bmp");
//    glBindTexture (GL_TEXTURE_2D, ImageTex);
//    cout<<ImageTex<<endl;
//    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
// }
 
// /* Handler for window re-size event. Called back when the window first appears and
//    whenever the window is re-sized with its new width and height */
// void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
//    // Compute aspect ratio of the new window
//    GLuint tex;
//    glGenTextures(1, &tex);
//    if (height == 0) height = 1;                // To prevent divide by 0
//    GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
//    // Set the viewport to cover the new window
//    glViewport(0, 0, width, height);
 
//    // Set the aspect ratio of the clipping volume to match the viewport
//    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
//    glLoadIdentity();             // Reset
//    // Enable perspective projection with fovy, aspect, zNear and zFar
//    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
// }
 
// /* Main function: GLUT runs as a console application starting at main() */
// int main(int argc, char** argv) {
   
//    glutInit(&argc, argv);            // Initialize GLUT
//    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
//    glutInitWindowSize(640, 480);   // Set the window's initial width & height
//    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
//    glutCreateWindow(title);          // Create window with the given title
//    glutDisplayFunc(display);       // Register callback handler for window re-paint event
//    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
//    initGL();                       // Our own OpenGL initialization
//    glutMainLoop();                 // Enter the infinite event-processing loop
//    return 0;
// }
