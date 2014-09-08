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

#include "BaseTestingEventHandler.h"
#include "CCSoomlaEntity.h"

using namespace cocos2d;

BaseTestingEventHandler::BaseTestingEventHandler() {
    eventStack = cocos2d::__Dictionary::create();
    eventStack->retain();
}

BaseTestingEventHandler::~BaseTestingEventHandler() {
    CC_SAFE_RELEASE(eventStack);
}

void BaseTestingEventHandler::addToEventStack(const std::string &key, cocos2d::Ref *value) {
    cocos2d::Ref *foundEntry = eventStack->objectForKey(key);
    cocos2d::__Array *entryArray = nullptr;
    if (foundEntry != nullptr) {
        entryArray = dynamic_cast<cocos2d::__Array *>(foundEntry);
    }
    else {
        entryArray = cocos2d::__Array::create();
        eventStack->setObject(entryArray, key);
    }
    
    entryArray->addObject(value);
}

cocos2d::__Array *BaseTestingEventHandler::getEventData(const std::string& eventName) {
    return dynamic_cast<cocos2d::__Array *>(eventStack->objectForKey(eventName));
}

bool BaseTestingEventHandler::checkEventFiredWith(const std::string& eventName, cocos2d::Ref *data) {
    cocos2d::__Array *eventArray = getEventData(eventName);
    
    if (eventArray == nullptr) {
        return false;
    }
    
    cocos2d::Ref *object;
    CCARRAY_FOREACH(eventArray, object) {
        if (object == data) {
            return true;
        }
    }
    
    return false;
}

bool BaseTestingEventHandler::checkEventFiredWithById(const std::string& eventName, cocos2d::Ref *data) {
    cocos2d::__Array *eventArray = getEventData(eventName);
    
    if (eventArray == nullptr) {
        return false;
    }
    
    cocos2d::Ref *object;
    CCARRAY_FOREACH(eventArray, object) {
        if (object == data) {
            return true;
        }
        else {
            soomla::CCSoomlaEntity *dataEntity = dynamic_cast<soomla::CCSoomlaEntity *>(data);
            soomla::CCSoomlaEntity *objectEntity = dynamic_cast<soomla::CCSoomlaEntity *>(object);
            if ((dataEntity != NULL) && (objectEntity != NULL)) {
                if (dataEntity->getId()->isEqual(objectEntity->getId())) {
                    return  true;
                }
            }
        }
    }
    
    return false;
}

bool BaseTestingEventHandler::checkEventFired(const std::string& eventName) {
    return (getEventData(eventName) != NULL);
}

void BaseTestingEventHandler::clearEventStack() {
    eventStack->removeAllObjects();
}