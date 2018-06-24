#pragma once
#pragma warning (disable : 4996)
#define ASIO_STANDALONE
#include "cocos2d.h"
USING_NS_CC;

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
//#include <boost/bind.hpp>
#include "asio.hpp"
//#include <boost/thread/thread.hpp>
#include "chat_message.h"
#include <fstream>
#pragma warning (disable : 4996)



using asio::ip::tcp;


typedef std::deque<chat_message> chat_message_queue;

class Client;

class chat_client
{
	friend class Client;
	//public:
	chat_client(asio::io_service& io_service,
		tcp::resolver::iterator endpoint_iterator);

	void write(const chat_message& msg);
	void close();
private:
	

	void do_connect(tcp::resolver::iterator endpoint_iterator);

	void do_read_header();

	void do_read_body();

	void do_write();
	/*-----------------------------------------------------------*/
private:
	//�ӷ�����յ�����Ϣ�б�
	std::deque<std::string> _orderList;

	//��ȡ��Ϣ�Ľӿڣ�һ�ζ�ȡһ������ͷ����ʼ��ȡ
	std::string getOrder();
	//������Ϣ�Ľӿ�
	void sendMessage(std::string sendMsg);
	/*-----------------------------------------------------------*/

private:
	asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

class Client :public Node {
	chat_client* _client;

public:
	std::mutex t_lock;

	void runClient();

	int client();
	/*-----------------------------------------------------------*/
	void sendMessage(std::string sendMsg);
	std::string getMessage();
	/*-----------------------------------------------------------*/

	static Client* create(std::string ip, int mode);
	
};


