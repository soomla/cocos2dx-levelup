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


#include "CCVirtualItemScore.h"
#include "CCError.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"

namespace soomla {
#define TAG "SOOMLA VirtualItemScore"


    CCVirtualItemScore *CCVirtualItemScore::create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId) {
        return CCVirtualItemScore::create(id, NULL, NULL, associatedItemId);
    }

    CCVirtualItemScore *CCVirtualItemScore::create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, cocos2d::CCString *associatedItemId) {
        CCVirtualItemScore *ret = new CCVirtualItemScore();
        if (ret->init(id, name, higherBetter, associatedItemId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCVirtualItemScore::init(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, cocos2d::CCString *associatedItemId) {
        bool result = CCScore::init(id, name, higherBetter);
        if (result) {
            setAssociatedItemId(associatedItemId);
            return true;
        }
        return result;
    }

    bool CCVirtualItemScore::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCScore::initWithDictionary(dict);
        if (result) {
            cocos2d::CCString *itemIdDict = dynamic_cast<cocos2d::CCString *>(
                    dict->objectForKey(CCLevelUpConsts::JSON_LU_ASSOCITEMID));
            if (itemIdDict) {
                setAssociatedItemId(itemIdDict);
            }
            return true;
        }
        return result;
    }

    cocos2d::CCDictionary *CCVirtualItemScore::toDictionary() {
        cocos2d::CCDictionary *dict = CCScore::toDictionary();

        if (mAssociatedItemId) {
            dict->setObject(mAssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID);
        }

        return dict;
    }

    char const *CCVirtualItemScore::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_VIRTUAL_ITEM_SCORE;
    }

    void CCVirtualItemScore::performSaveActions() {
        CCScore::performSaveActions();

        CCError *error = NULL;
        int amount = (int) getTempScore();
        CCStoreInventory::sharedStoreInventory()->giveItem(mAssociatedItemId->getCString(), amount, &error);
        if (error) {
            CCSoomlaUtils::logError(TAG, cocos2d::CCString::createWithFormat(
                    "Couldn't find item associated with a given VirtualItemScore. itemId: %s",
                    mAssociatedItemId->getCString())->getCString());
            CCSoomlaUtils::logError(TAG, error->getInfo());
        }
    }
}
