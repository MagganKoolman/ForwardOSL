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

//layout(location = 5) uniform int indices[nrOfLights];
//layout(location = 4) uniform int activeLights;

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
	vec3 lightpos;
	for (int i = 0; i < nrOfLights; i++)
	{
		index = i;
		lightpos = lights[index].position.xyz;
		if(length(lightpos - posOut) < lights[index].position.w){  
			vec3 diffuseVec = normalize(lightpos - posOut);
			diffuse += dot(diffuseVec, normalOut);

			vec3 eyeDir = normalize(lightpos - cameraPos);
			vec3 vHalfVector = reflect(diffuseVec, normalOut);
			specular += pow(max(dot(eyeDir, vHalfVector),0.0), 20);
		}
	}
	diffuse = max(diffuse, 0.0);
	specular = max(specular, 0.0);
	fragment_color = (0.2+diffuse+specular)*color;  
}