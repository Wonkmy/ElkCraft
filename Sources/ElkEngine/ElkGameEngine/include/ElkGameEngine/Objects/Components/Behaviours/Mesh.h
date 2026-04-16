#pragma once

#include <ElkRendering/Resources/RenderMesh.h>

#include "ElkGameEngine/export.h"
#include "ElkGameEngine/Objects/Components/Behaviours/ABehaviour.h"

namespace ElkGameEngine
{
	namespace Objects
	{
		namespace Components
		{
			namespace Behaviours
			{
				class ELK_GAMEENGINE_EXPORT Mesh : public Components::Behaviours::ABehaviour
				{
				public:
					Mesh();
					virtual ~Mesh() = default;

					ElkRendering::Resources::RenderMesh& GetRenderMesh();

					void SetRenderLayer(uint16_t p_renderLayer);
					uint16_t GetRenderLayer();

					void SetMesh(const ElkRendering::Resources::RenderMesh& p_mesh);
					const ElkRendering::Resources::RenderMesh& GetMesh() const;

					void SetColor(const glm::vec4& p_color);
					const glm::vec4& GetColor();

					void Update() override {}

				private:
					ElkRendering::Resources::RenderMesh m_renderMesh;
					uint16_t m_renderLayer;
					glm::vec4 m_color;
				};
			}
		}
	}
}