#pragma once
class NormalStage:public IGameObject
{
public:
	NormalStage();
	~NormalStage();
	void Update();
	void Render(RenderContext& rc);

private:

	ModelRender modelRender;
	PhysicsStaticObject physicsStaticObject;

};

