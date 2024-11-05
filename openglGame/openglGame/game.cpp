#include "game.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define SCREEN_WIDTH  1080
#define SCREEN_HEIGHT 720

Game::Game()
{

}

Game::~Game()
{

}


bool Game::Init()
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW \n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "openGL game", NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window \n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize Glad \n");
        return false;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


    while (!glfwWindowShouldClose(window))
    {
        Update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    if (!InitActors())
    {
        return false;
    }


	return true;
}


bool Game::InitActors()
{
    Box* box = new Box();

    Instance instanceA =
    {
        glm::vec3(1),
        glm::vec3(1),
        glm::vec3(1),
        glm::mat4(1),
    };

    Instance instanceB =
    {
        glm::vec3(1,5,1),
        glm::vec3(1),
        glm::vec3(1),
        glm::mat4(1),
    };

    box->AddInstance(instanceA);
    box->AddInstance(instanceB);
    renderedRenderable.push_back(box);



    return false;
}

void Game::Update()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;



    for (BaseActor*& actor : renderedActors)
    {
        actor->Update(currentFrame);
    }
}

void Game::Render()
{
    for (BaseRenderable*& renderable : renderedRenderable)
    {
        renderable->Render();
    }
}

void Game::Exit()
{
}
