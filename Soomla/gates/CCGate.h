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


#ifndef __CCGate_H_
#define __CCGate_H_

#include "CCSoomlaEntity.h"

namespace soomla {

    /**
     @class `CCGate`
     @brief A `Gate` is an object that defines certain criteria, and is opened
     when this criteria is met. `Gate`s are usually associated with `Mission`s:
     each `Mission` has a `Gate` that needs to be opened in order for the
     `Mission` to be complete.
     */
    class CCGate: public CCSoomlaEntity {

    public:

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *name = NULL);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        /**
         Attempts to open this `Gate`, if it has not been opened aready.
         */
        virtual bool open();

        /**
         Sets the `Gate` to open without checking if the `Gate` meets its criteria.
         @param open If set to `true` open the `Gate`.
         */
        virtual void forceOpen(bool open);

        /**
         Determines whether this `Gate` is open.
         @return If this `Gate` is open returns `true`; otherwise, `false`.
         */
        virtual bool isOpen();

        /**
         Checks if this `Gate` meets its criteria for opening.
         @return If this `Gate` can be opened returns `true`; otherwise, `false`.
         */
        virtual bool canOpen();
        
        //***** INTERNAL *****//
        virtual void onAttached();
        virtual void onDetached();

    protected:

        /**
         Registers relevant events. Each specific type of `Gate` must implement
         this method.
         */
        virtual void registerEvents() = 0;

        /**
         Unregisters relevant events. Each specific type of `Gate` must
         implement this method.
         */
        virtual void unregisterEvents() = 0;

        /**
         Checks if this `Gate` meets its criteria for opening.
         Each specific type of `Gate` must implement this method to add
         specific `Gate` criteria.
         @return If the criteria is met for opening this `Gate` returns `true`;
         otherwise `false`.
         */
        virtual bool canOpenInner() = 0;

        /**
         Opens this `Gate`.
         @return If this `Gate` was opened returns `true`; otherwise `false`.
         */
        virtual bool openInner() = 0;
        
    private:
        bool eventsRegistered;
    };
}

#endif //__CCGate_H_
