
// OurMindClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OurMindClient.h"
#include "OurMindClientDlg.h"
#include "afxdialogex.h"

#include "LandDlg.h"
#include "GetIpDlg.h"
#include "ChangeDlg.h"
#include "EditMindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COurMindClientDlg �Ի���


COurMindClientDlg::COurMindClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COurMindClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COurMindClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COurMindClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &COurMindClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &COurMindClientDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &COurMindClientDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &COurMindClientDlg::OnBnClickedButtonNew)
	ON_LBN_SELCHANGE(IDC_LIST_OWN, &COurMindClientDlg::OnSelchangeListOwn)
	ON_LBN_DBLCLK(IDC_LIST_OWN, &COurMindClientDlg::OnDblclkListOwn)
	ON_LBN_SELCHANGE(IDC_LIST_JOIN, &COurMindClientDlg::OnSelchangeListJoin)
	ON_LBN_DBLCLK(IDC_LIST_JOIN, &COurMindClientDlg::OnDblclkListJoin)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &COurMindClientDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDCANCEL, &COurMindClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// COurMindClientDlg ��Ϣ�������

BOOL COurMindClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ�����绷��
	ConnetcInit();

	//�������ڣ���ȡ������ip��ַ
	GetIpDlg ipdlg(this);
	if(ipdlg.DoModal()==IDOK)
	{
		g_ServerIp = ipdlg.Ip;
		g_ServerSocket.sin_family = AF_INET;
		g_ServerSocket.sin_addr.s_addr = inet_addr(CT2A(g_ServerIp));// "127.0.0.1" );
		g_ServerSocket.sin_port = htons(atoi(SERVER_PORT));
	}
	else
	{
		EndDialog(IDOK);
		return TRUE;
	}

	//�������ڣ���¼��ע��
	LandDlg landdlg(this);
	if(landdlg.DoModal()==IDOK)
		;
	else
	{
		EndDialog(IDOK);
		return TRUE;
	}

	//��ʼ��������
	//��¼��ʾUserId
	g_UserId = landdlg.UserId;
	SetDlgItemText(IDC_STATIC_USER, g_UserId);
	//��ʼ���ؼ�ָ��
	pButtonDel = (CButton *)GetDlgItem(IDC_BUTTON_DEL);
	pButtonDel->EnableWindow(FALSE);
	pEditMind = (CEdit *)GetDlgItem(IDC_EDIT_MINDMESSAGE);
	pListOwn = (CListBox *)GetDlgItem(IDC_LIST_OWN);
	pListJoin = (CListBox *)GetDlgItem(IDC_LIST_JOIN);

	if(GetListConnect(MyMindList, OurMindList)!=success)
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
	RefreshList();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COurMindClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COurMindClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COurMindClientDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


//�޸���Ϣ
void COurMindClientDlg::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//���������޸���Ϣ
	ChangeDlg changedlg(this);
	changedlg.DoModal();
}


//ˢ�°�ť
void COurMindClientDlg::OnBnClickedButtonRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//ɾ����ťʧЧ
	pButtonDel->EnableWindow(FALSE);
	//�����ȡ˼ά��ͼ�б�
	if(GetListConnect(MyMindList, OurMindList)!=success)
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
	RefreshList();
	//��ձ༭����ʾ��ʾ
	RefreshEdit(0);
}


//�½�˼ά��ͼ��ť
void COurMindClientDlg::OnBnClickedButtonNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�����༭����
	EditMindDlg editdlg(false, this);
	//��ȡ�½�˼ά��ͼ��Ϣ
	if(NewMindConnect(editdlg.TheMind)!=success)
	{
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		return;
	}
	//�򿪱༭����
	editdlg.DoModal();
	//֪ͨ�����༭
	//EditEndConnect();
	//��ȡ˼ά��ͼ�б�
	if(GetListConnect(MyMindList, OurMindList)!=success)
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
	RefreshList();
	RefreshEdit(0);
}


//ɾ��˼ά��ͼ��ť
void COurMindClientDlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int Index = pListOwn->GetCurSel();
	//��ȡ˼ά��ͼ�б�
	if(GetListConnect(MyMindList, OurMindList)!=success)
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
	RefreshList();
	pListOwn->SetCurSel(Index);
	//�ҵ������ʾ
	int i;
	MyMindList.pnode = MyMindList.qnode->pt;
	for(i=0; i<Index; i++)
		LIST_GO(MyMindList.pnode, pt);
	RefreshEdit(MyMindList.pnode);
	//������ʾ
	CString string;
	string.Format(L"��ǰ��%d�����ڱ༭��ȷ��Ҫɾ����˼ά��ͼ��", MyMindList.pnode->EditNum);
	if(MessageBox(string, L"ASK", MB_YESNO)==IDYES)
	{
		//����ɾ��
		if(DelMindConnect(MyMindList.pnode->MindName)!=success)
			MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		//ˢ�£�ɾ����ť��Ч
		pButtonDel->EnableWindow(FALSE);
		if(GetListConnect(MyMindList, OurMindList)!=success)
			MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		RefreshList();
		//��ձ༭����ʾ��ʾ
		RefreshEdit(0);
	}
	else
	{
		//ˢ�²���ʾ
		if(GetListConnect(MyMindList, OurMindList)!=success)
			MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		RefreshList();
		pListOwn->SetCurSel(Index);
	}
}


