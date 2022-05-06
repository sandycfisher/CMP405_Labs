#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
	//functional
	m_movespeed = 0.3f;
	m_normalCamRotRate = 0.5f;
	m_arcballCamRotRate = 0.5f;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;
	
	m_mousePosXOne = 0;
	m_mousePosXTwo = 0;
	m_mousePosYOne = 0;
	m_mousePosYTwo = 0;

	m_pivot = Vector3(0, 0, 0);
}

Camera::~Camera()
{

}

void Camera::Update(DX::StepTimer const& timer)
{
	m_mousePosXTwo = m_mousePosXOne;
	m_mousePosXOne = m_InputCommands.mouse_X;
	m_mousePosYTwo = m_mousePosYOne;
	m_mousePosYOne = m_InputCommands.mouse_Y;

	if (m_InputCommands.mouse_MB_Down)
		CamArcBallMode();
	else
		CamNormalMode();


}

void Camera::Tick(InputCommands* Input)
{
	m_InputCommands = *Input;
}

Matrix Camera::GetViewMatrix()
{
	return m_view;
}

void Camera::CamNormalMode()
{
	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
	//camera motion is on a plane, so kill the 7 component of the look direction
	if (m_InputCommands.mouse_RB_Down)
	{
		int xChange = m_mousePosXTwo - m_mousePosXOne;
		m_camOrientation.y += xChange * m_normalCamRotRate;

		int yChange = m_mousePosYTwo - m_mousePosYOne;
		m_camOrientation.x += yChange * m_normalCamRotRate;
	}

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);
	m_camLookDirection.Cross(m_camRight, m_camUp);



	//process input and update stuff

	if (m_InputCommands.forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (m_InputCommands.back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}

	if (m_InputCommands.up)
	{
		m_camPosition += m_camUp * m_movespeed;
	}
	if (m_InputCommands.down)
	{
		m_camPosition -= m_camUp * m_movespeed;
	}

	if (m_InputCommands.right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (m_InputCommands.left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}


	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	//apply camera vectors
	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}

void Camera::CamArcBallMode()
{

	int xChange = m_mousePosXTwo - m_mousePosXOne;
	int yChange = m_mousePosYTwo - m_mousePosYOne;

	m_camOrientation.y = xChange * m_arcballCamRotRate;
	m_camOrientation.x = yChange * m_arcballCamRotRate;

	m_camLookDirection = m_pivot;

	Matrix camPosMatrix = camPosMatrix.CreateTranslation((m_pivot + m_camPosition));
	Matrix camRotXMatrix = camRotXMatrix.CreateRotationX((m_camOrientation.x * 3.1415 / 180));
	Matrix camRotYMatrix = camRotYMatrix.CreateRotationY((m_camOrientation.y * 3.1415 / 180));

	Matrix finalMatrix = Matrix::Identity;
	finalMatrix = finalMatrix * camPosMatrix * camRotXMatrix * camRotYMatrix;

	m_camPosition = Vector3(finalMatrix._41, finalMatrix._42, finalMatrix._43);

	m_camLookAt = m_pivot;

	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
	
	m_camPosition = m_camPosition - m_pivot;
}

Vector3 Camera::GetCamPosition()
{
	return m_camPosition;
}

void Camera::SetPivot(DirectX::SimpleMath::Vector3 _pivot)
{
	m_pivot = _pivot;
}