
// ScreenGrapDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CScreenGrapDlg 对话框
UINT ThreadFunc(LPVOID pParam);
class CScreenGrapDlg : public CDialogEx
{
// 构造
public:
	CScreenGrapDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCREENGRAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HICON my_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	

public:
	bool m_IsPath;//判断是否设置保持路径
	BOOL m_IsTime;	//是否保存完一帧
	CString Path;
	CButton CB_EXIT;
	CButton CB_START;
	CButton CB_SUSPEND;
	CButton CB_STOP;
	CButton CB_ROUTE;
	CEdit CE_ROUTE;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool GrapScreen();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnTimer(UINT nTimerID);

};