//ѡ��ӵ���б���
void COurMindClientDlg::OnSelchangeListOwn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//ȷʵ��ѡ��һ��
	int Index = pListOwn->GetCurSel();
	if(Index!=-1)
	{
		//ɾ����ť��Ч
		pButtonDel->EnableWindow(TRUE);
		//��һ���б��ȡ��ѡ��
		pListJoin->SetCurSel(-1);
		//��ʾѡ����ϸ��Ϣ
		int i;
		MyMindList.pnode = MyMindList.qnode->pt;
		for(i=0; i<Index; i++)
			LIST_GO(MyMindList.pnode, pt);
		RefreshEdit(MyMindList.pnode);
	}
}


//ѡ������б���
void COurMindClientDlg::OnSelchangeListJoin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//ȷʵ��ѡ��һ��
	int Index = pListJoin->GetCurSel();
	if(Index!=-1)
	{
		//ɾ����ťʧЧ
		pButtonDel->EnableWindow(FALSE);
		//��һ���б��ȡ��ѡ��
		pListOwn->SetCurSel(-1);
		//��ʾѡ����ϸ��Ϣ
		int i;
		OurMindList.pnode = OurMindList.qnode->pt;
		for(i=0; i<Index; i++)
			LIST_GO(OurMindList.pnode, pt);
		RefreshEdit(OurMindList.pnode);
	}
}


//˫��ӵ���б���
void COurMindClientDlg::OnDblclkListOwn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//δѡ��ͷ���
	int Index = pListOwn->GetCurSel();
	if(Index==-1)
		return;
	//�ҵ�˼ά��ͼ
	int i;
	MyMindList.pnode = MyMindList.qnode->pt;
	for(i=0; i<Index; i++)
		LIST_GO(MyMindList.pnode, pt);
	//�����༭����
	EditMindDlg editdlg(false, this);
	//��ȡ�½�˼ά��ͼ��Ϣ
	PacketType type = SelMindConnect(editdlg.TheMind, *(MyMindList.pnode));
	if(type==fail)
	{
		MessageBox(L"��Ȩ���ʻ��˼ά��ͼ�ѱ�ɾ��", L"NO", MB_OK);
	}
	else if(type!=success)
	{
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		return;
	}
	else
	{
		//�򿪱༭����
		editdlg.DoModal();
		//֪ͨ�����༭
		//EditEndConnect();
	}
	//��ȡ˼ά��ͼ�б�
	if(GetListConnect(MyMindList, OurMindList)!=success)
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
	RefreshList();
	RefreshEdit(0);
}


//˫�������б���
void COurMindClientDlg::OnDblclkListJoin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//δѡ��ͷ���
	int Index = pListJoin->GetCurSel();
	if(Index==-1)
		return;
	//�ҵ�˼ά��ͼ
	int i;
	OurMindList.pnode = OurMindList.qnode->pt;
	for(i=0; i<Index; i++)
		LIST_GO(OurMindList.pnode, pt);
	//�����༭����
	EditMindDlg editdlg(true, this);
	//��ȡ�½�˼ά��ͼ��Ϣ
	PacketType type = SelMindConnect(editdlg.TheMind, *(OurMindList.pnode));
	if(type==fail)
	{
		MessageBox(L"��Ȩ���ʻ��˼ά��ͼ�ѱ�ɾ��", L"NO", MB_OK);
	}
	else if(type!=success)
	{
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		return;
	}
	else
	{
		//�򿪱༭����
		editdlg.DoModal();
		//֪ͨ�����༭
		//EditEndConnect();
	}
	//��ȡ˼ά��ͼ�б�
	if(GetListConnect(MyMindList, OurMindList)!=success)
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
	RefreshList();
	RefreshEdit(0);
}


//ˢ���б����ʾ
void COurMindClientDlg::RefreshList()
{
	//��ʾ�б�
	pListOwn->ResetContent();
	for(MyMindList.pnode=MyMindList.qnode->pt; MyMindList.pnode; LIST_GO(MyMindList.pnode, pt))
	{
		pListOwn->AddString(MyMindList.pnode->MindName);
	}
	pListJoin->ResetContent();
	int Tab[] = {80};
	pListJoin->SetTabStops(1, Tab);
	for(OurMindList.pnode=OurMindList.qnode->pt; OurMindList.pnode; LIST_GO(OurMindList.pnode, pt))
	{
		pListJoin->AddString(OurMindList.pnode->UserId+L"\t"+OurMindList.pnode->MindName);
	}
}


//ˢ�±༭����ʾ
void COurMindClientDlg::RefreshEdit(MindNode *pTheMind)
{
	CString Text;
	Text = L"";
	if(pTheMind)
	{
		int Tab[] = {100};
		pEditMind->SetTabStops(1, Tab);
		CString string;
		Text += L"ӵ���ߣ�"+pTheMind->UserId;
		Text += L"\t˼ά��ͼ���ƣ�"+pTheMind->MindName;
		string.Format(L"\r\n˼ά��ͼ��С��%d*%d", pTheMind->Length, pTheMind->Width);
		Text += string;
		if(pTheMind->ReadOnly)
			Text += L"\t�����û�ֻ��";
		else
			Text += L"\t�����û��ɱ༭";
		string.Format(L"\t�����û�������%d", pTheMind->ShareNum);
		Text += string;
		Text += L"\r\n�༭ʱ�䣺"+pTheMind->EditTime;
		string.Format(L"\t��ǰ�༭������%d", pTheMind->EditNum);
		Text += string;
	}
	pEditMind->SetWindowTextW(Text);
}


void COurMindClientDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
