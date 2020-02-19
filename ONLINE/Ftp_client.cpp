#include"Ftp_client.h"
#include<iostream>
#include<sstream> 
#include<fstream>

#define LOCAL_HOST "127.0.0.1"
#define PORT 21
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"msvcrtd.lib")
using namespace std;


FTP::FTP()
{
	filepath.clear();
	memset(sendbuff, 0, sizeof(sendbuff));
	memset(recbuffer, 0, sizeof(recbuffer));
	memset(ip, 0, sizeof(ip));
}

FTP::~FTP()
{
	closesocket(sock_ctrl);
	closesocket(sock_data);
	WSACleanup();
}
void FTP::set_userInfo(std::shared_ptr<usr_psd> &temp)
{
	info = temp;
}
/*
 function: create the sock necessary for TCP communication
 written by Qiu Zenghui 
 date : 2016-09-29
*/
bool FTP::creatSock()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err, result;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return false;
	}
	sock_ctrl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_ctrl == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}
/*


*/
bool FTP::login()
{
	struct sockaddr_in server;
	struct hostent *hp = nullptr;
	string errorinfo;
	memset(recbuffer, 0, sizeof(recbuffer));
	int ret, renum;
	hp = gethostbyname(info->get_ip().c_str());
	if (hp != nullptr)
	{
		server.sin_addr.S_un.S_addr = *(int *)(*hp->h_addr_list);  //get the ip address by the url
		strcpy_s(ip, inet_ntoa(server.sin_addr));
	}
	else
	{
		server.sin_addr.S_un.S_addr = inet_addr(info->get_ip().c_str());
	}
	server.sin_port = htons(21);
	server.sin_family = AF_INET;
	ret = connect(sock_ctrl, (sockaddr *)&server, sizeof(server));
 	if (ret == SOCKET_ERROR)
	{
		errorinfo = "connect failed please check the ip address or the network";
//		throw(errorinfo);
        return false;
	}
	renum = send_command(string("FTP"));
	Sleep(100);
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
//	cout <<"aaa::"<< recbuffer << endl;
	if (!check_response('2'))
	{
		return false;
	}
	renum = send_command("USER "+info->get_usr());
	Sleep(10);
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
//	cout << "aaa::" << recbuffer << endl;
	if (!check_response('3')) // the correct response is 331
	{
		return false;
	}
	renum = send_command("PASS "+info->get_psd());
	memset(recbuffer, 0, sizeof(recbuffer));
	Sleep(10);
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
///	cout << "aaa::" << recbuffer << endl;
	if (!check_response('2')) // the correct response is 230
	{
		return false;
	}
	CurrentDir = "/";
	return true;
}

/*
 function�� sedncommand,use to send anything to the server host and return the number of bytes
 written by Qiu Zenghui 
 2016-09-30
*/
int FTP::send_command(basic_string<char> s)
{
	int num;
	string temp = s + "\r\n";
	memset(sendbuff, 0, sizeof(sendbuff));
	temp.copy(sendbuff, temp.length());
	num = send(sock_ctrl, sendbuff, strlen(sendbuff), 0);
	return num;
}
/*
	type : bool 
	function: use to check whether the response from the server is right or not
	wrtten by Qiu Zenghui
*/
bool FTP::check_response(char a)
{
	if (recbuffer[0] != a)
		return false;
	else
		return true;
}
/*
	function:: use to make the 
*/
bool FTP::open_datatrs()
{
	int port1, port2;
	sock_data = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	cout << sock_ctrl << endl;
//	memset(recbuffer, 0, sizeof(recbuffer));
	send_command(string("PASV"));
	Sleep(10);
	int num = 0;
	num = recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	if (num < 0)
	{
		cout << "error code "<< WSAGetLastError() << endl;
		return false;
	}
//	cout << recbuffer << endl;
	if (!check_response('2'))
	{
		return false;
	}
	get_port_from_pasv(string(recbuffer), port1, port2);
	struct sockaddr_in temp;
	temp.sin_addr.S_un.S_addr = inet_addr(ip);
	temp.sin_family = AF_INET;
	temp.sin_port = htons(256 * port1 + port2);
	int ret = connect(sock_data, (sockaddr*)&temp, sizeof(temp));
	if (ret == SOCKET_ERROR)
		return false;
	else
		return true;
}

