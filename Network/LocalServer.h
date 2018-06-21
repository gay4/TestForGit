#pragma once

//#pragma warning(disable:4996)
//#define ASIO_STANDALONE

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "chat_message.h"

#include "cocos2d.h"

#define TEST_CODE

/*-----------------------------------------------------------*/
#include <cstdio>
#include <string>
//#include "Classes/Data.h"
/*-----------------------------------------------------------*/
#define MAX_PLAYER_NUM 4
using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;


class chat_participant
{
public:
	virtual ~chat_participant() {}
	virtual void deliver(const chat_message& msg) = 0; //participant should deliver message
	int _id = -1;
};

typedef std::shared_ptr<chat_participant> chat_participant_ptr;//shared ptr

class chat_server;//room����Ԫ
class chat_room
{
	friend class chat_server;
public:
	int getClientNum()
	{
		return _clientNum;
	}

	int getReadyClientNum()
	{
		return _preparedClientNum;
	}

	void startGame()
	{
		char info[50] = "";
		sprintf(info, "Start!(%d", _clientNum);

		deliver(stringToMsg(info));
	}

private:
	int _clientNum = 0;//�ͻ������������ʶ�����id
	int _preparedClientNum = 0;
	//int startFlag = false;//��Ϸ��ʼ���ֹ����

	bool	 _isIdUsed[MAX_PLAYER_NUM] = { 0,0,0,0 };//

public:
	void join(chat_participant_ptr participant)
	{
		participants_.insert(participant);//add a client
										  //��֮ǰ����Ϣдһ������µ�������
		for (auto msg : recent_msgs_)
			participant->deliver(msg);

		/*-----------------------------------------------------------*/
		//�������id��client
		++_clientNum;
		assert(_clientNum <= MAX_PLAYER_NUM);
		int validId = -1;
		for (int i = 0;i < MAX_PLAYER_NUM;++i)
		{
			if (!_isIdUsed[i])
			{
				validId = i;
				break;
			}
		}
		assert(validId >= 0);
		_isIdUsed[validId] = 1;
		participant->_id = validId;

		char s[20];
		sprintf(s, "Id(%d", validId + 1);
		chat_message msg = stringToMsg(s);

		participant->deliver(msg);
		/*-----------------------------------------------------------*/
	}

	void leave(chat_participant_ptr participant)
	{
		participants_.erase(participant);//remove a client

		_isIdUsed[participant->_id] = 0;//���flag
		std::cout << "id  " << participant->_id + 1 << "  is valid" << std::endl;
		--_clientNum;
		--_preparedClientNum;

		assert(_clientNum >= 0);
	}

	void deliver(const chat_message& msg)
	{

#ifdef TEST_CODE
		{
			if (msg.body()[msg.body_length() - 1] == 'T')//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����
			{
				std::string msg(msg.body(), msg.body_length());
				std::cout << msg << std::endl;

				return;
			}
		}
#endif
		if (msg.body()[0] == 'C')//Client ready!>>>>>>>>>>>>>>>>>>>>>>>>
		{
			++_preparedClientNum;
		
			return;
		}
		

		//�Ƚ����͵���Ϣ����������б�
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs)
			recent_msgs_.pop_front();//delete expired message

		for (auto participant : participants_)
			participant->deliver(msg);//����Ϣ�����еĶ���ת��һ��
	}

private:
	std::set<chat_participant_ptr> participants_;//all client
	enum { max_recent_msgs = 0 };//��������������¼����
	chat_message_queue recent_msgs_;


	chat_message stringToMsg(const char s[])
	{
		chat_message msg;

		msg.body_length(strlen(s));
		memcpy(msg.body(), s, msg.body_length());
		msg.encode_header();

		return msg;
	}
};//chat room

class chat_session :
	public chat_participant,
	public std::enable_shared_from_this<chat_session>
{
public:
	chat_session(tcp::socket socket, chat_room& room)
		: socket_(std::move(socket)),
		room_(room)
	{
	}
	void start()
	{
		//�յ�����֮�����Ƚ��ͻ����뵽room��
		//
		room_.join(shared_from_this());//add a participant

		do_read_header();//����Ϣ
	}
	void deliver(const chat_message& msg)
	{
		//
		bool write_in_progress = !write_msgs_.empty();//��
		write_msgs_.push_back(msg);//�Ὣ��Ϣ�ȷŵ�write_msgs_��
		if (!write_in_progress)
		{
			//write message
			do_write();
		}
	}
private:
	void do_read_header()
	{
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),//data,length
			[this, self](boost::system::error_code ec, std::size_t /*length*/)//lambada
		{
			if (!ec && read_msg_.decode_header())
			{
				do_read_body();// read body
			}
			else
			{
				auto ep_ = socket_.remote_endpoint();
				std::cout << "client : " << ep_.port() << " leave this room" << std::endl;

				room_.leave(shared_from_this());//read a eof
			}
		});
	}

	void do_read_body()
	{
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				room_.deliver(read_msg_);//deliver��������Ϣ�������ӽ����Ŀͻ����յ���ʷ��Ϣ
				do_read_header();//
			}
			else
			{
				room_.leave(shared_from_this());
			}
		});
	}

	void do_write()
	{
		auto self(shared_from_this());
		boost::asio::async_write(socket_,//��ǰsession��socket
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				//no change 
				std::string msg(write_msgs_.front().body(), write_msgs_.front().body_length());
				std::cout << msg << std::endl;
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				room_.leave(shared_from_this());
			}
		});
	}

	tcp::socket socket_;
	chat_room& room_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};//seesion

	class LocalServer;//ǰ������
class chat_server
{
	friend  class LocalServer;
public:
	//constructor
	chat_server(boost::asio::io_service& io_service,
		const tcp::endpoint& endpoint)
		: acceptor_(io_service, endpoint),//listen fd
		socket_(io_service)//conn fd
	{
		do_accept();
	}

private:
	void do_accept()
	{
		//a new connection
		acceptor_.async_accept(socket_,
			[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				auto ep_ = socket_.remote_endpoint();
				std::cout << "client : " << ep_.port() << " enter this room" << std::endl;

				auto newClient = std::make_shared<chat_session>(std::move(socket_), room_);
				newClient->start();//session

			}

			do_accept();
		});
	}

	tcp::acceptor acceptor_;
	tcp::socket socket_;
	//server should keep all client connected
	chat_room room_;//chat_room class//�������е�client
};

class LocalServer :public cocos2d::Node {

	typedef boost::shared_ptr<chat_server>  chat_server_ptr;
	typedef std::list<chat_server_ptr>      chat_server_list;
public:
	static LocalServer * create()
	{
		LocalServer *sprite = new LocalServer();
		if (sprite)
		{
			sprite->autorelease();
			sprite->runServer();

			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	int getClientNum()
	{
		return _server->room_.getClientNum();
	}

	int getReadyClientNum()
	{
		return _server->room_.getReadyClientNum();
	}

	void startGame()
	{
		_server->room_.startGame();
	}

private:
	chat_server * _server = nullptr;

private:
	bool init()
	{
		runServer();
		return true;
	}

	void runServer()
	{
		std::thread t(&LocalServer::server, this);
		t.detach();//ֱ�ӷ���
	}

	void server()
	{
		try
		{
			boost::asio::io_service io_service;

			std::list<chat_server> servers;
			
			tcp::endpoint endpoint(tcp::v4(), 1024);//listen 1024 port
			servers.emplace_back(io_service, endpoint);//constructor

			//servers.push_back(server_ptr);
			_server = &servers.front();//��ֵΪ�ڲ�ָ��

			io_service.run();
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
	}

};

