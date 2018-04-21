#include <iostream>
#include <string>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Leap.h"

#define PI 3.1415926

using namespace Leap;
using namespace std;

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;

// the key states. These variables will be zero
// when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int   xOrigin = -1;

// Converting ratio from mm to unit in OpenGL
float real2gl = 0.025;

Controller controller;
const Frame frame;

// Pointer for drawing quadratoc objects
GLUquadricObj *quadratic; 

// GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };  // Ambient Light Values ( NEW )
// GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };  // Diffuse Light Values ( NEW )
// GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f }; // Light Position ( NEW )

void changeSize(int w, int h) 
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) 
{
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void renderScene(void) 
{
    if (deltaMove)
        computePos(deltaMove);

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    // gluLookAt(  x, 1.0f, z,
    //         x+lx, 1.0f,  z+lz,
    //         0.0f, 1.0f,  0.0f);
    gluLookAt( 0,  8.0f,  9.0f,
            0.0f,  2.0f,  0.0f,
            0.0f,  1.0f,  0.0f);

    // Draw ground
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw points on the ground
    for(int i = -10; i < 10; i++)
	{
        for(int j=-10; j < 10; j++) 
		{
            glPushMatrix();
            glTranslatef(i*1.0, 0, j*1.0);
            glColor3f(1.0f, 1.0f, 1.0f);
            // The center is black
            if(i==0 && j==0){
                glColor3f(0.0f, 0.0f, 0.0f);
            }
            glutSolidSphere(0.05f,20,20);
            glPopMatrix();
        }
    }

    const Frame frame = controller.frame();
    HandList hands = frame.hands();
    for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) 
	{

        // Draw palm
		const Hand hand = *hl;
		float palmX = hand.palmPosition().x;
		float palmY = hand.palmPosition().y;
		float palmZ = hand.palmPosition().z;
		glColor3f(0.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(palmX*real2gl, palmY*real2gl, palmZ*real2gl);
		glutSolidSphere(0.3f,100,100);
		glPopMatrix();

		// Draw wrist
		Arm arm = hand.arm();
		float wristX = arm.wristPosition().x;
		float wristY = arm.wristPosition().y;
		float wristZ = arm.wristPosition().z;
		glColor3f(1.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(wristX*real2gl, wristY*real2gl, wristZ*real2gl);
		glutSolidSphere(0.2f,100,100);
		glPopMatrix();


        // Draw fingers
        const FingerList fingers = hand.fingers();
        for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl)
		{
            const Finger finger = *fl;
            // float tipX = finger.tipPosition().x;
            // float tipY = finger.tipPosition().y;
            // float tipZ = finger.tipPosition().z;
            // glColor3f(0.0f, 0.0f, 1.0f);
            // glPushMatrix();
            // glTranslatef(tipX*real2gl, tipY*real2gl, tipZ*real2gl);
            // glutSolidSphere(0.1f,100,100);
            // glPopMatrix();

            // Draw joints & bones
            for (int b = 0; b < 4; ++b) 
			{
                Bone::Type boneType = static_cast<Bone::Type>(b);
                Bone bone = finger.bone(boneType);
                float boneStartX = bone.prevJoint().x;
                float boneStartY = bone.prevJoint().y;
                float boneStartZ = bone.prevJoint().z;
                float boneEndX   = bone.nextJoint().x;
                float boneEndY   = bone.nextJoint().y;
                float boneEndZ   = bone.nextJoint().z;
                
                // Draw joints
                glColor3f(0.0f, 1.0f, 0.0f);
                glPushMatrix();
                glTranslatef(boneStartX*real2gl, boneStartY*real2gl, boneStartZ*real2gl);
                glutSolidSphere(0.08f,100,100);
                glPopMatrix();

                // Draw joints
                glColor3f(0.2f, 0.0f, 0.3f);
                glPushMatrix();
                glTranslatef(boneEndX*real2gl, boneEndY*real2gl, boneEndZ*real2gl);
                glutSolidSphere(0.08f,100,100);
                glPopMatrix();

                // Draw bones
                float boneVectorX = boneEndX - boneStartX;
                float boneVectorY = boneEndY - boneStartY;
                float boneVectorZ = boneEndZ - boneStartZ;
                float phi = atan2(boneVectorX, boneVectorZ) * 180 / PI;
                float theta = (-1) * atan2(boneVectorY, hypot(boneVectorX, boneVectorZ)) * 180 / PI;
                glColor3f(0.6f, 0.6f, 0.0f);
                glPushMatrix();
                glTranslatef(boneStartX*real2gl, boneStartY*real2gl, boneStartZ*real2gl);
                glRotatef(phi, 0.0f, 1.0f, 0.0f);
                glRotatef(theta, 1.0f, 0.0f, 0.0f);
                quadratic = gluNewQuadric();
                gluCylinder(quadratic,0.05f,0.05f,bone.length()*real2gl,32,32);
                glPopMatrix();

                gluDeleteQuadric(quadratic);
            }
        }
    }
    glutSwapBuffers();
} 

void processNormalKeys(unsigned char key, int xx, int yy) 
{

        if (key == 27)
              exit(0);
} 

void pressKey(int key, int xx, int yy) 
{

       switch (key) 
	   {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
       }
} 

void releaseKey(int key, int x, int y) 
{    

        switch (key) 
		{
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
} 

void mouseMove(int x, int y) 
{  

	// this will only be true when the left button is down
	if (xOrigin >= 0) 
	{
		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) 
{
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) 
	{
        // when the button is released
        if (state == GLUT_UP) 
		{
            angle += deltaAngle;
            xOrigin = -1;
        }
        else  
		{// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

int main(int argc, char **argv)
{
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Leap Motion Demo");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    // glShadeModel(GL_SMOOTH);
    // glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); // Setup The Ambient Light
    // glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); // Setup The Diffuse Light
    // glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);// Position The Light
    // glEnable(GL_LIGHT1); // Enable Light One

    // enter GLUT event processing cycle
    glutMainLoop();   

    return 1;
}
