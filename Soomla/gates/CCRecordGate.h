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



#ifndef __CCRecordGate_H_
#define __CCRecordGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCScore.h"

namespace soomla {

    /**
     A specific type of `Gate` that has an associated score and a desired
     record. The `Gate` opens once the player achieves the desired record for
     the given score.
     */
    class CCRecordGate: public CCGate {

        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mAssociatedScoreId, AssociatedScoreId, CCLevelUpConsts::JSON_LU_ASSOCSCOREID)
        SL_SYNTHESIZE_DOUBLE_RETAIN_WITH_DICT(mDesiredRecord, DesiredRecord, CCLevelUpConsts::JSON_LU_DESIRED_RECORD);
        CC_SYNTHESIZE(cocos2d::EventListener *, mEventListener, EventListener);

    public:
        CCRecordGate(): CCGate(), mAssociatedScoreId(NULL), mDesiredRecord(NULL), mEventListener(NULL) {
        }

        /**
         Creates an instance of `CCRecordGate`.
         @param id ID.
         @param associatedScoreId Associated score ID.
         @param desiredRecord Desired record.
         */
        static CCRecordGate *create(cocos2d::__String *id, cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord);

        SL_CREATE_WITH_DICTIONARY(CCRecordGate);

        virtual bool init(cocos2d::__String *id, cocos2d::__String *associatedScoreId, cocos2d::__Double *desiredRecord);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const;

        /**
         Converts this `Gate` to a Dictionary.
         @return The Dictionary representation of this `Gate`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCRecordGate();

    protected:

        /**
         Checks if this `Gate` meets its criteria for opening, by checking if
         this `Gate`'s associated `Score` has reached the desired record.
         @return If the `Gate` can be opened returns `true`; otherwise `false`.
         */
        virtual bool canOpenInner();

        /**
         Opens this `Gate` if it can be opened (its criteria has been met).
         @return Upon success of opening returns `true`; otherwise `false`.
         */
        virtual bool openInner();

        /**
         Registers relevant events: score-record changed event.
         */
        virtual void registerEvents();

        /**
         Unregisters relevant events: score-record changed event.
         */
        virtual void unregisterEvents();
        
        /**
         Opens this `Gate` if the score-record-changed event causes the `Gate`'s
         criteria to be met.
         */
        virtual void onScoreRecordChanged(cocos2d::EventCustom *event);
    };
}

#endif //__CCRecordGate_H_
