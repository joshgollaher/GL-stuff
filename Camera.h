#pragma once
#include <fwd.hpp>
#include <vec3.hpp>

class Camera
{
private:

    glm::vec3 position;

    //Pitch, yaw, roll
    glm::vec3 rotation;
    
public:

    enum class Direction
    {
        Left,
        Right,
        Up,
        Down
    };

    Camera();

    void setPosition(const glm::vec3& position) { this->position = position; }
    void setRotation(const glm::vec3& rotation) { this->rotation = rotation; }
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    
    void translate(Direction direction, float amount);
    void rotate(const glm::vec3& amount) { this->rotation += amount; }

    glm::vec3 front();
    glm::vec3 right();
    glm::vec3 up();
    
    const glm::mat4 viewMat();
};
