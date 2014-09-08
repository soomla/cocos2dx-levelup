//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCVirtualItemScore_H_
#define __CCVirtualItemScore_H_

#include "CCScore.h"

namespace soomla {

    class CCVirtualItemScore: public CCScore {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID);
    public:
        CCVirtualItemScore(): CCScore(), mAssociatedItemId(NULL) {
        }

        static CCVirtualItemScore *create(cocos2d::CCString *id, cocos2d::CCString *associatedItemId);
        static CCVirtualItemScore *create(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, cocos2d::CCString *associatedItemId);

        SL_CREATE_WITH_DICTIONARY(CCVirtualItemScore);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *name, cocos2d::CCBool *higherBetter, cocos2d::CCString *associatedItemId);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual cocos2d::CCDictionary *toDictionary();

        char const *getType() const;
    protected:
        virtual void performSaveActions();
    };

}

#endif //__CCVirtualItemScore_H_
