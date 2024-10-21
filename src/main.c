#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h>
#include "util/util.h"
#include <direct.h>
#include <cglm/struct/vec2.h>
#include <input/input.h>

float vertices[] = {
     0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  // top right
     0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bottom right
    -1.0, -1.0f, 0.0f, 0.0f, 1.0f,  // bottom left
    -1.0,  0.0f, 0.0f, 0.0f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

char infoLog[512];
int32_t success;

float remap(float value, float oldMin, float oldMax, float newMin, float newMax) {
    return (value - oldMin) / (oldMax - oldMin) * (newMax - newMin) + newMin;
}

int main(void) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Util_PrintMessage("%s", UTIL_MESSAGE_TYPE_FATAL, SDL_GetError());
        return -1;
    }
    
    SDL_Window* window = SDL_CreateWindow("CShooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_OPENGL);
    if (!window) {
        Util_PrintMessage("%s", UTIL_MESSAGE_TYPE_FATAL, SDL_GetError());
        return -1;
    }
    
    SDL_Surface* icon = IMG_Load("assets/logo.png");
    if (icon) {
        SDL_SetWindowIcon(window, icon);
    }
    else {
        Util_PrintMessage("%s\n", UTIL_MESSAGE_TYPE_ERROR, IMG_GetError());
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    SDL_GLContext openGLContext = SDL_GL_CreateContext(window);
    if (!openGLContext) {
        Util_PrintMessage("%s\n", UTIL_MESSAGE_TYPE_FATAL, SDL_GetError());
        return -1;
    }

    SDL_GL_SetSwapInterval(1);

    if (!oglgladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        Util_PrintMessage("Failed to load glad!\n", UTIL_MESSAGE_TYPE_FATAL);
    }
    
    HeapData vertexShaderCode;
    if (!Util_ReadFile("src-shader/baseVertex.vert", &vertexShaderCode, false)) {
        Util_PrintMessage("Failed to load vertex shader!\n", UTIL_MESSAGE_TYPE_FATAL);
        return -1;
    }
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode.bytes, &vertexShaderCode.size);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        Util_PrintMessage("Failed to compile vertex shader: %s\n", UTIL_MESSAGE_TYPE_FATAL, infoLog);
        return -1;
    }
    free(vertexShaderCode.bytes);

    HeapData pixelShaderCode;
    if (!Util_ReadFile("src-shader/basePixel.frag", &pixelShaderCode, false)) {
        Util_PrintMessage("Failed to load pixel shader!\n", UTIL_MESSAGE_TYPE_FATAL);
        return -1;
    }
    uint32_t pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(pixelShader, 1, &pixelShaderCode.bytes, &pixelShaderCode.size);
    glCompileShader(pixelShader);
    glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(pixelShader, sizeof(infoLog), NULL, infoLog);
        Util_PrintMessage("Failed to compile pixel shader:\n%s\n", UTIL_MESSAGE_TYPE_FATAL, infoLog);
        return -1;
    }
    free(pixelShaderCode.bytes);
    SDL_Surface* convertedIcon = SDL_ConvertSurfaceFormat(icon, SDL_PIXELFORMAT_RGBA32, NULL);
    if (!convertedIcon) {
        Util_PrintMessage("Failed to convert texture:\n%s", UTIL_MESSAGE_TYPE_FATAL, SDL_GetError());
        return -1;
    }
    SDL_FreeSurface(icon);
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, convertedIcon->w, convertedIcon->h, NULL, GL_RGBA, GL_UNSIGNED_BYTE, convertedIcon->pixels);
    SDL_FreeSurface(convertedIcon);
    glGenerateMipmap(GL_TEXTURE_2D);
    

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, pixelShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        Util_PrintMessage("Failed to link shader program:\n%s\n", UTIL_MESSAGE_TYPE_FATAL, infoLog);
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(pixelShader);

    uint32_t VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    BOOL shouldNotQuit = true;
    SDL_Event event;

    int x;
    int y;

    BOOL mouseWheel = false;

    while (shouldNotQuit) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    shouldNotQuit = false;
                    break;
                case SDL_MOUSEWHEEL:
                    Input_CheckMouseWheel(event.wheel);
                    mouseWheel = true;
                    break;
                default:
                    break;
            }
        }
        Input_PollStates();
        if (!mouseWheel) {
            Input_ResetMouseWheel();
        }
        else {
            mouseWheel = false;
        }


        keystate_t mouse4 = Input_GetMouseButton(MOUSEBUTTON4);
        keystate_t mouse5 = Input_GetMouseButton(MOUSEBUTTON5);
        ivec2s mouseDelta = Input_GetMouseDelta();
        vec2s mouseScrollDelta = Input_GetMouseWheelDelta();
        

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        SDL_GL_SwapWindow(window);
    }
}