// EditMindDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OurMindClient.h"
#include "EditMindDlg.h"
#include "afxdialogex.h"

#include "TimerDlg.h"
#include "LandDlg.h"


static int g_IntBuf[10000];


//��ʼ���ؼ�ID�б�
const int EditMindDlg::MindFreeItem[] = 
{
	IDC_STATIC_MINDNAME,
	IDC_STATIC_EDITNUM,
	IDC_STATIC_SHARENUM,
	IDC_STATIC_TIP,
};

const int EditMindDlg::MindLimitItem[] = 
{
	IDC_EDIT_MINDNAME,
	IDC_CHECK_READONLY,
	IDC_BUTTON_ADDROOT,
	IDC_BUTTON_SETLOCK,
	IDC_BUTTON_SETUNLOCK,
	IDC_CHECK_SETWITH,
	IDC_LIST_SHARELIST,
	IDC_EDIT_ADDSHARE,
	IDC_BUTTON_DELSHARE,
	IDC_BUTTON_ADDSHARE,
	IDC_STATIC_TIP2,
};

const int EditMindDlg::BlockFreeItem[] = 
{
	IDC_STATIC_BLOCKTEXT,
	IDC_EDIT_BLOCKTEXT,
	IDC_STATIC_SHAP,
	IDC_COMBO_SHAPE,
	IDC_STATIC_COLOR,
	IDC_BUTTON_SETWHITE,
	IDC_STATIC_RED,
	IDC_STATIC_GREEN,
	IDC_STATIC_BULE,
	IDC_SLIDER_RED,
	IDC_SLIDER_GREEN,
	IDC_SLIDER_BLUE,
	IDC_EDIT_RED,
	IDC_EDIT_GREEN,
	IDC_EDIT_BLUE,
	IDC_STATIC_LOCK,
	IDC_BUTTON_DELWITH,
	IDC_BUTTON_DELCOMBINE,
	IDC_BUTTON_ADDCHILD,
	IDC_BUTTON_ADDPARENT,
	IDC_BUTTON_LINETO,
	IDC_STATIC_TIP3,
	IDC_STATIC_TIP4,
	IDC_STATIC_LINEDIR,
	IDC_COMBO_LINEDIR,
};

const int EditMindDlg::BlockLimitItem[] = 
{
	IDC_BUTTON_SEPARATEROOT,
	IDC_BUTTON_DELSEPARETE,
};

const int EditMindDlg::AlwaysHideItem[] = 
{
	IDC_STATIC_SELLOCKBLOCK,
	IDC_STATIC_SELLINEBLOCK,
};

//��ʼ��������̬����
const double EditMindDlg::ZoomSize[] = 
{
	0.350, 0.455, 0.592, 0.769, 1, 1.2, 1.44, 1.782, 2.074, 2.488, 2.986, 3.583, 4.300, 5.160, 6.192, 7.430, 8.916
};
const int EditMindDlg::MaxZoomLevel = sizeof(ZoomSize)/sizeof(double);
const int EditMindDlg::DefaultZoom = 6;


// EditMindDlg �Ի���

IMPLEMENT_DYNAMIC(EditMindDlg, CDialogEx)

EditMindDlg::EditMindDlg(const bool EditLimit, CWnd* pParent/*=NULL*/):
	CDialogEx(EditMindDlg::IDD, pParent),
	EditLimit(EditLimit)
{

}

EditMindDlg::~EditMindDlg()
{
}

void EditMindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditMindDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditMindDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &EditMindDlg::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
ON_EN_CHANGE(IDC_EDIT_MINDNAME, &EditMindDlg::OnChangeEditMindname)
ON_EN_KILLFOCUS(IDC_EDIT_MINDNAME, &EditMindDlg::OnKillfocusEditMindname)
ON_MESSAGE(WM_MIND_UPDATA, &EditMindDlg::OnMindUpdata)
ON_MESSAGE(WM_INTERNET_ERROR, &EditMindDlg::OnInternetError)
ON_BN_CLICKED(IDC_BUTTON_ADDSHARE, &EditMindDlg::OnBnClickedButtonAddshare)
ON_BN_CLICKED(IDC_BUTTON_DELSHARE, &EditMindDlg::OnBnClickedButtonDelshare)
ON_BN_CLICKED(IDC_CHECK_READONLY, &EditMindDlg::OnClickedCheckReadonly)
ON_BN_CLICKED(IDC_CHECK_SETWITH, &EditMindDlg::OnClickedCheckSetwith)
ON_BN_CLICKED(IDC_BUTTON_ADDROOT, &EditMindDlg::OnBnClickedButtonAddroot)
ON_WM_RBUTTONDBLCLK()
ON_EN_CHANGE(IDC_EDIT_BLOCKTEXT, &EditMindDlg::OnChangeEditBlocktext)
ON_EN_KILLFOCUS(IDC_EDIT_BLOCKTEXT, &EditMindDlg::OnKillfocusEditBlocktext)
ON_BN_CLICKED(IDC_BUTTON_DELWITH, &EditMindDlg::OnBnClickedButtonDelwith)
ON_BN_CLICKED(IDC_BUTTON_DELCOMBINE, &EditMindDlg::OnBnClickedButtonDelcombine)
ON_BN_CLICKED(IDC_BUTTON_ADDCHILD, &EditMindDlg::OnBnClickedButtonAddchild)
ON_BN_CLICKED(IDC_BUTTON_ADDPARENT, &EditMindDlg::OnBnClickedButtonAddparent)
ON_BN_CLICKED(IDC_BUTTON_LINETO, &EditMindDlg::OnBnClickedButtonLineto)
ON_BN_CLICKED(IDC_BUTTON_SEPARATEROOT, &EditMindDlg::OnBnClickedButtonSeparateroot)
ON_BN_CLICKED(IDC_BUTTON_DELSEPARETE, &EditMindDlg::OnBnClickedButtonDelseparete)
ON_EN_CHANGE(IDC_EDIT_RED, &EditMindDlg::OnChangeEditRed)
ON_EN_CHANGE(IDC_EDIT_GREEN, &EditMindDlg::OnChangeEditGreen)
ON_EN_CHANGE(IDC_EDIT_BLUE, &EditMindDlg::OnChangeEditBlue)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_RED, &EditMindDlg::OnCustomdrawSliderRed)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GREEN, &EditMindDlg::OnCustomdrawSliderGreen)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BLUE, &EditMindDlg::OnCustomdrawSliderBlue)
ON_BN_CLICKED(IDC_BUTTON_SETWHITE, &EditMindDlg::OnBnClickedButtonSetwhite)
ON_CBN_SELCHANGE(IDC_COMBO_SHAPE, &EditMindDlg::OnSelchangeComboShap)
ON_CBN_SELCHANGE(IDC_COMBO_LINEDIR, &EditMindDlg::OnSelchangeComboLinedir)
ON_BN_CLICKED(IDC_BUTTON_SETLOCK, &EditMindDlg::OnBnClickedButtonSetlock)
ON_BN_CLICKED(IDC_BUTTON_SETUNLOCK, &EditMindDlg::OnBnClickedButtonSetunlock)
END_MESSAGE_MAP()


