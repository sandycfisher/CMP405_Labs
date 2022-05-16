#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
	// Setting movement rate variables
	m_movespeed = 0.3f;
	m_normalCamRotRate = 0.5f;
	m_arcballCamRotRate = 0.75f;

	// Setting position
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;
	
	// Setting orientation
	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	// Setting look at
	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	// Setting look direction
	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	// Setting right vector
	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;
	
	// Setting mouse pos'
	m_mousePosXOne = 0;
	m_mousePosXTwo = 0;
	m_mousePosYOne = 0;
	m_mousePosYTwo = 0;

	// Setting arcball variables
	m_pivot = Vector3(0, 0, 0);
	m_isReset = false;
}

Camera::~Camera()
{

}

void Camera::Update(DX::StepTimer const& timer)
{
	m_mousePosXTwo = m_mousePosXOne; // Set previous mouse x to be current mouse x before it is replaced
	m_mousePosXOne = m_InputCommands.mouse_X; // Update the current mouse x pos
	m_mousePosYTwo = m_mousePosYOne; // Set previous mouse y to be current mouse y before it is replaced
	m_mousePosYOne = m_InputCommands.mouse_Y; // Update the current mouse y pos

	if (m_isReset == true && m_InputCommands.mouse_MB_Down == false) // If the arcball camera is needing reset and the middle mouse button is down
		CamArcBallMode(); // Go through one more loop of the arcball camera to reset it
	

	if (m_InputCommands.mouse_MB_Down) // If the middle mouse button is down
		CamArcBallMode(); // Do arcball functionality
	else // If not
		CamNormalMode(); // Do free view functionality


}

void Camera::Tick(InputCommands* Input)
{
	m_InputCommands = *Input; // Update input
}

Matrix Camera::GetViewMatrix()
{
	return m_view;
}

void Camera::CamNormalMode()
{
	if (m_InputCommands.mouse_RB_Down) // If the right mouse button is down
	{
		int xChange = m_mousePosXTwo - m_mousePosXOne; // Find out the difference in movement for the mouse's x position
		m_camOrientation.y += xChange * m_normalCamRotRate; // Change orientation accordingly

		int yChange = m_mousePosYTwo - m_mousePosYOne; // Find out the difference in movement for the mouse's y position
		m_camOrientation.x += yChange * m_normalCamRotRate; // Change orientation accordingly
	}

	// Create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.Normalize(); // Normalise values

	// Create right and up vectors from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);
	m_camLookDirection.Cross(m_camRight, m_camUp);



	//process input and update position
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

	int xChange = m_mousePosXTwo - m_mousePosXOne; // Find out the difference in movement for the mouse's x position
	int yChange = m_mousePosYTwo - m_mousePosYOne; // Find out the difference in movement for the mouse's y position

	// Change orientation accordingly
	m_camOrientation.y = xChange * m_arcballCamRotRate;
	m_camOrientation.x = yChange * m_arcballCamRotRate;

	m_camLookDirection = m_pivot; // Set the look direction to be the pivot's location

	Matrix camPosMatrix = camPosMatrix.CreateTranslation((m_pivot + m_camPosition)); // Create translation matrix by creating a vector from the camera and pivot's position
	Matrix camRotXMatrix = camRotXMatrix.CreateRotationX((m_camOrientation.x * 3.1415 / 180)); // Create a rotation in the x direction using the x value of the camera orientation
	Matrix camRotYMatrix = camRotYMatrix.CreateRotationY((m_camOrientation.y * 3.1415 / 180)); // Create a rotation in the y direction using the y value of the camera orientation

	Matrix finalMatrix = Matrix::Identity; // Create final multiplication matrix
	finalMatrix = finalMatrix * camPosMatrix * camRotXMatrix * camRotYMatrix; // Multiply matrices in appropriate order. TRANSLATE FIRST THEN ROTATE TO CREATE THE ARCBALL EFFECT

	m_camPosition = Vector3(finalMatrix._41, finalMatrix._42, finalMatrix._43); // Update the camera's position to be the values from the matrix

	m_camLookAt = m_pivot; // Set the camera look at to be the pivot

	// This is here so that the arcball camera remains at the right distance from where it started. This is because the following lines flip the camera position in order for it to be 
	// at the right position. So in order for the user to see the camera only when the camera is not flipped the view matrix is only updated every second frame. This does half the frame 
	// rate of the camera, but I couldn't find a better solution... :/
	if (m_isReset == false)
	{
		m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
	}

	m_camPosition = m_pivot - m_camPosition; // Set camera position to be flipped or unflipped depending on the state

	m_isReset = !m_isReset; // Change the boolean variable to see if the view matrix will be updated next frame
}

Vector3 Camera::GetCamPosition()
{
	return m_camPosition;
}

void Camera::SetPivot(DirectX::SimpleMath::Vector3 _pivot)
{
	m_pivot = _pivot;
}

Vector3 Camera::GetPivot()
{
	return m_pivot;
}