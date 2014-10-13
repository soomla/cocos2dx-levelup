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


    CCVirtualItemScore *CCVirtualItemScore::create(cocos2d::__String *id, cocos2d::__String *associatedItemId) {
        return CCVirtualItemScore::create(id, NULL, NULL, associatedItemId);
    }

    CCVirtualItemScore *CCVirtualItemScore::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, cocos2d::__String *associatedItemId) {
        CCVirtualItemScore *ret = new CCVirtualItemScore();
        if (ret->init(id, name, higherBetter, associatedItemId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCVirtualItemScore::init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, cocos2d::__String *associatedItemId) {
        bool result = CCScore::init(id, name, higherBetter);
        if (result) {
            setAssociatedItemId(associatedItemId);
            return true;
        }
        return result;
    }

    bool CCVirtualItemScore::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCScore::initWithDictionary(dict);
        if (result) {
            cocos2d::__String *itemIdDict = dynamic_cast<cocos2d::__String *>(
                    dict->objectForKey(CCLevelUpConsts::JSON_LU_ASSOCITEMID));
            if (itemIdDict) {
                setAssociatedItemId(itemIdDict);
            }
            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *CCVirtualItemScore::toDictionary() {
        cocos2d::__Dictionary *dict = CCScore::toDictionary();

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
            CCSoomlaUtils::logError(TAG, cocos2d::__String::createWithFormat(
                    "Couldn't find item associated with a given VirtualItemScore. itemId: %s",
                    mAssociatedItemId->getCString())->getCString());
            CCSoomlaUtils::logError(TAG, error->getInfo());
        }
    }
}
