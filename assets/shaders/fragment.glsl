#version 460 core

out vec4 FragColor;
in vec3 color;
in vec2 uv;

uniform sampler2D grass_sampler;
uniform sampler2D land_sampler;
uniform sampler2D noise_sampler;
uniform sampler2D  kiri_sampler;


void main(){
	FragColor = texture(kiri_sampler, uv);
//	vec4 grass_color = texture(grass_sampler, uv);
//	vec4 land_color = texture(land_sampler, uv);
//	vec4 noise_color = texture(noise_sampler, uv);
//	float weight = noise_color.r;	//灰度图里面每个通道参数一样
//	vec4 final_color = grass_color * weight + land_color * (1.0 - weight);
//	FragColor = vec4(color.rgb, 1.0);
}  