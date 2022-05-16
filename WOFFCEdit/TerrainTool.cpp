#include "stdafx.h"
#include "TerrainTool.h"

IMPLEMENT_DYNAMIC(TerrainTool, CDialogEx)

BEGIN_MESSAGE_MAP(TerrainTool, CDialogEx)
	ON_COMMAND(IDOK, &TerrainTool::End) //ok button
	ON_COMMAND(IDCANCEL, &TerrainTool::End)
	ON_BN_CLICKED(IDC_CHECK1, &TerrainTool::SetHeightenDirectionUp)
	ON_BN_CLICKED(IDC_CHECK2, &TerrainTool::SetHeightenDirectionDown)
	ON_EN_CHANGE(IDC_EDIT1, &TerrainTool::SetBrushPosX)
	ON_EN_CHANGE(IDC_EDIT2, &TerrainTool::SetBrushPosY)
END_MESSAGE_MAP()

TerrainTool::TerrainTool(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG3, pParent)
{
	// Set variable to default
	m_isTerrainMode = false;
	m_isChunkNeedingUpdated = false;
	m_brushPosX = 64;
	m_brushPosY = 64;
	m_xChange = 0;
	m_yChange = 0;
	m_sensitivity = 0.05f;
}

TerrainTool::~TerrainTool()
{

}

///pass through pointers to the data in the tool we want to manipulate
void TerrainTool::SetObjectData()
{
	// Set variables to default
	m_isTerrainMode = false;
	m_isChunkNeedingUpdated = false;

	std::wstring posXTextEntry = std::to_wstring(m_brushPosX);
	SetDlgItemText(IDC_EDIT1, posXTextEntry.c_str());

	std::wstring posYTextEntry = std::to_wstring(m_brushPosY);
	SetDlgItemText(IDC_EDIT2, posYTextEntry.c_str());
}

void TerrainTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, m_listBox);

	DDX_Control(pDX, IDC_CHECK1, m_checkBox1); // Set check box 1
	DDX_Control(pDX, IDC_CHECK2, m_checkBox2); // Set check box 2
}

void TerrainTool::Tick(InputCommands* Input)
{
	m_InputCommands = *Input; // Update input

	m_mousePosXTwo = m_mousePosXOne; // Set old mouse x position
	m_mousePosXOne = m_InputCommands.mouse_X; // Set new mouse x position
	m_mousePosYTwo = m_mousePosYOne; // Set old mouse y position
	m_mousePosYOne = m_InputCommands.mouse_Y; // Set new mouse y position

	if (m_InputCommands.mouse_LB_Down && m_isTerrainMode) // If the left mouse button is down and the terrain manipulation mode is set to true
	{
		m_xChange += (m_mousePosXTwo - m_mousePosXOne) * m_sensitivity; // Find out the change in mouse x position and alter to appropriate sensitivity
		m_yChange += (m_mousePosYTwo - m_mousePosYOne) * m_sensitivity; // Find out the change in mouse y position and alter to appropriate sensitivity
	}
}

void TerrainTool::End()
{
	m_isTerrainMode = false; // Set terrain manipulation mode to false
	DestroyWindow();	//destroy the window properly.  Including the links and pointers created.  This is so the dialogue can start again. 
}

void TerrainTool::SetHeightenDirectionUp()
{
	if (m_checkBox1.GetCheck() == 1) // If the check box is checked
	{
		m_isDirectionUp = true; // Set upwards manipulation to true
		m_isTerrainMode = true; // Set terrain manipulation mode to true
	}
	else
	{
		m_isTerrainMode = false; // Set terrain manipulation mode to false
	}

	m_checkBox2.SetCheck(0); // Set downwards direction check box to be unchecked so as to not confuse the user
}

void TerrainTool::SetHeightenDirectionDown()
{
	if (m_checkBox2.GetCheck() == 1) // If the check box is checked
	{
		m_isDirectionUp = false; // Set upwards manipulation to false (downwards)
		m_isTerrainMode = true; // Set terrain manipulation mode to true
	}
	else
	{
		m_isTerrainMode = false; // Set terrain manipulation mode to false
	}

	m_checkBox1.SetCheck(0); // Set upwards direction check box to be unchecked so as to not confuse the user
}

void TerrainTool::SetBrushPosX()
{
	CString tempText; // Declare text variable
	GetDlgItemText(IDC_EDIT1, tempText); // Read text of the edit controls

	m_brushPosX = _ttoi(tempText); // Convert text to integer and set the brush x position to the converted int
	m_xChange = 0.0f; // Set the mouse x change back to 0
}

void TerrainTool::SetBrushPosY()
{
	CString tempText; // Declare text variable
	GetDlgItemText(IDC_EDIT2, tempText); // Read text of the edit controls

	m_brushPosY = _ttoi(tempText); // Convert text to integer and set the brush y position to the converted int
	m_yChange = 0.0f; // Set the mouse y change back to 0
}