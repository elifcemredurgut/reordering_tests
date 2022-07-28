#include "zhelpers.hpp"
#include <string>
#include <set>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#include <zmq.hpp>
#include <iostream>
#include <unistd.h>

#define sleep(n)        Sleep(n)
#endif

int main () {
    //  Prepare our context and socket
    zmq::context_t context (2);
    zmq::socket_t socket (context, zmq::socket_type::router);
    socket.bind ("tcp://*:5555");
    std::cout << "Listening..." << std::endl;
    std::set<std::string> s;
    while (true) {
        zmq::message_t request;
        zmq::message_t request_id;

        //  Wait for next request from client
        socket.recv(request_id, zmq::recv_flags::none);
        std::string id = std::string(static_cast<char*>(request_id.data()), request_id.size());
        std::cout << "Received test id: " << id << std::endl;
        char *cid = &id[0];
        s.insert(id);
        std::cout<< "IDS:" << std::endl;
        for (auto i = s.begin(); i != s.end(); ++i)
                std::cout << *i << " ";
        std::cout << std::endl;

        //socket.recv(request, zmq::recv_flags::none);
        //std::cout << "Received delimeter" << std::endl;

        socket.recv(request, zmq::recv_flags::none);
        std::string reqstr = std::string(static_cast<char*>(request.data()), request.size());
        std::cout << "Received data: " << reqstr << std::endl;
         //  Do some 'work'
        //sleep(1);

        if(reqstr == "recommend"){
                //
        }

        //  Send reply back to client
        //zmq::message_t reply_id (3);
        //memcpy (reply_id.data(), id, 3);
/*      socket.send(request_id, zmq::send_flags::none);
        std::cout << "Id sent" << std::endl;

        zmq::message_t reply_delimeter(0);
        (reply.data(), "", 0);
        socket.send(reply, zmq::send_flags::none);
        std::cout << "Delimeter sent" << std::endl;

        zmq::message_t reply (5);
        memcpy (reply.data (), "World", 5);
        socket.send (reply, zmq::send_flags::none);
        std::cout << "Reply sent" << std::endl;
*/
        s_sendmore(socket, "lol");
        s_sendmore(socket, "");
        s_send(socket, "Work!");
        std::cout << "Sent all to " << id << std::endl;

        //do more work
        //s_sendmore(socket, cid);
        //s_sendmore(socket, "");
        //s_send(socket, "send");
        //std::cout << "second message sent to " << id << std::endl;
         //
/*      s_sendmore(socket, s[1]);
        s_sendmore(socket, "");
        s_send(socket, "sleam");
        std::cout << "Sent to " << s[1] << std::endl;
*/
    }
    return 0;
}