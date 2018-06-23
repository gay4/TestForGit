#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "chat_message.h"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class Client;

class chat_client
{
	friend class Client;
//public:
	chat_client(boost::asio::io_service& io_service,
		tcp::resolver::iterator endpoint_iterator)
		: io_service_(io_service),
		socket_(io_service)//��ʼ��
	{
		do_connect(endpoint_iterator);
	}

	void write(const chat_message& msg)
	{
		io_service_.post(//�����첽�¼�
			[this, msg]()
		{
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress)
			{
				do_write();
			}
		});
	}

	void close()
	{
		io_service_.post([this]() { socket_.close(); });
	}

private:
	void do_connect(tcp::resolver::iterator endpoint_iterator)
	{
		//��������
		boost::asio::async_connect(socket_, endpoint_iterator,
			[this](boost::system::error_code ec, tcp::resolver::iterator)
		{
			if (!ec)
			{
				do_read_header();//��ȡ��Ϣ
			}
		});
	}

	void do_read_header()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg_.decode_header())
			{
				do_read_body();
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_read_body()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				/*-----------------------------------------------------------*/
				//����Ϣѹ����У���UnitManager��ȡ
				_orderList.push_back(std::string(read_msg_.body(),read_msg_.body_length()));
				/*-----------------------------------------------------------*/

				std::cout.write(read_msg_.body(), read_msg_.body_length());
				std::cout << "\n";//��ӡ��Ϣ����Ļ
				do_read_header();
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_write()
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)//handle write
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				socket_.close();
			}
		});
	}
	/*-----------------------------------------------------------*/
private:
	//�ӷ�����յ�����Ϣ�б�
	std::deque<std::string> _orderList;

	//��ȡ��Ϣ�Ľӿڣ�һ�ζ�ȡһ������ͷ����ʼ��ȡ
	std::string getOrder()
	{
		if (_orderList.empty())
			return std::string("null");

		std::string msg = _orderList.front();
		_orderList.pop_front();

		return msg;
	}
	//������Ϣ�Ľӿ�
	void sendMessage(std::string sendMsg)
	{
		chat_message msg;
		//std::string sendMsg = "hello server!";
		msg.body_length(sendMsg.size());
		memcpy(msg.body(), sendMsg.c_str(), msg.body_length());
		msg.encode_header();

		this->write(msg);
	}
	/*-----------------------------------------------------------*/

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

class Client :public Node {
	chat_client* _client;
	std::string _serverIp;
private:
	void runClient()
	{
		std::thread t(&Client::client, this);
		t.detach();
	}

	int client()
	{
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ _serverIp, "1024" });
		chat_client c(io_service, endpoint_iterator);//�ͻ���

		_client = &c;

		std::thread t([&io_service]() { io_service.run(); });//�����߳�ִ��io_service.run()

		while (1)
		{
			;
		}

		c.close();
		t.join();
	}
public:
	/*---------------UnitManager�շ���Ϣ�Ľӿ�---------------*/
	void sendMessage(std::string sendMsg)
	{
		_client->sendMessage(sendMsg);
	}

	std::string getMessage()
	{
		return _client->getOrder();
	}
	/*-----------------------------------------------------------*/

	static Client* create(std::string serverIp)
	{
		Client* sprite = new Client();
		if (sprite)
		{
			sprite->autorelease();
			sprite->_serverIp = serverIp;
			sprite->runClient();

			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	//��֪��ǰ�ж�������
	int getOrderSize()
	{
		return _client->_orderList.size();
	}

	bool isConnected()
	{
		return _client->_orderList.size() >= 1 
			&& _client->_orderList.front()[0] == 'I';
	}

	bool isStart()
	{
		return _client->_orderList.size() >= 2
			&& _client->_orderList.front()[0] == 'I'
			&& (*++(_client->_orderList.begin()))[0] == 'S';
	}

private:
	std::string getServerIp();
};