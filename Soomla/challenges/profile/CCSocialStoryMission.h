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


#ifndef __SocialStoryMission_H_
#define __SocialStoryMission_H_

#include "CCMission.h"
#include "CCUserProfileUtils.h"

namespace soomla {

    /**
     @class `CCSocialStoryMission`
     @brief NOTE: Social `Mission`s require the user to perform a specific
     social action in order to receive a `Reward`. Currently, the social
     provider that's available is Facebook, so the `Mission`s are FB-oriented.
     In the future, more social providers will be added.
     A specific type of `Mission` that has an associated story that includes a
     message, storyname, caption, link, and image. The `Mission` is complete
     once the player posts the story.
     */
    class CCSocialStoryMission: public CCMission {

    public:

        CCSocialStoryMission(): CCMission() {
        }

        /**
         Creates an instance of `CCSocialStoryMission`.
         @param id `Mission` ID.
         @param name `Mission` name.
         @param provider Social provider.
         @param message Message for the story.
         @param storyName Story name.
         @param caption Caption for the story image.
         @param link Link for the story.
         @param imgUrl Image URL for the story.
         */
        static CCSocialStoryMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                CCProvider provider, cocos2d::CCString *message,
                cocos2d::CCString *storyName, cocos2d::CCString *caption,
                cocos2d::CCString *link, cocos2d::CCString *imgUrl);

        /**
         Creates an instance of `CCSocialStoryMission`.
         @param id `Mission` ID.</param>
         @param name `Mission` name.</param>
         @param rewards Rewards.</param>
         @param provider Social provider.</param>
         @param message Message for the story.</param>
         @param storyName Story name.</param>
         @param caption Caption for the story image.</param>
         @param link Link for the story.</param>
         @param imgUrl Image URL for the story.
         */
        static CCSocialStoryMission *create(cocos2d::CCString *id, cocos2d::CCString *name,
                cocos2d::CCArray *rewards, CCProvider provider, cocos2d::CCString *message,
                cocos2d::CCString *storyName, cocos2d::CCString *caption,
                cocos2d::CCString *link, cocos2d::CCString *imgUrl);

        SL_CREATE_WITH_DICTIONARY(CCSocialStoryMission);

        const char *getType() const;

    };
}

#endif //__SocialStoryMission_H_
