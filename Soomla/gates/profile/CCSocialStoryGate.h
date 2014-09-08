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
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mMessage, Message, CCLevelUpConsts::JSON_LU_MESSAGE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mStoryName, StoryName, CCLevelUpConsts::JSON_LU_STORY_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mCaption, Caption, CCLevelUpConsts::JSON_LU_CAPTION);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mLink, Link, CCLevelUpConsts::JSON_LU_LINK);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mImgUrl, ImgUrl, CCLevelUpConsts::JSON_LU_IMG_LINK);
    public:
        CCSocialStoryGate(): CCSocialActionGate(),
                             mMessage(NULL), mStoryName(NULL),
                             mCaption(NULL), mLink(NULL), mImgUrl(NULL) {
        }

        static CCSocialStoryGate *create(cocos2d::__String *id, CCProvider provider,
                cocos2d::__String *message,
                cocos2d::__String *storyName, cocos2d::__String *caption,
                cocos2d::__String *link, cocos2d::__String *imgUrl);

        SL_CREATE_WITH_DICTIONARY(CCSocialStoryGate);
        virtual bool init(cocos2d::__String *id, CCProvider provider,
                cocos2d::__String *message,
                cocos2d::__String *storyName, cocos2d::__String *caption,
                cocos2d::__String *link, cocos2d::__String *imgUrl);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const override;

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCSocialStoryGate();

    protected:
        virtual bool openInner();
    };

}

#endif //__CCSocialStoryGate_H_
