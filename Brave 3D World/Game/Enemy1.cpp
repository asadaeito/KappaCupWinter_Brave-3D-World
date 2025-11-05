#include "stdafx.h"
#include "Enemy1.h"
#include "Player.h"

Enemy1::Enemy1()
{
	//アニメーションデータの読み込みと設定
	animationClips[enAnimationClip_Idle].Load("Assets/animData/Ant_idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/Ant_walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);

}                         

Enemy1::~Enemy1()
{

}

bool Enemy1::Start()
{
	//enemy1_modelRender.Init("Assets/modelData/Enemy/ant.tkm");

	enemy1_modelRender.Init("Assets/modelData/Enemy/ant.tkm",animationClips,enAnimationClip_Num,enModelUpAxisZ);

	//enemy1_position = { 0.0f,0.0f,0.0f };

	enemy1_characterController.Init(25.0f, 70.0f,enemy1_position);

	enemy1_modelRender.SetPosition(enemy1_position);

	enemy1_modelRender.SetScale({ 2.0f,2.0f,2.0f });

	m_boxCollider.Create(Vector3(5.0f, 5.0f, 5.0f));

	m_boxCollider.GetBody();

	return true;
}

void Enemy1::Update()
{

	Move();

	ManageState();

	Enemy1Animation();

	Rotation();

	OnPlayerStomp(p_player);

	enemy1_modelRender.Update();
}

void Enemy1::Move()
{
	//速度の初期化
	enemy1_moveSpeed.x = 0.0f;
	enemy1_moveSpeed.y = 0.0f;


	if (p_player == nullptr)
	{
		return;
	}

	//プレイヤーが死亡しているかどうかをチェックする
	//死んでいたら追跡フラグをfalseにする
	if (p_player->player_isDead)
	{
		isChasing = false;
		return;
	}

	//プレイヤーの現在位置を取得
	Vector3 Player_positon = p_player->GetPosition();

	//敵の位置からプレイヤーへのベクトルを求める
	Vector3 diff = Player_positon - enemy1_position;

	//Y軸方向の差は無視する。
	diff.y = 0.0f;

	//距離を計算
	float distance = diff.Length();

	//追跡を開始する距離
	const float chaseRange = 400.0f;

	//まだ追跡してない かつ プレイヤーが範囲内に入ったら追跡を開始する
	if (!isChasing && distance < chaseRange)
	{
		isChasing = true;
	}

	
	//追跡処理
	if (isChasing)
	{
		//方向ベクトルを正規化して長さ1にする
		//向きだけを取り出すことで、距離に関係なく一定速度で移動できるようになる
		diff.Normalize();

		//速さ
		float speedValue = 150.0f;

		enemy1_moveSpeed.x = diff.x * speedValue;
		enemy1_moveSpeed.z = diff.z * speedValue;

		//地面に着いていたら
		if (enemy1_characterController.IsOnGround())
		{
			//重力をなくす
			enemy1_moveSpeed.y = 0.0f;
		}
		//地面に着いていなかったら
		else
		{
			//重力を発生させる
			enemy1_moveSpeed.y -= 30.0f;
		}

		//キャラクターコントローラーを使って移動
		enemy1_position = enemy1_characterController.Execute(enemy1_moveSpeed, 1.0f / 60.0f);

		//モデルの描画位置を更新する(見た目を新しい位置に反映)
		enemy1_modelRender.SetPosition(enemy1_position);
	}
}

void Enemy1::Rotation()
{
	if (fabsf(enemy1_moveSpeed.x) >= 0.001f || fabsf(enemy1_moveSpeed.z) >= 0.001f)
	{
		//移動方向に向けて回転する
		enemy1_rotation.SetRotationYFromDirectionXZ(enemy1_moveSpeed);
		
		enemy1_modelRender.SetRotation(enemy1_rotation);
	}
}

void Enemy1::ManageState()
{
	if (fabsf(enemy1_moveSpeed.x) >= 0.001f || fabsf(enemy1_moveSpeed.z) > 0.001f)
	{
		//移動中は1
		enemy1State = 1;
	}
	//xとzの移動速度がなかったら。
	else
	{
		//停止中は0
		enemy1State = 0;
	}
}

void Enemy1::Enemy1Animation()
{
	switch (enemy1State)
	{
		//enemy1Stateが0(待機)だったら
	case 0:
		enemy1_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case 1:
		enemy1_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}

void Enemy1::OnPlayerStomp(Player* p_player)
{
	//プレイヤーの現在位置を取得
	Vector3 player_pos = p_player->GetPosition();

	//敵の現在位置とプレイヤーの現在位置のベクトルを求める
	Vector3 diff = player_pos - enemy1_position;

	//横方向の距離を求める
	float horizontalDist = sqrtf(diff.x * diff.x + diff.z * diff.z);

	float PlayerVerticalSpeed = p_player->GetVerticalSpeed();

	static float prevDiffY = 0.0f;
	float currentDiffY = diff.y;

	if (prevDiffY > 30.0f && currentDiffY <= 30.0f &&
		horizontalDist < 30.0f && PlayerVerticalSpeed < 0.0f)
	{
		Damage();
	}

	prevDiffY = currentDiffY;

	//踏まれたと判定する条件
	//1,プレイヤーが敵より上に一定距離
	//2,横方向のズレ
	//3.プレイヤーが落下中
	/*if (diff.y > 30.0f && horizontalDist < 30.0f&&PlayerVerticalSpeed<0.0f)
	{
		Damage();
	}*/
}

void Enemy1::Damage()
{
	//ダメージ処理
	enemy1_HP -= 100;

	//HPが0以下になったら消滅
	if (enemy1_HP < 0)
	{
		DeleteGO(this);
	}
}

void Enemy1::Render(RenderContext& rc)
{
	enemy1_modelRender.Draw(rc);
}