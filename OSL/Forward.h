#pragma once
#include <GL\glew.h>
#include <GL\GL.h>
#include <glm\glm.hpp>
#include "Lights.h"

class Forward {
public:
	int nrOfSpheres;
	int nrOfCubes;
	Lights lights;
	const int nrOfLights = 10;
	int sphereSize;
	Forward();
	~Forward();
	void init();
	void render(glm::mat4 view, glm::mat4 viewProj, glm::vec3 position, float dt);
	glm::mat4* cubes;
	glm::mat4* spheres;
	GLuint cubeVao;
	GLuint sphereVao;
	GLuint cubeTex;
	GLuint sphereTex;
	GLuint programID;
};