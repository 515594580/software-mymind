// ChangeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OurMindClient.h"
#include "OurMindClientDlg.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"

#include "LandDlg.h"


// ChangeDlg 对话框

IMPLEMENT_DYNAMIC(ChangeDlg, CDialogEx)

ChangeDlg::ChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangeDlg::IDD, pParent)
{

}

ChangeDlg::~ChangeDlg()
{
}

void ChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChangeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChangeDlg 消息处理程序


void ChangeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//获取输入字符串
	GetDlgItemText(IDC_EDIT_PW, Password);
	GetDlgItemText(IDC_EDIT_PW2, Password2);
	GetDlgItemText(IDC_EDIT_PW3, Password3);
	
	if(LandDlg::StringRule(Password)==0)
	{
		MessageBox(L"密码不合法", L"NO", MB_OK);
		return;
	}
	if(LandDlg::StringRule(Password2)==0)
	{
		MessageBox(L"新密码不合法", L"NO", MB_OK);
		return;
	}
	if(Password2!=Password3)
	{
		MessageBox(L"密码不一致", L"NO", MB_OK);
		return;
	}
	
	//连接服务器检验
	PacketType type = ChangeConnect(g_UserId, Password, Password2);
	if(type==error)
	{
		MessageBox(L"服务器错误", L"NO", MB_OK);
		return;
	}
	else if(type==fail)
	{
		MessageBox(L"用户名已存在", L"NO", MB_OK);
		return;
	}
	else if(type!=success)
		assert(0);

	//返回

	CDialogEx::OnOK();
}
