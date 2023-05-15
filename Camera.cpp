#include "Camera.h"
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

Camera::Camera()
{
    position = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = glm::vec3(0.0f, 90.0f, 0.0f);
}

void Camera::translate(Direction direction, float amount)
{
    switch(direction)
    {
        case Direction::Left:
            position -= right() * amount;
            break;
        case Direction::Right:
            position += right() * amount;
            break;
        case Direction::Up:
            position += front() * amount;
            break;
        case Direction::Down:
            position -= front() * amount;
            break;
    }
}

glm::vec3 Camera::front()
{
    const float pitch = rotation[0];
    const float yaw = rotation[1];
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    return front;
}

glm::vec3 Camera::right()
{
    const glm::vec3 up(0, 1, 0);
    return glm::normalize(glm::cross(front(), up)); // TODO: parameterize up
}

glm::vec3 Camera::up()
{
    return glm::normalize(glm::cross(right(), front()));
}

const glm::mat4 Camera::viewMat()
{
    return glm::lookAt(position, position + front(), up());
}
