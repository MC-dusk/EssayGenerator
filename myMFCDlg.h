#include "EssayGenerator.h"
//#include "gbk2utf8.h"

// myMFCDlg.h: 头文件
//

#pragma once


// CmyMFCDlg 对话框
class CmyMFCDlg : public CDialogEx
{
// 构造
public:
	CmyMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CString m_strInput1;  // 保存从编辑框中读取的值
	CString m_strInput2;  // 保存从编辑框中读取的值
	CString m_strOutput; // 保存处理后的值

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
