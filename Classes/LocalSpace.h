#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace LocalSpace {
	
	int ipindex;                                ///����ȷ���ӵ�ip��ַ��ip�б��������
	int serverIndex;                            ///server���ڵ�ip��ַ��ip�б��������

	std::string                 ipOut;          ///�ܳɹ��������ӵ�ip��ַ�ַ���
	std::string                 currentIp;      ///��ǰ���ӵ�ip��ַ�ַ���
	std::vector<std::string>    ipList;         ///�������ӵ������ε��豸��ip��ַ��
	std::vector<std::string>    serverIpList;   ///�ܹ������ϵ�, ����server��ip��ַ��
}