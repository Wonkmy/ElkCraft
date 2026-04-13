#include "stdafx.h"
#include "ElkCraft/Gameplay/EntityController.h"

using namespace ElkTools::Utils;
using namespace ElkGameEngine::Objects::Components;
using namespace ElkGameEngine::Objects::Components::Behaviours;
using namespace ElkCraft::Gameplay;

EntitiyController::EntitiyController(ElkCraft::Terrain::World* p_world)
	:m_rigidbody(nullptr)
{

}

EntitiyController::~EntitiyController()
{

}

void EntitiyController::Update() {
	// 这里简单的实现一个通过sin函数让实体上下浮动的效果
	

	float time = Time::GetDeltaTime();
	
	float newY = m_owner->transform->GetPosition().y + sin(time * floatSpeed) * floatHeight;
	glm::vec3 newPosition = glm::vec3(m_owner->transform->GetPosition().x, newY, m_owner->transform->GetPosition().z);
	m_owner->transform->SetPosition(newPosition);
}