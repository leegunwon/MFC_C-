
// con2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "con2.h"
#include "con2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ccon2Dlg 대화 상자



Ccon2Dlg::Ccon2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CON2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccon2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RED, m_EditRed);
	DDX_Control(pDX, IDC_EDIT_GREEN, m_EditGreen);
	DDX_Control(pDX, IDC_EDIT_BLUE, m_EditBlue);
	DDX_Control(pDX, IDC_SCROLLBAR_RED, m_ScrollbarRed);
	DDX_Control(pDX, IDC_SCROLLBAR_GREEN, m_ScrollbarGreen);
	DDX_Control(pDX, IDC_SCROLLBAR_BLUE, m_ScrollbarBlue);
}

BEGIN_MESSAGE_MAP(Ccon2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Ccon2Dlg 메시지 처리기

BOOL Ccon2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ScrollbarRed.SetScrollRange(0, 255, FALSE);
	m_ScrollbarGreen.SetScrollRange(0, 255, FALSE);
	m_ScrollbarBlue.SetScrollRange(0, 255, FALSE);
	m_ScrollbarRed.SetScrollPos(255);
	m_ScrollbarGreen.SetScrollPos(0);
	m_ScrollbarBlue.SetScrollPos(0);

	GetDlgItem(IDC_STATIC_PICTURE)->GetWindowRect(&m_rectPic);
	//GetWindowRect은화면전체에서위치값을계산하기때문에
	//이를 클라이언트 영역 좌표로 재계산하여 멤버 변수 m_rectPic에 저장한다.
	ScreenToClient(&m_rectPic);
	ChangeColor();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Ccon2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Ccon2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		//브러시를 생성해서 dc가 선택하도록 한다.
		CBrush NewBrush, * oldBrush;
		NewBrush.CreateSolidBrush(m_rectColor);
		oldBrush = dc.SelectObject(&NewBrush);
		//픽쳐 컨트롤에 사각형을 그린다.
		dc.Rectangle(&m_rectPic);
		//브러시를 원상 복구한다. 
		dc.SelectObject(oldBrush);
		//사용 후에는 브러시를 소멸시킨다 .
		NewBrush.DeleteObject();
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Ccon2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

