#ifndef OPENGLCUSTOMTEST_SHADER_H
#define OPENGLCUSTOMTEST_SHADER_H

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

class Program {
private:
    std::string m_filename;
    std::string m_vertex_shader;
    std::string m_fragment_shader;
    unsigned int m_id;

    bool LoadShaderFromFile();
    static int createShader(unsigned int type, const std::string &body);

    mutable std::unordered_map<std::string, int> locations;
    int GetUniformLocation(const std::string &name) const;
public:
    explicit Program(const std::string &filename);

    bool Compile();
    void Bind();
    void Unbind();

    template <typename M>
    void setUniform4x4(const std::string &name, const M &u) {
        auto location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(u));
    }

    void setUniform1f(const std::string &name, float u) {
        auto location = GetUniformLocation(name);
        glUniform1f(location, u);
    }
};


#endif //OPENGLCUSTOMTEST_SHADER_H
