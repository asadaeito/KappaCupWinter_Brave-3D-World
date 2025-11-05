#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class NormalStage;
class MovingFloor;
class Enemy1;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	//空(スカイキューブ)の初期化
	void InitSky();

	ModelRender m_modelRender;

	Vector3 m_position;

	Player* m_player;

	GameCamera* gameCamera;

	NormalStage* normalStage;

	MovingFloor* movingFloor;

	Vector3 enemy1_pos[3] =
	{
		{0.0f,0.0f,600.0f},
		{0.0f,0.0f,700.0f},
		{0.0f,0.0f,800.0f}
	};

	Enemy1* enemy1[3];

	//空の描画用
	SkyCube* m_skyCube = nullptr;
	int m_skyCubeType = enSkyCubeType_Day;
};

