 ///
 /// @file    TestAcceptor.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 15:42:14
 ///
 
#include "SpellcorrectServer.h"
#include "MyDict.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

/* wd::Threadpool * gThreadpool = nullptr; */

/* class Task */
/* { */
/* public: */
/* 	Task(const string & msg, */
/* 		 const wd::TcpConnectionPtr & conn) */
/* 	: _msg(msg) */
/* 	, _conn(conn) */
/* 	{} */

/* 	//运行在线程池的某一个子线程中 */
/* 	void process() */
/* 	{ */
/* 		//decode */
/* 		//compute */
/* 		//encode */
/* 		string response = _msg;//要返回给客户端的消息 */
/* 		//_conn->send(response);//由线程池的线程(计算线程)完成数据的发送,在设计上来说，是不合理的 */
/* 							  //数据发送的工作要交还给IO线程(Reactor所在的线程)完成 */
/* 							  //将send的函数的执行延迟到IO线程取操作 */
/* 		_conn->sendInLoop(response); */
/* 	} */
/* private: */
/* 	string _msg; */
/* 	wd::TcpConnectionPtr _conn; */
/* }; */
 
/* //回调函数体现了扩展性 */
/* void onConnection(const wd::TcpConnectionPtr & conn) */
/* { */
/* 	cout << conn->toString() << " has connected!" << endl; */
/* 	conn->send("welcome to server."); */
/* } */

/* void onMessage(const wd::TcpConnectionPtr & conn) */
/* { */
/* 	cout << "onMessage...." << endl; */
/* 	string msg = conn->receive(); */
/* 	cout << ">> receive msg from client: " << msg << endl; */
/* 	//业务逻辑的处理要交给线程池处理 */
/* 	//decode */
/* 	//compute */
/* 	//encode */
/* 	//::sleep(2);//碰到需要长时间的处理时，响应速度会降下来 */
/* 	//conn->send(msg); */
/* 	Task task(msg, conn); */

/* 	gThreadpool->addTask(std::bind(&Task::process, task)); */
/* } */

/* void onClose(const wd::TcpConnectionPtr & conn) */
/* { */
/* 	cout << "onClose...." << endl; */
/* 	cout << conn->toString() << " has closed!" << endl; */
/* } */

/* using namespace wd; */
/* class EchoServer */
/* { */
/* public: */
/* 	void onConnection(const TcpConnectionPtr & conn); */
/* 	void onMessage(const TcpConnectionPtr & conn); */
/* 	void onClose(const TcpConnectionPtr & conn); */

/* 	void process();//业务逻辑的处理 */

/* private: */
/* 	Threadpool _threadpool; */
/* 	TcpServer _server; */
/* }; */

int main(void)
{
	/* wd::Threadpool threadpool(4, 10); */ 
	/* threadpool.start(); */
	
	/* gThreadpool = &threadpool; */

	/* wd::TcpServer server("172.16.0.15", 8888); */

	/* server.setConnectionCallback(onConnection); */
	/* server.setMessageCallback(onMessage); */
	/* server.setCloseCallback(onClose); */

	/* server.start(); */

    //离线部分
    //建立词典
    string yuliaoPath("/home/ubuntu/projectC++/data");
    wd::DictProducer dict(yuliaoPath);
    dict.build_dict();
    dict.store_dict("/home/ubuntu/projectC++/dict/Dictionary");
    //建立索引表
    wd::IndexProducer index("/home/ubuntu/projectC++/dict/Dictionary");//随意填，单例对象
    index.init();
    index.store("/home/ubuntu/projectC++/dict/");

    wd::MyDict *mydict=wd::MyDict::getInstance();
    mydict->init("/home/ubuntu/projectC++/dict/");

    //在线部分
    wd::SpellcorrectServer spcoServer("172.16.0.15",8888,4,10);
    spcoServer.start();

	return 0;
}
