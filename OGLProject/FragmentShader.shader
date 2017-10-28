#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
	vec3 specular;
    float shininess;
}; 

//struct Light {
//    vec3 position;
//
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform Material material;
//uniform Light light;

struct DirLight {
	vec3 direction;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light_, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
	
	//// ambient
 //   vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
 // 	
 //   // diffuse 
 //   vec3 norm = normalize(Normal);
 //   vec3 lightDir = normalize(light.position - FragPos);
 //   float diff = max(dot(norm, lightDir), 0.0);
 //   vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
 //   
 //   // specular
 //   vec3 viewDir = normalize(viewPos - FragPos);
 //   vec3 reflectDir = reflect(-lightDir, norm);  
 //   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
 //   vec3 specular = light.specular * (spec * material.specular);
 //       
 //   vec3 result = ambient + diffuse + specular;
	////vec3 result = ambient;
 //   FragColor = vec4(result, 1.0);
	
	//FragColor = texture( material.diffuse, TexCoords );

	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(dirLight.position - FragPos);

	// phase 1: Directional lighting
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	// phase 2: Point lights
	/*for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);*/

	FragColor = vec4(result, 1.0);

}

vec3 CalcDirLight(DirLight light_, vec3 norm, vec3 lightDir)
{
	//vec3 lightDir = normalize(-light.direction);
	//// diffuse shading
	//float diff = max(dot(normal, lightDir), 0.0);
	//// specular shading
	//vec3 reflectDir = reflect(-lightDir, normal);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//// combine results
	//vec3 ambient = light.ambient  * vec3(texture(material.diffuse, TexCoords));
	//vec3 diffuse = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
	//vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	//return (ambient + diffuse + specular);


	// ambient
	vec3 ambient = light_.ambient * texture(material.diffuse, TexCoords).rgb;
	 	
	// diffuse 
	/*vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);*/
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light_.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
	   
	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light_.specular * (spec * material.specular);
	       
	return  ambient + diffuse + specular;
}

//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//	vec3 lightDir = normalize(light.position - fragPos);
//	// diffuse shading
//	float diff = max(dot(normal, lightDir), 0.0);
//	// specular shading
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	// attenuation
//	float distance = length(light.position - fragPos);
//	float attenuation = 1.0 / (light.constant + light.linear * distance +
//		light.quadratic * (distance * distance));
//	// combine results
//	vec3 ambient = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//	vec3 diffuse = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords.xy));
//	ambient *= attenuation;
//	diffuse *= attenuation;
//	specular *= attenuation;
//	return (ambient + diffuse + specular);
//}