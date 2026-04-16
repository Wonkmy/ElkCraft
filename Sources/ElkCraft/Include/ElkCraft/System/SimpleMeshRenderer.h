#pragma once

// ====== 必须顺序：先 glew 再 glfw ======
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <iostream>

// ========================
// Vertex
// ========================
struct SMR_Vertex
{
    float position[3];
    float normal[3];
    float uv[2];
};

// ========================
// Shader
// ========================
class SMR_Shader
{
public:
    unsigned int ID;

    const char* vertexSrc = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;
        layout (location = 2) in vec2 aUV;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec2 uv;

        void main()
        {
            uv = aUV;
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

    const char* fragmentSrc = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 uv;

        void main()
        {
            FragColor = vec4(uv, 0.0, 1.0);
        }
    )";

    void Init()
    {
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSrc, NULL);
        glCompileShader(vertex);
        Check(vertex, "VERTEX");

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSrc, NULL);
        glCompileShader(fragment);
        Check(fragment, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        Check(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Use()
    {
        glUseProgram(ID);
    }

    void SetMat4(const char* name, const float* value)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, value);
    }

private:
    void Check(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];

        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Shader Error: " << type << "\n" << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Program Error:\n" << infoLog << std::endl;
            }
        }
    }
};

// ========================
// Mesh
// ========================
class SMR_Mesh
{
public:
    unsigned int VAO, VBO, EBO;

    std::vector<SMR_Vertex> vertices;
    std::vector<unsigned int> indices;

    void Init()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
            vertices.size() * sizeof(SMR_Vertex),
            vertices.data(),
            GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(unsigned int),
            indices.data(),
            GL_STATIC_DRAW);

        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SMR_Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SMR_Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // uv
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SMR_Vertex), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    void Draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

// ========================
// MeshRenderer
// ========================
class SMR_MeshRenderer
{
public:
    SMR_Mesh* mesh = nullptr;
    SMR_Shader* shader = nullptr;

    float model[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    void Render(const float* view, const float* projection)
    {
        if (!mesh || !shader) return;

        shader->Use();

        shader->SetMat4("model", model);
        shader->SetMat4("view", view);
        shader->SetMat4("projection", projection);

        mesh->Draw();
    }
};

// ========================
// 创建一个三角形
// ========================
inline SMR_Mesh CreateSimpleTriangle()
{
    SMR_Mesh mesh;

    mesh.vertices = {
        {{-0.5f, -0.5f, 0}, {0,0,1}, {0,0}},
        {{ 0.5f, -0.5f, 0}, {0,0,1}, {1,0}},
        {{ 0.0f,  0.5f, 0}, {0,0,1}, {0.5f,1}}
    };

    mesh.indices = { 0,1,2 };

    mesh.Init();
    return mesh;
}