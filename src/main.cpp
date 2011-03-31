//	Test code for a project called The Hidden Kingdom
//	by Molly Schwartz
//	with many thanks for coding help from
//	Kyle McDonald, Shahar Zaks, Rune Madsen & John Schwartz
//	Using Depth Visualizer and Kinect code from the 
//  3d Sensing and & Visualization class taught by Kyle McDonald & Zach Lieberman
//	Some particle code adapted/inspired by Open Frameworks ADVANCED 3D EXAMPLE
//  Spring 2011



#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	//ofSetupOpenGL(&window, 1024, 480 * 2, OF_WINDOW);
	ofSetupOpenGL(&window, 800, 800, OF_WINDOW);
	ofRunApp(new testApp());
}
