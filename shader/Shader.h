#ifndef OPENGLCUSTOMTEST_SHADER_H
#define OPENGLCUSTOMTEST_SHADER_H

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

class Program {
private:
    std::string m_filename;
    std::string m_vertex_shader;
    std::string m_fragment_shader;
    unsigned int m_id;

    bool LoadShaderFromFile();
    static int createShader(unsigned int type, const std::string &body);
public:
    explicit Program(const std::string &filename);

    bool Compile();
    void Bind();
    void Unbind();

    template <typename M>
    void setUniform4x4(const std::string &name, const M &u) {
        auto location = glGetUniformLocation(this->m_id, name.c_str());
        if (location == -1) {
            std::cerr << "Unknown var: " << name << std::endl;
            return;
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(u));

    }
};


#endif //OPENGLCUSTOMTEST_SHADER_H
