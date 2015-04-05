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


#include "CCGatesList.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCDomainHelper.h"

namespace soomla {

    USING_NS_CC;

    bool CCGatesList::init(cocos2d::CCString *id, CCArray *gates) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            if (gates != NULL) {
                setGates(gates);
            }
            else {
                setGates(cocos2d::CCArray::create());
            }
            return true;
        }
        return result;
    }


    bool CCGatesList::init(cocos2d::CCString *id, CCGate *gate) {
        cocos2d::CCArray *gates = cocos2d::CCArray::create();
        gates->addObject(gate);
        return init(id, gates);
    }

    bool soomla::CCGatesList::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            CCObject *ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_GATES);
            if (ref) {
                CCArray *gatesDict = dynamic_cast<CCArray *>(ref);
                setGates((CCDomainHelper::getInstance()->getDomainsFromDictArray(gatesDict)));
            }
            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *soomla::CCGatesList::toDictionary() {
        cocos2d::CCDictionary *dict = CCGate::toDictionary();

        if (mGates) {
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(mGates), CCLevelUpConsts::JSON_LU_GATES);
        }

        return dict;
    }

    unsigned int CCGatesList::count() {
        return mGates->count();
    }

    void CCGatesList::add(CCGate *gate) {
        if (gate == NULL) {
            return;
        }
        
        gate->onAttached();
        mGates->addObject(gate);
    }

    void CCGatesList::remove(CCGate *gate) {
        if (gate == NULL) {
            return;
        }
        
        gate->onDetached();
        mGates->removeObject(gate);
    }
    
    cocos2d::CCArray *CCGatesList::getGates() const {
        return mGates;
    }
    
    void CCGatesList::setGates(cocos2d::CCArray *gates) {
        if (mGates != gates)
        {
            if (mGates != NULL) {
                CCObject *ref;
                CCGate *gate;
                CCARRAY_FOREACH(mGates, ref) {
                    gate = dynamic_cast<CCGate *>(ref);
                    gate->onDetached();
                }
            }
            
            CC_SAFE_RETAIN(gates);
            CC_SAFE_RELEASE(mGates);
            mGates = gates;
            
            if (mGates != NULL) {
                CCObject *ref;
                CCGate *gate;
                CCARRAY_FOREACH(mGates, ref) {
                    gate = dynamic_cast<CCGate *>(ref);
                    gate->onAttached();
                }
            }
        }
    }

    bool CCGatesList::openInner() {
        if (canOpen()) {
            // There's nothing to do here... If CanOpen returns true it means that the gates list meets the condition for being opened.
            forceOpen(true);
            return true;
        }

        return false;
    }

    void CCGatesList::registerEvents() {
        if (!isOpen()) {
            CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CCGatesList::onGateOpened),
                                                                          CCLevelUpConsts::EVENT_GATE_OPENED, NULL);
        }
    }

    void CCGatesList::unregisterEvents() {
        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CCLevelUpConsts::EVENT_GATE_OPENED);
    }
    
    void CCGatesList::onGateOpened(cocos2d::CCDictionary *eventData) {
        CCGate *gate = dynamic_cast<CCGate *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_GATE));
        CC_ASSERT(gate);
        
        if (mGates->containsObject(gate)) {
            if (canOpen()) {
                forceOpen(true);
            }
        }
    }

    CCGatesList::~CCGatesList() {
        CC_SAFE_RELEASE(mGates);
    }
}
