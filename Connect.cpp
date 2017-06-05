
//���紦���ļ�


#include "stdafx.h"
#include "OurMindClient.h"
#include "OurMindClientDlg.h"


CString g_ServerIp;//�󶨷�����IP
sockaddr_in g_ServerSocket;//�������׽���



/****************************************************************/
/*************************������ͬ����ʼ*************************/
/****************************************************************/
//��֤���ճ��Ⱥ���
void CertainRecv(SOCKET sock, void *buf, int len)
{
	static char buf2[100000];
	int num = 0;
	int temp;
	while(num<len)
	{
		temp = recv(sock, buf2+num, len-num, 0);
		if(temp>0)
			num += temp;
	}
	memcpy(buf, buf2, len);
}


//����CString
void SendCString(SOCKET sock, CString &string)
{
	int len = string.GetLength()+1;
	send(sock, (char *)&len, sizeof(int), 0);
	send(sock, (char *)(LPCWSTR)string, sizeof(wchar_t)*len, 0);//�û���
}


//����CString
void RecvCString(SOCKET sock, CString &string)
{
	static wchar_t buf[100000] = {0};
	int len;
	CertainRecv(sock, &len, sizeof(int));
	CertainRecv(sock, buf, sizeof(wchar_t)*len);
	string = buf;
}
/****************************************************************/
/*************************������ͬ������*************************/
/****************************************************************/



//�����ʼ������
void ConnetcInit()
{
	WSADATA wsaData;
    int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
    if ( iResult != NO_ERROR )
        //printf("Error at WSAStartup()\n");
		assert(0);
}


//���Է�����ip����
bool TestServerIp(CString &Ip)
{
	
    //set up the connection�������ӣ�������ǶԷ���ip�˿�
    g_ServerSocket.sin_family = AF_INET;
    g_ServerSocket.sin_addr.s_addr = inet_addr(CT2A(Ip));// "127.0.0.1" );
    g_ServerSocket.sin_port = htons(atoi(SERVER_PORT));

	//�������ӷ�����
	SOCKET ConnectSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if (ConnectSocket==INVALID_SOCKET)
	{
		//printf( "Error at socket(): %ld\n", WSAGetLastError() );
		assert(0);
	}

	//�����Ӳ��ϣ��򷵻�false
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
	{
		return false;
	}
	
	//�������ӱ�־��
	PacketType type;
	type = hello;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);

	//�������ݰ�
	CertainRecv(ConnectSocket, &type, sizeof(type));
	bool result;
	if(type==success)
		result = true;
	else
		result = false;

	//�Ͽ�����
	closesocket(ConnectSocket);

	return result;
}


//��¼���罻��
PacketType LoginConnect(CString &UserId, CString &Password)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = login;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, UserId);//�û���
	SendCString(ConnectSocket, Password);//����
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//ע�����罻��
PacketType RegistConnect(CString &UserId, CString &Password)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = regist;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, UserId);//�û���
	SendCString(ConnectSocket, Password);//����
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//�޸���Ϣ���罻��
PacketType ChangeConnect(CString &UserId, CString &Password, CString &Password2)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = change;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, UserId);//�û���
	SendCString(ConnectSocket, Password);//����
	SendCString(ConnectSocket, Password2);//������
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//�����ȡ˼ά��ͼ�б�
PacketType GetListConnect(ListTemplet<MindNode> &MyMindList, ListTemplet<MindNode> &OurMindList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = getlist;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	MyMindList.Recv(ConnectSocket);//ӵ��˼ά��ͼ�б�
	OurMindList.Recv(ConnectSocket);//����˼ά��ͼ�б�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return success;
}


//�½�˼ά��ͼ
PacketType NewMindConnect(MindNode &RcvMind)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = newmind;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	RcvMind.Recv(ConnectSocket);//��˼ά��ͼ
	RcvMind.BlockTree.Recv(ConnectSocket);//��˼ά��ͼ�ֿ���

	//�Ͽ�����
	closesocket(ConnectSocket);
	return success;
}


//ѡ��˼ά��ͼ
PacketType SelMindConnect(MindNode &RcvMind, MindNode &TheMind)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = selmind;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	SendCString(ConnectSocket, TheMind.UserId);//ӵ����
	SendCString(ConnectSocket, TheMind.MindName);//˼ά��ͼ����
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
	{
		RcvMind.Recv(ConnectSocket);//˼ά��ͼ
		RcvMind.BlockTree.Recv(ConnectSocket);//˼ά��ͼ�ֿ���
	}

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//ɾ��˼ά��ͼ
PacketType DelMindConnect(CString MindName)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = delmind;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	SendCString(ConnectSocket, MindName);//˼ά��ͼ��

	//�Ͽ�����
	closesocket(ConnectSocket);
	return success;
}