//���ڳ�ʼ������
BOOL EditMindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʼ���ؼ�ָ��
	int i=0;
	for(i=0; i<sizeof(MindFreeItem)/sizeof(int); i++)
		pMindFreeItem[i] = GetDlgItem(MindFreeItem[i]);
	for(i=0; i<sizeof(MindLimitItem)/sizeof(int); i++)
		pMindLimitItem[i] = GetDlgItem(MindLimitItem[i]);
	for(i=0; i<sizeof(BlockFreeItem)/sizeof(int); i++)
		pBlockFreeItem[i] = GetDlgItem(BlockFreeItem[i]);
	for(i=0; i<sizeof(BlockLimitItem)/sizeof(int); i++)
		pBlockLimitItem[i] = GetDlgItem(BlockLimitItem[i]);
	for(i=0; i<sizeof(AlwaysHideItem)/sizeof(int); i++)
		pAlwaysHideItem[i] = GetDlgItem(AlwaysHideItem[i]);

	//��ʼ���ؼ���ʾ
	for(i=0; i<sizeof(BlockFreeItem)/sizeof(int); i++)
		pBlockFreeItem[i]->ShowWindow(SW_HIDE);
	for(i=0; i<sizeof(BlockLimitItem)/sizeof(int); i++)
		pBlockLimitItem[i]->ShowWindow(SW_HIDE);
	for(i=0; i<sizeof(AlwaysHideItem)/sizeof(int); i++)
		pAlwaysHideItem[i]->ShowWindow(SW_HIDE);

	//��ʼ���ؼ�������
	if(EditLimit)
	{
		for(i=0; i<sizeof(MindLimitItem)/sizeof(int); i++)
			pMindLimitItem[i]->EnableWindow(FALSE);
		for(i=0; i<sizeof(BlockLimitItem)/sizeof(int); i++)
			pBlockLimitItem[i]->EnableWindow(FALSE);
	}

	//��ʼ���ؼ�ָ�뼰��������
	CString string;
	//��ͼ���ֱ༭��
	pEditMindName = (CEdit *)GetDlgItem(IDC_EDIT_MINDNAME);
	pEditMindName->SetWindowTextW(TheMind.MindName);
	LastMindName = TheMind.MindName;
	//�����û��б��
	pListShareList = (CListBox *)GetDlgItem(IDC_LIST_SHARELIST);
	RefreshShareList(false);
	//��ӹ����û��༭��
	pEditAddShare = (CEdit *)GetDlgItem(IDC_EDIT_ADDSHARE);
	//�༭������̬��
	pStaticEditNum = (CStatic *)GetDlgItem(IDC_STATIC_EDITNUM);
	string.Format(L"�༭������%d", TheMind.EditNum);
	pStaticEditNum->SetWindowTextW(string);
	//����������̬��
	pStaticShareNum = (CStatic *)GetDlgItem(IDC_STATIC_SHARENUM);
	string.Format(L"����������%d", TheMind.ShareNum);
	pStaticShareNum->SetWindowTextW(string);
	//ֻ����ѡ��ť
	pCheckReadOnly = (CButton *)GetDlgItem(IDC_CHECK_READONLY);
	pCheckReadOnly->SetCheck(TheMind.ReadOnly? BST_CHECKED:BST_UNCHECKED);
	//����������ѡ��ť
	pCheckSetWith = (CButton *)GetDlgItem(IDC_CHECK_SETWITH);
	SetWith = false;
	//���ñ༭�ڵ�״̬
	EditBlockStatus = false;
	//�ֿ����ֱ༭��
	pEditBlockText = (CEdit *)GetDlgItem(IDC_EDIT_BLOCKTEXT);
	//�ֿ�������̬��
	pStaticLock = (CStatic *)GetDlgItem(IDC_STATIC_LOCK);
	//������ɫ�༭��
	ColorAcceptFlag = false;
	pEditRed = (CEdit *)GetDlgItem(IDC_EDIT_RED);
	pEditGreen = (CEdit *)GetDlgItem(IDC_EDIT_GREEN);
	pEditBlue = (CEdit *)GetDlgItem(IDC_EDIT_BLUE);
	//������ɫ������
	pSliderRed = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_RED);
	pSliderRed->SetRange(0, 255);
	pSliderGreen = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_GREEN);
	pSliderGreen->SetRange(0, 255);
	pSliderBlue = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_BLUE);
	pSliderBlue->SetRange(0, 255);
	//ѡ����״��Ͽ�
	pComboShape = (CComboBox *)GetDlgItem(IDC_COMBO_SHAPE);
	pComboShape->AddString(CString(L"����"));
	pComboShape->AddString(CString(L"Բ�Ǿ���"));
	pComboShape->AddString(CString(L"��Բ��"));
	pComboShape->AddString(CString(L"����"));
	pComboShape->AddString(CString(L"����"));
	pComboShape->AddString(CString(L"ƽ���ı���"));
	pComboShape->AddString(CString(L"�˱���"));
	//��ʾѡ��̬��
	pStaticSelLineBlock = (CStatic *)GetDlgItem(IDC_STATIC_SELLINEBLOCK);
	pStaticSelLockBlock = (CStatic *)GetDlgItem(IDC_STATIC_SELLOCKBLOCK);
	//ѡ������Ͽ�
	pComboLineDir = (CComboBox *)GetDlgItem(IDC_COMBO_LINEDIR);
	pComboLineDir->AddString(CString(L"����"));
	pComboLineDir->AddString(CString(L"����"));
	pComboLineDir->AddString(CString(L"����"));
	pComboLineDir->AddString(CString(L"����"));


	//��ʼ����ͼ����
	CornerPoint.SetPoint(0, 0);
	ZoomLevel = DefaultZoom;
	GetClientRect(&rectEditArea);
	rectEditArea.right = 870;
	rectBackArea = rectEditArea;
	rectBackArea.right ++;
	rectBackArea.bottom ++;

	//��ʼ��״̬����
	LBottonStatus = false;
	RBottonStatus = false;
	EditBlockStatus = false;
	ChooseLineBlock = false;
	ChooseLockBlock = false;
	ChooseUnlockBlock = false;

	//��ͬ���ù������߳�
	pThread = AfxBeginThread(ThreadFunc, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void EditMindDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	PaintMind(&dc);

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


//ͬ���������̻߳ص�����
UINT EditMindDlg::ThreadFunc(LPVOID pParam)
{
	EditMindDlg *pthis = (EditMindDlg *)pParam;
	pthis->pTimerDlg = new TimerDlg(pthis->TheMind, pthis->EditLimit, pthis, 
		pthis->csNetUpdata, pthis->csDataUpdata);
	TimerDlg *pDlg = pthis->pTimerDlg;
	pthis->pTimerDlg->DoModal();
	delete pDlg;
	return 0;
}


// EditMindDlg ��Ϣ�������


//�����������¼�
void EditMindDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//ȡ���κοؼ������뽹��
	SetFocus();

	//�����ڱ༭״̬
	if(EditBlockStatus && ChooseLineBlock==false)
	{
		if(!rectEditArea.PtInRect(point))
			return;

		//���ݸ��»��⿪ʼ
		csDataUpdata.Lock();

		//�жϵ�����ĸ��ֿ�������
		BlockNode *pBlock;
		CPoint point2 = RealToImage(point);
		pBlock = ChoiseBlock(TheMind.BlockTree.qnode->pch, point2);
		//���ڱ༭�ֿ�������
		if(pBlock==pEditBlock)
		{
			LBottonStatus = true;
			LBottonPoint = CPoint(pBlock->PosX, pBlock->PosY)-point2;
			SetCapture();
		}

		//���ݸ��»������
		csDataUpdata.Unlock();
	}
	//��ѡ�����ӵ��ֿ�
	else if(ChooseLineBlock)
	{
		//������»��⿪ʼ
		csNetUpdata.Lock();

		//�жϵ�����ĸ��ֿ�������
		BlockNode *pBlock;
		CPoint point2 = RealToImage(point);
		pBlock = ChoiseBlock(TheMind.BlockTree.qnode->pch, point2);

		//���ڱ༭�ֿ�������
		if(pBlock==pEditBlock)
		{
			//������»������
			csNetUpdata.Unlock();
			MessageBox(L"�ֿ鲻�������Լ�", L"NO", MB_OK);
			return;
		}
		//������հ״�
		else if(pBlock==0)
		{
			//������»������
			csNetUpdata.Unlock();
			ChooseLineBlock = false;
			pStaticSelLineBlock->ShowWindow(SW_HIDE);
			return;
		}

		TheMind.BlockTree.pnode = pBlock;
		int deep = TheMind.BlockTree.GetLocal(g_IntBuf);
		//���벢�����༭
		PacketType Type = BlockLineToConnect(*pEditBlock, OperateList, deep, g_IntBuf);

		if(Type==fail)
		{
			//ʧȥȨ����ת��״̬����ͼ
			TurnMindStatus();
			CClientDC dc(this);
			PaintMind(&dc);

			//������»������
			csNetUpdata.Unlock();

			MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
			return;
		}
		else if(Type==clash)
		{
			//������»������
			csNetUpdata.Unlock();
			MessageBox(L"����ֿ鲻�ɷ��ʻ����������ӷֿ�", L"NO", MB_OK);
			return;
		}
		else if(Type==nopermission)
		{
			//������»������
			csNetUpdata.Unlock();
			MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
			Exit();
			return;
		}
		else if(Type!=success)
		{
			//������»������
			csNetUpdata.Unlock();
			//�Ͽ����ӣ��˳�
			MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
			Exit();
			return;
		}
		//��������ʾ
		OperateData(TheMind, OperateList);
		ChooseLineBlock = false;
		pStaticSelLineBlock->ShowWindow(SW_HIDE);
		OnMindUpdata(0, 0);

		//������»������
		csNetUpdata.Unlock();
	}
	//��ѡ�������ֿ�
	else if(ChooseLockBlock || ChooseUnlockBlock)
	{
		//������»��⿪ʼ
		csNetUpdata.Lock();

		//�жϵ�����ĸ��ֿ�������
		BlockNode *pBlock;
		CPoint point2 = RealToImage(point);
		pBlock = ChoiseBlock(TheMind.BlockTree.qnode->pch, point2);

		//������հ״�
		if(pBlock==0)
		{
			//������»������
			csNetUpdata.Unlock();
			ChooseLockBlock = false;
			ChooseUnlockBlock = false;
			pStaticSelLockBlock->ShowWindow(SW_HIDE);
			return;
		}

		TheMind.BlockTree.pnode = pBlock;
		int deep = TheMind.BlockTree.GetLocal(g_IntBuf);
		//���벢�����༭
		PacketType Type = LockBlockConnect(deep, g_IntBuf, OperateList, ChooseLockBlock, SetWith);

		if(Type!=success && Type!=fail)
		{
			//������»������
			csNetUpdata.Unlock();
			//�Ͽ����ӣ��˳�
			MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
			Exit();
			return;
		}
		else
		{
			//ʧ�ܵ���
			if(Type==fail)
			{
				//������»������
				csNetUpdata.Unlock();

				MessageBox(L"��ѡ�ֿ��ѱ�ɾ��", L"NO", MB_OK);
				return;
			}

			//�ı�
			OperateData(TheMind, OperateList);
			ChooseLockBlock = false;
			ChooseUnlockBlock = false;
			pStaticSelLockBlock->ShowWindow(SW_HIDE);

			//ˢ��������ʾ
			OnMindUpdata(0, 0);

			//������»������
			csNetUpdata.Unlock();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


//������̧���¼�
void EditMindDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(EditBlockStatus && LBottonStatus)
	{
		LBottonStatus = false;
		CPoint point2 = RealToImage(point);
		pEditBlock->PosX = point2.x+LBottonPoint.x;
		pEditBlock->PosY = point2.y+LBottonPoint.y;
		
		//���ݸ��»��⿪ʼ
		CClientDC dc(this);

		//��������
		if(pEditBlock->PosX<0)
			pEditBlock->PosX = 0;
		else if(pEditBlock->PosX>TheMind.Length-pEditBlock->Length)
			pEditBlock->PosX = TheMind.Length-pEditBlock->Length;
		if(pEditBlock->PosY<0)
			pEditBlock->PosY = 0;
		else if(pEditBlock->PosY>TheMind.Width-pEditBlock->Width)
			pEditBlock->PosY = TheMind.Width-pEditBlock->Width;

		csDataUpdata.Lock();
		PaintMind(&dc);
		//���ݸ��»������
		csDataUpdata.Unlock();

		if(!RBottonStatus)
			::ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


//������˫���¼�
void EditMindDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!rectEditArea.PtInRect(point))
		return;
	BlockNode *pBlock;
	CPoint point2 = RealToImage(point);
	
	//������»��⿪ʼ
	csNetUpdata.Lock();
	pBlock = ChoiseBlock(TheMind.BlockTree.qnode->pch, point2);

	//�жϵ�����ĸ��ֿ�������
	//��Ϊ�Լ�����
	if(EditBlockStatus && pBlock==pEditBlock)
	{
		//������»������
		csNetUpdata.Unlock();
		return;
	}
	else
	{
		//��Ϊ�ֿ�༭״̬
		if(EditBlockStatus)
		{
			//�����˳��ֿ�༭״̬
			PacketType Type = FinishBlockConnect(*pEditBlock, OperateList);

			if(Type==fail)
			{
				//ʧȥȨ����ת��״̬����ͼ
				TurnMindStatus();
				CClientDC dc(this);
				PaintMind(&dc);

				//������»������
				csNetUpdata.Unlock();

				MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
				return;
			}
			else if(Type==nopermission)
			{
				//������»������
				csNetUpdata.Unlock();
				MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
				Exit();
				return;
			}
			else if(Type!=success)
			{
				//������»������
				csNetUpdata.Unlock();
				//�Ͽ����ӣ��˳�
				MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
				Exit();
				return;
			}
			else
			{
				//��������ʾ��ת��״̬
				OperateData(TheMind, OperateList);
				TurnMindStatus();
				OnMindUpdata(0, 0);
			}
		}

		//��δѡ�зֿ�
		if(pBlock==0)
		{
			//������»������
			csNetUpdata.Unlock();
			return;
		}

		//��������������
		if(EditLimit && pBlock->Lock && pBlock->LockUser.GetLength()==0)
		{
			//������»������
			csNetUpdata.Unlock();

			MessageBox(L"�˷ֿ��ֹ�����û��༭", L"NO", MB_OK);
			return;
		}
		else if(pBlock->Lock && pBlock->LockUser.GetLength()>0)
		{
			//������»������
			csNetUpdata.Unlock();

			MessageBox(L"�˷ֿ����ڱ������û��༭", L"NO", MB_OK);
			return;
		}
		//������������
		else
		{
			TheMind.BlockTree.pnode = pBlock;
			int deep = TheMind.BlockTree.GetLocal(g_IntBuf);
			//�����·ֿ�Ȩ��
			PacketType Type = ApplyBlockConnect(g_IntBuf, deep, OperateList);

			if(Type==fail)
			{
				//������»������
				csNetUpdata.Unlock();
				MessageBox(L"û�б༭Ȩ�޻�÷ֿ��ѱ�ɾ��", L"NO", MB_OK);
				return;
			}
			else if(Type==nopermission)
			{
				//������»������
				csNetUpdata.Unlock();
				MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
				Exit();
				return;
			}
			else if(Type!=success)
			{
				//������»������
				csNetUpdata.Unlock();
				//�Ͽ����ӣ��˳�
				MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
				Exit();
				return;
			}
			else
			{
				//��������ʾ��ת��״̬
				OperateData(TheMind, OperateList);
				TurnBlockStatus(pBlock);
				OnMindUpdata(0, 0);
		
				//������»������
				csNetUpdata.Unlock();
			}
		}
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


//����Ҽ������¼�
void EditMindDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!rectEditArea.PtInRect(point))
		return;
	RBottonStatus = true;
	RBottonPoint = CornerPoint-point;
	LBottonZoom = ZoomSize[ZoomLevel];
	SetCapture();

	CDialogEx::OnRButtonDown(nFlags, point);
}


//����Ҽ�̧���¼�
void EditMindDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(RBottonStatus)
	{
		RBottonStatus = false;
		CornerPoint.x = point.x+(int)(RBottonPoint.x*ZoomSize[ZoomLevel]/LBottonZoom);
		CornerPoint.y = point.y+(int)(RBottonPoint.y*ZoomSize[ZoomLevel]/LBottonZoom);

		//���ݸ��»��⿪ʼ
		CClientDC dc(this);
		csDataUpdata.Lock();
		PaintMind(&dc);
		//���ݸ��»������
		csDataUpdata.Unlock();

		if(!LBottonStatus)
			::ReleaseCapture();
	}

	CDialogEx::OnRButtonUp(nFlags, point);
}


//����Ҽ�˫���¼�
void EditMindDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if(!rectEditArea.PtInRect(point))
		return;
	CornerPoint.SetPoint(0, 0);
	ZoomLevel = DefaultZoom;
	
	CClientDC dc(this);
	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();
	PaintMind(&dc);
	//���ݸ��»������
	csDataUpdata.Unlock();

	CDialogEx::OnRButtonDblClk(nFlags, point);
}


