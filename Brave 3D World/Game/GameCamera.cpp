#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//プレイヤーのインスタンスを取得
	m_player = FindGO<Player>("player");

	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(0.0f, 100.0f, -250.0f);

	//カメラのニアクリップとフォークリップを設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(40000.0f);

	return true;
}

void GameCamera::Update()
{
	//カメラを更新
	//注視点を計算する
	Vector3 target = m_player->m_position;

	//プレイヤーの足元からちょっと上を注視点にする
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3 * x);
	qRot.Apply(m_toCameraPos);

	//X軸周りの回転
	Vector3 axisX;
	//カメラの回転の上限をチェックする
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	//回転軸を正規化（長さ1に）
	axisX.Normalize();
	//計算した軸を使って回転クォータニオンを作成（1.3度 x y入力分回転）
	qRot.SetRotationDeg(axisX, 1.3f * y);
	//カメラの方向ベクトルに回転を適用
	qRot.Apply(m_toCameraPos);

	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f)
	{
		//カメラが上向きすぎ
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f)
	{
		//カメラが下向きすぎ
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する
	Vector3 pos = target + m_toCameraPos;
	//カメラに注視点と視点を設定する
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新
	g_camera3D->Update();
}