//
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


#ifndef __CCGatesList_H_
#define __CCGatesList_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCBalanceMission.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualGood.h"

namespace soomla {

    /**
     @class `CCGatesList`
     @brief A representation of one or more `Gate`s which together define a
     composite criteria for progressing between the game's `World`s or `Level`s.
     */
    class CCGatesList: public CCGate {

        friend class CCGateListEventHandler;
        CC_SYNTHESIZE_RETAIN(CCLevelUpEventHandler *, mEventHandler, EventHandler);

    public:
        CCGatesList(): CCGate(), mGates(NULL), mEventHandler(NULL) {
        }

        bool init(cocos2d::CCString *id, cocos2d::CCArray *gates = NULL);
        bool init(cocos2d::CCString *id, CCGate *gate);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCGatesList();

        /**
         Retrieves the number of gates in this `Gateslist`.
         */
        unsigned int count();

        /**
         Adds the given gate to this gateslist.
         @param gate Gate to add.
         */
        void add(CCGate *gate);

        /**
         Removes the given gate from this gateslist.
         @param gate Gate to remove.
         */
        void remove(CCGate *gate);
        
        cocos2d::CCArray *getGates() const;
        void setGates(cocos2d::CCArray *gates);

    protected:

        /**
         Opens this gateslist if it can be opened (its criteria has been met).
         @return If the gate has been opened returns `true`; otherwise `false`.
         */
        virtual bool openInner();

        /**
         Registers relevant events: gate-opened event.
         */
        virtual void registerEvents();

        /**
         Unregisters relevant events: gate-opened event.
         */
        virtual void unregisterEvents();
        
    private:
        cocos2d::CCArray *mGates;
    };

    class CCGateListEventHandler: public CCSimpleLevelUpEventHandler {

    private:

        CCGatesList *mGatesList;

    public:

        /**
         Creates an instance of `CCGateListEventHandler`.
         @param gatesList The `GatesList` associated with this event handler.
         */
        static CCGateListEventHandler *create(CCGatesList *gatesList);

        /**
         Opens this gateslist if the gate-opened event causes the GatesList
         composite criteria to be met.
         @param gate Gate that was opened.
         */
        virtual void onGateOpened(CCGate *gate);
    };
}

#endif //__CCGatesList_H_
