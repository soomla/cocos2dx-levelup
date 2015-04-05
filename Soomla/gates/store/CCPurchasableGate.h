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



#ifndef __CCPurchasableGate_H_
#define __CCPurchasableGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    /**
     A specific type of `Gate` that has an associated virtual item. The `Gate`
     opens once the item has been purchased.
     */
    class CCPurchasableGate: public CCGate {
        friend class CCPurchasableGateEventHanler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID)
    public:
        CCPurchasableGate(): CCGate(), mAssociatedItemId(NULL) {
        }

        /**
         Creates an instance of `CCPurchasableGate`.
         @param id ID of this `CCPurchasableGate`.
         @param associatedItemId Associated item ID.
         */
        static CCPurchasableGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId);

        SL_CREATE_WITH_DICTIONARY(CCPurchasableGate);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *associatedItemId);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        /**
         Converts this `Gate` to a Dictionary.
         @return The Dictionary representation of this `CCPurchasableGate`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCPurchasableGate();

    protected:

        /**
         Registers relevant events: item-purchased event.
         */
        virtual void registerEvents();

        /**
         Unregisters relevant events: item-purchased event.
         */
        virtual void unregisterEvents();

        /**
         Checks if this `Gate` meets its criteria for opening.
         @return Always `true`.
         */
        virtual bool canOpenInner();

        /**
         Opens this `Gate` by buying its associated item.
         @return If purchase was successfully made returns `true`; otherwise
         `false`.
         */
        virtual bool openInner();
        
        virtual void onItemPurchased(cocos2d::CCDictionary *eventData);
    };
}


#endif //__CCPurchasableGate_H_
