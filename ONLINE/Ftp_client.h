#pragma once
#include<winsock.h>
#include<iostream>
#include<vector>
#include"commandparameter.h"
class FTP
{
public:
	FTP();
	~FTP();
    char recbuffer[4096];
	void set_userInfo(std::shared_ptr<usr_psd> &temp);
	bool creatSock();
	bool login();
	bool CD_command(std::string &directory);
	bool get_file(std::string filename);
	bool upload_file();    // upload files,not directories
	int send_command(basic_string<char> s);
	bool cmd_list();   //get the current context of the directory 
	bool open_datatrs();   // open the data transfer mode 
	bool check_response(char a);   //use to check whether the response is right or not
	bool check_sock_alive(SOCKET &clientSocket);  // to check whether the socket is connected or not
	void add_file_path(basic_string<char> path);
	std::string get_dir();
	inline int getFileCount()
	{
		return filecount;
	}
	inline void ClearVector()
	{
		std::vector<std::string>().swap(filename);
		std::vector<std::string>().swap(filepath);
	}
protected:

	void getfileName();   //���ļ�·�������л���ļ�����
	void get_port_from_pasv(basic_string<char> s, int &p1, int &p2);
	int GetFileData(const char *file_path);    // GET the size of file given 

private:

	char sendbuff[4096];
	char ip[30];  // ���ڴ��ip��ַ
	int filecount;
	std::vector<std::string> filepath;
	std::vector<std::string> filename;
	std::string CurrentDir;    //���ڴ�ŵ�ǰ��Ŀ¼
	SOCKET sock_ctrl;  //for transfer control commands
	SOCKET sock_data;  // for data transfer
	std::shared_ptr<usr_psd> info;
};
