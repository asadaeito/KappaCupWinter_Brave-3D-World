#pragma once

class Player;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

private:

	bool Start();
	void Update();


	//ƒƒ“ƒo[•Ï”

	Player* m_player;

	Vector3 m_toCameraPos;
};

