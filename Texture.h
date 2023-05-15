#pragma once
#include <string>

class Texture
{
private:

    unsigned int m_id;
    
public:

    Texture(const std::string& path);

    void bind() const;
    void unbind();
    
};
