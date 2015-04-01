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

#include "CCWorldCompletionGate.h"
#include "CCStoreEventDispatcher.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCWorld.h"
#include "CCSoomlaLevelUp.h"

namespace soomla {

    USING_NS_CC;

#define TAG "SOOMLA WorldCompletionGate"

    CCWorldCompletionGate *CCWorldCompletionGate::create(cocos2d::__String *id, cocos2d::__String *associatedWorldId) {
        CCWorldCompletionGate *ret = new CCWorldCompletionGate();
        if (ret->init(id, associatedWorldId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCWorldCompletionGate::init(cocos2d::__String *id, cocos2d::__String *associatedWorldId) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setAssociatedWorldId(associatedWorldId);
            return true;
        }
        return result;
    }

    bool CCWorldCompletionGate::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            fillAssociatedWorldIdFromDict(dict);
            return true;
        }
        return result;
    }

    const char *CCWorldCompletionGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE;
    }

    cocos2d::__Dictionary *CCWorldCompletionGate::toDictionary() {
        cocos2d::__Dictionary *dict = CCGate::toDictionary();

        putAssociatedWorldIdToDict(dict);

        return dict;
    }

    CCWorldCompletionGate::~CCWorldCompletionGate() {
        CC_SAFE_RELEASE(mAssociatedWorldId);
    }


    void CCWorldCompletionGate::registerEvents() {
        if (!isOpen()) {
            setEventListener(Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCLevelUpConsts::EVENT_WORLD_COMPLETED,
                                                                                                  CC_CALLBACK_1(CCWorldCompletionGate::onWorldCompleted, this)));
        }
    }

    void CCWorldCompletionGate::unregisterEvents() {
        if (mEventListener) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(mEventListener);
            setEventListener(NULL);
        }
    }

    bool CCWorldCompletionGate::canOpenInner() {
        CCWorld *world = CCSoomlaLevelUp::getInstance()->getWorld(mAssociatedWorldId->getCString());
        return world != NULL && world->isCompleted();
    }

    bool CCWorldCompletionGate::openInner() {
        if (canOpen()) {
            forceOpen(true);
            return true;
        }

        return false;
    }
    
    void CCWorldCompletionGate::onWorldCompleted(cocos2d::EventCustom *event) {
        __Dictionary *eventData = (__Dictionary *)event->getUserData();
        CCWorld *world = dynamic_cast<CCWorld *>(eventData->objectForKey(CCLevelUpConsts::DICT_ELEMENT_WORLD));
        CC_ASSERT(world);
        
        if (world->getId()->compare(mAssociatedWorldId->getCString()) == 0) {
            forceOpen(true);
        }
    }
}
