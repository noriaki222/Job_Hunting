#pragma once
#include "Base\Camera.h"
#include <Windows.h>

class TestCamera : public CCamera
{
public:
	TestCamera();

	virtual void Init();
	virtual void Update();

private:
	struct Argument
	{
		DirectX::XMFLOAT2 mouseMove;
		DirectX::XMVECTOR vCamFront;
		DirectX::XMVECTOR vCamSide;
		DirectX::XMVECTOR vCamUp;
		DirectX::XMVECTOR vCamPos;
		DirectX::XMVECTOR vCamLook;
		float focus;
	};
	void UpdateState();
	void UpdateOrbit(Argument& arg);
	void UpdateTrack(Argument& arg);
	void UpdateDolly(Argument& arg);
	void UpdateFlight(Argument& arg);
	int m_state;
	POINT m_oldPos;

};