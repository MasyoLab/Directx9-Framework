#pragma once

#include "dxlib.h"

class TransformObject :
	public mslib::object::GameObject,
	public mslib::transform::Transform
{
public:
	TransformObject();
	~TransformObject();

	/**
	@brief 更新
	*/
	virtual void Update();

	/**
	@brief 姿勢行列の更新
	*/
	virtual void UpdateMatrix();

	/**
	@brief GUIに表示する機能
	*/
	virtual void GUISystem() override;
};

