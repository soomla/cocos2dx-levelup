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


#include "CCScoreStorage.h"
#include "CCScore.h"
#include "CCLevelUpBridge.h"

namespace soomla {
    static CCScoreStorage *sInstance = nullptr;

    CCScoreStorage *soomla::CCScoreStorage::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCScoreStorage();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCScoreStorage::setLatestScore(CCScore *score, double newValue) {
        CCLevelUpBridge::getInstance()->scoreSetLatestScore(score, newValue);
    }

    double CCScoreStorage::getLatestScore(CCScore *score) {
        return CCLevelUpBridge::getInstance()->scoreGetLatestScore(score);
    }

    void CCScoreStorage::setRecordScore(CCScore *score, double newValue) {
        CCLevelUpBridge::getInstance()->scoreSetRecordScore(score, newValue);
    }

    double CCScoreStorage::getRecordScore(CCScore *score) {
        return CCLevelUpBridge::getInstance()->scoreGetRecordScore(score);
    }
}
