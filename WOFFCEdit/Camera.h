#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "InputCommands.h"
#include "Camera.h"
#include <vector>

class Camera
{
public:

	Camera();
	~Camera();

	// Basic game loop
	void Tick(InputCommands* Input);
	void Update(DX::StepTimer const& timer);

	DirectX::SimpleMath::Matrix GetViewMatrix();
	DirectX::SimpleMath::Vector3 GetCamPosition();
	void SetPivot(DirectX::SimpleMath::Vector3 _pivot);

private:

	void CamNormalMode();
	void CamArcBallMode();

	InputCommands						m_InputCommands;
	float								m_movespeed;

	//camera
	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;
	DirectX::SimpleMath::Vector3        m_camUp;
	float m_normalCamRotRate;
	float m_arcballCamRotRate;

	DirectX::SimpleMath::Matrix         m_view;

	int m_mousePosXOne;
	int m_mousePosXTwo;
	int m_mousePosYOne;
	int m_mousePosYTwo;

	DirectX::SimpleMath::Vector3 m_pivot;
};

