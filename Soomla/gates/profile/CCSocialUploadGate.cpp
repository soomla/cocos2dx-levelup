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

//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCSocialUploadGate.h"
#include "CCGateStorage.h"
#include "CCSoomlaProfile.h"

namespace soomla {

#define TAG "SOOMLA SocialUploadGate"

    CCSocialUploadGate *CCSocialUploadGate::create(cocos2d::CCString *id, CCProvider provider,
            cocos2d::CCString *fileName, cocos2d::CCString *message) {

        CCSocialUploadGate *ret = new CCSocialUploadGate();
        if (ret->init(id, provider, fileName, message)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSocialUploadGate::init(cocos2d::CCString *id, CCProvider provider,
            cocos2d::CCString *fileName, cocos2d::CCString *message) {

        bool result = CCSocialActionGate::init(id, provider);

        if (result) {
            setFileName(fileName);
            setMessage(message);

            return true;
        }
        return result;
    }

    bool CCSocialUploadGate::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {

            fillFileNameFromDict(dict);
            fillMessageFromDict(dict);

            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCSocialUploadGate::toDictionary() {
        cocos2d::CCDictionary *dict = CCSoomlaEntity::toDictionary();

        putFileNameToDict(dict);
        putMessageToDict(dict);

        return dict;
    }

    const char *CCSocialUploadGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_UPLOAD_GATE;
    }

    CCSocialUploadGate::~CCSocialUploadGate() {
        CC_SAFE_RELEASE(mFileName);
        CC_SAFE_RELEASE(mMessage);
    }

    bool CCSocialUploadGate::openInner() {
        if (canOpen()) {

            CCSoomlaProfile::getInstance()->uploadImage(getProvider(),
                    getMessage()->getCString(), getFileName()->getCString(), NULL, NULL);

            return true;
        }

        return false;
    }

}