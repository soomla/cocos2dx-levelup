/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
 
#ifndef __BaseTestingEventHandler_H
#define __BaseTestingEventHandler_H

#include "cocos2d.h"

class BaseTestingEventHandler {
public:
    BaseTestingEventHandler();
    ~BaseTestingEventHandler();
    
    cocos2d::__Array *getEventData(const std::string& eventName);
    bool checkEventFired(const std::string& eventName);
    bool checkEventFiredWith(const std::string& eventName, cocos2d::Ref *data);
    bool checkEventFiredWithById(const std::string& eventName, cocos2d::Ref *data);
    
    void clearEventStack();
    
protected:
    void addToEventStack(const std::string &key, cocos2d::Ref *value);
    
private:
    cocos2d::__Dictionary *eventStack;
};

#endif // __BaseTestingEventHandler_H
