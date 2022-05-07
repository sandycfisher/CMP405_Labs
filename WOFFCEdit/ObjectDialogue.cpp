#include "stdafx.h"
#include "ObjectDialogue.h"

IMPLEMENT_DYNAMIC(ObjectDialogue, CDialogEx)

BEGIN_MESSAGE_MAP(ObjectDialogue, CDialogEx)
	ON_COMMAND(IDOK, &ObjectDialogue::End) //ok button
	ON_EN_UPDATE(IDC_EDIT1, &ObjectDialogue::SetObjectPosX)
	ON_EN_CHANGE(IDC_EDIT2, &ObjectDialogue::SetObjectPosY)
	ON_EN_CHANGE(IDC_EDIT3, &ObjectDialogue::SetObjectPosZ)
	ON_EN_CHANGE(IDC_EDIT4, &ObjectDialogue::SetObjectRotX)
	ON_EN_CHANGE(IDC_EDIT5, &ObjectDialogue::SetObjectRotY)
	ON_EN_CHANGE(IDC_EDIT6, &ObjectDialogue::SetObjectRotZ)
	ON_EN_CHANGE(IDC_EDIT7, &ObjectDialogue::SetObjectScaleX)
	ON_EN_CHANGE(IDC_EDIT8, &ObjectDialogue::SetObjectScaleY)
	ON_EN_CHANGE(IDC_EDIT9, &ObjectDialogue::SetObjectScaleZ)
END_MESSAGE_MAP()

ObjectDialogue::ObjectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph)		//constructor used in modal
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_sceneGraph = SceneGraph;
	m_isObjectManipulationMode = true;
	m_isListNeedingUpdated = false;
}

ObjectDialogue::ObjectDialogue(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_isObjectManipulationMode = true;
	m_isListNeedingUpdated = false;
}

ObjectDialogue::~ObjectDialogue()
{

}

///pass through pointers to the data in the tool we want to manipulate
void ObjectDialogue::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection)
{
	m_isObjectManipulationMode = true;
	m_isListNeedingUpdated = false;
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;

	std::wstring staticTextEntry = L"Selected Object ID: " + std::to_wstring(*m_currentSelection);
	SetDlgItemText(IDC_STATIC1_, staticTextEntry.c_str());

	int posX = m_sceneGraph->at(*m_currentSelection).posX;
	std::wstring posXTextEntry = std::to_wstring(posX);
	SetDlgItemText(1003, posXTextEntry.c_str());

	int posY = m_sceneGraph->at(*m_currentSelection).posY;
	std::wstring posYTextEntry = std::to_wstring(posY);
	SetDlgItemText(IDC_EDIT2, posYTextEntry.c_str());

	int posZ = m_sceneGraph->at(*m_currentSelection).posZ;
	std::wstring posZTextEntry = std::to_wstring(posZ);
	SetDlgItemText(IDC_EDIT3, posZTextEntry.c_str());

	int rotX = m_sceneGraph->at(*m_currentSelection).rotX;
	std::wstring rotXTextEntry = std::to_wstring(rotX);
	SetDlgItemText(IDC_EDIT4, rotXTextEntry.c_str());

	int rotY = m_sceneGraph->at(*m_currentSelection).rotY;
	std::wstring rotYTextEntry = std::to_wstring(rotY);
	SetDlgItemText(IDC_EDIT5, rotYTextEntry.c_str());

	int rotZ = m_sceneGraph->at(*m_currentSelection).rotZ;
	std::wstring rotZTextEntry = std::to_wstring(rotZ);
	SetDlgItemText(IDC_EDIT6, rotZTextEntry.c_str());

	int scaleX = m_sceneGraph->at(*m_currentSelection).scaX;
	std::wstring scaleXTextEntry = std::to_wstring(scaleX);
	SetDlgItemText(IDC_EDIT7, scaleXTextEntry.c_str());

	int scaleY = m_sceneGraph->at(*m_currentSelection).scaY;
	std::wstring scaleYTextEntry = std::to_wstring(scaleY);
	SetDlgItemText(IDC_EDIT8, scaleYTextEntry.c_str());

	int scaleZ = m_sceneGraph->at(*m_currentSelection).scaZ;
	std::wstring scaleZTextEntry = std::to_wstring(scaleZ);
	SetDlgItemText(IDC_EDIT9, scaleZTextEntry.c_str());
}

void ObjectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1_, m_static);
}

void ObjectDialogue::End()
{
	m_isObjectManipulationMode = false;
	DestroyWindow();	//destroy the window properly.  Including the links and pointers created.  This is so the dialogue can start again. 
}

void ObjectDialogue::SetObjectPosX()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT1, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).posX = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectPosY()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT2, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).posY = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectPosZ()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT3, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).posZ = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectRotX()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT4, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).rotX = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectRotY()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT5, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).rotY = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectRotZ()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT6, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).rotZ = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectScaleX()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT7, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).scaX = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectScaleY()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT8, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).scaY = tempNum;
	m_isListNeedingUpdated = true;
}

void ObjectDialogue::SetObjectScaleZ()
{
	CString tempText;
	GetDlgItemText(IDC_EDIT9, tempText);

	float tempNum = _ttoi(tempText);
	m_sceneGraph->at(*m_currentSelection).scaZ = tempNum;
	m_isListNeedingUpdated = true;
}