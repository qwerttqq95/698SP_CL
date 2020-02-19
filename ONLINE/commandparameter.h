#pragma once 
#include<iostream>
#include "memory"
using  namespace std;
class usr_psd
{
public:
	usr_psd();
	~usr_psd();
	void set_paramater(string ip,string user = "anonymous",string psd = "none");
    string get_ip();
    string get_usr();
    string get_psd();
private:
    string ip_addr;   // it can be eather url or ip address
    string usr_name;  // if no usr name required,just set as anonymous
    string psd;   //
	//stri
	/* data */
	
};