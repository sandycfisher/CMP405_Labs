#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>


class TerrainTool : public CDialogEx
{
	DECLARE_DYNAMIC(TerrainTool)

public:
	TerrainTool(CWnd* pParent, std::vector<SceneObject>* SceneGraph);
	TerrainTool(CWnd* pParent = NULL);
	virtual ~TerrainTool();
	void SetObjectData(std::vector<SceneObject>* SceneGraph, int* Selection);

	bool m_isTerrainMode;
	bool m_isChunkNeedingUpdated;
	bool m_isDirectionUp;

	float m_brushPosX;
	float m_brushPosY;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();
	afx_msg void SetHeightenDirectionUp();
	afx_msg void SetHeightenDirectionDown();
	afx_msg void SetBrushPosX();
	afx_msg void SetBrushPosY();

	std::vector<SceneObject>* m_sceneGraph;
	int* m_currentSelection;

	DECLARE_MESSAGE_MAP()

public:

	CButton m_checkBox1;
	CButton m_checkBox2;
};

