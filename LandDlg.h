
#pragma once


// LandDlg �Ի���

class LandDlg : public CDialogEx
{
	//��Ԫ
	friend class COurMindClientDlg;//����


	DECLARE_DYNAMIC(LandDlg)

public:
	LandDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LandDlg();

// �Ի�������
	enum { IDD = IDD_LANDDLG };

	//����
protected:
	CString UserId;
	CString Password;
	CString Password2;

	//����
public:
	static bool StringRule(CString &string);//�ж��ַ����Ϻ�����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedRegist();
};
