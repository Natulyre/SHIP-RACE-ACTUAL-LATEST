#include "Tunnel.h"

const float TUNNEL_SCALE_X = 20.f;
const float TUNNEL_SCALE_Y = 20.f;
const float TUNNEL_SCALE_Z = 100.f;
const float ROTATION_COEFF = 3.f;

Tunnel::Tunnel()
	:PrimitiveModel(PrimitiveModel_Type::CYLINDER)
	, mCurrentRotation(0.f)
{
	SetScale(TUNNEL_SCALE_X, TUNNEL_SCALE_Y, TUNNEL_SCALE_Z);
}


Tunnel::~Tunnel()
{
}

void Tunnel::Update()
{
	//The tunnel's rotation is constantly changed to simulate ship movement.
	mCurrentRotation += ROTATION_COEFF * gTimer->GetDeltaTime();
	SetRotationZ(mCurrentRotation);
}

void Tunnel::SetActive(bool toggle)
{
	isActive = toggle;
}