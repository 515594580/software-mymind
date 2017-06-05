#pragma once


// EditMindDlg �Ի���

/*
���̣߳�
��Ӧ��Ϣ��
���û��༭˼ά��ͼ��Ϊ��������������ϴ��κ��ӳ��ϴ���
�����ϴ�����������룬���������棬
�ӳ��ϴ�����־λ����ʱ���̣߳��ȴ���ʱ���߳��ϴ�
�ֿ�༭Ϊ������ͷ�����
����ֿ�ʱ������ֿ�ͬʱ�������
ע���ʱ����ķֿ���ܻ�ı�ֿ鶨λ���飬�ɷ���������
���ص��µķֿ鶨λ���飬ʹ�ô˽��зֿ�༭
����ֿ�༭ָ�룬ʹ�ø��½ṹ����Ӱ��༭
�ͷŷֿ�ͬ���ͷŷֿ�ͬʱ�������
�ı䶨λ����ͬ��
ע�ⲻ�ڱ���ֱ�Ӳ����ֿ���£����ܻ�ʧ�ܻ���ǰ����������ϵ����
�ɷ���������������ֻ�账���صĲ���������
��ϵ�������ڷֿ������ͷ�֮�䣬��ʱҪ���������������
֮��Ҳ�᷵�ز�������
�߼��ɷ�����ά�����ͻ��˽��в�������

�ڶ��̣߳�
ʱ���жϿ���0.2s
��ʱ��������������
�������û�������־λ��λʱ�ϴ���ͼ��Ϣͬʱ���͸�������
�½���ͼ�����洢���ظ��£���֤��ʱ�����ճ��
��ͼ������Ȩ�޿��ƣ��ֿ������������ƣ���ϵ���²�Ӱ��ָ��
�ʵڶ��̲߳��ᷢ���༭��ͻ

�߳�ͬ����
���������ٽ����������ٽ����������ٽ���
�����ٽ����߼��ϰ��������ٽ���
���ڼ�ʱ���̣߳�˳��Ϊ��
{
�����ٽ�������
�����ٽ�������
������Ϊ
�����ٽ�������
�����ٽ�������
�����ٽ�������
������Ϊ
�����ٽ�������
}
�����߳���Ҫ�������ʱ��ʹ�������ٽ���
��Ҫ���ݲ���ʱ��ʹ�������ٽ���

*/


#define WM_MIND_UPDATA WM_USER+1
#define WM_INTERNET_ERROR WM_USER+2

#define GETR(r) ((BYTE)(r))
#define GETG(g) ((BYTE)((g)>>8))
#define GETB(b) ((BYTE)((b)>>16))
#define SETR(r, color) ((color) = (color)&(0xFFFF00)|(BYTE)(r))
#define SETG(g, color) ((color) = (color)&(0xFF00FF)|((BYTE)(g)<<8))
#define SETB(b, color) ((color) = (color)&(0x00FFFF)|((BYTE)(b)<<16))


class EditMindDlg : public CDialogEx
{
	//��Ԫ
	friend class COurMindClientDlg;//����


