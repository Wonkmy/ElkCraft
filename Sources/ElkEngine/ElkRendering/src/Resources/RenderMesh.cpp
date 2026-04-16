#include "stdafx.h"

#include "ElkRendering/Resources/RenderMesh.h"

using namespace ElkRendering::Resources;

RenderMesh::RenderMesh()
{
	Setup();
}

void RenderMesh::Setup()
{
	InitPositions();
	InitIndices();
	InitBuffers();
}

void RenderMesh::Draw() const
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderMesh::UpdateSSBO() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(m_vertices), m_vertices);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void RenderMesh::InitPositions()
{
	m_vertices[0].position[0] = -1;
	m_vertices[0].position[1] = -1;
	m_vertices[0].position[2] = 0;
	m_vertices[1].position[0] = 1;
	m_vertices[1].position[1] = -1;
	m_vertices[1].position[2] = 0;
	m_vertices[2].position[0] = 1;
	m_vertices[2].position[1] = 1;
	m_vertices[2].position[2] = 0;
	m_vertices[3].position[0] = -1;
	m_vertices[3].position[1] = 1;
	m_vertices[3].position[2] = 0;
}

void RenderMesh::InitIndices()
{
	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 2;
	m_indices[4] = 3;
	m_indices[5] = 0;
}

void RenderMesh::InitBuffers()
{
	// VAO stuffs
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	// VBO stuffs
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), m_vertices, GL_STATIC_DRAW);
	// EBO struffs
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), m_indices, GL_STATIC_DRAW);
	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
						  reinterpret_cast<void*>(offsetof(Vertex, normal)));
	// vertex textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
						  reinterpret_cast<void*>(offsetof(Vertex, texCoords)));
	// Unbind all
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}