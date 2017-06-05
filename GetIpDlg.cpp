// GetIpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OurMindClient.h"
#include "GetIpDlg.h"
#include "afxdialogex.h"


// GetIpDlg �Ի���

IMPLEMENT_DYNAMIC(GetIpDlg, CDialogEx)

GetIpDlg::GetIpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GetIpDlg::IDD, pParent)
{

}

GetIpDlg::~GetIpDlg()
{
}

void GetIpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GetIpDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GetIpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// GetIpDlg ��Ϣ�������


void GetIpDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ�����ַ���
	GetDlgItemText(IDC_EDIT_IP, Ip);

	//����ip����
	if(TestServerIp(Ip))
		CDialogEx::OnOK();
	else
	{
		MessageBox(L"IP����������δ����", L"NO", MB_OK);
	}
}
