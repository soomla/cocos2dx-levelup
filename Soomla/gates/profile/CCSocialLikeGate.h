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


#ifndef __CCSocialLikeGate_H_
#define __CCSocialLikeGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

    /**
     NOTE: Social `Gate`s require the user to perform a specific social action 
     in order to open the `Gate`. Currently, the social provider that's 
     available is Facebook, so the `Gates`s are FB-oriented. In the future, 
     more social providers will be added.
     
     A specific type of `Gate` that has an associated page name.
     The `Gate` opens once the player "Likes" the associated page.
     */
    class CCSocialLikeGate: public CCSocialActionGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mPageName, PageName, CCLevelUpConsts::JSON_LU_PAGE_NAME);
    public:
        CCSocialLikeGate(): CCSocialActionGate(), mPageName(NULL) {
        }
        
        /**
         Creates an instance of `CCSocialLikeGate`.
         @param id `Gate` ID.
         @param provider Social provider.
         @param pageName Name of the page to "Like" in order to open this `Gate`.
         */
        static CCSocialLikeGate *create(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *pageName);

        SL_CREATE_WITH_DICTIONARY(CCSocialLikeGate);

        virtual bool init(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *pageName);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        /**
         Converts this `SocialLikeGate` to a Dictionary.
         @return The Dictionary representation of this `CCSocialLikeGate`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSocialLikeGate();

    protected:
        
        /**
         Opens this `Gate` by "liking" the associated page.
         @return If the page was successfully "liked" returns `true`; otherwise
         `false`.
         */
        virtual bool openInner();
    };

}

#endif //__CCSocialLikeGate_H_
