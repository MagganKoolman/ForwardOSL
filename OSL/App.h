#pragma once
#include "Forward.h"
#include "Camera.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "src\SOIL.h"
#include <string>
#include "Lights.h"

class App {
struct vtxData{
	float a, b, c, x, y, z, u, v;
};
struct face {
	vtxData a, b, c;
};
struct betterData {
	glm::vec3 pos, normals;
	glm::vec2 UV;
};
struct betterFace {
	betterData f1, f2, f3;
};

private:
	int sphereSize;
	GLuint sphereVa;
	GLuint cubeVa;
	Forward forwardProgram;
	GLFWwindow* w;
	Camera camera;
	glm::mat4 cubeMatrices[12*12*2];
	glm::mat4 sphereMatrices[12*12*2];
	glm::vec3 movement = { 0,0,0 };

	void controls(float dt);
public:
	App();
	~App();
	void run();
	GLuint createSphereVBO(int resolution);
	GLuint createSphereVBO(int xRes, int yRes);
	GLuint createCubeVBO();
	void createCubes();
	void createSpheres();
	void updateInputs();
	GLuint loadTexture(std::string path);

	GLuint fbo;
	GLuint screenSaveTex;
	void createFrameBuffer();
	void saveFrameToFile(int nr);
};