/*
 
*/
void FTP::get_port_from_pasv(basic_string<char> s, int &p1, int &p2)
{
	string str1, str2;
	int temp = s.rfind(',');    //  227 Entering Passive Mode (10,10,98,16,253,63).
	int index_1, index_2;
	index_1 = s.rfind(',', temp - 1);
	str1.assign(s, index_1 + 1, temp - index_1 - 1);
	index_2 = s.find(')', index_1);
	str2.assign(s, temp + 1, index_2 - temp - 1);
	//std::cout << str1 << endl;
	stringstream ss;
	ss << str1;
	ss >> p1;
	ss.clear();
	ss.str("");
	ss << str2;
	ss >> p2;
	//return 0;
}
/*
use to check whether the socket is connected or not
written by Qiu Zenghui
date:2016-10-04
*/

bool FTP::check_sock_alive(SOCKET &clientSocket)
{

	char buff[32];
	char *send_buff = "helo\r\n";
	send(clientSocket, send_buff, strlen(send_buff), 0);
	Sleep(50);
	int recvBytes = recv(clientSocket, buff, sizeof(buff), MSG_PEEK);
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	int sockErr = errno;

	//cout << "In close function, recv " << recvBytes << " bytes, err " << sockErr << endl;  

	if (recvBytes > 0) //Get data  
		return true;

	if ((recvBytes == -1) && (sockErr == EWOULDBLOCK)) //No receive data  
		return false;

	return true;;
}
/*
function : to get the director and the files of the current directory

*/
bool FTP::cmd_list()
{
	string cmd = "LIST";
	int temp;
	if (!check_sock_alive(sock_ctrl))
	{
		string error = "socket has been closed,please connect again";
		throw error;
	}
	if (!open_datatrs())
	{
		return false;    //failed beacuse of the failure of data sock connect
	}
	send_command(cmd);
	memset(recbuffer, 0, sizeof(recbuffer));
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	if (!check_response('1'))  // the correct response is 150
	{
		return false;
	}
	memset(recbuffer, 0, sizeof(recbuffer));
	while ((temp = recv(sock_data, recbuffer, sizeof(recbuffer), 0))>0)
	{
		Sleep(20);
		cout << recbuffer;
	}
	closesocket(sock_data);
	return true;
}
/*
function��change the current directory��include CDUP(back to the superior directory and change to other directorys)

*/
bool FTP::CD_command(std::string &directory)
{
	string cmd;
	if (!check_sock_alive(sock_ctrl))
	{
		string error = "socket has been closed,please connect again";
		throw error;
	}
	if (directory == "..")
	{
		cmd = string("CDUP");
		if (CurrentDir == "/")
		{
			string error = "�Ѿ��Ǹ�Ŀ¼�ˣ��޷������ϲ㡣";
			throw error;
		}
	}
	else
	{
		cmd = string("CWD ") + directory;
	}
	send_command(cmd);
	memset(recbuffer, 0, sizeof(recbuffer));
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	if (!check_response('2'))  // the correct response is 250
	{
		string error = "No such directory";
		throw error;
	}
	if (CurrentDir == "/")
		CurrentDir += directory;  //���µ�ǰĿ¼
	else
	{
		if (directory != "..")
			CurrentDir += "/" + directory;
		else    // �����ϲ�
		{
			int index = CurrentDir.rfind('/');
			CurrentDir.erase(index, CurrentDir.length() - index);
			if (CurrentDir.length() == 0)  //�ص��˸�Ŀ¼
			{
				CurrentDir = "/";
			}
		}
	}
	cmd_list();
	return true;
}

/*
function : to get a file from the server,you should guarentee that it is a file not a directory
written by Qiu Zenghui

*/
bool FTP::get_file(std::string filename)
{
	char *tempbuff = new char[4096];
	if (!check_sock_alive(sock_ctrl))
	{
		string error = "socket has been closed,please connect again";
		throw error;
	}

	string cmd;

	cmd = "TYPE I";
	send_command(cmd);
	memset(recbuffer, 0, sizeof(recbuffer));// the correct response should be 200 Set Type to be I
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	//cout << recbuffer << endl;
	if (!check_response('2'))
	{
		string error = "Could not open the binary transfer mode!";
		throw error;
	}
	open_datatrs();
	cmd = "RETR " + filename;
	send_command(cmd);
	memset(recbuffer, 0, sizeof(recbuffer));// the correct response should be 150 Opening ASCII mode data connection for **
	recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	if (!check_response('1'))
		return false;    // failed beacuse of no such directory
	int length;

	fstream fout; 
	fout.open(filename, ios::out | ios::binary|ios::app);
	//ff.write(temp, strlen(temp));
	if (!fout.is_open())
	{
		cout << "could not write to loacl files" << endl;
	}
	
	else
	{
		while ((length = recv(sock_data, recbuffer, sizeof(recbuffer), 0)) > 0)
		{
		//	RETR CC98FTP����.xlsx
			//int baseaddress = (int)&recbuffer;
		//	cout << recbuffer << endl;
		//	cout << &recbuffer << endl;
		//	cout << &(this->recbuffer) << endl;
		//	string temp(recbuffer);
			fout.write(recbuffer, strlen(recbuffer));
		//	memset(recbuffer, 0, sizeof(recbuffer));
		}
		fout.close();
	}
	closesocket(sock_data);
	return true;
}