//����ƶ��¼�
void EditMindDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	bool change = false;
	CClientDC dc(this);

	if(RBottonStatus)
	{
		CornerPoint.x = point.x+(int)(RBottonPoint.x*ZoomSize[ZoomLevel]/LBottonZoom);
		CornerPoint.y = point.y+(int)(RBottonPoint.y*ZoomSize[ZoomLevel]/LBottonZoom);
		change = true;
	}
	if(EditBlockStatus && LBottonStatus)
	{
		CPoint point2 = RealToImage(point);
		pEditBlock->PosX = point2.x+LBottonPoint.x;
		pEditBlock->PosY = point2.y+LBottonPoint.y;
		change = true;

		//��������
		if(pEditBlock->PosX<0)
			pEditBlock->PosX = 0;
		else if(pEditBlock->PosX>TheMind.Length-pEditBlock->Length)
			pEditBlock->PosX = TheMind.Length-pEditBlock->Length;
		if(pEditBlock->PosY<0)
			pEditBlock->PosY = 0;
		else if(pEditBlock->PosY>TheMind.Width-pEditBlock->Width)
			pEditBlock->PosY = TheMind.Width-pEditBlock->Width;
	}

	if(change)
	{
		//���ݸ��»��⿪ʼ
		csDataUpdata.Lock();
		PaintMind(&dc);
		//���ݸ��»������
		csDataUpdata.Unlock();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


//�������¼�
BOOL EditMindDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	ScreenToClient(&pt);
	if(!rectEditArea.PtInRect(pt))
		return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
	double lastzoom = ZoomSize[ZoomLevel];
	if(zDelta>0)
	{
		if(ZoomLevel>=MaxZoomLevel-1)
			return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
		ZoomLevel ++;
	}
	else
	{
		if(ZoomLevel<=0)
			return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
		ZoomLevel --;
	}
	CornerPoint.x = pt.x+(int)((CornerPoint.x-pt.x)*ZoomSize[ZoomLevel]/lastzoom);
	CornerPoint.y = pt.y+(int)((CornerPoint.y-pt.y)*ZoomSize[ZoomLevel]/lastzoom);

	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();
	CClientDC dc(this);
	PaintMind(&dc);
	//���ݸ��»������
	csDataUpdata.Unlock();

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


//��ϢԤ���������������������Ϣ
BOOL EditMindDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN
		&& (pMsg->wParam==VK_RIGHT || pMsg->wParam==VK_LEFT || pMsg->wParam==VK_DOWN || pMsg->wParam==VK_UP))
	{
		ProcessKeyDown(pMsg->wParam);
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


//������Ϣ����
void EditMindDlg::ProcessKeyDown(WPARAM Key)
{
	if(EditLimit && EditBlockStatus==false)
		return;

	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();
	CClientDC dc(this);

	if(EditBlockStatus)
	{
		switch(Key)
		{
		case VK_RIGHT:
			pEditBlock->Length += (int)(5/ZoomSize[ZoomLevel]+1);
			if(pEditBlock->Length>TheMind.Length-pEditBlock->PosX)
				pEditBlock->Length = TheMind.Length-pEditBlock->PosX;
			break;
		case VK_LEFT:
			pEditBlock->Length -= (int)(5/ZoomSize[ZoomLevel]+1);
			if(pEditBlock->Length<MIN_BLOCK_LENGTH)
				pEditBlock->Length = MIN_BLOCK_LENGTH;
			break;
		case VK_DOWN:
			pEditBlock->Width += (int)(5/ZoomSize[ZoomLevel]+1);
			if(pEditBlock->Width>TheMind.Width-pEditBlock->PosY)
				pEditBlock->Width = TheMind.Width-pEditBlock->PosY;
			break;
		case VK_UP:
			pEditBlock->Width -= (int)(5/ZoomSize[ZoomLevel]+1);
			if(pEditBlock->Width<MIN_BLOCK_WIDTH)
				pEditBlock->Width = MIN_BLOCK_WIDTH;
			break;
		}
	}
	else
	{
		switch(Key)
		{
		case VK_RIGHT:
			TheMind.Length += (int)(10/ZoomSize[ZoomLevel]+1);
			break;
		case VK_LEFT:
			TheMind.Length -= (int)(10/ZoomSize[ZoomLevel]+1);
			if(TheMind.Length<TheMind.Pos_X)
				TheMind.Length = TheMind.Pos_X;
			if(TheMind.Length<MIN_LENGTH)
				TheMind.Length = MIN_LENGTH;
			break;
		case VK_DOWN:
			TheMind.Width += (int)(10/ZoomSize[ZoomLevel]+1);
			break;
		case VK_UP:
			TheMind.Width -= (int)(10/ZoomSize[ZoomLevel]+1);
			if(TheMind.Width<TheMind.Pos_Y)
				TheMind.Width = TheMind.Pos_Y;
			if(TheMind.Width<MIN_WIDTH)
				TheMind.Width = MIN_WIDTH;
			break;
		}
		pTimerDlg->UpdataFlag = true;
	}

	PaintMind(&dc);
	//���ݸ��»������
	csDataUpdata.Unlock();
}


//OK��Ϣ�¼�
void EditMindDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ܾ���Ӧ
	//CDialogEx::OnOK();
}


