#pragma once


// ChangeDlg �Ի���

class ChangeDlg : public CDialogEx
{
	//��Ԫ
	friend class COurMindClientDlg;//����


	DECLARE_DYNAMIC(ChangeDlg)

public:
	ChangeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangeDlg();

// �Ի�������
	enum { IDD = IDD_CHANGEDLG };

	//����
protected:
	CString Password;
	CString Password2;
	CString Password3;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
