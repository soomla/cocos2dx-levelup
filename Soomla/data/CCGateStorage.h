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
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCGateStorage_H_
#define __CCGateStorage_H_

#include "cocos2d.h"
#include "CCMission.h"

namespace soomla {
    
    /**
     @class
     @brief A utility class for persisting and querying the state of `Gate`s.
     Use this class to check if a certain `Gate` is open, or to open it.
     */
    class CCGateStorage: cocos2d::CCObject {
        
    public:
        static CCGateStorage *getInstance();
        
        /**
         Determines if the given `Gate` is open.
         @param gate `Gate` to check if is open.
         @return If the given `Gate` is open returns `true`; otherwise, `false`.
         */
        bool isOpen(CCGate *gate);
        
        /**
         Sets the given `Gate` as open if the given parameter `open` is `true`;
         otherwise sets as closed.
         @param gate The `Gate` to open/close.
         @param open If set to `true` set the `Gate` to open;
         @param notify If set to `true` trigger event.
         */
        void setOpen(CCGate *gate, bool open);
        void setOpen(CCGate *gate, bool open, bool notify);
    };
}

#endif //__CCGateStorage_H_
