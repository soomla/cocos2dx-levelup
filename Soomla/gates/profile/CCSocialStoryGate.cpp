//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialStoryGate.h"
#include "CCGateStorage.h"
#include "CCSoomlaProfile.h"

namespace soomla {

#define TAG "SOOMLA SocialStatusGate"

    CCSocialStoryGate *CCSocialStoryGate::create(cocos2d::CCString *id, CCProvider provider,
            cocos2d::CCString *message,
            cocos2d::CCString *storyName, cocos2d::CCString *caption,
            cocos2d::CCString *link, cocos2d::CCString *imgUrl) {

        CCSocialStoryGate *ret = new CCSocialStoryGate();
        if (ret->init(id, provider, message, storyName, caption, link, imgUrl)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSocialStoryGate::init(cocos2d::CCString *id, CCProvider provider,
            cocos2d::CCString *message,
            cocos2d::CCString *storyName, cocos2d::CCString *caption,
            cocos2d::CCString *link, cocos2d::CCString *imgUrl) {

        bool result = CCSocialActionGate::init(id, provider);

        if (result) {
            setMessage(message);
            setStoryName(storyName);
            setCaption(caption);
            setLink(link);
            setImgUrl(imgUrl);

            return true;
        }
        return result;
    }

    bool CCSocialStoryGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {

            fillMessageFromDict(dict);
            fillStoryNameFromDict(dict);
            fillCaptionFromDict(dict);
            fillLinkFromDict(dict);
            fillImgUrlFromDict(dict);

            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCSocialStoryGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCSoomlaEntity::toDictionary();

        putMessageToDict(dict);
        putStoryNameToDict(dict);
        putCaptionToDict(dict);
        putLinkToDict(dict);
        putImgUrlToDict(dict);

        return dict;
    }

    const char *CCSocialStoryGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STORY_GATE;
    }

    CCSocialStoryGate::~CCSocialStoryGate() {
        CC_SAFE_RELEASE(mMessage);
        CC_SAFE_RELEASE(mStoryName);
        CC_SAFE_RELEASE(mCaption);
        CC_SAFE_RELEASE(mLink);
        CC_SAFE_RELEASE(mImgUrl);
    }

    bool CCSocialStoryGate::openInner() {
        if (canOpen()) {

            CCSoomlaProfile::getInstance()->updateStory(getProvider(),
                    getMessage()->getCString(), getStoryName()->getCString(),
                    getCaption()->getCString(), "",
                    getLink()->getCString(), getImgUrl()->getCString(), NULL, NULL);

            return true;
        }

        return false;
    }

}