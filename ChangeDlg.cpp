// ChangeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OurMindClient.h"
#include "OurMindClientDlg.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"

#include "LandDlg.h"


// ChangeDlg �Ի���

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


// ChangeDlg ��Ϣ�������


void ChangeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//��ȡ�����ַ���
	GetDlgItemText(IDC_EDIT_PW, Password);
	GetDlgItemText(IDC_EDIT_PW2, Password2);
	GetDlgItemText(IDC_EDIT_PW3, Password3);
	
	if(LandDlg::StringRule(Password)==0)
	{
		MessageBox(L"���벻�Ϸ�", L"NO", MB_OK);
		return;
	}
	if(LandDlg::StringRule(Password2)==0)
	{
		MessageBox(L"�����벻�Ϸ�", L"NO", MB_OK);
		return;
	}
	if(Password2!=Password3)
	{
		MessageBox(L"���벻һ��", L"NO", MB_OK);
		return;
	}
	
	//���ӷ���������
	PacketType type = ChangeConnect(g_UserId, Password, Password2);
	if(type==error)
	{
		MessageBox(L"����������", L"NO", MB_OK);
		return;
	}
	else if(type==fail)
	{
		MessageBox(L"�û����Ѵ���", L"NO", MB_OK);
		return;
	}
	else if(type!=success)
		assert(0);

	//����

	CDialogEx::OnOK();
}
