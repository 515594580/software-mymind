#pragma once


// GetIpDlg �Ի���

class GetIpDlg : public CDialogEx
{
	//��Ԫ
	friend class COurMindClientDlg;//����


	DECLARE_DYNAMIC(GetIpDlg)

public:
	GetIpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GetIpDlg();

// �Ի�������
	enum { IDD = IDD_GETIPDLG };

	//���ݱ���
protected:
	CString Ip;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
