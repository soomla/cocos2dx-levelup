//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCRecordGate.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCLevelUp.h"
#include "CCSoomlaUtils.h"

namespace soomla {

#define TAG "SOOMLA RecordGate"

    CCRecordGate *CCRecordGate::create(cocos2d::CCString *id, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord) {
        CCRecordGate *ret = new CCRecordGate();
        if (ret->init(id, associatedScoreId, desiredRecord)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCRecordGate::init(cocos2d::CCString *id, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setAssociatedScoreId(associatedScoreId);
            setDesiredRecord(desiredRecord);
            return true;
        }
        return result;
    }

    bool CCRecordGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            fillAssociatedScoreIdFromDict(dict);
            fillDesiredRecordFromDict(dict);
            return true;
        }
        return result;
    }

    const char *CCRecordGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_RECORD_GATE;
    }

    cocos2d::CCDictionary *CCRecordGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCGate::toDictionary();

        putAssociatedScoreIdToDict(dict);
        putDesiredRecordToDict(dict);

        return dict;
    }

    CCRecordGate::~CCRecordGate() {
        CC_SAFE_RELEASE(mAssociatedScoreId);
        CC_SAFE_RELEASE(mDesiredRecord);
    }

    bool CCRecordGate::canOpenInner() {
        CCScore *score = CCLevelUp::getInstance()->getScore(mAssociatedScoreId->getCString());
        if (score == NULL) {
            CCSoomlaUtils::logError(TAG, cocos2d::CCString::createWithFormat(
                    "(canOpenInner) couldn't find score with scoreId: %s", mAssociatedScoreId->getCString()
            )->getCString());
            return false;
        }

        return score->hasRecordReached(mDesiredRecord->getValue());
    }

    bool CCRecordGate::openInner() {
        if (canOpen()) {
            // There's nothing to do here... If the DesiredRecord was reached then the gate is just open.
            forceOpen(true);
            return true;
        }

        return false;
    }

    void CCRecordGate::registerEvents() {
        if (!isOpen()) {
            setEventHandler(CCRecordGateEventHandler::create(this));
            CCLevelUpEventDispatcher::getInstance()->addEventHandler(getEventHandler());
        }
    }

    void CCRecordGate::unregisterEvents() {
        CCLevelUpEventHandler *eventHandler = getEventHandler();
        if (eventHandler) {
            CCLevelUpEventDispatcher::getInstance()->removeEventHandler(eventHandler);
            setEventHandler(NULL);
        }
    }

    CCRecordGateEventHandler *CCRecordGateEventHandler::create(CCRecordGate *recordGate) {
        CCRecordGateEventHandler *ret = new CCRecordGateEventHandler();
        ret->autorelease();

        ret->mRecordGate = recordGate;

        return ret;
    }

    void CCRecordGateEventHandler::onScoreRecordChanged(CCScore *score) {

        if (score->getId()->compare(mRecordGate->mAssociatedScoreId->getCString()) == 0 &&
                score->hasRecordReached(mRecordGate->mDesiredRecord->getValue())) {

            // We were thinking what will happen if the score's record will be broken over and over again.
            // It might have made this function being called over and over again.
            // It won't be called b/c ForceOpen(true) calls 'unregisterEvents' inside.
            mRecordGate->forceOpen(true);
        }
    }
}
