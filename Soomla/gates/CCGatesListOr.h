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



#ifndef __CCGatesListOr_H_
#define __CCGatesListOr_H_

#include "CCGatesList.h"

namespace soomla {

    /**
     A specific type of `GatesList` that can be opened if AT LEAST ONE `Gate`
     in its list is open.
     */
    class CCGatesListOr : public CCGatesList {

    public:

        /**
         Creates an instance of `CCGatesListOr`.
         @param id ID.
         @param gates List of `Gate`s.
         */
        static CCGatesListOr *create(cocos2d::__String *id, cocos2d::__Array *gates = NULL);

        /**
         Constructor for `GatesList` with one `Gate`.
         @param id ID.
         @param singleGate Single `Gate` in this `GatesList`.
         */
        static CCGatesListOr *create(cocos2d::__String *id, CCGate *singleGate);

        SL_CREATE_WITH_DICTIONARY(CCGatesListOr);

        virtual const char *getType() const override;

    protected:

        /**
         Checks if this `GatesList` meets its criteria for opening, by checking
         that AT LEAST ONE `Gate` in the list are open.
         @return If AT LEAST ONE `Gate` in this `GatesList` is open returns
         `true`; otherwise `false`.
         */
        virtual bool canOpenInner();
    };
}


#endif //__CCGatesListAnd_H_
