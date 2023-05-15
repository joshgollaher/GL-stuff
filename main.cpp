#include <iostream>
#include <SFML/Window.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glad.h"
#include "Shader.h"
#include "OBJ_Loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Camera.h"
#include "Model.h"
#include "stb_image.h"
#include "Texture.h"


int main()
{
	objl::Loader loader;
	if(!loader.LoadFile("sphere.obj"))
	{
		std::cerr << "Couldn't load model" << std::endl;
	}

	sf::ContextSettings settings;
	settings.depthBits = 8;
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	if(!window.setActive(true))
	{
		return EXIT_FAILURE;
	}
	//Load GL extensions
	gladLoadGL();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);  
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glViewport(0, 0, window.getSize().x, window.getSize().y);

	Shader shader{ "fragment.glsl", "vertex.glsl" };

	
	//position, color, tex coord
	std::vector<float> vertexData;

	for(auto& vertex : loader.LoadedVertices)
	{
		vertexData.push_back(vertex.Position.X);
		vertexData.push_back(vertex.Position.Y);
		vertexData.push_back(vertex.Position.Z);
		vertexData.push_back(1); // R
		vertexData.push_back(1); // G
		vertexData.push_back(1); // B
		vertexData.push_back(vertex.TextureCoordinate.X);
		vertexData.push_back(vertex.TextureCoordinate.Y);
		vertexData.push_back(vertex.Normal.X);
		vertexData.push_back(vertex.Normal.Y);
		vertexData.push_back(vertex.Normal.Z);
	}

	Model model(shader, vertexData, loader.LoadedIndices);
	
	Texture texture("container.jpg");
	
	Camera camera;
	camera.setPosition(glm::vec3(0, 0, -3.0f));

	sf::Clock time;
	sf::Clock fpsClock;
	float secondCounter = 0;

	int frames_since_last = 0;

	bool running = true;
	while(running)
	{
		//Print the fps every second
		++frames_since_last;
		float dt = fpsClock.restart().asSeconds();
		secondCounter += dt;
		if(secondCounter >= 1)
		{
			std::cout << "FPS: " << frames_since_last << std::endl;
			secondCounter = 0;
			frames_since_last = 0;
		}

		sf::Event event{};
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if(event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			camera.translate(Camera::Direction::Left, 3 * dt);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			camera.translate(Camera::Direction::Right, 3 * dt);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			camera.translate(Camera::Direction::Up, 3 * dt);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			camera.translate(Camera::Direction::Down, 3 * dt);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // Kind stupid but mouse move events are kinda dumb in sfml
		{
			camera.rotate(glm::vec3(0, -60 * dt, 0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			camera.rotate(glm::vec3(0, 60 * dt, 0));
		}
		
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		texture.bind();
		model.draw(camera);
		texture.unbind();

		window.display();
	}

    return EXIT_SUCCESS;
}
