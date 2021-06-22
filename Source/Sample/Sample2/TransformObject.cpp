#include "TransformObject.h"

TransformObject::TransformObject()
{
	SetComponentName("TransformObject");
}

TransformObject::~TransformObject()
{
}

void TransformObject::Update()
{
}

void TransformObject::UpdateMatrix()
{
	CreateWorldMatrix();
}

void TransformObject::GUISystem()
{
	GUIGameObject();
	GUITransform();
}
