//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCWorldCompletionGate.h"
#include "CCStoreEventDispatcher.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCWorld.h"
#include "CCLevelUp.h"

namespace soomla {

    USING_NS_CC;

#define TAG "SOOMLA WorldCompletionGate"

    CCWorldCompletionGate *CCWorldCompletionGate::create(cocos2d::CCString *id, cocos2d::CCString *associatedWorldId) {
        CCWorldCompletionGate *ret = new CCWorldCompletionGate();
        if (ret->init(id, associatedWorldId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCWorldCompletionGate::init(cocos2d::CCString *id, cocos2d::CCString *associatedWorldId) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setAssociatedWorldId(associatedWorldId);
            return true;
        }
        return result;
    }

    bool CCWorldCompletionGate::initWithDictionary(cocos2d::CCDictionary *dict) {
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

    cocos2d::CCDictionary *CCWorldCompletionGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCGate::toDictionary();

        putAssociatedWorldIdToDict(dict);

        return dict;
    }

    CCWorldCompletionGate::~CCWorldCompletionGate() {
        CC_SAFE_RELEASE(mAssociatedWorldId);
    }


    void CCWorldCompletionGate::registerEvents() {
        if (!isOpen()) {
            setEventHandler(CCWorldCompletionGateEventHanler::create(this));
            CCLevelUpEventDispatcher::getInstance()->addEventHandler(getEventHandler());
        }
    }

    void CCWorldCompletionGate::unregisterEvents() {
        CCLevelUpEventHandler *eventHandler = getEventHandler();
        if (eventHandler) {
            CCLevelUpEventDispatcher::getInstance()->removeEventHandler(eventHandler);
            setEventHandler(NULL);
        }
    }

    bool CCWorldCompletionGate::canOpenInner() {
        CCWorld *world = CCLevelUp::getInstance()->getWorld(mAssociatedWorldId->getCString());
        return world != NULL && world->isCompleted();
    }

    bool CCWorldCompletionGate::openInner() {
        if (canOpen()) {
            forceOpen(true);
            return true;
        }

        return false;
    }

    CCWorldCompletionGateEventHanler *CCWorldCompletionGateEventHanler::create(CCWorldCompletionGate *worldCompletionGate) {
        CCWorldCompletionGateEventHanler *ret = new CCWorldCompletionGateEventHanler();
        ret->autorelease();

        ret->mWorldCompletionGate = worldCompletionGate;

        return ret;
    }

    void CCWorldCompletionGateEventHanler::onWorldCompleted(CCWorld *world) {
        if (world->getId()->compare(mWorldCompletionGate->mAssociatedWorldId->getCString()) == 0) {
            mWorldCompletionGate->forceOpen(true);
        }
    }
}

