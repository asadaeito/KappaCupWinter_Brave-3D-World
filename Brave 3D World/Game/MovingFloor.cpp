#include "stdafx.h"
#include "MovingFloor.h"
#include "Player.h"

namespace
{
	Vector3 SCALE = Vector3{ 3.0f,1.0f,3.0f };//サイズ
	float SPEED = 200.0f;//スピード
	float LIMITEDE = 300.0f;//振り幅
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
	Vector3 COLLISION_SIZE = Vector3(365.0f, 5.0f, 215.0f);
}

MovingFloor::MovingFloor()
{
	
}

MovingFloor::~MovingFloor()
{

}

bool MovingFloor::Start()
{
	m_modelRender.Init("Assets/modelData/NormalStage/demostage.tkm");
	m_modelRender.SetScale(SCALE);

	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");

	//コリジョンオブジェクトを
	//動く床の上に設置する(キャラクターが上に乗ったら反応するようにしたいため)
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);
	

	m_firstPosition = m_position;

	m_player = FindGO<Player>("player");

	return true;
}

void MovingFloor::Move()
{
	Vector3 moveSpeed = Vector3::Zero;

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.y = - SPEED;
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		moveSpeed.y = SPEED;
	}

	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstPosition.y - LIMITEDE >= m_position.y)
		{
			m_MovingFloorState = enMovingFloorState_MovingLeft;
		}
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		if (m_firstPosition.y + LIMITEDE <= m_position.y)
		{
			m_MovingFloorState = enMovingFloorState_MovingRight;
		}
	}

	m_modelRender.SetPosition(m_position);

	if (m_player != nullptr && m_collisionObject != nullptr)
	{
		auto& cc = m_player->GetCharacterController();

		if (m_collisionObject->IsHit(cc))
		{
			
			m_player->AddMoveSpeed(moveSpeed);
		}
	}
}

void MovingFloor::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}
	
	m_physicsStaticObject.Release();
	m_physicsStaticObject.CreateFromModel(
		m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix()
	);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);

	Move();

	m_modelRender.Update();
}

void MovingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);


}