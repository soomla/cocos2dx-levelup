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


#ifndef __SocialUploadMission_H_
#define __SocialUploadMission_H_

#include "CCMission.h"
#include "CCUserProfileUtils.h"

namespace soomla {

    /**
     @class `CCSocialUploadMission`
     @brief NOTE: Social `Mission`s require the user to perform a specific
     social action in order to receive a `Reward`. Currently, the social
     provider that's available is Facebook, so the `Mission`s are FB-oriented.
     In the future, more social providers will be added.

     A specific type of `Mission` that has an associated filename and message.
     The `Mission` is complete once the player uploads the image.
     */
    class CCSocialUploadMission: public CCMission {

    public:

        CCSocialUploadMission(): CCMission() {
        }
        
        /**
         Creates an instance of `CCSocialUploadMission`.
         @param id `Mission` ID.
         @param name `Mission` name.
         @param provider Social provider.
         @param fileName Name of file to upload.
         @param message Message to accompany the image.
         */
        static CCSocialUploadMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                CCProvider provider, cocos2d::CCString *fileName, cocos2d::CCString *message);

        /**
         Creates an instance of `CCSocialUploadMission`.
         @param id `Mission` ID.
         @param name `Mission` name.
         @param rewards Rewards for this `Mission`.
         @param provider Social provider.
         @param fileName Name of file to upload.
         @param message Message to accompany the image.
         */
        static CCSocialUploadMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards,
                CCProvider provider, cocos2d::CCString *fileName, cocos2d::CCString *message);

        SL_CREATE_WITH_DICTIONARY(CCSocialUploadMission);

        const char *getType() const;

    };
}

#endif //__SocialUploadMission_H_
