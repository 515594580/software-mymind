
// LandDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OurMindClient.h"
#include "LandDlg.h"
#include "afxdialogex.h"


// LandDlg �Ի���

IMPLEMENT_DYNAMIC(LandDlg, CDialogEx)

LandDlg::LandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LandDlg::IDD, pParent)
{

}

LandDlg::~LandDlg()
{
}

void LandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LandDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LandDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_LOGIN, &LandDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_REGIST, &LandDlg::OnBnClickedRegist)
END_MESSAGE_MAP()


// LandDlg ��Ϣ�������


void LandDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void LandDlg::OnBnClickedLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//��ȡ�����ַ���
	GetDlgItemText(IDC_EDIT_ID, UserId);
	GetDlgItemText(IDC_EDIT_PW, Password);

	if(StringRule(UserId)==0)
	{
		MessageBox(L"�û������Ϸ�", L"NO", MB_OK);
		return;
	}
	if(StringRule(Password)==0)
	{
		MessageBox(L"���벻�Ϸ�", L"NO", MB_OK);
		return;
	}

	//���ӷ���������
	PacketType type = LoginConnect(UserId, Password);
	if(type==error)
	{
		MessageBox(L"����������", L"NO", MB_OK);
		return;
	}
	else if(type==fail)
	{
		MessageBox(L"�û��������ڻ��������", L"NO", MB_OK);
		return;
	}
	else if(type!=success)
		assert(0);

	//����
	CDialogEx::OnOK();
}


void LandDlg::OnBnClickedRegist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ�����ַ���
	GetDlgItemText(IDC_EDIT_ID, UserId);
	GetDlgItemText(IDC_EDIT_PW, Password);
	GetDlgItemText(IDC_EDIT_PW2, Password2);
	
	if(StringRule(UserId)==0)
	{
		MessageBox(L"�û������Ϸ�", L"NO", MB_OK);
		return;
	}
	if(StringRule(Password)==0)
	{
		MessageBox(L"���벻�Ϸ�", L"NO", MB_OK);
		return;
	}
	if(Password!=Password2)
	{
		MessageBox(L"���벻һ��", L"NO", MB_OK);
		return;
	}
	
	//���ӷ���������
	PacketType type = RegistConnect(UserId, Password);
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


//�ж��ַ����Ϻ�����
bool LandDlg::StringRule(CString &string)
{
	int len = string.GetLength();
	int i;
	if(len<3 || len>20)
		return false;
	for(i=0; i<len; i++)
	{
		if(!(string[i]>='0' && string[i]<='9' || string[i]>='a' && string[i]<='z' || string[i]>='A' && string[i]<='Z'))
			return false;
	}
	return true;
}