//�رհ�ť����¼�
void EditMindDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�˳�
	Exit();
}


//����˼ά��ͼ��Ϣ��������ֻ�������绥���е���
afx_msg LRESULT EditMindDlg::OnMindUpdata(WPARAM wParam, LPARAM lParam)
{
	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	CString string;
	//�������Ʊ༭ʱ����ĳЩ��Ϣ����ֹ���ڱ༭���ƻ�
	if(EditLimit==true)
	{
		//��ͼ���ֱ༭��
		pEditMindName->SetWindowTextW(TheMind.MindName);
	}
	//�������
	//�����û��б��
	RefreshShareList(true);
	//�༭������̬��
	string.Format(L"�༭������%d", TheMind.EditNum);
	pStaticEditNum->SetWindowTextW(string);
	//����������̬��
	string.Format(L"����������%d", TheMind.ShareNum);
	pStaticShareNum->SetWindowTextW(string);
	//ֻ����ѡ��ť
	pCheckReadOnly->SetCheck(TheMind.ReadOnly? BST_CHECKED:BST_UNCHECKED);

	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
	return 0;
}


//��������û��Ȩ����Ϣ
afx_msg LRESULT EditMindDlg::OnInternetError(WPARAM wParam, LPARAM lParam)
{
	if(wParam==0)
	{
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
	}
	else if(wParam==1)
	{
		MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
		Exit();
	}
	else if(wParam==2)
	{
		MessageBox(L"û�б༭Ȩ��", L"NO", MB_OK);
		TurnMindStatus();
		CClientDC dc(this);
		PaintMind(&dc);
	}
	return 0;
}


//��ͼ���Ʊ༭���ַ��ı��¼�
void EditMindDlg::OnChangeEditMindname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString string;
	pEditMindName->GetWindowTextW(string);
	//��Ϊ�س���ȡ�����뽹��
	if(string==LastMindName)
	{
		SetFocus();
	}
	LastMindName = string;
}


//��ͼ���Ʊ༭��ʧȥ���뽹�㣬���˴����л����ɱ��س�����
void EditMindDlg::OnKillfocusEditMindname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�������л�����������������
	if(GetFocus()==0)
		return;

	CString string;
	pEditMindName->GetWindowTextW(string);
	if(NameRule(string))
	{
		//�Ϸ�
		if(string==TheMind.MindName)
			//δ�ı��˳�
			return;

		//������»��⿪ʼ
		csNetUpdata.Lock();

		//ͬ��������
		PacketType Type = ChangeNameConnect(string);
		if(Type==fail)
		{
			//������»������
			csNetUpdata.Unlock();
			//�������ָ�
			MessageBox(L"�������Ѵ���", L"NO", MB_OK);
			pEditMindName->SetWindowTextW(TheMind.MindName);
			LastMindName = TheMind.MindName;
		}
		else if(Type!=success)
		{
			//������»������
			csNetUpdata.Unlock();
			//�Ͽ����ӣ��˳�
			MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
			Exit();
		}
		else
		{
			//�ı�
			TheMind.MindName = string;
			pTimerDlg->TheMind.MindName = string;
			//������»������
			csNetUpdata.Unlock();
		}
	}
	else
	{
		//���Ϸ����ָ�
		MessageBox(L"���Ʋ��Ϸ�", L"NO", MB_OK);
		pEditMindName->SetWindowTextW(TheMind.MindName);
		LastMindName = TheMind.MindName;
	}
}


//���빲���û���ť����¼�
void EditMindDlg::OnBnClickedButtonAddshare()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString string;
	pEditAddShare->GetWindowTextW(string);
	//�����жϺϷ���
	if(LandDlg::StringRule(string)==false)
	{
		MessageBox(L"�û������Ϸ�", L"NO", MB_OK);
		return;
	}

	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	int result;
	if(BinarySearch(TheMind.ShareUser, string, 0, TheMind.ShareNum-1, result))
	{
		//���ݸ��»������
		csDataUpdata.Unlock();
		
		MessageBox(L"���û��ѱ�����", L"NO", MB_OK);
		return;
	}
	else if(g_UserId==string)
	{
		//���ݸ��»������
		csDataUpdata.Unlock();
		
		MessageBox(L"���ܹ����Լ�", L"NO", MB_OK);
		return;
	}
	else
	{
		//���ݸ��»������
		csDataUpdata.Unlock();
	}

	//������»��⿪ʼ
	csNetUpdata.Lock();

	//ͬ��������
	PacketType Type = AddShareConnect(string);
	if(Type==fail)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"���û���������", L"NO", MB_OK);
	}
	else if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
	}
	else
	{
		//�ı�
		int i;
		for(i=TheMind.ShareNum-1; i>result; i--)
		{
			TheMind.ShareUser[i+1] = TheMind.ShareUser[i];
			TheMind.UserStatus[i+1] = TheMind.UserStatus[i];
		}
		TheMind.ShareUser[result+1] = string;
		TheMind.UserStatus[result+1] = false;
		TheMind.ShareNum ++;
		RefreshShareList(false);
		//������»������
		csNetUpdata.Unlock();
	}
}


//ɾ�������û���ť����¼�
void EditMindDlg::OnBnClickedButtonDelshare()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int Index = pListShareList->GetCurSel();
	if(Index==-1)
	{
		MessageBox(L"��ѡ��һ��", L"NO", MB_OK);
		return;
	}
	
	//������»��⿪ʼ
	csNetUpdata.Lock();

	//ͬ��������
	PacketType Type = DelShareConnect(TheMind.ShareUser[Index]);
	if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
	}
	else
	{
		//�ı�
		int i;
		for(i=Index; i<TheMind.ShareNum-1; i++)
		{
			TheMind.ShareUser[i] = TheMind.ShareUser[i+1];
			TheMind.UserStatus[i] = TheMind.UserStatus[i+1];
		}
		TheMind.ShareNum --;
		RefreshShareList(false);
		//������»������
		csNetUpdata.Unlock();
	}
}


//ֻ����ѡ��ť����¼�
void EditMindDlg::OnClickedCheckReadonly()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	pTimerDlg->UpdataFlag = true;
	TheMind.ReadOnly = pCheckReadOnly->GetCheck()==BST_CHECKED? true:false;

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//����������ѡ��ť����¼�
void EditMindDlg::OnClickedCheckSetwith()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	SetWith = pCheckSetWith->GetCheck()==BST_CHECKED? true:false;
}


//��Ӹ��ڵ㰴ť����¼�
void EditMindDlg::OnBnClickedButtonAddroot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CPoint point = RealToImage(CPoint(0, 0));
	
	//������»��⿪ʼ
	csNetUpdata.Lock();
	
	//ͬ��������
	PacketType Type = BlockAddRootConnect(point.x, point.y, OperateList);

	if(Type!=success && Type!=fail)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
		return;
	}
	else
	{
		//�ı�
		OperateData(TheMind, OperateList);

		//ʧ�ܵ���
		if(Type==fail)
		{
			OnMindUpdata(0, 0);
			//������»������
			csNetUpdata.Unlock();

			MessageBox(L"˼ά��ͼû���㹻�ߴ�����·ֿ�", L"NO", MB_OK);
			return;
		}

		//ת���ڵ�༭״̬
		TurnBlockStatus(TheMind.BlockTree.qnode->pch);

		//ˢ��������ʾ
		OnMindUpdata(0, 0);

		//������»������
		csNetUpdata.Unlock();
	}
}


//�ֿ����ֱ༭���ַ��ı��¼�
void EditMindDlg::OnChangeEditBlocktext()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString string;
	pEditBlockText->GetWindowTextW(string);
	//��Ϊ�س���ȡ�����뽹��
	if(string==LastBlockText)
	{
		SetFocus();
	}
	LastBlockText = string;
}


