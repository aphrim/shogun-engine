//Credit to learnopengl.com for original shader utility class
#pragma once
#include "include.hpp"
#include "vector.hpp"

namespace SHOGUN {
class Shader
{
public:
    unsigned int ID;
  
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string &name, Vector3 value) const;
    void setVec3(const std::string &name, float v1, float v2, float v3) const;

    std::string vertexPath, fragmentPath;
};
}
