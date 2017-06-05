#pragma once

// TimerDlg �Ի���


#define TIMER_VALUE 500//ʱ�Ӵ���ʱ��

class TimerDlg : public CDialogEx
{
	//��Ԫ
	friend class EditMindDlg;//����


	DECLARE_DYNAMIC(TimerDlg)

public:
	TimerDlg(MindNode &TheMind, const bool EditLimit, CWnd *pFatherWnd, 
		CCriticalSection &csNetUpdata, CCriticalSection &csDataUpdata);//��׼���캯��
	virtual ~TimerDlg();

// �Ի�������
	enum { IDD = IDD_TIMERDLG };

	//����
protected:
	MindNode &TheMind;//��ǰ˼ά��ͼ
	const bool EditLimit;//�༭����
	bool UpdataFlag;//���±�־
	ListTemplet<class OperateNode> OperateList;//���ղ�������
	const CWnd *pFatherWnd;//�߼�������ָ��
	//�߳�ͬ��
	CCriticalSection &csNetUpdata;//��������ٽ���
	CCriticalSection &csDataUpdata;//���ݸ����ٽ���

	//����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNcPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
