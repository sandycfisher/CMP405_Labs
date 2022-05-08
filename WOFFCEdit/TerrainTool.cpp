#include "stdafx.h"
#include "TerrainTool.h"

IMPLEMENT_DYNAMIC(TerrainTool, CDialogEx)

BEGIN_MESSAGE_MAP(TerrainTool, CDialogEx)
	ON_COMMAND(IDOK, &TerrainTool::End) //ok button
	ON_BN_CLICKED(IDC_CHECK1, &TerrainTool::SetHeightenDirectionUp)
	ON_BN_CLICKED(IDC_CHECK2, &TerrainTool::SetHeightenDirectionDown)
	ON_EN_CHANGE(IDC_EDIT1, &TerrainTool::SetBrushPosX)
	ON_EN_CHANGE(IDC_EDIT2, &TerrainTool::SetBrushPosY)
END_MESSAGE_MAP()

TerrainTool::TerrainTool(CWnd* pParent, std::vector<SceneObject>* SceneGraph)		//constructor used in modal
	: CDialogEx(IDD_DIALOG3, pParent)
{
	m_sceneGraph = SceneGraph;
	m_isTerrainMode = false;
	m_isChunkNeedingUpdated = false;
	m_brushPosX = 64;
	m_brushPosY = 64;
}

TerrainTool::TerrainTool(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG3, pParent)
{
	m_isTerrainMode = false;
	m_isChunkNeedingUpdated = false;
	m_brushPosX = 64;
	m_brushPosY = 64;
}

TerrainTool::~TerrainTool()
{

}

///pass through pointers to the data in the tool we want to manipulate
void TerrainTool::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection)
{
	m_isTerrainMode = false;
	m_isChunkNeedingUpdated = false;
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;

	std::wstring posXTextEntry = std::to_wstring(m_brushPosX);
	SetDlgItemText(IDC_EDIT1, posXTextEntry.c_str());

	std::wstring posYTextEntry = std::to_wstring(m_brushPosY);
	SetDlgItemText(IDC_EDIT2, posYTextEntry.c_str());
}

void TerrainTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, m_listBox);

	DDX_Control(pDX, IDC_CHECK1, m_checkBox1);
	DDX_Control(pDX, IDC_CHECK2, m_checkBox2);
}

void TerrainTool::End()
{
	m_isTerrainMode = false;
	DestroyWindow();	//destroy the window properly.  Including the links and pointers created.  This is so the dialogue can start again. 
}

void TerrainTool::SetHeightenDirectionUp()
{
	if (m_checkBox1.GetCheck() == 1)
	{
		m_isDirectionUp = true;
		m_isTerrainMode = true;
	}
	else
	{
		m_isTerrainMode = false;
	}

	m_checkBox2.SetCheck(0);
}

void TerrainTool::SetHeightenDirectionDown()
{
	if (m_checkBox2.GetCheck() == 1)
	{
		m_isDirectionUp = false;
		m_isTerrainMode = true;
	}
	else
	{
		m_isTerrainMode = false;
	}

	m_checkBox1.SetCheck(0);
}

void TerrainTool::SetBrushPosX()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT1, tempText);

	m_brushPosX = _ttof(tempText);
}

void TerrainTool::SetBrushPosY()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT2, tempText);

	m_brushPosY = _ttof(tempText);
}