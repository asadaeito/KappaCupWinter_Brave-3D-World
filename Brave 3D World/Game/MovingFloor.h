#pragma once

class Player;

class MovingFloor : public IGameObject
{
public:
	MovingFloor();
	~MovingFloor();
	bool Start()override;
	void Move();
	void Update()override;
	void Render(RenderContext& rc)override;

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

private:

	ModelRender m_modelRender;
	
	Vector3 m_position;

	Vector3 m_firstPosition;

	PhysicsStaticObject m_physicsStaticObject;

	CollisionObject* m_collisionObject = nullptr;
	
	Player* m_player = nullptr;

	float m_moveSpeed;


	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState m_MovingFloorState = enMovingFloorState_MovingRight;
};

