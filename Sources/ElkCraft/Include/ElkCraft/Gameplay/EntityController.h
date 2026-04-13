#pragma once

#include <ElkGameEngine/ElkGameEngine.h>
#include <ElkTools/Utils/BlocksInfo.h>

#include "ElkCraft/Terrain/World.h"

namespace ElkCraft::Gameplay {
	class EntitiyController : public ElkGameEngine::Objects::Components::Behaviours::ABehaviour 
	{
	public:
		EntitiyController(ElkCraft::Terrain::World* p_world);
		~EntitiyController();

		void Update() override;
	private:
		std::shared_ptr<ElkGameEngine::Objects::Components::Behaviours::Rigidbody> m_rigidbody;
		float floatHeight = 0.5f; // 浮动高度
		float floatSpeed = 1.0f; // 浮动速度
	};
}
