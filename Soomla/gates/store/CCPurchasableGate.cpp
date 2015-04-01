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


#include "CCPurchasableGate.h"
#include "CCStoreEventDispatcher.h"
#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"

namespace soomla {

    USING_NS_CC;

#define TAG "SOOMLA PurchasableGate"

    CCPurchasableGate *CCPurchasableGate::create(cocos2d::__String *id, cocos2d::__String *associatedItemId) {
        CCPurchasableGate *ret = new CCPurchasableGate();
        if (ret->init(id, associatedItemId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCPurchasableGate::init(cocos2d::__String *id, cocos2d::__String *associatedItemId) {
        bool result = CCGate::init(id, NULL);
        if (result) {
            setAssociatedItemId(associatedItemId);
            return true;
        }
        return result;
    }

    bool CCPurchasableGate::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCGate::initWithDictionary(dict);
        if (result) {
            fillAssociatedItemIdFromDict(dict);
            return true;
        }
        return result;
    }

    const char *CCPurchasableGate::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_PURCHASABLE_GATE;
    }

    cocos2d::__Dictionary *CCPurchasableGate::toDictionary() {
        cocos2d::__Dictionary *dict = CCGate::toDictionary();

        putAssociatedItemIdToDict(dict);

        return dict;
    }

    CCPurchasableGate::~CCPurchasableGate() {
        CC_SAFE_RELEASE(mAssociatedItemId);
    }


    void CCPurchasableGate::registerEvents() {
        if (!isOpen()) {
            setEventListener(Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_ITEM_PURCHASED,
                                                                                                  CC_CALLBACK_1(CCPurchasableGate::onItemPurchased, this)));
        }
    }

    void CCPurchasableGate::unregisterEvents() {
        if (mEventListener) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(mEventListener);
            setEventListener(NULL);
        }
    }

    bool CCPurchasableGate::canOpenInner() {
        return true;
    }

    bool CCPurchasableGate::openInner() {
        CCError *error = NULL;
        CCStoreInventory::sharedStoreInventory()->buyItem(mAssociatedItemId->getCString(), this->getId()->getCString(), &error);
        if (error) {
            if (error->getInfo())
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Cannot purchase this item. itemId: %s",
                    mAssociatedItemId->getCString())->getCString());
            CCSoomlaUtils::logError(TAG, error->getInfo());
            return false;
        }
        return true;
    }
    
    void CCPurchasableGate::onItemPurchased(cocos2d::EventCustom *event) {
        __Dictionary *eventData = (__Dictionary *)event->getUserData();
        CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
        CC_ASSERT(purchasableVirtualItem);
        __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD));
        CC_ASSERT(payload);
        
        if ((purchasableVirtualItem->getItemId()->compare(getAssociatedItemId()->getCString()) == 0)
            && payload->isEqual(getId())) {
            forceOpen(true);
        }
    }
}
