//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCSocialStoryGate_H_
#define __CCSocialStoryGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

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

        virtual const char *getType() const override;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSocialStoryGate();

    protected:
        virtual bool openInner();
    };

}

#endif //__CCSocialStoryGate_H_
