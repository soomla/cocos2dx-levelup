//
// Created by Shubin Fedor on 19/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCMissionStorage.h"
#include "CCLevelUpService.h"

namespace soomla {
    static CCMissionStorage *sInstance = NULL;

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
        return CCLevelUpService::getInstance()->missionSetCompleted(mission, completed, notify);
    }

    bool CCMissionStorage::isCompleted(CCMission *mission) {
        return getTimesCompleted(mission) > 0;
    }

    int CCMissionStorage::getTimesCompleted(CCMission *mission) {
        return CCLevelUpService::getInstance()->missionGetTimesCompleted(mission);
    }
}