//�ֿ����ֱ༭��ʧȥ���뽹�㣬���˴����л����ɱ��س�����
void EditMindDlg::OnKillfocusEditBlocktext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�������л�����������������
	if(GetFocus()==0)
		return;

	CString string;
	pEditBlockText->GetWindowTextW(string);

	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	//�ı�
	pEditBlock->Text = string;
	
	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//ɾ�������ӷֿ鰴ť����¼�
void EditMindDlg::OnBnClickedButtonDelwith()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(EditLimit && pEditBlock->ppr->ppr==0)
	{
		MessageBox(L"�����û�û�н����漰���ֿ��ϵ�Ĳ���Ȩ��", L"NO", MB_OK);
		return;
	}

	//������»��⿪ʼ
	csNetUpdata.Lock();

	//�����˳��ֿ�༭״̬
	PacketType Type = BlockDelWithConnect(*pEditBlock, OperateList);

	if(Type==fail)
	{
		//ʧȥȨ����ת��״̬����ͼ
		TurnMindStatus();
		CClientDC dc(this);
		PaintMind(&dc);

		//������»������
		csNetUpdata.Unlock();

		MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
		return;
	}
	else if(Type==clash)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"�����漰�������ڲ�����ӵ���������ķֿ�", L"NO", MB_OK);
		return;
	}
	else if(Type==nopermission)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
		Exit();
		return;
	}
	else if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
		return;
	}
	//������ת��״̬��ʾ
	OperateData(TheMind, OperateList);
	TurnMindStatus();
	OnMindUpdata(0, 0);

	//������»������
	csNetUpdata.Unlock();
}


//ɾ���ϲ��ӷֿ鰴ť����¼�
void EditMindDlg::OnBnClickedButtonDelcombine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(EditLimit && pEditBlock->ppr->ppr==0)
	{
		MessageBox(L"�����û�û�н����漰���ֿ��ϵ�Ĳ���Ȩ��", L"NO", MB_OK);
		return;
	}

	//������»��⿪ʼ
	csNetUpdata.Lock();

	//�����˳��ֿ�༭״̬
	PacketType Type = BlockDelCombineConnect(*pEditBlock, OperateList);

	if(Type==fail)
	{
		//ʧȥȨ����ת��״̬����ͼ
		TurnMindStatus();
		CClientDC dc(this);
		PaintMind(&dc);

		//������»������
		csNetUpdata.Unlock();

		MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
		return;
	}
	else if(Type==clash)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"�����漰�������ڲ�����ӵ���������ķֿ�", L"NO", MB_OK);
		return;
	}
	else if(Type==nopermission)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
		Exit();
		return;
	}
	else if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
		return;
	}
	//������ת��״̬��ʾ
	OperateData(TheMind, OperateList);
	TurnMindStatus();
	OnMindUpdata(0, 0);

	//������»������
	csNetUpdata.Unlock();
}


//����ӷֿ鰴ť����¼�
void EditMindDlg::OnBnClickedButtonAddchild()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//������»��⿪ʼ
	csNetUpdata.Lock();

	//���벢�����༭
	PacketType Type = BlockAddChildConnect(*pEditBlock, OperateList, pEditBlock->PosX, pEditBlock->PosY);

	if(Type==fail)
	{
		//ʧȥȨ����ת��״̬����ͼ
		TurnMindStatus();
		CClientDC dc(this);
		PaintMind(&dc);

		//������»������
		csNetUpdata.Unlock();

		MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
		return;
	}
	else if(Type==clash)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"�����漰�������ڲ�����ӵ���������ķֿ�", L"NO", MB_OK);
		return;
	}
	else if(Type==nopermission)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
		Exit();
		return;
	}
	else if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
		return;
	}
	//��������ʾ
	OperateData(TheMind, OperateList);
	OnMindUpdata(0, 0);

	//������»������
	csNetUpdata.Unlock();
}


//��Ӹ��ֿ鰴ť����¼�
void EditMindDlg::OnBnClickedButtonAddparent()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(EditLimit && pEditBlock->ppr->ppr==0)
	{
		MessageBox(L"�����û�û�н����漰���ֿ��ϵ�Ĳ���Ȩ��", L"NO", MB_OK);
		return;
	}

	//������»��⿪ʼ
	csNetUpdata.Lock();
	
	//���벢�����༭
	PacketType Type = BlockAddParentConnect(*pEditBlock, OperateList, pEditBlock->PosX, pEditBlock->PosY);

	if(Type==fail)
	{
		//ʧȥȨ����ת��״̬����ͼ
		TurnMindStatus();
		CClientDC dc(this);
		PaintMind(&dc);

		//������»������
		csNetUpdata.Unlock();

		MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
		return;
	}
	else if(Type==clash)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"�����漰�������ڲ�����ӵ���������ķֿ�", L"NO", MB_OK);
		return;
	}
	else if(Type==nopermission)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
		Exit();
		return;
	}
	else if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
		return;
	}
	//��������ʾ
	OperateData(TheMind, OperateList);
	OnMindUpdata(0, 0);

	//������»������
	csNetUpdata.Unlock();
}


//���ӵ����зֿ鰴ť����¼�
void EditMindDlg::OnBnClickedButtonLineto()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(EditLimit && pEditBlock->ppr->ppr==0)
	{
		MessageBox(L"�����û�û�н����漰���ֿ��ϵ�Ĳ���Ȩ��", L"NO", MB_OK);
		return;
	}

	ChooseLineBlock = true;
	pStaticSelLineBlock->ShowWindow(SW_SHOW);
}


//����Ϊ���ֿ鰴ť����¼�
void EditMindDlg::OnBnClickedButtonSeparateroot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//������»��⿪ʼ
	csNetUpdata.Lock();
	
	//���벢�����༭
	PacketType Type = BlockSeparateRootConnect(*pEditBlock, OperateList);

	if(Type==fail)
	{
		//ʧȥȨ����ת��״̬����ͼ
		TurnMindStatus();
		CClientDC dc(this);
		PaintMind(&dc);

		//������»������
		csNetUpdata.Unlock();

		MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
		return;
	}
	else if(Type==clash)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"�����漰�������ڲ�����ӵ���������ķֿ�", L"NO", MB_OK);
		return;
	}
	else if(Type==nopermission)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
		Exit();
		return;
	}
	else if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
		return;
	}
	//��������ʾ
	OperateData(TheMind, OperateList);
	OnMindUpdata(0, 0);

	//������»������
	csNetUpdata.Unlock();
}


//ɾ�������ӷֿ鰴ť����¼�
void EditMindDlg::OnBnClickedButtonDelseparete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//������»��⿪ʼ
	csNetUpdata.Lock();

	//�����˳��ֿ�༭״̬
	PacketType Type = BlockDelSeparateConnect(*pEditBlock, OperateList);

	if(Type==fail)
	{
		//ʧȥȨ����ת��״̬����ͼ
		TurnMindStatus();
		CClientDC dc(this);
		PaintMind(&dc);

		//������»������
		csNetUpdata.Unlock();

		MessageBox(L"ʧȥ�༭Ȩ�ޣ��޸�ʧ��", L"NO", MB_OK);
		return;
	}
	else if(Type==clash)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"�����漰�������ڲ�����ӵ���������ķֿ�", L"NO", MB_OK);
		return;
	}
	else if(Type==nopermission)
	{
		//������»������
		csNetUpdata.Unlock();
		MessageBox(L"˼ά��ͼ��ɾ�����ѱ��Ƴ������û���", L"NO", MB_OK);
		Exit();
		return;
	}
	else if(Type!=success)
	{
		//������»������
		csNetUpdata.Unlock();
		//�Ͽ����ӣ��˳�
		MessageBox(L"��������Ͽ�����", L"NO", MB_OK);
		Exit();
		return;
	}
	//������ת��״̬��ʾ
	OperateData(TheMind, OperateList);
	TurnMindStatus();
	OnMindUpdata(0, 0);

	//������»������
	csNetUpdata.Unlock();
}


//���ú�ɫ�༭���ַ������¼�
void EditMindDlg::OnChangeEditRed()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if(ColorAcceptFlag==false)
		return;

	CString string, string2;
	pEditRed->GetWindowTextW(string);
	int num = CStringTo255(string);
	
	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	//�ı�
	ColorAcceptFlag = false;
	SETR(num, pEditBlock->Color);
	string2.Format(L"%d", num);
	pSliderRed->SetPos(num);
	if(string!=string2)
	{
		pEditRed->SetWindowTextW(string2);
	}
	ColorAcceptFlag = true;
	
	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//������ɫ�༭���ַ������¼�
void EditMindDlg::OnChangeEditGreen()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if(ColorAcceptFlag==false)
		return;

	CString string, string2;
	pEditGreen->GetWindowTextW(string);
	int num = CStringTo255(string);
	
	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	//�ı�
	ColorAcceptFlag = false;
	SETG(num, pEditBlock->Color);
	string2.Format(L"%d", num);
	pSliderGreen->SetPos(num);
	if(string!=string2)
	{
		pEditGreen->SetWindowTextW(string2);
	}
	ColorAcceptFlag = true;
	
	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//������ɫ�༭���ַ������¼�
