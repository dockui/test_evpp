//
//  main.cpp
//  test_evpp
//
//  Created by caobo on 2018/7/13.
//  Copyright © 2018年 caobo. All rights reserved.
//

#include <iostream>

#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "startg .." << std::endl;
//    evpp ep;
//    ep.HelloWorld("hello dss");
    
    std::string addr = "0.0.0.0:9099";
    int thread_num = 1;
    evpp::EventLoop loop;
    evpp::TCPServer server(&loop, addr, "TCPEchoServer", thread_num);
    server.SetMessageCallback([](const evpp::TCPConnPtr& conn,
                                 evpp::Buffer* msg) {
        
        bool bget = false;
        evpp::Slice slice;
        while ( msg->GetMsgPack(&slice) )
        {
            bget = true;
            std::string str = slice.ToString();
            std::cout << str << std::endl;
            
            evpp::Buffer buffer(str.length(), 2);
            buffer.Write(str.c_str(), str.length());
            int16_t len = str.length();
            buffer.Prepend(&len, 2);
            conn->Send(&buffer);
        }
        if (bget && msg->size() && (msg->size() < evpp::Buffer::kInitialSize / 3) ){
            msg->Shrink(evpp::Buffer::kInitialSize);
        }
        
//        std::string str = std::string(msg->data(), msg->length());
//        std::cout << str << std::endl;
//        //        std::cout << str;
//
//        conn->Send(msg);
        
    });
    server.SetConnectionCallback([](const evpp::TCPConnPtr& conn) {
        if (conn->IsConnected()) {
            std::cout << "A new connection from " << conn->remote_addr() << std::endl;
        } else {
            std::cout << "Lost the connection from " << conn->remote_addr() << std::endl;
        }
    });
    server.Init();
    server.Start();
    loop.Run();
    
    return 0;
}
