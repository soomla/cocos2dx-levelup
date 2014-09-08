//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCSocialLikeGate_H_
#define __CCSocialLikeGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

    class CCSocialLikeGate: public CCSocialActionGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mPageName, PageName, CCLevelUpConsts::JSON_LU_PAGE_NAME);
    public:
        CCSocialLikeGate(): CCSocialActionGate(), mPageName(NULL) {
        }

        static CCSocialLikeGate *create(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *pageName);

        SL_CREATE_WITH_DICTIONARY(CCSocialLikeGate);

        virtual bool init(cocos2d::CCString *id, CCProvider provider, cocos2d::CCString *pageName);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSocialLikeGate();

    protected:
        virtual bool openInner();
    };

}

#endif //__CCSocialLikeGate_H_
