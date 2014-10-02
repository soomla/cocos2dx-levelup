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


#ifndef __CCSocialStatusGate_H_
#define __CCSocialStatusGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

    /**
     NOTE: Social `Gate`s require the user to perform a specific social
     action in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.
     
     A specific type of `Gate` that has an associated status. The `Gate`
     is opened once the player posts the status.
     */
    class CCSocialStatusGate: public CCSocialActionGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mStatus, Status, CCLevelUpConsts::JSON_LU_STATUS);
    public:
        CCSocialStatusGate(): CCSocialActionGate(), mStatus(NULL) {
        }
        
        /**
         Constructor.
         @param id `Gate` ID.
         @param provider Social provider.
         @param status Status to post in order to open this `Gate`.
         */
        static CCSocialStatusGate *create(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *status);

        SL_CREATE_WITH_DICTIONARY(CCSocialStatusGate)
        virtual bool init(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *status);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;
        
        /**
         Converts this `SocialStatusGate` to a JSONObject.
         @return The JSON object.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSocialStatusGate();

    protected:
        
        /**
         Opens this `Gate` by posting the associated status.
         @return If the status was successfully posted returns `true`; 
         otherwise `false`.
         */
        virtual bool openInner();
    };

}

#endif //__CCSocialStatusGate_H_
