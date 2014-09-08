//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCVirtualItemScore_H_
#define __CCVirtualItemScore_H_

#include "CCScore.h"

namespace soomla {

    class CCVirtualItemScore: public CCScore {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID);
    public:
        CCVirtualItemScore(): CCScore(), mAssociatedItemId(NULL) {
        }

        static CCVirtualItemScore *create(cocos2d::__String *id, cocos2d::__String *associatedItemId);
        static CCVirtualItemScore *create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, cocos2d::__String *associatedItemId);

        SL_CREATE_WITH_DICTIONARY(CCVirtualItemScore);

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, cocos2d::__String *associatedItemId);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual cocos2d::__Dictionary *toDictionary();

        char const *getType() const;
    protected:
        virtual void performSaveActions() override;
    };

}

#endif //__CCVirtualItemScore_H_
