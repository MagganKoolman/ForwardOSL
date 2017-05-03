#include "Lights.h"
#include <iostream>
Lights::Lights()
{

}

Lights::~Lights()
{
	delete[] allLights;
}

void Lights::update(GLuint programID, float dt)
{
	timer += dt;
	glm::vec3 pos;
	for (int i = 0; i < nrOfLight; i++) {
		pos.x = i * 4 + cosf(i*timer);
		pos.z = i * 4 + sinf(i*timer);
		allLights[i].position = vec4(pos, allLights[i].position.w);
		lightboxes[i].position = pos;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, this->lightBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(aLight) * nrOfLight, this->allLights, GL_DYNAMIC_DRAW);

	GLint lightLoc = glGetUniformBlockIndex(programID, "Lights");
	glBindBufferBase(GL_UNIFORM_BUFFER, lightLoc, this->lightBuffer);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Lights::init(GLuint programID, int nrOfLights)
{
	this->allLights = new aLight[nrOfLights];
	this->lightboxes = new Hitbox[nrOfLights];
	GLint lightLoc = glGetUniformBlockIndex(programID, "Lights");
	GLint blockSize;
	glGetActiveUniformBlockiv(programID, lightLoc, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

	if (blockSize != sizeof(aLight) * nrOfLights)
		std::cout << "Light uniform block and CPU buffer are not same size!!!! Bad!!!\n";

	glGenBuffers(1, &this->lightBuffer);

	glm::vec3 pos;
	for (int i = 0; i < nrOfLights; i++)
	{
		pos = vec3(10 * i, 0.5, 10 * i);
		this->allLights[i].position = glm::vec4(pos, 5);
		this->allLights[i].colora = vec4(0.5, 0.5, 0.5, 1);
		this->lightboxes[i].init(pos, 5);
	}
	this->nrOfLight = nrOfLights;
	update(programID, 0.05f);
}