//֪ͨ�����༭
PacketType EditEndConnect()
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = editend;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���

	//�Ͽ�����
	closesocket(ConnectSocket);
	return success;
}


//֪ͨ��������
PacketType ChangeNameConnect(CString &Name)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = changename;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	SendCString(ConnectSocket, Name);//������
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//��ӹ����û�
PacketType AddShareConnect(CString UserId)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = addshare;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	SendCString(ConnectSocket, UserId);//�����û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//ɾ�������û�
PacketType DelShareConnect(CString UserId)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = delshare;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	SendCString(ConnectSocket, UserId);//�����û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ������������
PacketType LockBlockConnect(int Deep, int Local[], ListTemplet<class OperateNode> &OperateList, 
							bool IsLock, bool SetWith)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = lockblock;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	send(ConnectSocket, (char *)&Deep, sizeof(Deep), 0);//��λ����
	send(ConnectSocket, (char *)Local, sizeof(int)*Deep, 0);//��λ����
	send(ConnectSocket, (char *)&IsLock, sizeof(IsLock), 0);//�Ƿ�����
	send(ConnectSocket, (char *)&SetWith, sizeof(SetWith), 0);//��������
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//�ϴ�˼ά��ͼ
PacketType UpMindConnect(MindNode &TheMind, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = upmind;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	TheMind.Send(ConnectSocket);//˼ά��ͼ
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//����˼ά��ͼ
PacketType KeepMindConnect(ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = keepmind;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//����˼ά��ͼ
PacketType DownMindConnect(ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = downmind;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success || type==fail)
		OperateList.Recv(ConnectSocket);//��������

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ����ֿ�༭
PacketType ApplyBlockConnect(int Local[], int Deep, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = applyblock;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	send(ConnectSocket, (char *)&Deep, sizeof(Deep), 0);//���
	send(ConnectSocket, (char *)Local, sizeof(int)*Deep, 0);//��λ����
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ��ɷֿ�༭
PacketType FinishBlockConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = finishblock;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	TheBlock.Send(ConnectSocket);//�ֿ�����
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ��Ӹ��ֿ�
PacketType BlockAddRootConnect(int x, int y, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blockaddroot;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	send(ConnectSocket, (char *)&x, sizeof(x), 0);//����x
	send(ConnectSocket, (char *)&y, sizeof(y), 0);//����y
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨɾ�������ӷֿ�
PacketType BlockDelWithConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blockdelwith;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨɾ���ϲ��ӷֿ�
PacketType BlockDelCombineConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blockdelcombine;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ����ӷֿ�
PacketType BlockAddChildConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList, 
								int x, int y)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blockaddchild;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	send(ConnectSocket, (char *)&x, sizeof(x), 0);//����x
	send(ConnectSocket, (char *)&y, sizeof(y), 0);//����y
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ���븸�ֿ�
PacketType BlockAddParentConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList, 
								 int x, int y)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blockaddparent;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	send(ConnectSocket, (char *)&x, sizeof(x), 0);//����x
	send(ConnectSocket, (char *)&y, sizeof(y), 0);//����y
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ���ӵ����зֿ�
PacketType BlockLineToConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList, 
								 int Deep, int Local[])
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blocklineto;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	send(ConnectSocket, (char *)&Deep, sizeof(Deep), 0);//��λ����
	send(ConnectSocket, (char *)Local, sizeof(int)*Deep, 0);//��λ����
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ����Ϊ���ֿ�
PacketType BlockSeparateRootConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blockseparateroot;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}


//֪ͨ����Ϊ���ֿ�
PacketType BlockDelSeparateConnect(BlockNode &TheBlock, ListTemplet<class OperateNode> &OperateList)
{
	//���ӷ�����
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ConnectSocket, (SOCKADDR*)&g_ServerSocket, sizeof(g_ServerSocket))==SOCKET_ERROR)//�������ӣ��ҵ�socket������Է�socket����
		return error;

	//��������
	PacketType type;
	type = blockdelseparate;
	send(ConnectSocket, (char *)&type, sizeof(type), 0);//����
	SendCString(ConnectSocket, g_UserId);//�û���
	//��������
	CertainRecv(ConnectSocket, &type, sizeof(type));//��־
	if(type==success)
		OperateList.Recv(ConnectSocket);//��������
	else if(type==fail)
		TheBlock.Recv(ConnectSocket);//�ָ��ֿ�

	//�Ͽ�����
	closesocket(ConnectSocket);
	return type;
}

