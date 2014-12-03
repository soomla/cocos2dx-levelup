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



#ifndef __CCSocialLikeMission_H_
#define __CCSocialLikeMission_H_

#include "CCMission.h"
#include "CCUserProfileUtils.h"

namespace soomla {

    /**
     @class `CCSocialLikeMission`
     @brief NOTE: Social `Mission`s require the user to perform a specific
     social action in order to receive a `Reward`. Currently, the social
     provider that's available is Facebook, so the `Mission`s are FB-oriented.
     In the future, more social providers will be added.
     A specific type of `Mission` that has an associated page name.
     The `Mission` is complete once the player "Likes" the page.
     */
    class CCSocialLikeMission: public CCMission {

    public:

        CCSocialLikeMission(): CCMission() {
        }
        /**
         Creates an instance of `CCSocialLikeMission`.
         @param id `Mission` ID.
         @param name `Mission` name.
         @param provider Social provider.
         @param pageName Name of the page to "Like" in order to complete this
         `Mission`.
         */
        static CCSocialLikeMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                CCProvider provider, cocos2d::CCString *pageName);

        /**
         Creates an instance of `CCSocialLikeMission`.
         @param id `Mission` ID.
         @param name `Mission` name.
         @param rewards Rewards for completing this `Mission`.
         @param provider Social provider.
         @param pageName Name of the page to "Like" in order to complete this
         `Mission`.
         */
        static CCSocialLikeMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, CCProvider provider, cocos2d::CCString *pageName);

        SL_CREATE_WITH_DICTIONARY(CCSocialLikeMission);

        virtual const char *getType() const;
    };
}

#endif //__CCSocialLikeMission_H_
