#include "stdafx.h"
#include "ObjectDialogue.h"

IMPLEMENT_DYNAMIC(ObjectDialogue, CDialogEx)

BEGIN_MESSAGE_MAP(ObjectDialogue, CDialogEx)
	ON_COMMAND(IDOK, &ObjectDialogue::End) //ok button
	ON_COMMAND(IDCANCEL, &ObjectDialogue::End)
	ON_EN_CHANGE(IDC_EDIT1, &ObjectDialogue::SetObjectPosX) // Setup each editable controls to the appropriate function
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
	m_isObjectManipulationMode = true; // Set the manipulation mode to true as soon as the dialog box opens
	m_isListNeedingUpdated = false; // Set the object list needing updated to false
}

ObjectDialogue::ObjectDialogue(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_isObjectManipulationMode = true; // Set the manipulation mode to true as soon as the dialog box opens
	m_isListNeedingUpdated = false; // Set the object list needing updated to false
}

ObjectDialogue::~ObjectDialogue()
{

}

///pass through pointers to the data in the tool we want to manipulate
void ObjectDialogue::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection)
{
	m_isObjectManipulationMode = true; // Set the manipulation mode to true as soon as the dialog box opens
	m_isListNeedingUpdated = false; // Set the object list needing updated to false
	m_sceneGraph = SceneGraph; // Set scene graph variable
	m_currentSelection = selection; // Set currently selected object id

	std::wstring staticTextEntry = L"Selected Object ID: " + std::to_wstring(*m_currentSelection); // Set the text to show the currently selected object's id
	SetDlgItemText(IDC_STATIC1_, staticTextEntry.c_str());

	// Show the object's current x position
	int posX = m_sceneGraph->at(*m_currentSelection).posX;
	std::wstring posXTextEntry = std::to_wstring(posX);
	SetDlgItemText(1003, posXTextEntry.c_str());

	// Show the object's current y position
	int posY = m_sceneGraph->at(*m_currentSelection).posY;
	std::wstring posYTextEntry = std::to_wstring(posY);
	SetDlgItemText(IDC_EDIT2, posYTextEntry.c_str());

	// Show the object's current z position
	int posZ = m_sceneGraph->at(*m_currentSelection).posZ;
	std::wstring posZTextEntry = std::to_wstring(posZ);
	SetDlgItemText(IDC_EDIT3, posZTextEntry.c_str());

	// Show the object's current x rotation
	int rotX = m_sceneGraph->at(*m_currentSelection).rotX;
	std::wstring rotXTextEntry = std::to_wstring(rotX);
	SetDlgItemText(IDC_EDIT4, rotXTextEntry.c_str());

	// Show the object's current y rotation
	int rotY = m_sceneGraph->at(*m_currentSelection).rotY;
	std::wstring rotYTextEntry = std::to_wstring(rotY);
	SetDlgItemText(IDC_EDIT5, rotYTextEntry.c_str());

	// Show the object's current z rotation
	int rotZ = m_sceneGraph->at(*m_currentSelection).rotZ;
	std::wstring rotZTextEntry = std::to_wstring(rotZ);
	SetDlgItemText(IDC_EDIT6, rotZTextEntry.c_str());

	// Show the object's current x scale
	int scaleX = m_sceneGraph->at(*m_currentSelection).scaX;
	std::wstring scaleXTextEntry = std::to_wstring(scaleX);
	SetDlgItemText(IDC_EDIT7, scaleXTextEntry.c_str());

	// Show the object's current y scale
	int scaleY = m_sceneGraph->at(*m_currentSelection).scaY;
	std::wstring scaleYTextEntry = std::to_wstring(scaleY);
	SetDlgItemText(IDC_EDIT8, scaleYTextEntry.c_str());

	// Show the object's current z scale
	int scaleZ = m_sceneGraph->at(*m_currentSelection).scaZ;
	std::wstring scaleZTextEntry = std::to_wstring(scaleZ);
	SetDlgItemText(IDC_EDIT9, scaleZTextEntry.c_str());
}

void ObjectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void ObjectDialogue::End()
{
	m_isObjectManipulationMode = false; // Set the object manipulation mode to false
	DestroyWindow();	//destroy the window properly.  Including the links and pointers created.  This is so the dialogue can start again. 
}

void ObjectDialogue::SetObjectPosX()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT1, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).posX = tempNum; // Set the object x position to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectPosY()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT2, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).posY = tempNum; // Set the object y position to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectPosZ()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT3, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).posZ = tempNum; // Set the object z position to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectRotX()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT4, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).rotX = tempNum; // Set the object x rotation to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectRotY()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT5, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).rotY = tempNum; // Set the object y rotation to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectRotZ()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT6, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).rotZ = tempNum; // Set the object z rotation to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectScaleX()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT7, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).scaX = tempNum; // Set the object x scale to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectScaleY()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT8, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).scaY = tempNum; // Set the object y scale to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}

void ObjectDialogue::SetObjectScaleZ()
{
	CString tempText; // Create text variable
	GetDlgItemText(IDC_EDIT9, tempText); // Read the current text in the editable control box

	float tempNum = _ttoi(tempText); // Set temp variable to be text in the editable control box
	m_sceneGraph->at(*m_currentSelection).scaZ = tempNum; // Set the object z scale to be what was in the box
	m_isListNeedingUpdated = true; // Set the list to be updated next frame
}