/*
function: get the file name from the path given 
written by Qiu Zenghui

*/
// �ļ�·����ʽ
// C:\DIR\NAME
void FTP::getfileName()
{
	int i;
	string temp, name;
	int index;
	for (i = 0; i < filepath.size(); i++)
	{
		temp = filepath[i];
		index = temp.rfind('\\');
		if (index == std::string::npos)  //�Ҳ���
		{
			filename.push_back(temp);
		}
		else
		{
			name.assign(temp, index+1, temp.length() - index);
			filename.push_back(name);
		}
	}
}
/*
	send files from loacal server
	attention: it should not be a directory
*/
bool FTP::upload_file()
{
	getfileName();
	string name, path;
	string error;
	int length=0, bytecount=0;
	bool index = true;  // ��������ļ���Ч����Ϊfalse���׳��쳣
	filecount = 0;
	if (filename.size() == 0)  // û�и����ļ�
	{
		error = "no file given";
		throw error;
	}
	if (!check_sock_alive(sock_ctrl))
	{
		error = "socket has been closed,please connect again";
		throw error;
	}

	for (int i = 0; i < filename.size(); i++)
	{
		bytecount = 0;
		name = filename[i];
		path = filepath[i];
		
		length = GetFileData(path.c_str());
		if (length == -1)
		{
			index = false;
			continue;   // ����ļ��޷��򿪣������ϴ��������ļ�������
		}
		string cmd;

		cmd = "TYPE I";
		send_command(cmd);
		memset(recbuffer, 0, sizeof(recbuffer));// the correct response should be 200 Set Type to be I
		recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
		if (!check_response('2'))
		{
			error = "Could not open the binary transfer mode!";
			throw error;
		}
		if (!open_datatrs())
		{
			error = "Could not open the data transfer socket!";
			throw error;
		}

		cmd = "STOR " + name;
		send_command(cmd);
		memset(recbuffer, 0, sizeof(recbuffer));// the correct response should be 200 Set Type to be I
		recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	//	cout << recbuffer << endl;
		if (check_response('5'))
		{
			error = "you have no permission to upload file here";
			throw error;
		}

		fstream fin(path, ios::in | ios::binary);
		bytecount = 0;
		while (bytecount < length)     //���ζ�ȡ4096�ֽڷ���
		{
			fin.seekg(bytecount, ios::beg);   // �ļ���ָ����ƶ�
			if (bytecount + 4096 <= length) 
			{
				fin.read(sendbuff, 4096);
				Sleep(10);
				send(sock_data, sendbuff, 4096,0);
			}
			else
			{
				fin.read(sendbuff, length - bytecount);
				Sleep(10);
				send(sock_data, sendbuff,length - bytecount,0);
			}
			bytecount += 4096;
		}
		
		closesocket(sock_data);
		filecount++;
		memset(recbuffer, 0, sizeof(recbuffer));// the correct response should be 200 Set Type to be I
		recv(sock_ctrl, recbuffer, sizeof(recbuffer), 0);
	//	cout << recbuffer << endl;
		closesocket(sock_data);
	}
	if (!index)
	{
		error = "some file given not exist or could not open";
		throw(error);
	}
	return true;
}

/*
	function : to get the bytes of the file given
*/
int FTP::GetFileData(const char *file_path)
{
	if (file_path == NULL)
	{
		return -1;
	}
	fstream file_in(file_path, ios::in | ios::binary);
	if (!file_in.is_open())
		return -1;
	file_in.seekg(0, ios::end);
	int file_length = file_in.tellg();  //���ض�ָ�뵱ǰ��λ��
	file_in.close();
	//file_buffer_[file_length] = '\0';
	//	cout << file_buffer_ << endl;
	return file_length;
}

/*
function : to return the current directory
*/
string FTP::get_dir()
{
	return  CurrentDir;
}
/*
*/
void FTP::add_file_path(basic_string<char> path)
{
	filepath.push_back(path);
}