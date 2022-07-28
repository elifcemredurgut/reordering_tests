#include <zmq.hpp>
#include <iostream>
#include <unistd.h>
#include "serv.h"
#include <string>
//#include <future>


ZmqServer::ZmqServer() : m_context(1), socket(m_context, ZMQ_ROUTER){
}

void ZmqServer::bind(std::string protocol ,int port){
    std::string bind_param;
    bind_param = protocol + "://*:" + std::to_string(port);
    socket.bind(bind_param);
}

std::string ZmqServer::receive(){
    zmq::message_t message;
    //  Wait for next request from client
    socket.recv (&message);
    std::cout << "Received message : " << message << std::endl;
    return std::string(static_cast<char*>(message.data()), message.size());
}

void ZmqServer::send(std::string msg){
    //  Send reply back to client
    zmq::message_t reply (msg.size());
    memcpy (reply.data (), msg.c_str(), msg.size());
    socket.send(reply);
}

void ZmqServer::sendmore(std::string msg){
    //  Send reply back to client
    zmq::message_t reply (msg.size());
    memcpy (reply.data (), msg.c_str(), msg.size());
    socket.send(reply, ZMQ_SNDMORE);
}


