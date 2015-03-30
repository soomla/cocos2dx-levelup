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

#include "CCMissionStorage.h"
#include "CCLevelUpBridge.h"

namespace soomla {
    static CCMissionStorage *sInstance = nullptr;

    CCMissionStorage *soomla::CCMissionStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCMissionStorage();
            sInstance->retain();
        }
        return sInstance;
    }


    void CCMissionStorage::setCompleted(CCMission *mission, bool completed) {
        return this->setCompleted(mission, completed, true);
    }

    void CCMissionStorage::setCompleted(CCMission *mission, bool completed, bool notify) {
        return CCLevelUpBridge::getInstance()->missionSetCompleted(mission, completed, notify);
    }

    bool CCMissionStorage::isCompleted(CCMission *mission) {
        return getTimesCompleted(mission) > 0;
    }

    int CCMissionStorage::getTimesCompleted(CCMission *mission) {
        return CCLevelUpBridge::getInstance()->missionGetTimesCompleted(mission);
    }
}
