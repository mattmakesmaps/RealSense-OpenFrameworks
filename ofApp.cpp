#include "ofApp.h"

const int ofApp::appWidth = 848 * 2;
const int ofApp::appHeight = 480 * 2;
int ofApp::squareLength = 60;
//--------------------------------------------------------------
void ofApp::setup() {
	rs2_pipe.start();

	
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);

}

//--------------------------------------------------------------
void ofApp::update() {
	// Block program until frames arrive
	rs2::frameset frames = rs2_pipe.wait_for_frames();
	// Try to get a frame of a depth image
	rs2::depth_frame depth = frames.get_depth_frame();

	squares.clear();

	for (int x = 0; x <= (appWidth - squareLength); x += squareLength) {
		for (int y = 0; y <= (appHeight - squareLength); y += squareLength) {
			auto ds = std::make_shared<DepthSquare>(x, y, squareLength);
			squares.push_back(ds);
		}
	}

	for (auto square: squares) {
		ofApp::updateDepth(depth, square.get());
	}
}


//--------------------------------------------------------------
void ofApp::draw() {
	
	for (auto& square: squares) {
		square->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 't') ofToggleFullscreen();
	if(key == 'p') squareLength += 10;
	if (key == 'o') {
		if(squareLength > 10)
			squareLength -= 10;
	};
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::resized(int w, int h){
}

void ofApp::updateDepth(const rs2::depth_frame& depthFrame, DepthSquare* ptrDepthSquare)
{
	std::vector<float> distances;

	// Get the depth frame's dimensions
	const auto depthFrame_width = depthFrame.get_width();
	const auto depthFrame_height = depthFrame.get_height();

	// Translate the square's origin coordinate into depth coordinates
	const auto squareXOriginMapped = ofMap(ptrDepthSquare->getX(), 0, appWidth, 0, depthFrame_width, true);
	const auto squareYOriginMapped = ofMap(ptrDepthSquare->getY(), 0, appHeight, 0, depthFrame_height, true);
	const auto mappedLength = ptrDepthSquare->getLength() / 2;

	for (auto i = 0; i < mappedLength; i++)
	{
		for (auto j = 0; j < mappedLength; j++)
		{
			// is this right?
			//auto sample_cell_x = squareXOriginMapped + j;
			//auto sample_cell_y = squareYOriginMapped + i;
			// or is this right?
			auto sample_cell_x = squareXOriginMapped + i;
			auto sample_cell_y = squareYOriginMapped + j;
			float dist_at_cell = depthFrame.get_distance(sample_cell_x, sample_cell_y);
			distances.push_back(dist_at_cell);
		}
	}

	// filter out zeros using `Erase-remove idiom`
	distances.erase(std::remove_if(distances.begin(), distances.end(), [](float distance) {return distance < 0.1; }), distances.end());
	float sum = 0;
	for (auto& distance_sample : distances) {
		sum += distance_sample;
	}
	auto average_distance = sum / distances.size();
	if (std::isnan(average_distance))
		average_distance = 0.05;
	if (std::isinf(average_distance))
		average_distance = 4.0;

	ptrDepthSquare->setDepth(average_distance);
}

