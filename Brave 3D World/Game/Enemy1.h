#pragma once

class Player;

class Enemy1:public IGameObject
{
public:

	Enemy1();
	~Enemy1();

	bool Start() override;

	void Move();

	void Rotation();

	void ManageState();

	void Enemy1Animation();

	void OnPlayerStomp(Player*p_player);

	void Damage();

	void Update() override;

	void Render(RenderContext& rc)override;

	Vector3 enemy1_position;

	int enemy1_HP = 100;

	void SetPosition(const Vector3&pos)
	{
		enemy1_position = pos;
	}

	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Num,
	};

	Player* p_player = nullptr;

private:

	ModelRender enemy1_modelRender;

	Vector3 enemy1_moveSpeed;

	Quaternion enemy1_rotation;

	CharacterController enemy1_characterController;

	AnimationClip animationClips[enAnimationClip_Num];

	//í«ê’ÉtÉâÉO
	bool isChasing = false;
	
	//
	int enemy1State;

	BoxCollider m_boxCollider;
};

