#pragma once
#include <glm.hpp>
#include <vector>

#include "Camera.h"
#include "Shader.h"

class Model
{
private:

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Shader shader;

    std::vector<float> vertices;
    std::vector<unsigned> indices;

    glm::vec3 position;
    glm::vec3 rotation;
    
public:

    Model(const Shader& shader, std::vector<float> vertices, std::vector<unsigned> indices);
    ~Model();
    
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    
    void draw(Camera& camera);
    
};
