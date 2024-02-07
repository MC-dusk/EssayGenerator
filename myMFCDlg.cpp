//#include "EssayGenerator.h"
#include <ctime>

// myMFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "myMFC.h"
#include "myMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "gbk2utf8.h" // 这一条include不能放前面，只能放后面，也不能放在头文件，不然会报link2005和link1169重定义错误，很坑，原理不明

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CmyMFCDlg 对话框



CmyMFCDlg::CmyMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmyMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CmyMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CmyMFCDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CmyMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CmyMFCDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CmyMFCDlg 消息处理程序

BOOL CmyMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	// 初始化编辑框的值
	SetDlgItemText(IDC_EDIT1, _T("就业"));
	SetDlgItemText(IDC_EDIT2, _T("500"));
	SetDlgItemText(IDC_EDIT3, _T("使用指南：\r\n在上方分别输入主题和字数，已经置入默认值，可以直接点击生成\r\n点击复制，复制到剪贴板\r\n点击保存，保存markdown文件到程序所在路径"));

	//SetWindowText(L"DZY");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmyMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmyMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmyMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ProcessInput(const CString& strInput1, const CString& strInput2, CString& strOutput)
{
	//strOutput = strInput1 + strInput2;

	strOutput.Empty(); // 清空输出
	ifstream file("data.json");
	if (file.is_open()) file.close();
	else
	{
		strOutput = L"请提供data.json";
		return;
	}
	EssayGenerator generator("./data.json"); // 读取json
	if (strInput1.IsEmpty() || strInput2.IsEmpty()) // 非法输入，退出
	{
		strOutput = generator.error(1).c_str();
		return;
	}
	string theme1 = GbkToUtf8(CStringA(strInput1)); // 读取主题输入，gbk转utf8
	int essay_num1 = _ttoi(strInput2);
	if (essay_num1 < 300)
	{
		strOutput = generator.error(2).c_str(); // 非法输入，退出
		return;
	}
	if (essay_num1 > 20000)
	{
		strOutput = generator.error(3).c_str(); // 非法输入，退出
		return;
	}
	size_t begin_num = (size_t)(essay_num1 * 0.5); // 文章各部分长度
	size_t body_num = (size_t)(essay_num1 * 1);
	size_t end_num = begin_num;
	string outTemp, newline= "\r\n\r\n";

	string title = generator.get_title(theme1); // 输出标题
	outTemp += "# ";
	outTemp += title;
	outTemp += newline;
	string beginning; // 输出开头
	while (beginning.size() < begin_num)
	{
		beginning += generator.get_beginning(theme1);
	}
	outTemp += beginning;
	outTemp += newline;
	string body; // 输出中部
	while (body.size() < body_num)
	{
		body += generator.get_body(theme1);
	}
	outTemp += body;
	outTemp += newline;
	string ending; // 输出结尾
	while (ending.size() < end_num)
	{
		ending += generator.get_ending(theme1);
	}
	outTemp += ending;
	outTemp += newline;

	strOutput = Utf8ToGbk(outTemp.c_str()).c_str(); // string类型的输出，utf8转gbk，手动转char*类型，再自动转CString

	return; // 运行结束
}

void CmyMFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 从编辑框中读取值
	GetDlgItemText(IDC_EDIT1, m_strInput1);
	GetDlgItemText(IDC_EDIT2, m_strInput2);

	// 处理输入并保存到输出变量中
	ProcessInput(m_strInput1, m_strInput2, m_strOutput);

	// 将输出变量中的值显示到编辑框中
	SetDlgItemText(IDC_EDIT3, m_strOutput);
}


void CmyMFCDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	// 退出
	CDialogEx::OnCancel();
}


void CmyMFCDlg::OnBnClickedButton2()
{
	if (!OpenClipboard())
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	// Remove the current Clipboard contents
	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"));
		return;
	}
	size_t sizeInWords = (m_strOutput.GetLength() + 1); // 分配内存用sizeInBytes，宽字符复制用sizeInWords
	size_t sizeInBytes = sizeInWords * sizeof(TCHAR);
	// Get the currently selected data
	HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, sizeInBytes);
	if (hGlob != NULL) // 内存分配成功
	{
		_tcscpy_s((TCHAR*)hGlob, sizeInWords, m_strOutput);
		// For the appropriate data formats...
		if (::SetClipboardData(CF_UNICODETEXT, hGlob) == NULL)
		{
			CString msg;
			msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
			AfxMessageBox(msg);
			CloseClipboard();
			GlobalFree(hGlob);
			return;
		}
	}
	CloseClipboard();
}


void CmyMFCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	std::time_t timestamp = std::time(nullptr);
	wstring fileName = L"主题：" + CStringW(m_strInput1) + L"，字数：" + CStringW(m_strInput2) + L"，时间：";
	fileName += to_wstring(timestamp);
	if (fileName.empty()) return;
	fileName += L".md";

	//ofstream outfile; // 不用wofstream是不行的，但如果用了，前面string就都得改wstring
	//outfile.open(fileName.c_str());
	//int len = m_strOutput.GetLength()*sizeof(wchar_t);
	//string out((char*)m_strOutput.GetString(), len);
	//outfile.write(out.c_str(), len);
	//outfile.close();

	ofstream outfile;
	outfile.open(fileName.c_str(), ios::binary); // 必须二进制模式，否则自动补\r导致双重换行
	CStringA out(m_strOutput);
	outfile.write(out, out.GetLength());
	outfile.close();

	//CFile outfile; // MFC的类，写入访问失败，不知道为什么
	//outfile.Open(fileName.c_str(), CFile::modeCreate | CFile::typeUnicode);
	//outfile.Write(m_strOutput, m_strOutput.GetLength());
	//outfile.Close();
}
