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
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCPurchasingMission_H_
#define __CCPurchasingMission_H_

#include "CCMission.h"

namespace soomla {
    
    /**
     @class `CCPurchasingMission`
     @brief A specific type of `Mission` that has an associated virtual 
     item. The `Mission` is complete once the item has been purchased.
     */
    class CCPurchasingMission: public CCMission {
        
    public:
        CCPurchasingMission(): CCMission() {
        }
        
        /**
         Creates an instance of `CCPurchasingMission`.
         @param id ID of this `CCPurchasingMission`.
         @param name Name of this `CCPurchasingMission`.
         @param associatedItemId ID of the item that is to be purchased.
         */
        static CCPurchasingMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCString *associatedItemId);
        
        /**
         Creates an instance of `CCPurchasingMission`.
         @param id ID of this `CCPurchasingMission`.
         @param name Name of this `CCPurchasingMission`.
         @param rewards `Reward`s for this `CCPurchasingMission`.
         @param associatedItemId ID of the item that is to be purchased.
         */
        static CCPurchasingMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, cocos2d::CCString *associatedItemId);

        SL_CREATE_WITH_DICTIONARY(CCPurchasingMission);

        virtual const char *getType() const;
    };
}

#endif //__CCPurchasingMission_H_
