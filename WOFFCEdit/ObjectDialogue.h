#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>


class ObjectDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectDialogue)

public:
	ObjectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph);
	ObjectDialogue(CWnd* pParent = NULL);
	virtual ~ObjectDialogue();
	void SetObjectData(std::vector<SceneObject>* SceneGraph, int* Selection);

	bool m_isObjectManipulationMode; // Boolean for if the object is being manipulated or not
	bool m_isListNeedingUpdated; // Boolean for when the object needs to change its visual position, rotation or scale

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End(); // Destroys dialog box

	afx_msg void SetObjectPosX(); // Sets the object position for each axis
	afx_msg void SetObjectPosY();
	afx_msg void SetObjectPosZ();

	afx_msg void SetObjectRotX(); // Sets the object rotation for each axis
	afx_msg void SetObjectRotY();
	afx_msg void SetObjectRotZ();

	afx_msg void SetObjectScaleX(); // Sets the object scale for each axis
	afx_msg void SetObjectScaleY();
	afx_msg void SetObjectScaleZ();

	std::vector<SceneObject>* m_sceneGraph; 
	int* m_currentSelection; // Currently selected object

	DECLARE_MESSAGE_MAP()

public:
};

