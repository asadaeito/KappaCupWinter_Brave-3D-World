#pragma once

class Player:public IGameObject
{
public:
	Player();
	~Player();

	//初期化処理やオブジェクトのポインター取得
	bool Start();

	//更新処理
	void Update();

	//リスポーン処理
	void Respawn();

	//移動処理
	void Move();

	//回転処理
	void Rotation();

	//ステート管理
	void ManageState();

	//アニメーション
	void PlayerAnimation();

	//攻撃処理
	void Attack();

	//描画処理
	void Render(RenderContext& rc);

	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	//プレイヤーの現在位置(ワールド座標)を取得する
	Vector3 GetPosition()const
	{
		return m_position;
	}

	float GetVerticalSpeed()const
	{
		return m_moveSpeed.y;
	}

	//プレイヤーに紐づいてるキャラクターコントローラーを取得する
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	//プレイヤーの移動速度に加算する
	//例:移動床やダッシュなど追加速度を与えたい時に使用
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}

	//プレイヤーが死亡しているかどうか
	bool player_isDead = false;

	//プレイヤーのポジション
	Vector3 m_position;

private:

	//プレイヤーのモデル
	ModelRender m_modelRender;

	//プレイヤーの移動速度
	Vector3 m_moveSpeed;

	Vector3 m_floorValocity = { 0.0f,0.0f,0.0f };//乗っている床の速度

	//プレイヤーの回転
	Quaternion m_rotation;

	//移動、当たり判定
	CharacterController m_characterController;

	//ボックスコライダー(当たり判定)
	BoxCollider m_boxCollider;	

	AnimationClip animationClips[enAnimationClip_Num];

	//ダッシュ中かどうか
	bool isDashing = false;

	//プレイヤーの状態管理
	int playerState;
};

