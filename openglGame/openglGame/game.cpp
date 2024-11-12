#include "game.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <camera.h>
#include <shader.h>
#include <lightingManager.h>

#define SCREEN_WIDTH  1080
#define SCREEN_HEIGHT 720

#define WINDOW_NAME "openGL game"

#define CAPTURE_MOUSE true
#define SCREEN_ALLOWED_TO_RESIZE true
#define CLEAR_COLOR 0.1f, 0.1f, 0.1f, 1.0f


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

    m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME, NULL, NULL);

    if (m_window == NULL)
    {
        printf("Failed to create GLFW window \n");
        glfwTerminate();
        return false;
    }

    /*
     this allows to pass a pointer to Game as a workaround 
     that glfw funtions need to be static
    */
    glfwSetWindowUserPointer(m_window, this);
    glfwMakeContextCurrent(m_window);


    if (SCREEN_ALLOWED_TO_RESIZE)
    {
        glfwSetFramebufferSizeCallback(m_window, OnResize);
    }

    glfwSetCursorPosCallback(m_window, OnMouseInput);
    glfwSetScrollCallback(m_window, OnScroll);
    glfwSetKeyCallback(m_window, OnKeyInput);


    if (CAPTURE_MOUSE)
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize Glad \n");
        return false;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);



    if (!InitActors())
    {
        printf("Failed to initialize actors \n");
        return false;
    }

    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(CLEAR_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Update();
        Render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }



	return true;
}

bool Game::InitActors()
{
    m_sceneCameras.push_back(Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    m_currentCamera = &m_sceneCameras[0];
    m_camController = new CameraController(*m_currentCamera);
    m_shaders.push_back(Shader("standardShader.vs", "standardShader.fs"));

    std::vector<LightingManager::Sun> suns;
    suns.push_back(
    {
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(1.0f),
        1.0f                                            
    });


    std::vector<LightingManager::SpotLight> spotLights;
    //spotLights.push_back(
    //{
    //    glm::vec3(1.0f, 1.0f, 1.0f),
    //    glm::vec3(1.0f, 1.0f, 1.0f),
    //    glm::vec3(1.0f, 1.0f, 1.0f),
    //    1.0f
    //});


    std::vector<LightingManager::AreaLight> areaLights;
    //areaLights.push_back(
    //{
    //    glm::vec3(1.0f, 1.0f, 1.0f),
    //    glm::vec3(1.0f, 1.0f, 0.0f),
    //    1.0f
    //});
    lightingManager = new LightingManager(suns, spotLights, areaLights);


    
    Monkey* monkey = new Monkey(*m_currentCamera, &m_shaders[0]);

    Instance InstanceArray[10 * 10];

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            InstanceArray[i + j * 10] = Instance
            (
                glm::vec3(j * -4.0f, 0.0f, i * -4.0f + -4.0f),
                glm::vec3(0.0f), 
                glm::vec3(1.0f)
            );

            monkey->AddInstance(InstanceArray[i + j * 10]);
        }
    }

    m_renderedRenderable.push_back(monkey);

    return true;
}

void Game::Update()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    // Smooth camera movement
    UpdateKeyInputs();

    for (BaseActor*& actor : m_renderedActors)
    {
        actor->Update(currentFrame);
    }
}

void Game::UpdateKeyInputs()
{
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_camController->ProcessKeyboard(CameraController::FORWARD, m_deltaTime);
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_camController->ProcessKeyboard(CameraController::BACKWARD, m_deltaTime);
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_camController->ProcessKeyboard(CameraController::RIGHT, m_deltaTime);
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_camController->ProcessKeyboard(CameraController::LEFT, m_deltaTime);
    }
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
    {
        m_camController->ProcessKeyboard(CameraController::UP, m_deltaTime);
    }
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        m_camController->ProcessKeyboard(CameraController::DOWN, m_deltaTime);
    }

}

void Game::Render()
{
    Shader* shader = &m_shaders[0];
    shader->use();  // Bind the shader

    unsigned int lightingBlockIndex = glGetUniformBlockIndex(shader->ID, "Lighting");
    if (lightingBlockIndex != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(shader->ID, lightingBlockIndex, 0);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, *lightingManager->LookAtLightingUBO());
    }
    else
    {
        std::cerr << "UBO block 'Lighting' not found in shader." << std::endl;
    }

    // Render all objects
    for (BaseRenderable*& renderable : m_renderedRenderable)
    {
        renderable->Render();
    }

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, 0);
}



void Game::Exit()
{
}

void Game::OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
}

void Game::OnMouseInput(GLFWwindow* window, double xposIn, double yposIn)
{
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    glm::vec2 pos = glm::vec2(static_cast<float>(xposIn), static_cast<float>(yposIn));
    game->m_camController->ProcessMouseMovement(pos);
}

void Game::OnScroll(GLFWwindow* window, double xoffset, double yoffset)
{

}

void Game::OnResize(GLFWwindow* window, int width, int height)
{

}
