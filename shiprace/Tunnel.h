#pragma once

#include "PrimitiveModel.h"

class Tunnel :
	public PrimitiveModel
{
public:
	Tunnel();
	~Tunnel();

	void Update();
	void SetActive(bool toggle);


private:
	float mCurrentRotation;

};

