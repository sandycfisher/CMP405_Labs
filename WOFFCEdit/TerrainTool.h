#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "InputCommands.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>


class TerrainTool : public CDialogEx
{
	DECLARE_DYNAMIC(TerrainTool)

public:
	TerrainTool(CWnd* pParent = NULL);
	virtual ~TerrainTool();
	void SetObjectData();
	void Tick(InputCommands* Input);

	bool m_isTerrainMode; // Boolean for if the terrain tool is meant to be manipulating the terrain right now
	bool m_isChunkNeedingUpdated; // Boolean for if the height map needs updated
	bool m_isDirectionUp; // Boolean for if the terrain is being manipulated upwards or downwards

	float m_brushPosX; // X position of the brush
	float m_brushPosY; // Y position of the brush
	float m_xChange; // X change of the mouse position
	float m_yChange; // Y change of the mouse position


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End(); // Destroy dialog box
	afx_msg void SetHeightenDirectionUp(); // Change check box for upward terrain manipulation
	afx_msg void SetHeightenDirectionDown(); // Change check box for downward terrain manipulation
	afx_msg void SetBrushPosX(); // Change brush x position in edit controls
	afx_msg void SetBrushPosY(); // Change brush y positoin in edit controls

	InputCommands m_InputCommands; // Local input commands variable

	int m_mousePosXOne; // Current mouse x position
	int m_mousePosXTwo; // Last frame's mouse x position
	int m_mousePosYOne; // Current mouse y position
	int m_mousePosYTwo; // Last frame's mouse y position
	float m_sensitivity; // Mouse sensitivity variable

	DECLARE_MESSAGE_MAP()


	CButton m_checkBox1; // Check box for upwards manipulation
	CButton m_checkBox2; // Check box for downwards manipulation
public:


};

