#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include "util/util.h"

void printBytes(int8_t* bytes, size_t count) {
    for(size_t i = 0; i < count; i++) {
        printf("%c", bytes[i]);
    }
    printf("\n");
}

int main(void) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("%s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_OPENGL);
    SDL_Surface* icon = IMG_Load("assets/logo.png");
    SDL_SetWindowIcon(window, icon);
    if(!window) {
        printf("%s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GLContext openGLContext;
    openGLContext = SDL_GL_CreateContext(window);
    if(!openGLContext) {
        printf("%s\n", SDL_GetError());
        return -1;
    }

    if(!oglgladLoadGLLoader(SDL_GL_GetProcAddress)) {
        printf("GLAD failed to init!\n");
        return -1;
    }
    BOOL shouldNotQuit = true;
    SDL_Event event;

    SDL_GL_SetSwapInterval(1);

    char infoLog[512];
    int success;

    HeapData vertexData;
    if(!Util_ReadFile("src-shader/baseVertex.vert", &vertexData, false)) {
        printf("reading vertex shader failed!\n");
        return -1;
    }
    //printBytes(vertexData.bytes, vertexData.size);
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLint vertexDataSize = (GLint) vertexData.size;
    glShaderSource(vertexShader, 1, (const GLchar *const*) &vertexData.bytes, &vertexDataSize);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        printf("vertex shader compile failed:\n%s\n", infoLog);
        return -1;
    }

    HeapData pixelData;
    if(!Util_ReadFile("src-shader/basePixel.frag", &pixelData, false)) {
        printf("reading pixel shader failed!\n");
        return -1;
    }
    uint32_t pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLint pixelDataSize = (GLint) pixelData.size;
    glShaderSource(pixelShader, 1, (const GLchar *const*) &pixelData.bytes, &pixelDataSize);
    glCompileShader(pixelShader);
    glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(pixelShader, sizeof(infoLog), NULL, infoLog);
        printf("pixel shader compile failed:\n%s\n", infoLog);
        return -1;
    }

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, pixelShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        printf("shader program link failed:\n%s\n", infoLog);
        return -1;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(pixelShader);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    uint32_t VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 


    while(shouldNotQuit) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) {
                printf("closing!\n");
                shouldNotQuit = false;
                break;
            }
        }

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(openGLContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}