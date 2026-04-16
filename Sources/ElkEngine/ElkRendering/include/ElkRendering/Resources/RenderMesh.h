#pragma once

#include "ElkRendering/export.h"

namespace ElkRendering
{
	namespace Resources
	{
		class ELK_RENDERING_EXPORT RenderMesh
		{
		public:
			struct ELK_RENDERING_EXPORT Vertex
			{
				float position[3];
				float normal[3];
				float texCoords[2];
			};

			RenderMesh();
			~RenderMesh() = default;

			void Setup();
			void Draw() const;
			void UpdateSSBO() const;

		private:
			void InitBuffers();
			void InitPositions();
			void InitIndices();

			/* Buffers */
			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ssbo;
			GLuint m_ebo;

			Vertex m_vertices[4];

			unsigned int m_indices[6];
		};
	}
}
