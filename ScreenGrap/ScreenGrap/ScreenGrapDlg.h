
// ScreenGrapDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CScreenGrapDlg �Ի���
UINT ThreadFunc(LPVOID pParam);
class CScreenGrapDlg : public CDialogEx
{
// ����
public:
	CScreenGrapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCREENGRAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	HICON my_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	

public:
	bool m_IsPath;//�ж��Ƿ����ñ���·��
	BOOL m_IsTime;	//�Ƿ񱣴���һ֡
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
