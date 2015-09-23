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
#include "CCLevelUpEventDispatcher.h"
#include "CCKeyValueStorage.h"
#include "CCNativeMissionStorage.h"

namespace soomla {

#define DB_MISSION_KEY_PREFIX "soomla.levelup.missions."

    USING_NS_CC;

    static CCMissionStorage *sInstance = nullptr;

    CCMissionStorage *soomla::CCMissionStorage::getInstance() {
        if (!sInstance)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sInstance = new CCNativeMissionStorage();
#else
            sInstance = new CCMissionStorage();
#endif
        }
        return sInstance;
    }

    void CCMissionStorage::setCompleted(CCMission *mission, bool completed) {
        return this->setCompleted(mission, completed, true);
    }

    void CCMissionStorage::setCompleted(CCMission *mission, bool completed, bool notify) {
        int total = this->getTimesCompleted(mission) + (completed ? 1 : -1);
        if (total < 0) {
            total = 0;
        }

        this->setTimesCompleted(mission, total);

        if (notify) {
            if (completed) {
                CCLevelUpEventDispatcher::getInstance()->onMissionCompleted(mission);
            } else {
                CCLevelUpEventDispatcher::getInstance()->onMissionCompletionRevoked(mission);
            }
        }
    }

    bool CCMissionStorage::isCompleted(CCMission *mission) {
        return getTimesCompleted(mission) > 0;
    }

    int CCMissionStorage::getTimesCompleted(CCMission *mission) {
        const char *key = this->keyMissionTimesCompletedWithMissionId(mission->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        return (val != NULL && strlen(val) > 0) ? __String::create(val)->intValue() : 0;
    }

    void CCMissionStorage::setTimesCompleted(CCMission *mission, int timesCompleted) {
        const char *key = this->keyMissionTimesCompletedWithMissionId(mission->getId()->getCString());
        const char *val = __String::createWithFormat("%d", timesCompleted)->getCString();
        CCKeyValueStorage::getInstance()->setValue(key, val);
    }

    char const *CCMissionStorage::keyMissionTimesCompletedWithMissionId(char const *missionId) {
        return this->keyMissionsWithMissionId(missionId, "timesCompleted");
    }

    char const *CCMissionStorage::keyMissionsWithMissionId(char const *missionId, char const *postfix) {
        return __String::createWithFormat("%s%s.%s", DB_MISSION_KEY_PREFIX, missionId, postfix)->getCString();
    }

    char const *CCMissionStorage::getKeyMissionPrefix() {
        return DB_MISSION_KEY_PREFIX;
    }
}
