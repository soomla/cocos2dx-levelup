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


#ifndef __CCGatesListAnd_H_
#define __CCGatesListAnd_H_

#include "CCGatesList.h"

namespace soomla {

    /**
     @class `CCGatesListAnd`
     @brief A specific type of `GatesList` that can be opened only if ALL
     `Gate`s in its list are open.
     */
    class CCGatesListAnd : public CCGatesList {

    public:

        /**
         Creates an instance of `CCGatesListAnd`.
         @param id ID of this `CCGatesListAnd`.
         @param gates List of `Gate`s.
         */
        static CCGatesListAnd *create(cocos2d::CCString *id, cocos2d::CCArray *gates = NULL);

        /**
         Creates an instance of `CCGatesListAnd`.
         @param id ID of this `CCGatesListAnd`.
         @param singleGate Single `Gate` in this `GatesList`.
         */
        static CCGatesListAnd *create(cocos2d::CCString *id, CCGate *singleGate);

        SL_CREATE_WITH_DICTIONARY(CCGatesListAnd);

        virtual const char *getType() const;

    protected:

        /**
         Checks if this `GatesList` meets its criteria for opening, by checking
         that ALL `Gate`s in the list are open.
         @return If ALL `Gate`s in this `GatesList` are open returns `true`;
         otherwise `false`.
         */
        virtual bool canOpenInner();
    };
}


#endif //__CCGatesListAnd_H_
