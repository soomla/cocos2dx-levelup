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

//
// Created by Shubin Fedor on 20/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#ifndef __CCRecordGate_H_
#define __CCRecordGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCSimpleLevelUpEventHandler.h"

namespace soomla {
    
    /**
     A specific type of `Gate` that has an associated score and a desired 
     record. The `Gate` opens once the player achieves the desired record for 
     the given score.
     */
    class CCRecordGate: public CCGate {
        
        friend class CCRecordGateEventHandler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedScoreId, AssociatedScoreId, CCLevelUpConsts::JSON_LU_ASSOCSCOREID)
        SL_SYNTHESIZE_DOUBLE_RETAIN_WITH_DICT(mDesiredRecord, DesiredRecord, CCLevelUpConsts::JSON_LU_DESIRED_RECORD);
        CC_SYNTHESIZE(CCLevelUpEventHandler *, mEventHandler, EventHandler);
        
    public:
        CCRecordGate(): CCGate(), mAssociatedScoreId(NULL), mDesiredRecord(NULL), mEventHandler(NULL) {
        }

        /**
         Creates an instance of `CCRecordGate`.
         @param id ID.
         @param associatedScoreId Associated score ID.
         @param desiredRecord Desired record.
         */
        static CCRecordGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord);

        SL_CREATE_WITH_DICTIONARY(CCRecordGate);

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *associatedScoreId, cocos2d::CCDouble *desiredRecord);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;
        
        /**
         Converts this `Gate` to a Dictionary.
         @return The Dictionary representation of this `Gate`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

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
    };

    class CCRecordGateEventHandler: public CCSimpleLevelUpEventHandler {
        
    private:
        CCRecordGate *mRecordGate;
        
    public:
        
        /**
         Creates an instance of `CCRecordGateEventHandler`.
         @param recordGate The `RecordGate` associated with this event handler. 
         */
        static CCRecordGateEventHandler *create(CCRecordGate *recordGate);
        
        /**
         Opens this `Gate` if the score-record-changed event causes the `Gate`'s 
         criteria to be met.
         @param score The `Score` whose record has changed.
         */
        void onScoreRecordChanged(CCScore *score);
    };
}

#endif //__CCRecordGate_H_
