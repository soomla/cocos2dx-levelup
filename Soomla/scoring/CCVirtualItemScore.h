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



#ifndef __CCVirtualItemScore_H_
#define __CCVirtualItemScore_H_

#include "CCScore.h"

namespace soomla {

    /**
     A specific type of `Score` that has an associated virtual item.
     The score is related to the specific item ID. For example: a game
     that has an "energy" virtual item can have energy points.
     */
    class CCVirtualItemScore: public CCScore {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mAssociatedItemId, AssociatedItemId, CCLevelUpConsts::JSON_LU_ASSOCITEMID);
    public:
        CCVirtualItemScore(): CCScore(), mAssociatedItemId(NULL) {
        }

        /**
         Creates an instance of `CCVirtualItemScore`.
         @param id ID.
         @param associatedItemId Associated virtual item ID.
         */
        static CCVirtualItemScore *create(cocos2d::__String *id, cocos2d::__String *associatedItemId);

        /**
         Creates an instance of `CCVirtualItemScore`.
         @param id ID.
         @param name Name.
         @param higherBetter If set to `true` higher is better.
         @param associatedItemId Associated virtual item ID.
         */
        static CCVirtualItemScore *create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, cocos2d::__String *associatedItemId);

        SL_CREATE_WITH_DICTIONARY(CCVirtualItemScore);

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, cocos2d::__String *associatedItemId);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        /**
         Converts this `CCVirtualItemScore` to a Dictionary.
         @return The Dictionary representation of this `CCVirtualItemScore`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

        char const *getType() const;

    protected:

        /**
         Gives your user the temp-score amount of the associated item.
         */
        virtual void performSaveActions() override;
    };

}

#endif //__CCVirtualItemScore_H_
