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


#ifndef __CCSocialStoryGate_H_
#define __CCSocialStoryGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

    /**
     NOTE: Social `Gate`s require the user to perform a specific social action
     in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     A specific type of `Gate` that has an associated story. The `Gate`
     is opened once the player posts the story.
     */
    class CCSocialStoryGate: public CCSocialActionGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mMessage, Message, CCLevelUpConsts::JSON_LU_MESSAGE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mStoryName, StoryName, CCLevelUpConsts::JSON_LU_STORY_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mCaption, Caption, CCLevelUpConsts::JSON_LU_CAPTION);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mLink, Link, CCLevelUpConsts::JSON_LU_LINK);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mImgUrl, ImgUrl, CCLevelUpConsts::JSON_LU_IMG_LINK);
    public:
        CCSocialStoryGate(): CCSocialActionGate(),
                             mMessage(NULL), mStoryName(NULL),
                             mCaption(NULL), mLink(NULL), mImgUrl(NULL) {
        }
        
        /**
         Creates an instance of `CCSocialStoryGate`.
         @param id `Gate` ID.
         @param provider Social provider.
         @param message Message for the story.
         @param storyName Story name.
         @param caption Caption for the story image.
         @param link Link for the story.
         @param imgUrl Image URL for the story.
         */
        static CCSocialStoryGate *create(cocos2d::CCString *id, CCProvider provider,
                cocos2d::CCString *message,
                cocos2d::CCString *storyName, cocos2d::CCString *caption,
                cocos2d::CCString *link, cocos2d::CCString *imgUrl);

        SL_CREATE_WITH_DICTIONARY(CCSocialStoryGate);
        virtual bool init(cocos2d::CCString *id, CCProvider provider,
                cocos2d::CCString *message,
                cocos2d::CCString *storyName, cocos2d::CCString *caption,
                cocos2d::CCString *link, cocos2d::CCString *imgUrl);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        /**
         Converts this `SocialStoryGate` to a Dictionary.
         @param The Dictionary representation of `CCSocialStoryGate`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSocialStoryGate();

    protected:

        /**
         Opens this `Gate` by posting the associated story.
         @return If the story was successfully posted returns `true`;
         otherwise `false`.
         */
        virtual bool openInner();
    };

}

#endif //__CCSocialStoryGate_H_
