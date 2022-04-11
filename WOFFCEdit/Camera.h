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

private:

	InputCommands						m_InputCommands;
	float								m_movespeed;

	//camera
	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;
	float m_camRotRate;

	DirectX::SimpleMath::Matrix         m_view;
};

