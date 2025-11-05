#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//アニメーションデータの読み込みと設定
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	m_characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{

}

bool Player::Start()
{
	

	m_modelRender.Init("Assets/modelData/unityChan.tkm",animationClips,enAnimationClip_Num,enModelUpAxisY);

	return true;
}

void Player::Move()
{
	//x.zの移動速度を初期化
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得する
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y方向に移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	//ダッシュ処理を追加
	//Bボタン押しっぱなしでダッシュ
	isDashing = g_pad[0]->IsPress(enButtonB);

	//三項演算子でダッシュか歩きかでスピードを変える
	float speed = isDashing ? 500.0f : 320.0f;

	//左スティックの入力量と120.0fを乗算
	forward*=stickL.y* speed;
	right*=stickL.x* speed;

	//移動速度に上記で計算したベクトルを加算する
	m_moveSpeed += right + forward;

	//地面に着いていたら
	if (m_characterController.IsOnGround())
	{
		//重力をなくす
		m_moveSpeed.y = 0.0f;

		//床の移動量を検出する(動く床用)
		//CharacterControllerから床の速度を取得
		//m_characterController=m_characterController.

		//Aボタンが押されたら
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプをさせる
			m_moveSpeed.y = 1000.0f;

			//足元にBoxコリジョンを発生させる
			
		}
	}
	//地面に着いていなかったら
	else
	{
		//重力を発生させる
		m_moveSpeed.y -= 30.0f;
	}

	//キャラクターコントローラーを使って座標を移動させる
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}

	//絵描きさんに座標を教える
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

		//回転を絵描きさんに教える
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{
	if (m_characterController.IsOnGround() == false)
	{
		//ジャンプ中はステート1
		playerState = 1;

		//ここでManageStateの処理を終了させる
		return;
	}
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (isDashing)
		{
			//ダッシュはステート3
			playerState = 3;
		}
		else
		{
			//歩きをはステート2
			playerState = 2;
		}
	}
	//xとzの移動速度がなかったら(スティックの入力がなかったら)
	else
	{
		//待機はステート0
		playerState = 0;
	}
}

void Player::PlayerAnimation()
{
	switch (playerState)
	{
		//プレイヤーステートが0(待機)だったら
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

		//プレイヤーステートが1(ジャンプ中)だったら
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	
		//プレイヤーステートが2(歩き)だったら
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;

		//プレイヤーステートが3(ダッシュ)だったら
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Attack()
{

}

void Player::Respawn()
{
	//プレイヤーの位置をリスポーン地点に戻す
	if (m_position.y < -900.0f)
	{
		m_position = Vector3(0.0f, 0.0f, 0.0f);
		m_modelRender.SetPosition(m_position);
		//当たり判定の位置もリセットする
		m_characterController.SetPosition(m_position);
		//モデルの位置もリセット(見た目用)
		m_position = m_position;

	}
}

void Player::Update()
{
	Move();

	Rotation();

	Respawn();

	ManageState();

	PlayerAnimation();

	m_modelRender.Update();
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}