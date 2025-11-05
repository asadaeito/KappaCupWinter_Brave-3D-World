#include "stdafx.h"
#include "NormalStage.h"

NormalStage::NormalStage()
{
	modelRender.Init("Assets/modelData/NormalStage/normalStage01.tkm");
	physicsStaticObject.CreateFromModel(modelRender.GetModel(),
		modelRender.GetModel().GetWorldMatrix());

	//“–‚½‚è”»’è‚Ì‰ÂŽ‹‰»
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

NormalStage::~NormalStage()
{

}

void NormalStage::Update()
{
	modelRender.Update();
}

void NormalStage::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}