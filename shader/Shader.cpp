#include "Shader.h"

#include <fstream>
#include <sstream>


Program::Program(const std::string &filename): m_filename(filename) {

}

bool Program::Compile() {
    if (!this->LoadShaderFromFile())
        return false;

    auto vertex_shader = Program::createShader(GL_VERTEX_SHADER, this->m_vertex_shader);
    auto fragment_shader = Program::createShader(GL_FRAGMENT_SHADER, this->m_fragment_shader);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return false;
    }

    this->m_id = glCreateProgram();
    glAttachShader(this->m_id, vertex_shader);
    glAttachShader(this->m_id, fragment_shader);
    glLinkProgram(this->m_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return true;
}

void Program::Bind() {
    glUseProgram(this->m_id);
}

void Program::Unbind() {
    glUseProgram(this->m_id);
}

bool Program::LoadShaderFromFile() {
    std::ifstream f;
    f.open(this->m_filename);

    if (!f) {
        std::cerr << "Error during opening file: " << this->m_filename << std::endl;
        return false;
    }

    int mode = 0;
    for (std::string line; std::getline(f, line); ) {
        if (line.find("#shader") == 0){
            std::stringstream ss(line);
            std::string tmp, p;
            ss >> tmp >> p;
            if (p == "vertex") {
                mode = 1;
                continue;
            }
            else if (p == "fragment") {
                mode = 2;
                continue;
            }
        }
        if (mode == 1) {
            this->m_vertex_shader.append(line + "\n");
        }
        else if (mode == 2) {
            this->m_fragment_shader.append(line + "\n");
        }
    }

    f.close();

    return true;
}

int Program::createShader(unsigned int type, const std::string &body) {

    auto shader = glCreateShader(type);
    auto p = body.c_str();
    glShaderSource(shader, 1, &p, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        char buff[2048];
        int buffLen;
        glGetShaderInfoLog(shader, 2048, &buffLen, buff);
        std::cerr << "Errors during compilation: \n" << buff << std::endl;
        return 0;
    }
    return shader;
}

