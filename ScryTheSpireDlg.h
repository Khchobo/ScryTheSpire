// ScryTheSpireDlg.h : The header file for the CDHtmlDialog used in the application.

#pragma once

enum AppState
{
	AS_WAITING_FOR_WINDOW,
	AS_WAITING_FOR_CARDS,
	AS_CARDS_FOUND,
	AS_ERROR
};

// CScryTheSpireDlg dialog
class CScryTheSpireDlg : public CDHtmlDialog
{
// Construction
public:
	CScryTheSpireDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCRYTHESPIRE_DIALOG, IDH = IDR_HTML_SCRYTHESPIRE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

	// Prevent ActiveX from complaining
	BOOL IsExternalDispatchSafe() { return TRUE; }

	AppState GetCurrentState();

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	// Store state of App
	AppState m_appState;

	DECLARE_DISPATCH_MAP()
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
