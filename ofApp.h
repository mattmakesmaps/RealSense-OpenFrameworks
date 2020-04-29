#pragma once
#include <librealsense2/rs.hpp>
#include "ofMain.h"
#include "ofxBox2d.h"
#include "depthSquare.h"

// -------------------------------------------------
class ofApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);

	void updateDepth(const rs2::depth_frame& depthFrame, DepthSquare* ptrDepthSquare);
	
	vector <shared_ptr<DepthSquare>> squares;

	rs2::pipeline rs2_pipe;

	static const int appWidth;
	static const int appHeight;
	static int squareLength;
};
