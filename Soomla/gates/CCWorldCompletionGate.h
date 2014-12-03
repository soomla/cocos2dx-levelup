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



#ifndef __CCWorldCompletionGate_H_
#define __CCWorldCompletionGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCSimpleStoreEventHandler.h"
#include "CCSimpleLevelUpEventHandler.h"
#include "CCWorld.h"

namespace soomla {

    /**
     A specific type of `Gate` that has an associated world. The `Gate` opens
     once the `World` has been completed.
     */
    class CCWorldCompletionGate: public CCGate {
        friend class CCWorldCompletionGateEventHanler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mAssociatedWorldId, AssociatedWorldId, CCLevelUpConsts::JSON_LU_ASSOCWORLDID)
        CC_SYNTHESIZE_RETAIN(CCLevelUpEventHandler *, mEventHandler, EventHandler);

    public:

        CCWorldCompletionGate(): CCGate(), mAssociatedWorldId(NULL), mEventHandler(NULL) {
        }

        /**
         Constructor.
         @param id ID.
         @param associatedWorldId Associated world ID.
         */
        static CCWorldCompletionGate *create(cocos2d::CCString *id, cocos2d::CCString *associatedWorldId);

        SL_CREATE_WITH_DICTIONARY(CCWorldCompletionGate)
        bool init(cocos2d::CCString *id, cocos2d::CCString *associatedWorldId);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        /**
         Converts this `Gate` to a Dictionary.
         @return The Dictionary representation of this `Gate`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCWorldCompletionGate();

    protected:

        /**
         Registers relevant events: world-completed event.
         */
        virtual void registerEvents();

        /**
         Unregisters relevant events: world-completed event.
         */
        virtual void unregisterEvents();

        /**
         Checks if this `Gate` meets its criteria for opening, by checking that
         the associated world is not null and has been completed.
         @return If this `World` can be opened returns `true`; otherwise `false`.
         */
        virtual bool canOpenInner();

        /**
         Opens this `Gate` if it can be opened (its criteria has been met).
         @return Upon success of opening returns `true`; otherwise `false`.
         */
        virtual bool openInner();
    };

    class CCWorldCompletionGateEventHanler: public CCSimpleLevelUpEventHandler {

    private:
        CCWorldCompletionGate *mWorldCompletionGate;

    public:
        CCWorldCompletionGateEventHanler(): mWorldCompletionGate(NULL) {
        }

        /**
         Creates an instance of `CCWorldCompletionGateEventHanler`.
         @param worldCompletionGate The `WorldCompletionGate` associated with
         this event handler.
         */
        static CCWorldCompletionGateEventHanler *create(CCWorldCompletionGate *worldCompletionGate);

        /**
         Opens this `Gate` if the world-completed event causes the `Gate`'s
         criteria to be met.
         @param world `World` to be compared to the associated `World`.
         */
        void onWorldCompleted(CCWorld *world);
    };
}

#endif //__CCWorldCompletionGate_H_
