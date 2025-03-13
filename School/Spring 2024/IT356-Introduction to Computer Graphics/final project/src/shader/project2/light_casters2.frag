#version 430 core
out vec4 FragColor;

struct Material {
    sampler2D texture1;
    sampler2D texture2;    
    float shininess;
}; 
uniform Material material;

struct Light {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;

void main()
{
    if(gl_FrontFacing){
        //ambient
        vec3 ambient = light.ambient * vec3(texture(material.texture1, TexCoords));
    
        //diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture1, TexCoords));  
    
        //specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.texture1, TexCoords));  
    
        //spotlight (soft edges)
        float theta = dot(lightDir, normalize(-light.direction)); 
        float epsilon = (light.cutOff - light.outerCutOff);
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	    //we'll leave ambient unaffected so we always have a little light.
        diffuse  *= intensity;
        specular *= intensity;
    
        //attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        //ambient  *= attenuation; 
        diffuse   *= attenuation;
        specular *= attenuation;   
        
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    else{
        //ambient
        vec3 ambient = light.ambient * vec3(texture(material.texture2, TexCoords));
    
        //diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture2, TexCoords));  
    
        //specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.diffuse * spec * vec3(texture(material.texture2, TexCoords));  
    
        //spotlight (soft edges)
        float theta = dot(lightDir, normalize(-light.direction)); 
        float epsilon = (light.cutOff - light.outerCutOff);
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	    //we'll leave ambient unaffected so we always have a little light.
        diffuse  *= intensity;
        specular *= intensity;
    
        //attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        //ambient  *= attenuation; 
        diffuse   *= attenuation;
        specular *= attenuation;   
        
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
} 