void EditMindDlg::OnChangeEditBlue()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if(ColorAcceptFlag==false)
		return;

	CString string, string2;
	pEditBlue->GetWindowTextW(string);
	int num = CStringTo255(string);
	
	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	//�ı�
	ColorAcceptFlag = false;
	SETB(num, pEditBlock->Color);
	string2.Format(L"%d", num);
	pSliderBlue->SetPos(num);
	if(string!=string2)
	{
		pEditBlue->SetWindowTextW(string2);
	}
	ColorAcceptFlag = true;
	
	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//���ú�ɫ�������ػ��¼�
void EditMindDlg::OnCustomdrawSliderRed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int num = pSliderRed->GetPos();
	if(pEditBlock && num!=GETR(pEditBlock->Color))
	{
		//���ݸ��»��⿪ʼ
		csDataUpdata.Lock();

		//�ı�
		ColorAcceptFlag = false;
		SETR(num, pEditBlock->Color);
		CString string;
		string.Format(L"%d", num);
		pEditRed->SetWindowTextW(string);
		ColorAcceptFlag = true;

		//�ػ�ͼ
		CClientDC dc(this);
		PaintMind(&dc);

		//���ݸ��»������
		csDataUpdata.Unlock();
	}
}


//������ɫ�������ػ��¼�
void EditMindDlg::OnCustomdrawSliderGreen(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int num = pSliderGreen->GetPos();
	if(pEditBlock && num!=GETG(pEditBlock->Color))
	{
		//���ݸ��»��⿪ʼ
		csDataUpdata.Lock();

		//�ı�
		ColorAcceptFlag = false;
		SETG(num, pEditBlock->Color);
		CString string;
		string.Format(L"%d", num);
		pEditGreen->SetWindowTextW(string);
		ColorAcceptFlag = true;

		//�ػ�ͼ
		CClientDC dc(this);
		PaintMind(&dc);

		//���ݸ��»������
		csDataUpdata.Unlock();
	}
}


//������ɫ�������ػ��¼�
void EditMindDlg::OnCustomdrawSliderBlue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int num = pSliderBlue->GetPos();
	if(pEditBlock && num!=GETB(pEditBlock->Color))
	{
		//���ݸ��»��⿪ʼ
		csDataUpdata.Lock();

		//�ı�
		ColorAcceptFlag = false;
		SETB(num, pEditBlock->Color);
		CString string;
		string.Format(L"%d", num);
		pEditBlue->SetWindowTextW(string);
		ColorAcceptFlag = true;

		//�ػ�ͼ
		CClientDC dc(this);
		PaintMind(&dc);

		//���ݸ��»������
		csDataUpdata.Unlock();
	}
}


//�ָ�Ϊ��ɫ��ť����¼�
void EditMindDlg::OnBnClickedButtonSetwhite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	//�ı�
	ColorAcceptFlag = false;
	pEditBlock->Color = RGB(255, 255, 255);
	CString string;
	string.Format(L"%d", 255);
	pEditRed->SetWindowTextW(string);
	pEditGreen->SetWindowTextW(string);
	pEditBlue->SetWindowTextW(string);
	pSliderRed->SetPos(255);
	pSliderGreen->SetPos(255);
	pSliderBlue->SetPos(255);
	ColorAcceptFlag = true;

	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//ѡ����״��Ͽ�ѡ��ı��¼�
void EditMindDlg::OnSelchangeComboShap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int num = pComboShape->GetCurSel();
	if(num==-1)
		assert(0);

	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	pEditBlock->Shape = (enumShape)num;

	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//ѡ������Ͽ�ѡ��ı��¼�
void EditMindDlg::OnSelchangeComboLinedir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int num = pComboLineDir->GetCurSel();
	if(num==-1)
		assert(0);

	//���ݸ��»��⿪ʼ
	csDataUpdata.Lock();

	pEditBlock->Dir = (enumDir)num;

	//�ػ�ͼ
	CClientDC dc(this);
	PaintMind(&dc);

	//���ݸ��»������
	csDataUpdata.Unlock();
}


//�����ֿ�༭��ť����¼�
void EditMindDlg::OnBnClickedButtonSetlock()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	ChooseLockBlock = true;
	pStaticSelLockBlock->ShowWindow(SW_SHOW);
}


//���÷ֿ�༭��ť����¼�
void EditMindDlg::OnBnClickedButtonSetunlock()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	ChooseUnlockBlock = true;
	pStaticSelLockBlock->ShowWindow(SW_SHOW);
}


//�����������
bool EditMindDlg::NameRule(CString &string)
{
	int len = string.GetLength();
	int i;
	if(len<1 || len>20)
		return false;
	for(i=0; i<len; i++)
	{
		if(string[i]<=256)
		{
			if(!(string[i]>='0' && string[i]<='9' || string[i]>='a' && string[i]<='z' || string[i]>='A' && string[i]<='Z'))
				return false;
		}
	}
	return true;
}


//�ַ���ѹ�����ֵ�255
int EditMindDlg::CStringTo255(CString &string)
{
	int n = string.GetLength();
	if(n>3)
		return 255;
	else if(n==3)
	{
		if(string[0]>'2' || string[0]=='2' && string[1]>'5' 
			|| string[0]=='2' && string[1]=='5' && string[2]>'5')
			return 255;
		return (string[0]-'0')*100+(string[1]-'0')*10+(string[2]-'0');
	}
	else if(n==2)
		return (string[0]-'0')*10+(string[1]-'0');
	else if(n==1)
		return (string[0]-'0');
	else
		return 0;
}


//ˢ�¹����û��б����ʾ
void EditMindDlg::RefreshShareList(bool KeepSel)
{
	int Index = pListShareList->GetCurSel();
	pListShareList->ResetContent();
	int i;
	CString string;
	int Tab[] = {80};
	pListShareList->SetTabStops(1, Tab);
	for(i=0; i<TheMind.ShareNum; i++)
	{
		string = TheMind.ShareUser[i];
		if(TheMind.UserStatus[i])
			string += L"\t����";
		pListShareList->AddString(string);
	}
	if(KeepSel)
		pListShareList->SetCurSel(Index);
}


//˼ά��ͼ��ͼ
void EditMindDlg::PaintMind(CDC *pdc)
{
	CBrush brush;
	CPen pen;
	CFont font;
	CRect rect;
	CPoint point1, point2;

	//������������λͼ
	CDC dcMem;
	CBitmap bitmap;
	dcMem.CreateCompatibleDC(pdc);
	bitmap.CreateCompatibleBitmap(pdc, rectEditArea.Width(), rectEditArea.Height());
	dcMem.SelectObject(&bitmap);
	CDC dcMem2;
	CBitmap bitmap2;
	dcMem2.CreateCompatibleDC(pdc);
	bitmap2.CreateCompatibleBitmap(pdc, rectEditArea.Width(), rectEditArea.Height());
	dcMem2.SelectObject(&bitmap2);

	//�ֱ��������λͼ
	dcMem2.FillSolidRect(rectEditArea.left, rectEditArea.top, 
		rectEditArea.Width(), rectEditArea.Height(), RGB(201,211,227));
	
	dcMem.FillSolidRect(rectEditArea.left, rectEditArea.top, 
		rectEditArea.Width(), rectEditArea.Height(), RGB(255,255,255));

	//��������ӳ��
	dcMem.SetMapMode(MM_ANISOTROPIC);
	dcMem.SetWindowExt(rectEditArea.right, rectEditArea.bottom);
	dcMem.SetViewportExt((int)(rectEditArea.right*ZoomSize[ZoomLevel]), 
		(int)(rectEditArea.bottom*ZoomSize[ZoomLevel]));
	dcMem.SetViewportOrg(CornerPoint);

	//��������
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	brush.CreateSolidBrush(RGB(0, 0, 0));
	dcMem.SelectObject(pen);
	dcMem.SelectObject(brush);
	PaintLine(&dcMem, TheMind.BlockTree.qnode->pch);
	pen.DeleteObject();
	brush.DeleteObject();

	//���Ʒֿ�
	font.CreatePointFont((int)(160/**ZoomSize[ZoomLevel]*/), _T("Times New Roman"));
	dcMem.SelectObject(font);
	dcMem.SetBkMode(TRANSPARENT);
	PaintBlock(&dcMem, TheMind.BlockTree.qnode->pch, brush, pen);
	font.DeleteObject();

	//�������ڱ༭�ֿ�������
	if(EditBlockStatus)
	{
		pen.CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		dcMem.SelectObject(pen);
		dcMem.SelectStockObject(NULL_BRUSH);
		PaintShape(&dcMem, pEditBlock->Shape, CRect(pEditBlock->PosX, pEditBlock->PosY, 
			pEditBlock->PosX+pEditBlock->Length, pEditBlock->PosY+pEditBlock->Width));
		pen.DeleteObject();
	}

	//����λͼת��
	dcMem2.StretchBlt(CornerPoint.x, CornerPoint.y, (int)(TheMind.Length*ZoomSize[ZoomLevel]), 
		(int)(TheMind.Width*ZoomSize[ZoomLevel]), &dcMem, 0, 0, TheMind.Length, TheMind.Width, SRCCOPY);

	pdc->BitBlt(rectEditArea.left, rectEditArea.top, rectEditArea.Width(), rectEditArea.Height(), 
		&dcMem2, 0, 0, SRCCOPY);
	//pdc->BitBlt(0, 0, rectEditArea.Width(), rectEditArea.Height(), &dcMem, 0, 0, SRCCOPY);

	////���ü�������
	//pdc->SetMapMode(MM_TEXT);
	//CRgn rgn;
	//rgn.CreateRectRgnIndirect(rectEditArea);
	//pdc->SelectClipRgn(&rgn);

	////���Ǳ���Ϊԭʼɫ��
	//pdc->SelectStockObject(NULL_PEN);
	//brush.CreateSolidBrush(RGB(201,211,227));
	//pdc->SelectObject(&brush);
	//pdc->Rectangle(rectBackArea);
	//brush.DeleteObject();

	////��������ӳ��
	//pdc->SetMapMode(MM_ISOTROPIC);
	//pdc->SetWindowExt(rectEditArea.right, rectEditArea.bottom);
	//pdc->SetViewportExt((int)(rectEditArea.right*ZoomSize[ZoomLevel]), 
	//	(int)(rectEditArea.bottom*ZoomSize[ZoomLevel]));
	//pdc->SetViewportOrg(CornerPoint);
	//
	////����ͼ����
	//pdc->SelectStockObject(NULL_PEN);
	//brush.CreateSolidBrush(RGB(255,255,255));
	//pdc->SelectObject(&brush);
	//point1.SetPoint(0, 0);
	//point2.SetPoint(TheMind.Length, TheMind.Width);
	//rect.SetRect(point1, point2);
	//pdc->Rectangle(rect);
	//brush.DeleteObject();

	////���Ʒֿ�
	//font.CreatePointFont((int)(100/**ZoomSize[ZoomLevel]*/), _T("Times New Roman"));
	//pdc->SelectObject(font);
	//pdc->SetBkMode(TRANSPARENT);
	//PaintBlock(pdc, TheMind.BlockTree.qnode->pch, brush, pen);
	//font.DeleteObject();

	////�������ڱ༭�ֿ�������
	//if(EditBlockStatus)
	//{
	//	pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	//	pdc->SelectObject(pen);
	//	pdc->SelectStockObject(NULL_BRUSH);
	//	PaintShape(pdc, pEditBlock->Shape, CRect(pEditBlock->PosX, pEditBlock->PosY, 
	//		pEditBlock->PosX+pEditBlock->Length, pEditBlock->PosY+pEditBlock->Width));
	//	pen.DeleteObject();
	//}
}


