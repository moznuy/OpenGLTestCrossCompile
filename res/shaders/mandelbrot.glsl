#shader vertex
#version 330 core

layout(location = 0) in vec4 a_pos;
//uniform mat4 MVP;
//out vec4 v_pos;

void main() {
    gl_Position = a_pos;
}



#shader fragment
#version 330 core

//in vec4 v_pos;
uniform float scale;
out vec4 fragColor;


vec2 cmpxmul(in vec2 a, in vec2 b) {
    return vec2(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
}

vec2 cmpxadd(in vec2 a, in vec2 b) {
    return vec2(a.x + b.x, a.y + b.y);
}

//vec2 cmpxpow(in vec2 c, int p) {
//    vec2 tmp = vec2(1.0,0.0) ;
//    for (int i = 0; i < p; ++i) {
//        c = cmpxmul(tmp, c);
//    }
//    return c;
//}

void main() {
//    float scale = 0.001; uniform
//    vec2 pos = vec2(-2, -0.5) / scale;
//    vec2 c = (gl_FragCoord.xy + pos) * scale;
    vec2 c = (gl_FragCoord.xy + vec2(-800, -600))*scale + vec2(-1, 0);
    vec2 z = vec2(0, 0);
    int t = 200;

    float escape = -1;
    for (int i = 0; i < t; ++i) {
        z = cmpxadd(cmpxmul(z, z), c);
        if (dot(z, z) > 4) {
            escape = i;
            break;
        }
    }
    vec4 color = vec4(0.,0.,0.,1.);
    vec3 abc = vec3(1, 1/sqrt(2), 1/(7*pow(3, 1/8)));
    if (escape >= 0) {
        escape = log(escape) / log(2.f);

        //sqrt(escape/ t);
//        color = vec4(
//        (1+cos(2*3.14159*escape*abc.x))/2,
//        (1+cos(2*3.14159*escape*abc.y))/2,
//        (1+cos(2*3.14159*escape*abc.z))/2,
//        1) ;
        color = vec4(((1+cos(2*3.14159*escape*abc))/2).xyz, 1) ;
    }

    //escape ? vec4(0, 0, 0, 1) : vec4(color, color, color, 1); // vec4(v_pos.xyz, 1); //vec4(0.2, 0.5, 0.7, 1.0);
    fragColor = color;
}