
// MFCApplicationDBDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationDB.h"
#include "MFCApplicationDBDlg.h"
#include "afxdialogex.h"

//KHD 추가
#include "CMysqlController.h"
#include <string.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream> 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

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


// CMFCApplicationDBDlg 대화 상자



CMFCApplicationDBDlg::CMFCApplicationDBDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONDB_DIALOG, pParent)
	, m_BookName(_T(""))
	, m_author(_T(""))
	, m_other(_T(""))
	, m_price(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_BookName);
	DDX_Text(pDX, IDC_EDIT2, m_author);
	DDX_Text(pDX, IDC_EDIT4, m_other);
	DDX_Text(pDX, IDC_EDIT3, m_price);
	DDX_Control(pDX, IDC_LIST1, m_DataList);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplicationDBDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplicationDBDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplicationDBDlg 메시지 처리기

BOOL CMFCApplicationDBDlg::OnInitDialog()
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
	m_DataList.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 100);
	m_DataList.InsertColumn(1, _T("bookname"), LVCFMT_CENTER, 100);
	m_DataList.InsertColumn(2, _T("author"), LVCFMT_CENTER, 100);
	m_DataList.InsertColumn(3, _T("price"), LVCFMT_CENTER, 100);
	m_DataList.InsertColumn(4, _T("other"), LVCFMT_CENTER, 100);
	m_DataList.SetExtendedStyle(m_DataList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplicationDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplicationDBDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplicationDBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationDBDlg::OnBnClickedButton1()
{
	// cstring -> string -> stringstream
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMysqlController conn;
	CString result;
	string result_str;
	string line;
	stringstream result_stream;
	

	m_DataList.DeleteAllItems();
	
	if (conn.SelectQuery("select * from TB_Book", result) == true)
	{
		result_str = string(CT2CA(result));
		result_stream.str(result_str);

		while (getline(result_stream, line))
		{
			stringstream lineStream(line); //한줄의 데이터를 가지고 사용
			string cell;
			CString cell2;
			int count0 = m_DataList.GetItemCount();
			int count1 = 0;
			while (getline(lineStream, cell, ','))
			{
				cell2 = cell.c_str();
				
				if (count1 == 0)
				{
					m_DataList.InsertItem(count0, cell2);
				}
				else
				{
					m_DataList.SetItem(count0, count1, LVIF_TEXT, cell2, 0, 0,
						0, 0);
				}
				count1++;
			}
			

		}

		UpdateData(false);
		AfxMessageBox(result);
	}

}


void CMFCApplicationDBDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMysqlController conn;

	UpdateData(TRUE);
	char* send_data;
	CString result;
	result = "insert into TB_Book(bookname, author, price, other) VALUES('";
	result += (m_BookName + "','");
	result +=  m_author + "',";
	result += m_price + ",";
	result += m_other + ")";
	send_data = (LPSTR)(LPCSTR)result;

	if (conn.InsertQuery(send_data) == true)
	{
		AfxMessageBox(_T("성공"));
	}
	else
	{
		AfxMessageBox(_T("실패"));
	}
	
	UpdateData(FALSE);
}