//˼ά��ͼ�ֿ�ݹ��ͼ
void EditMindDlg::PaintBlock(CDC *pdc, BlockNode *pBlock, CBrush &brush, CPen &pen)
{
	CRect rect;
	if(pBlock==0)
		return;
	while(pBlock->pt)
		LIST_GO(pBlock, pt);
	while(pBlock)
	{
		//�����ӷֿ�
		PaintBlock(pdc, pBlock->pch, brush, pen);

		//��������
		//��������״̬ѡ��������ʽ
		if(pBlock->Lock && pBlock->LockUser.GetLength()==0)
			pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		else if(pBlock->Lock)
			pen.CreatePen(PS_SOLID, 4, RGB(128, 128, 128));
		else
			pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		brush.CreateSolidBrush(pBlock->Color);
		pdc->SelectObject(pen);
		pdc->SelectObject(brush);
		rect.SetRect(pBlock->PosX, pBlock->PosY, 
			pBlock->PosX+pBlock->Length, pBlock->PosY+pBlock->Width);
		PaintShape(pdc, pBlock->Shape, rect);
		pen.DeleteObject();
		brush.DeleteObject();
		//��������
		pdc->DrawText(pBlock->Text, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		//����ǰ�ֵֿܷ�
		LIST_GO(pBlock, qt);
	}
}


//˼ά��ͼ���ߵݹ��ͼ
void EditMindDlg::PaintLine(CDC *pdc, BlockNode *pBlock)
{
	CRect rect;
	if(pBlock==0)
		return;
	while(pBlock->pt)
		LIST_GO(pBlock, pt);
	while(pBlock)
	{
		//�Ǹ��ֿ�����Ƹ��ֿ������
		if(pBlock->ppr->ppr)
		{
			//��������������
			CPoint pointArray[4];
			switch(pBlock->Dir)
			{
			case dirup:
				pointArray[0].SetPoint(pBlock->ppr->PosX+pBlock->ppr->Length/2, pBlock->ppr->PosY+pBlock->ppr->Width);
				pointArray[3].SetPoint(pBlock->PosX+pBlock->Length/2, pBlock->PosY);
				pointArray[1].SetPoint(pointArray[0].x, (pointArray[0].y+pointArray[3].y)/2);
				pointArray[2].SetPoint(pointArray[3].x, (pointArray[0].y+pointArray[3].y)/2);
				break;
			case dirdown:
				pointArray[0].SetPoint(pBlock->ppr->PosX+pBlock->ppr->Length/2, pBlock->ppr->PosY);
				pointArray[3].SetPoint(pBlock->PosX+pBlock->Length/2, pBlock->PosY+pBlock->Width);
				pointArray[1].SetPoint(pointArray[0].x, (pointArray[0].y+pointArray[3].y)/2);
				pointArray[2].SetPoint(pointArray[3].x, (pointArray[0].y+pointArray[3].y)/2);
				break;
			case dirleft:
				if(pBlock->ppr->Shape==eche || pBlock->ppr->Shape==para)
					pointArray[0].SetPoint(pBlock->ppr->PosX+pBlock->ppr->Length*3/4, pBlock->ppr->PosY+pBlock->ppr->Width/2);
				else
					pointArray[0].SetPoint(pBlock->ppr->PosX+pBlock->ppr->Length, pBlock->ppr->PosY+pBlock->ppr->Width/2);
				if(pBlock->Shape==eche || pBlock->Shape==para)
					pointArray[3].SetPoint(pBlock->PosX+pBlock->ppr->Length*1/4, pBlock->PosY+pBlock->Width/2);
				else
					pointArray[3].SetPoint(pBlock->PosX, pBlock->PosY+pBlock->Width/2);
				pointArray[1].SetPoint((pointArray[0].x+pointArray[3].x)/2, pointArray[0].y);
				pointArray[2].SetPoint((pointArray[0].x+pointArray[3].x)/2, pointArray[3].y);
				break;
			case dirright:
				if(pBlock->ppr->Shape==eche || pBlock->ppr->Shape==para)
					pointArray[0].SetPoint(pBlock->ppr->PosX+pBlock->ppr->Length*1/4, pBlock->ppr->PosY+pBlock->ppr->Width/2);
				else
					pointArray[0].SetPoint(pBlock->ppr->PosX, pBlock->ppr->PosY+pBlock->ppr->Width/2);
				if(pBlock->Shape==eche || pBlock->Shape==para)
					pointArray[3].SetPoint(pBlock->PosX+pBlock->Length*3/4, pBlock->PosY+pBlock->Width/2);
				else
					pointArray[3].SetPoint(pBlock->PosX+pBlock->Length, pBlock->PosY+pBlock->Width/2);
				pointArray[1].SetPoint((pointArray[0].x+pointArray[3].x)/2, pointArray[0].y);
				pointArray[2].SetPoint((pointArray[0].x+pointArray[3].x)/2, pointArray[3].y);
				break;
			}
			pdc->PolyBezier(pointArray, 4);
			//�����߻�������
			double centerX = (double)(pointArray[0].x+pointArray[3].x)/2;
			double centerY = (double)(pointArray[0].y+pointArray[3].y)/2;
			double tempDX = pointArray[3].x+pointArray[2].x-pointArray[1].x-pointArray[0].x;
			double tempDY = pointArray[3].y+pointArray[2].y-pointArray[1].y-pointArray[0].y;
			double tempDR = sqrt(tempDX*tempDX+tempDY*tempDY);
			tempDR = max(tempDR, 1);
			double proportionX = tempDX/tempDR;
			double proportionY = tempDY/tempDR;
			double len = 5;
			double temp, tempX, tempY;
			tempX = centerX+len*proportionX;
			tempY = centerY+len*proportionY;
			pointArray[0].SetPoint((int)(tempX+modf(tempX, &temp)), (int)(tempY+modf(tempY, &temp)));
			tempX = centerX-len*proportionX-len*proportionY;
			tempY = centerY-len*proportionY+len*proportionX;
			pointArray[1].SetPoint((int)(tempX+modf(tempX, &temp)), (int)(tempY+modf(tempY, &temp)));
			tempX = centerX-len*proportionX+len*proportionY;
			tempY = centerY-len*proportionY-len*proportionX;
			pointArray[2].SetPoint((int)(tempX+modf(tempX, &temp)), (int)(tempY+modf(tempY, &temp)));
			pdc->Polygon(pointArray, 3);
		}

		//�����ӷֿ�
		PaintLine(pdc, pBlock->pch);

		//����ǰ�ֵֿܷ�
		LIST_GO(pBlock, qt);
	}
}


//������״
void EditMindDlg::PaintShape(CDC *pdc, enumShape Shape, CRect &rectSize)
{
	CPoint point[8];
	int temp;
	switch(Shape)
	{
	case rect:
		pdc->Rectangle(rectSize);
		break;
	case rore:
		temp = min(rectSize.Width(), rectSize.Height())*2/3;
		point[0].SetPoint(temp, temp);
		pdc->RoundRect(rectSize, point[0]);
		break;
	case round:
		pdc->Ellipse(rectSize);
		break;
	case eche:
		point[0].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.top);
		point[1].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.top);
		point[2].SetPoint(rectSize.right, rectSize.bottom);
		point[3].SetPoint(rectSize.left, rectSize.bottom);
		pdc->Polygon(point, 4);
		break;
	case diamond:
		point[0].SetPoint((rectSize.left+rectSize.right)/2, rectSize.top);
		point[1].SetPoint(rectSize.right, (rectSize.top+rectSize.bottom)/2);
		point[2].SetPoint((rectSize.left+rectSize.right)/2, rectSize.bottom);
		point[3].SetPoint(rectSize.left, (rectSize.top+rectSize.bottom)/2);
		pdc->Polygon(point, 4);
		break;
	case para:
		point[0].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.top);
		point[1].SetPoint(rectSize.right, rectSize.top);
		point[2].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.bottom);
		point[3].SetPoint(rectSize.left, rectSize.bottom);
		pdc->Polygon(point, 4);
		break;
	case octa:
		point[0].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.top);
		point[1].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.top);
		point[2].SetPoint(rectSize.right, (3*rectSize.top+rectSize.bottom)/4);
		point[3].SetPoint(rectSize.right, (rectSize.top+3*rectSize.bottom)/4);
		point[4].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.bottom);
		point[5].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.bottom);
		point[6].SetPoint(rectSize.left, (rectSize.top+3*rectSize.bottom)/4);
		point[7].SetPoint(rectSize.left, (3*rectSize.top+rectSize.bottom)/4);
		pdc->Polygon(point, 8);
		break;
	}
}


