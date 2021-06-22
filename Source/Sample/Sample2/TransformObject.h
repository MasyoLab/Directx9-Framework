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
	@brief �X�V
	*/
	virtual void Update();

	/**
	@brief �p���s��̍X�V
	*/
	virtual void UpdateMatrix();

	/**
	@brief GUI�ɕ\������@�\
	*/
	virtual void GUISystem() override;
};

