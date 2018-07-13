//
//  evpp.cpp
//  evpp
//
//  Created by caobo on 2018/7/13.
//  Copyright © 2018年 caobo. All rights reserved.
//

#include <iostream>
#include "evpp.hpp"
#include "evppPriv.hpp"

void evpp::HelloWorld(const char * s)
{
    evppPriv *theObj = new evppPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void evppPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