//˼ά��ͼ�ݹ�ѡ�����ڷֿ�
BlockNode *EditMindDlg::ChoiseBlock(BlockNode *pBlock, CPoint &point)
{
	CRect rect;
	BlockNode *MyBlock = 0, *tempBlock;
	if(pBlock==0)
		return 0;
	while(pBlock->pt)
		LIST_GO(pBlock, pt);
	while(pBlock)
	{
		//�ж��ӷֿ�
		tempBlock = ChoiseBlock(pBlock->pch, point);
		if(tempBlock)
			MyBlock = tempBlock;

		//�ж�����
		rect.SetRect(pBlock->PosX, pBlock->PosY, 
			pBlock->PosX+pBlock->Length, pBlock->PosY+pBlock->Width);
		if(JustShape(pBlock->Shape, rect, point))
			MyBlock = pBlock;

		//����ǰ�ֵֿܷ�
		LIST_GO(pBlock, qt);
	}
	return MyBlock;
}


//�ж���״
bool EditMindDlg::JustShape(enumShape Shape, CRect &rectSize, CPoint &JudgePoint)
{
	CPoint point[8];
	CRgn rgn;
	switch(Shape)
	{
	case rect:
		rgn.CreateRectRgnIndirect(&rectSize);
		break;
	case round:
		rgn.CreateEllipticRgnIndirect(&rectSize);
		break;
	case rore:
		rgn.CreateRoundRectRgn(rectSize.left, rectSize.top, rectSize.right, rectSize.bottom, 
			rectSize.Width()/3, rectSize.Height()/3);
		break;
	case eche:
		point[0].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.top);
		point[1].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.top);
		point[2].SetPoint(rectSize.right, rectSize.bottom);
		point[3].SetPoint(rectSize.left, rectSize.bottom);
		rgn.CreatePolygonRgn(point, 4, ALTERNATE);
		break;
	case diamond:
		point[0].SetPoint((rectSize.left+rectSize.right)/2, rectSize.top);
		point[1].SetPoint(rectSize.right, (rectSize.top+rectSize.bottom)/2);
		point[2].SetPoint((rectSize.left+rectSize.right)/2, rectSize.bottom);
		point[3].SetPoint(rectSize.left, (rectSize.top+rectSize.bottom)/2);
		rgn.CreatePolygonRgn(point, 4, ALTERNATE);
		break;
	case para:
		point[0].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.top);
		point[1].SetPoint(rectSize.right, rectSize.top);
		point[2].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.bottom);
		point[3].SetPoint(rectSize.left, rectSize.bottom);
		rgn.CreatePolygonRgn(point, 4, ALTERNATE);
		break;
	case octa:
		point[0].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.top);
		point[1].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.top);
		point[2].SetPoint(rectSize.right, (3*rectSize.top+rectSize.bottom)/4);
		point[3].SetPoint(rectSize.right, (rectSize.top+3*rectSize.bottom)/4);
		point[4].SetPoint((rectSize.left+3*rectSize.right)/4, rectSize.bottom);
		point[5].SetPoint((3*rectSize.left+rectSize.right)/4, rectSize.bottom);
		point[6].SetPoint(rectSize.left, (rectSize.top+3*rectSize.bottom)/4);
		point[7].SetPoint(rectSize.left, (3*rectSize.top+rectSize.bottom)/4);
		rgn.CreatePolygonRgn(point, 8, ALTERNATE);
		break;
	}
	return (rgn.PtInRegion(JudgePoint)!=0);
}


//ͼ������ת��ʵ����
CPoint EditMindDlg::ImageToReal(const CPoint &point)
{
	CPoint NewPoint;
	NewPoint.x = CornerPoint.x+(int)(point.x*ZoomSize[ZoomLevel]);
	NewPoint.y = CornerPoint.y+(int)(point.y*ZoomSize[ZoomLevel]);
	return NewPoint;
}
//��ʵ����תͼ������
CPoint EditMindDlg::RealToImage(const CPoint &point)
{
	CPoint NewPoint;
	NewPoint.x = (int)((point.x-CornerPoint.x)/ZoomSize[ZoomLevel]);
	NewPoint.y = (int)((point.y-CornerPoint.y)/ZoomSize[ZoomLevel]);
	return NewPoint;
}


//ת���ֿ�༭״̬
void EditMindDlg::TurnBlockStatus(BlockNode *pBlock)
{
	//ת��״̬��
	EditBlockStatus = true;
	pEditBlock = pBlock;
	LBottonStatus = false;

	ChooseLockBlock = false;
	ChooseUnlockBlock = false;
	pStaticSelLockBlock->ShowWindow(SW_HIDE);

	//��ʼ���ؼ�����
	//�ֿ����ֱ༭��
	pEditBlockText->SetWindowTextW(pEditBlock->Text);
	LastBlockText = pEditBlock->Text;
	//�ֿ�������̬��
	if(pBlock->LockUser.GetLength()==0)
		pStaticLock->SetWindowTextW(L"�˷ֿ鹲���û������޸�");
	else
		pStaticLock->SetWindowTextW(L"�˷ֿ鹲���û������޸�");
	//������ɫ�༭��
	ColorAcceptFlag = false;
	CString string;
	string.Format(L"%d", GETR(pEditBlock->Color));
	pEditRed->SetWindowTextW(string);
	string.Format(L"%d", GETG(pEditBlock->Color));
	pEditGreen->SetWindowTextW(string);
	string.Format(L"%d", GETB(pEditBlock->Color));
	pEditBlue->SetWindowTextW(string);
	ColorAcceptFlag = true;
	//������ɫ������
	pSliderRed->SetPos(GETR(pEditBlock->Color));
	pSliderGreen->SetPos(GETG(pEditBlock->Color));
	pSliderBlue->SetPos(GETB(pEditBlock->Color));
	//������״��Ͽ�
	pComboShape->SetCurSel(pEditBlock->Shape);
	//���÷�����Ͽ�
	pComboLineDir->SetCurSel(pEditBlock->Dir);

	int i;
	//�л��ؼ���ʾ
	for(i=0; i<sizeof(MindFreeItem)/sizeof(int); i++)
		pMindFreeItem[i]->ShowWindow(SW_HIDE);
	for(i=0; i<sizeof(MindLimitItem)/sizeof(int); i++)
		pMindLimitItem[i]->ShowWindow(SW_HIDE);
	for(i=0; i<sizeof(BlockFreeItem)/sizeof(int); i++)
		pBlockFreeItem[i]->ShowWindow(SW_SHOW);
	for(i=0; i<sizeof(BlockLimitItem)/sizeof(int); i++)
		pBlockLimitItem[i]->ShowWindow(SW_SHOW);
}
//ת����ͼ�༭״̬
void EditMindDlg::TurnMindStatus()
{
	//ת��״̬��
	EditBlockStatus = false;
	pEditBlock = 0;

	ChooseLineBlock = false;
	pStaticSelLineBlock->ShowWindow(SW_HIDE);


	int i;
	//�л��ؼ���ʾ
	for(i=0; i<sizeof(MindFreeItem)/sizeof(int); i++)
		pMindFreeItem[i]->ShowWindow(SW_SHOW);
	for(i=0; i<sizeof(MindLimitItem)/sizeof(int); i++)
		pMindLimitItem[i]->ShowWindow(SW_SHOW);
	for(i=0; i<sizeof(BlockFreeItem)/sizeof(int); i++)
		pBlockFreeItem[i]->ShowWindow(SW_HIDE);
	for(i=0; i<sizeof(BlockLimitItem)/sizeof(int); i++)
		pBlockLimitItem[i]->ShowWindow(SW_HIDE);
}


//�˳�
void EditMindDlg::Exit()
{
	::SendMessage(pTimerDlg->m_hWnd, WM_CLOSE, 0, 0);
	CDialogEx::OnCancel();
}
