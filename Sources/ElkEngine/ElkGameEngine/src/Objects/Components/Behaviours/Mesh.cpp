#include "stdafx.h"

#include "ElkGameEngine/Objects/Components/Behaviours/Mesh.h"

using namespace ElkGameEngine::Objects::Components::Behaviours;

Mesh::Mesh()
{
	SetName("Mesh");
	m_renderLayer = 0;
	m_color = glm::vec4(1.f);
}

ElkRendering::Resources::RenderMesh& Mesh::GetRenderMesh()
{
	return m_renderMesh;
}

void Mesh::SetMesh(const ElkRendering::Resources::RenderMesh & p_mesh)
{
	m_renderMesh = p_mesh;
}

const ElkRendering::Resources::RenderMesh & Mesh::GetMesh() const
{
	return m_renderMesh;
}

void Mesh::SetRenderLayer(uint16_t p_renderLayer)
{
	m_renderLayer = p_renderLayer;
}

uint16_t Mesh::GetRenderLayer()
{
	return m_renderLayer;
}

void Mesh::SetColor(const glm::vec4 & p_color)
{
	m_color = p_color;
}

const glm::vec4 & Mesh::GetColor()
{
	return m_color;
}