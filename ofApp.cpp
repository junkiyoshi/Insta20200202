#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(24);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto R = 200;
	auto v_span = 5;
	auto u_span = 8;
	auto v_start = ofGetFrameNum();
	for (auto r = 10; r <= 50; r += 5) {

		v_start += ofGetFrameNum();
		for (auto v = v_start; v < v_start + 30; v += v_span) {

			for (auto u = 0; u < 360; u += u_span) {

				auto noise_seed = this->make_point(R, r, u + u_span * 0.5, v + v_span * 0.5);
				auto noise_value = ofNoise(glm::vec4(noise_seed * 0.005, ofGetFrameNum() * 0.01));

				vector<glm::vec3> vertices;
				vertices.push_back(this->make_point(R, r, u, v));
				vertices.push_back(this->make_point(R, r, u + u_span, v));
				vertices.push_back(this->make_point(R, r, u + u_span, v + v_span));
				vertices.push_back(this->make_point(R, r, u, v + v_span));

				int index = this->face_mesh.getNumVertices();
				this->face_mesh.addVertices(vertices);
				this->frame_mesh.addVertices(vertices);

				this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 2);
				this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

				this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 1);
				this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 2);
				this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 3);
				this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 0);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(300);

	ofSetColor(239);
	this->face_mesh.drawFaces();

	ofSetColor(39);
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);
	z += ofMap(ofNoise(cos(v), sin(v), ofGetFrameNum() * 0.005), 0, 1, -50, 50);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}