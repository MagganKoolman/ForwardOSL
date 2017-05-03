#version 430
 
in vec3 normalOut;
in vec3 posOut;
in vec2 UVout;

out vec4 fragment_color;

layout(location = 2) uniform vec3 cameraPos;

layout(location = 0)uniform sampler2D someTex;

struct Light{
	vec4 position;
	vec4 colora;
};

const int nrOfLights = 10;

layout(std140) uniform Lights
{
  Light lights[nrOfLights];
};

layout(location = 5) uniform int indices[nrOfLights];
layout(location = 4) uniform int activeLights;

void main()
{
	vec4 color = texture(someTex, UVout);
	fragment_color = color;
	vec3 diffuseVec;
	float diffuse = 0;
	vec3 eyeDir;
	vec3 vHalfVector;
	float specular = 0;
	int index = 0;
	for (int i = 0; i < activeLights; i++)
	{
		index = indices[i];
		if (length(lights[index].position.xyz - posOut) < lights[index].position.w)
		{
			diffuseVec = normalize(lights[index].position.xyz - posOut);
			diffuse += dot(diffuseVec, normalOut);

			eyeDir = normalize(lights[index].position.xyz  - cameraPos);
			vHalfVector = reflect(diffuseVec, normalOut);
			specular += pow(max(dot(eyeDir, vHalfVector),0.0), 20);
		}
	}
	diffuse = max(diffuse, 0.0);
	specular = max(specular, 0.0);
	fragment_color = (0.2+diffuse+specular)*color;  
}