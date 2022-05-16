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

	// Getters for view matrix, position and pivot as well as setter for pivot 
	DirectX::SimpleMath::Matrix GetViewMatrix();
	DirectX::SimpleMath::Vector3 GetCamPosition();
	DirectX::SimpleMath::Vector3 GetPivot();
	void SetPivot(DirectX::SimpleMath::Vector3 _pivot);

private:

	void CamNormalMode();
	void CamArcBallMode();

	InputCommands						m_InputCommands; // Local input commands
	float								m_movespeed; // Variable for how fast the camera will move

	//camera
	DirectX::SimpleMath::Vector3		m_camPosition; // Camera position
	DirectX::SimpleMath::Vector3		m_camOrientation; // Camera orientation
	DirectX::SimpleMath::Vector3		m_camLookAt; // Point where camera is looking at
	DirectX::SimpleMath::Vector3		m_camLookDirection; // The direction the camera is looking at
	DirectX::SimpleMath::Vector3		m_camRight; // Camera right vector (used for moving sideways)
	DirectX::SimpleMath::Vector3        m_camUp; // Camera up vector (for moving up relative to the camera's look direction
	float m_normalCamRotRate; // Camera's rotation rate for when it is in free view
	float m_arcballCamRotRate; // Camera's rotation rate for when it is in arcball mode

	DirectX::SimpleMath::Matrix         m_view; // Camera view matrix

	int m_mousePosXOne; // Current mouse x position
	int m_mousePosXTwo; // Last frame's x position of mouse
	int m_mousePosYOne; // Current mouse y position
	int m_mousePosYTwo; // Last frame's y position of mouse

	DirectX::SimpleMath::Vector3 m_pivot; // Position for where the camera is going to pivot around
	bool m_isReset; // Bool variable for if the arcball position is reset or not (explained in .cpp)
};

