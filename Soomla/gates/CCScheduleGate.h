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


#ifndef __CCScheduleGate_H_
#define __CCScheduleGate_H_

#include "CCGate.h"
#include "CCSchedule.h"

namespace soomla {

    /**
     A specific type of `Gate` that has a schedule that defines when the `Gate`
     can be opened. The `Gate` opens once the player tries to open it in the
     time frame of the defined schedule.
     */
    class CCScheduleGate: public CCGate {
        CC_SYNTHESIZE_RETAIN(CCSchedule *, mSchedule, Schedule);

    public:

        /**
         Creates an instance of `CCScheduleGate`.
         @param id ID of this `Gate`.
         @param schedule Schedule associated with this `Gate`.
         */
        static CCScheduleGate *create(cocos2d::__String *id, CCSchedule *schedule);

        SL_CREATE_WITH_DICTIONARY(CCScheduleGate);

        virtual bool init(cocos2d::__String *id, CCSchedule *schedule);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const override;

        /**
         Converts this `Gate` to a Dictionary.
         @return The Dictionary representation of this `Gate`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCScheduleGate();

    protected:

        /**
         Registers relevant events: In this case there are none.
         */
        virtual void registerEvents();

        /**
         Unregisters relevant events: In this case there are none.
         */
        virtual void unregisterEvents();

        /**
         Checks if this `Gate` meets its criteria for opening.
         @return If this `Gate` can be opened returns `true`; otherwise `false`.
         */
        virtual bool canOpenInner();

        /**
         Opens this `Gate` if it can be opened (its criteria has been met).
         @return Upon success of opening returns `true`; otherwise `false`.
         */
        virtual bool openInner();
    };

}

#endif //__CCScheduleGate_H_
