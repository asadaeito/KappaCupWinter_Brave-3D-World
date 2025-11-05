#include "stdafx.h"
#include "Game.h"
#include "NormalStage.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy1.h"
#include "MovingFloor.h"

Game::Game()
{
	//プレイヤーを作成
	m_player = NewGO<Player>(0, "player");

	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	normalStage = NewGO<NormalStage>(0, "normalStage");

	movingFloor = NewGO<MovingFloor>(0, "movingFloor");
	movingFloor->SetPosition(Vector3(0.0f, 200.0f, 3000.0f));

	for (int i = 0; i < 3; i++)
	{
		enemy1[i] = NewGO<Enemy1>(1, "enemy1");
		//各エネミーにプレイヤーの情報を渡す
		enemy1[i]->p_player = m_player;

		enemy1[i]->SetPosition(enemy1_pos[i]);
		
	}

	

}

Game::~Game()
{
	
}

void Game::InitSky()
{
	//SkyCubeの生成
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	//空の明るさ設定
	m_skyCube->SetLuminance(1.0f);

	//SkyCubeの種類の設定
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

	//環境光の計算のためのIBLテクスチャをセットする
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);

	//環境日光の影響が分かりやすいように、ディレクションはオフに
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

bool Game::Start()
{
	InitSky();

	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}