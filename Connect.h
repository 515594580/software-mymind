
#pragma once

//���紦���ļ�"


extern CString g_ServerIp;
extern sockaddr_in g_ServerSocket;//�������׽���


/****************************************************************/
/*************************������ͬ����ʼ*************************/
/****************************************************************/

#define SERVER_PORT "12345"


//tcp���ϼ�Э��
enum PacketType
{
	//��־λ
	defaultvalue,//ȱʡֵ
	error,//���Ӵ���
	success,//�ɹ�
	fail,//ʧ��
	nopermission,//û��Ȩ��
	clash,//��ͻ

	//�û���Ϣ����
	hello,//���ӷ�����
	login,//��¼
	regist,//ע��
	change,//�޸���Ϣ
	logout,//ע��
	getlist,//�����ȡ˼ά��ͼ�б�
	newmind,//�½�˼ά��ͼ
	selmind,//ѡ��˼ά��ͼ
	delmind,//ɾ��˼ά��ͼ
	editend,//�����༭

	//��ͼ�༭����
	changename,//��������
	addshare,//��ӹ����û�
	delshare,//ɾ�������û�
	lockblock,//��������������
	upmind,//�ϴ�˼ά��ͼ
	keepmind,//�޸ı�˼ά��ͼ
	downmind,//����˼ά��ͼ
	applyblock,//����༭�ֿ�
	finishblock,//��ɷֿ�༭
	blockaddroot,//��Ӹ��ֿ�
	blockdelwith,//�ֿ�ɾ�������ӷֿ�
	blockdelcombine,//�ֿ�ɾ���ϲ��ӷֿ�
	blockaddchild,//�ֿ�����ӷֿ�
	blockaddparent,//�ֿ���븸�ֿ�
	blocklineto,//�ֿ����ӵ��·ֿ�
	blockseparateroot,//�ֿ����Ϊ���ֿ�
	blockdelseparate,//�ֿ�ɾ�������ӷֿ�

};


//��֤���ճ��Ⱥ���
void CertainRecv(SOCKET sock, void *buf, int len);


//����CString
void SendCString(SOCKET sock, CString &string);


//����CString
void RecvCString(SOCKET sock, CString &string);

/****************************************************************/
/*************************������ͬ������*************************/
/****************************************************************/



//�����ʼ������
void ConnetcInit();


//���Է�����ip����
bool TestServerIp(CString &Ip);


//��¼���罻��
PacketType LoginConnect(CString &UserId, CString &Password);


//ע�����罻��
PacketType RegistConnect(CString &UserId, CString &Password);


//�޸���Ϣ���罻��
PacketType ChangeConnect(CString &UserId, CString &Password, CString &Password2);


//�����ȡ˼ά��ͼ�б�
PacketType GetListConnect(ListTemplet<MindNode> &MyMindList, ListTemplet<MindNode> &OurMindList);


//�½�˼ά��ͼ
PacketType NewMindConnect(MindNode &RcvMind);


//ѡ��˼ά��ͼ
PacketType SelMindConnect(MindNode &RcvMind, MindNode &TheMind);


//ɾ��˼ά��ͼ
PacketType DelMindConnect(CString MindName);


//֪ͨ�����༭
PacketType EditEndConnect();


//֪ͨ��������
PacketType ChangeNameConnect(CString &Name);


//��ӹ����û�
PacketType AddShareConnect(CString UserId);


//ɾ�������û�
PacketType DelShareConnect(CString UserId);


//֪ͨ������������
PacketType LockBlockConnect(int Deep, int Local[], ListTemplet<class OperateNode> &OperateList, 
							bool IsLock, bool SetWith);


//�ϴ�˼ά��ͼ
PacketType UpMindConnect(MindNode &TheMind, ListTemplet<class OperateNode> &OperateList);


//����˼ά��ͼ
PacketType KeepMindConnect(ListTemplet<class OperateNode> &OperateList);


//����˼ά��ͼ
PacketType DownMindConnect(ListTemplet<class OperateNode> &OperateList);


//֪ͨ����ֿ�༭
PacketType ApplyBlockConnect(int Local[], int Deep, ListTemplet<class OperateNode> &OperateList);


//֪ͨ��ɷֿ�༭
PacketType FinishBlockConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList);


//֪ͨ��Ӹ��ֿ�
PacketType BlockAddRootConnect(int x, int y, ListTemplet<class OperateNode> &OperateList);


//֪ͨɾ�������ӷֿ�
PacketType BlockDelWithConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList);


//֪ͨɾ���ϲ��ӷֿ�
PacketType BlockDelCombineConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList);


//֪ͨ����ӷֿ�
PacketType BlockAddChildConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList, 
								int x, int y);


//֪ͨ���븸�ֿ�
PacketType BlockAddParentConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList, 
								 int x, int y);


//֪ͨ���ӵ����зֿ�
PacketType BlockLineToConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList, 
								 int Deep, int Local[]);


//֪ͨ����Ϊ���ֿ�
PacketType BlockSeparateRootConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList);


//֪ͨ����Ϊ���ֿ�
PacketType BlockDelSeparateConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList);