	DECLARE_DYNAMIC(EditMindDlg)

public:
	EditMindDlg(const bool EditLimit, CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~EditMindDlg();

// �Ի�������
	enum { IDD = IDD_EDITMINDDLG };

	//����
public:
	//˼ά��ͼ�������
	MindNode TheMind;//��ǰ˼ά��ͼ��Ϊ���ƶ�������
	const bool EditLimit;//�༭����
	ListTemplet<class OperateNode> OperateList;//���ղ�������

	//˼ά��ͼ��ͼ����
	CRect rectEditArea;//�༭����
	CRect rectBackArea;//��������
	CPoint CornerPoint;//�ǵ�����
	int ZoomLevel;//���ŵȼ�
	const static double ZoomSize[];//���ųߴ�
	const static int MaxZoomLevel;//������ŵȼ�
	const static int DefaultZoom;//Ĭ�����ŵȼ�

	//˼ά��ͼ״̬����
	bool EditBlockStatus;//�༭�ڵ�״̬
	BlockNode *pEditBlock;//�༭�ڵ�
	bool LBottonStatus;//������״̬
	CPoint LBottonPoint;//����������
	double LBottonZoom;//�Ҽ�������ż�¼
	bool RBottonStatus;//�Ҽ����״̬
	CPoint RBottonPoint;//�Ҽ��������
	bool ChooseLineBlock;//ѡ�����߷ֿ�״̬
	bool ChooseLockBlock;//ѡ�������ֿ�״̬
	bool ChooseUnlockBlock;//ѡ������ֿ�״̬

	//�߳�ͬ��
	CWinThread *pThread;//ͬ���������߳�
	class TimerDlg *pTimerDlg;//������ͬ���̴߳���
	CCriticalSection csNetUpdata;//��������ٽ���
	CCriticalSection csDataUpdata;//���ݸ����ٽ���

	//�ؼ�ָ�뼰�丨������
	CEdit *pEditMindName;//��ͼ���ֱ༭��
	CString LastMindName;//��ͼ���ָ�������
	CListBox *pListShareList;//�����û��б��
	CEdit *pEditAddShare;//��ӹ����û��༭��
	CStatic *pStaticEditNum;//�༭������̬��
	CStatic *pStaticShareNum;//����������̬��
	CButton *pCheckReadOnly;//ֻ����ѡ��ť
	CButton *pCheckSetWith;//����������ѡ��ť
	bool SetWith;//��������״̬����
	CEdit *pEditBlockText;//�ֿ����ֱ༭��
	CString LastBlockText;//�ֿ����ָ�������
	CStatic *pStaticLock;//�ֿ�������̬��
	CEdit *pEditRed;//���ú�ɫ�༭��
	CEdit *pEditGreen;//������ɫ�༭��
	CEdit *pEditBlue;//������ɫ�༭��
	bool ColorAcceptFlag;//��ɫ�����ⲿ�仯��־
	CSliderCtrl *pSliderRed;//���ú�ɫ������
	CSliderCtrl *pSliderGreen;//������ɫ������
	CSliderCtrl *pSliderBlue;//������ɫ������
	CComboBox *pComboShape;//ѡ����״��Ͽ�
	CStatic *pStaticSelLineBlock;//ѡ�����ӷֿ龲̬��
	CStatic *pStaticSelLockBlock;//ѡ�������ֿ龲̬��
	CComboBox *pComboLineDir;//ѡ������Ͽ�

	//�оٿؼ�ID
protected:
	const static int MindFreeItem[];//˼ά��ͼ�����ƿؼ�
	const static int MindLimitItem[];//˼ά��ͼ���ƿؼ�
	const static int BlockFreeItem[];//�ֿ������ƿؼ�
	const static int BlockLimitItem[];//�ֿ����ƿؼ�
	const static int AlwaysHideItem[];//�����ؿؼ�
	CWnd *pMindFreeItem[100];//˼ά��ͼ�����ƿؼ�ָ��
	CWnd *pMindLimitItem[100];//˼ά��ͼ���ƿؼ�ָ��
	CWnd *pBlockFreeItem[100];//�ֿ������ƿؼ�ָ��
	CWnd *pBlockLimitItem[100];//�ֿ����ƿؼ�ָ��
	CWnd *pAlwaysHideItem[100];//�����ؿؼ�ָ��

	//����
protected:
	static UINT ThreadFunc(LPVOID pParam);//ͬ���������̻߳ص�����
	bool NameRule(CString &string);//�����������
	int CStringTo255(CString &string);//�ַ���ѹ�����ֵ�255
	void RefreshShareList(bool KeepSel);//ˢ�¹����û��б����ʾ
	void PaintMind(CDC *pdc);//˼ά��ͼ��ͼ
	void PaintBlock(CDC *pdc, BlockNode *pBlock, CBrush &brush, CPen &pen);//˼ά��ͼ�ֿ�ݹ��ͼ
	void PaintLine(CDC *pdc, BlockNode *pBlock);//˼ά��ͼ���ߵݹ��ͼ
	void EditMindDlg::PaintShape(CDC *pdc, enumShape Shape, CRect &rect);//������״
	BlockNode *ChoiseBlock(BlockNode *pBlock, CPoint &point);//˼ά��ͼ�ݹ�ѡ�����ڷֿ�
	bool JustShape(enumShape Shape, CRect &rectSize, CPoint &JudgePoint);//�ж���״
	CPoint ImageToReal(const CPoint &point);//ͼ������ת��ʵ����
	CPoint RealToImage(const CPoint &point);//��ʵ����תͼ������
	void TurnBlockStatus(BlockNode *pBlock);//ת���ֿ�༭״̬
	void TurnMindStatus();//ת����ͼ�༭״̬
	void ProcessKeyDown(WPARAM Key);//������Ϣ����
	void Exit();//�˳�����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnChangeEditMindname();
	afx_msg void OnKillfocusEditMindname();
protected:
	afx_msg LRESULT OnMindUpdata(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInternetError(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonAddshare();
	afx_msg void OnBnClickedButtonDelshare();
	afx_msg void OnClickedCheckReadonly();
	afx_msg void OnClickedCheckSetwith();
	afx_msg void OnBnClickedButtonAddroot();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChangeEditBlocktext();
	afx_msg void OnKillfocusEditBlocktext();
	afx_msg void OnBnClickedButtonDelwith();
	afx_msg void OnBnClickedButtonDelcombine();
	afx_msg void OnBnClickedButtonAddchild();
	afx_msg void OnBnClickedButtonAddparent();
	afx_msg void OnBnClickedButtonLineto();
	afx_msg void OnBnClickedButtonSeparateroot();
	afx_msg void OnBnClickedButtonDelseparete();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnChangeEditRed();
	afx_msg void OnChangeEditGreen();
	afx_msg void OnChangeEditBlue();
	afx_msg void OnCustomdrawSliderRed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderGreen(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderBlue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSetwhite();
	afx_msg void OnSelchangeComboShap();
	afx_msg void OnSelchangeComboLinedir();
	afx_msg void OnBnClickedButtonSetlock();
	afx_msg void OnBnClickedButtonSetunlock();
};