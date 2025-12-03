#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Color;
uniform sampler2D diffuseTexture;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform vec3 lightDir;

uniform mat4 lightSpaceMatrix;
uniform sampler2D depthMap;

float ShadowCalculation(vec4 fragPosLightSpace);

void main() {
	vec3 lightColor = vec3(1.0, 0.95, 0.9); 
	vec3 norm = normalize(Normal);

	//Ambient
	vec3 ambient = 0.3f * lightColor;

	//Diffuse
	float diff = max(dot(norm, -lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 reflectedDir = reflect(-lightDir, norm);
	vec3 viewDir = normalize(viewPos - FragPos);
	float spec = pow(max(dot(reflectedDir, viewDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec4 FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
	float shadow = ShadowCalculation(FragPosLightSpace);
	vec3 result = (diffuse + (1.0 - shadow )* (ambient + specular)) * Color * texture(diffuseTexture, TexCoords).xyz;
	FragColor = vec4(result, 1.0);
}

float ShadowCalculation(vec4 fragPosLightSpace) {
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5; 
	float closestDepth = texture(depthMap, projCoords.xy).r;   
	float currentDepth = projCoords.z;
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
    return shadow;
}


