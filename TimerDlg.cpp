// TimerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OurMindClient.h"
#include "TimerDlg.h"
#include "afxdialogex.h"

#include "EditMindDlg.h"


// TimerDlg �Ի���

IMPLEMENT_DYNAMIC(TimerDlg, CDialogEx)

TimerDlg::TimerDlg(MindNode &TheMind, const bool EditLimit, CWnd *pFatherWnd, 
	CCriticalSection &csNetUpdata, CCriticalSection &csDataUpdata)
:
	CDialogEx(TimerDlg::IDD, 0),
	TheMind(TheMind), EditLimit(EditLimit), pFatherWnd(pFatherWnd), 
	csNetUpdata(csNetUpdata), csDataUpdata(csDataUpdata)
{
	
}

TimerDlg::~TimerDlg()
{
}

void TimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TimerDlg, CDialogEx)
	ON_WM_NCPAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// TimerDlg ��Ϣ�������


//��ʼ������
BOOL TimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//���ضԻ���
	MoveWindow(0, 0, 0, 0);

	//��ʼ��״̬
	UpdataFlag = false;

	//���ö�ʱ��
	SetTimer(1, TIMER_VALUE, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//�����ǿͻ����ػ�ͼ����
void TimerDlg::OnNcPaint()
{
	// TODO: �ڴ˴������Ϣ����������

	//�������ضԻ���
	ShowWindow(SW_HIDE);
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnNcPaint()
}


//��ʱ��������
void TimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	PacketType type;
	
	//������»��⿪ʼ
	csNetUpdata.Lock();

	//�������������
	if(EditLimit)
	{
		type = DownMindConnect(OperateList);
		if(type==fail)
			::PostMessage(pFatherWnd->m_hWnd, WM_INTERNET_ERROR, 2, 0);
	}
	else
	{
		//���ݸ��»��⿪ʼ
		csDataUpdata.Lock();

		if(UpdataFlag)
		{
			MindNode CopyMind;
			CopyMind.Copy(TheMind);
			UpdataFlag = false;

			//���ݸ��»������
			csDataUpdata.Unlock();

			type = UpMindConnect(TheMind, OperateList);
		}
		else
		{
			//���ݸ��»������
			csDataUpdata.Unlock();

			type = KeepMindConnect(OperateList);
		}
	}

	if(type==error || type==nopermission)
	{
		//������»������
		csNetUpdata.Unlock();

		//����������Ϣ�����߳�
		if(type==error)
			::SendMessage(pFatherWnd->m_hWnd, WM_INTERNET_ERROR, 0, 0);
		else if(type==nopermission)
			::SendMessage(pFatherWnd->m_hWnd, WM_INTERNET_ERROR, 1, 0);
	}
	else
	{
		//�������ݸ���
		if(OperateList.num>0)
		{
			//���ݸ��»��⿪ʼ
			csDataUpdata.Lock();

			bool MindChange;
			MindChange = OperateData(TheMind, OperateList);
			//����Ϣ�����߳�
			::PostMessage(pFatherWnd->m_hWnd, WM_MIND_UPDATA, MindChange, 0);

			//���ݸ��»������
			csDataUpdata.Unlock();
		}

		//������»������
		csNetUpdata.Unlock();
	}

	//����ʱ��
	SetTimer(1, TIMER_VALUE, NULL);
}
