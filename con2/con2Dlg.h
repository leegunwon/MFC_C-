
// con2Dlg.h: 헤더 파일
//

#pragma once


// Ccon2Dlg 대화 상자
class Ccon2Dlg : public CDialogEx
{
// 생성입니다.
public:
	Ccon2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CON2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditRed;
	CEdit m_EditGreen;
	CEdit m_EditBlue;
	CScrollBar m_ScrollbarRed;
	CScrollBar m_ScrollbarGreen;
	CScrollBar m_ScrollbarBlue;
	CRect m_rectPic;
	COLORREF m_rectColor;
	void ChangeColor();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
