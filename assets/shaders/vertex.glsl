#version 460 core

layout (location = 0) in vec3 aPos;	//��vao��0������Ҫ����
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;
uniform float time;
uniform float speed;
out vec3 color;  //���¸��׶����color�ı���
out vec2 uv;

void main(){
	float scale = 1.0 / time;
	vec3 sPos = aPos * scale;
	gl_Position = vec4(sPos, 1.0);
	//color = aColor * (sin(time) + 1.0) / 2.0;
	color = aColor;
	uv  = aUV;
	//uv = vec2(aUV.x + time * speed, aUV.y);
	// time = time + 1.0;
}
