#shader vertex
#version 330 core

layout(location = 0) in vec4 a_pos;

uniform mat4 MVP;
out vec4 v_pos;

void main() {
   gl_Position = v_pos = MVP * vec4(a_pos.xy, 0, 1);
}


#shader fragment
#version 330 core
in vec4 v_pos;
void main() {
   gl_FragColor = vec4(1,1,1,1);//vec4(v_pos.xyz, 1); //vec4(0.2, 0.5, 0.7, 1.0);
}