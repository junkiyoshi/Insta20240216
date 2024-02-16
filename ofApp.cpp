#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(ofGetFrameNum() * 0.72);

	float R = 230;
	float r = 10;
	float u_span = 3;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	int v_span = 1;
	for (int v_start = 0; v_start < 360; v_start += v_span) {

		int v_end = v_start + v_span;
		int span = 1;

		r = ofMap(ofNoise(cos(v_start * DEG_TO_RAD) * 3, sin(v_start * DEG_TO_RAD) * 3, ofGetFrameNum() * 0.005), 0, 1, R * -0.5, R * 0.5);

		for (int v = v_start; v <= v_end; v += span) {

			for (int u = 0; u < 180; u += u_span) {

				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v - span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v - span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v + span * 0.5));
				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v + span * 0.5));

				line.addVertex(this->make_point(R, r, u - u_span * 0.51, v - span * 0.51));
				line.addVertex(this->make_point(R, r, u + u_span * 0.51, v - span * 0.51));
				line.addVertex(this->make_point(R, r, u + u_span * 0.51, v + span * 0.51));
				line.addVertex(this->make_point(R, r, u - u_span * 0.51, v + span * 0.51));

				for (int i = 0; i < 4; i++) {

					line.addColor(ofColor(239));
					r > 0 ? face.addColor(ofColor(239, 39, 39)) : face.addColor(ofColor(39, 39, 239));
				}

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				if (v == v_start) {

					line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);
				}

				if (v == v_end) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				}

				if (u == 0) {

					line.addIndex(line.getNumVertices() - 4); line.addIndex(line.getNumVertices() - 1);
				}

				if (u == 180 - u_span) {

					line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
				}
			}
		}
	}

	face.draw();
	line.drawWireframe();

	this->cam.end();

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ���w�f�b�T������ �`���Ċy���ސ��w�����@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}