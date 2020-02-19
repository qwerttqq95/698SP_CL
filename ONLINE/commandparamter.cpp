#include"commandparameter.h"
using namespace std;

usr_psd::usr_psd()
{

}
usr_psd::~usr_psd()
{

}
void usr_psd::set_paramater(string ip, string user, string psd )
{
	this->usr_name = user;
	this->ip_addr = ip;
	this->psd = psd;
}
string usr_psd::get_ip()
{
	return this->ip_addr;
}
string usr_psd::get_psd()
{
	return this->psd;
}
string usr_psd::get_usr()
{
	return this->usr_name;
}
