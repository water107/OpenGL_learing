#version 460 core

layout (location = 0) in vec3 aPos;	//向vao中0号属性要数据
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;
uniform float time;
uniform float speed;
out vec3 color;  //向下个阶段输出color的变量
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
