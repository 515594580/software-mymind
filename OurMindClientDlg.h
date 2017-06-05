
// OurMindClientDlg.h : ͷ�ļ�
//

#pragma once


// COurMindClientDlg �Ի���
class COurMindClientDlg : public CDialogEx
{
// ����
public:
	COurMindClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OURMINDCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//����
protected:
	//CString UserId;
	CButton *pButtonDel;//ɾ����ť
	CEdit *pEditMind;//��ʾ˼ά��ͼ�ı���
	CListBox *pListOwn;//ӵ��˼ά��ͼ�б��
	CListBox *pListJoin;//����˼ά��ͼ�б��
	ListTemplet<MindNode> MyMindList;//ӵ��˼ά��ͼ
	ListTemplet<MindNode> OurMindList;//����˼ά��ͼ

	//����
protected:
	void RefreshList();//ˢ���б����ʾ
	void RefreshEdit(MindNode *pTheMind);//ˢ�±༭����ʾ

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnSelchangeListOwn();
	afx_msg void OnDblclkListOwn();
	afx_msg void OnSelchangeListJoin();
	afx_msg void OnDblclkListJoin();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedCancel();
};
