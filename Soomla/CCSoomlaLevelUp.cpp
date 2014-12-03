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


#include "CCSoomlaLevelUp.h"

#include "CCWorld.h"
#include "CCLevel.h"
#include "CCChallenge.h"
#include "CCGatesList.h"
#include "CCLevelUpService.h"
#include "CCDomainHelper.h"
#include "CCKeyValueStorage.h"
#include "CCJsonHelper.h"

namespace soomla {

#define DB_KEY_PREFIX "soomla.levelup."
#define TAG "SOOMLA LevelUp"

    USING_NS_CC;

    static CCSoomlaLevelUp *sInstance = NULL;

    CCSoomlaLevelUp *CCSoomlaLevelUp::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCSoomlaLevelUp();
            sInstance->retain();
        }
        return sInstance;
    }

    bool ifLevel(CCWorld *innerWorld) {
        return strcmp(innerWorld->getType(), CCLevelUpConsts::JSON_JSON_TYPE_LEVEL) == 0;
    }

    bool ifCompletedLevel(CCWorld *innerWorld) {
        return strcmp(innerWorld->getType(), CCLevelUpConsts::JSON_JSON_TYPE_LEVEL) == 0 &&
                innerWorld->isCompleted();
    }

    bool ifWorld(CCWorld *innerWorld) {
        return strcmp(innerWorld->getType(), CCLevelUpConsts::JSON_JSON_TYPE_WORLD) == 0;
    }

    bool ifCompletedWorld(CCWorld *innerWorld) {
        return strcmp(innerWorld->getType(), CCLevelUpConsts::JSON_JSON_TYPE_WORLD) == 0 &&
                innerWorld->isCompleted();
    }

    bool ifWorldOrLevel(CCWorld *innerWorld) {
        return ifWorld(innerWorld) || ifLevel(innerWorld);
    }

    cocos2d::CCDictionary *CCSoomlaLevelUp::toDictionary() {
        cocos2d::CCDictionary *dict = cocos2d::CCDictionary::create();

        dict->setObject(mInitialWorld->toDictionary(), CCLevelUpConsts::JSON_LU_MAIN_WORLD);
        
        if (mRewards) {
            CCArray *rewardArray = CCArray::create();
            CCDictElement* el = NULL;
            CCDICT_FOREACH(mRewards, el) {
                rewardArray->addObject(el->getObject());
            }
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(rewardArray), CCLevelUpConsts::JSON_REWARDS);
        }
        return dict;
    }

    CCSoomlaLevelUp::~CCSoomlaLevelUp() {
        CC_SAFE_RELEASE(mInitialWorld);
        CC_SAFE_RELEASE(mRewards);
    }

    void CCSoomlaLevelUp::initialize(CCWorld *initialWorld, CCArray *rewards) {
        if (mInitialWorld) {
            mInitialWorld->release();
        }
        mInitialWorld = initialWorld;
        if (mInitialWorld) {
            mInitialWorld->retain();
        }

        if (rewards != NULL) {
            CCDictionary *rewardMap = CCDictionary::create();
            CCObject *ref;
            CCReward *reward;
            CCARRAY_FOREACH(rewards, ref) {
                    reward = (CCReward *) ref;
                    rewardMap->setObject(reward, reward->getId()->getCString());
                }

            if (mRewards) {
                mRewards->release();
            }
            mRewards = rewardMap;
            if (mRewards) {
                mRewards->retain();
            }
        }

        save();

        CCLevelUpService::getInstance()->initLevelUp();
    }

    CCReward *CCSoomlaLevelUp::getReward(const char *rewardId) {
        if (mRewards == NULL) {
            return NULL;
        }

        return dynamic_cast<CCReward *>(mRewards->objectForKey(rewardId));
    }

    CCGate *CCSoomlaLevelUp::getGate(char const *gateId) {
        CCGate *gate = NULL;
        gate = fetchGateFromGate(gateId, mInitialWorld->getGate());
        if (gate != NULL) {
            return gate;
        }

        gate = fetchGateFromMissions(gateId, mInitialWorld->getMissions());
        if (gate != NULL) {
            return gate;
        }

        return this->fetchGate(gateId, mInitialWorld->getInnerWorldsMap());
    }
    CCMission *CCSoomlaLevelUp::getMission(char const *missionId) {
        CCMission *retMission = NULL;

        CCObject *ref;
        CCMission *mission;
        CCARRAY_FOREACH(mInitialWorld->getMissions(), ref) {
                mission = dynamic_cast<CCMission *>(ref);
                CC_ASSERT(mission);
                if (mission->getId()->compare(missionId) == 0) {
                    retMission = mission;
                    break;
                }
            }

        if (retMission == NULL) {
            return fetchMission(missionId, mInitialWorld->getInnerWorldsMap());
        }

        return retMission;
    }

    CCScore *CCSoomlaLevelUp::getScore(const char *scoreId) {
        CCDictionary *scores = mInitialWorld->getScores();
        CCScore *score = dynamic_cast<CCScore *>(scores->objectForKey(scoreId));
        if (score == NULL) {
            score = fetchScoreFromWorlds(scoreId, mInitialWorld->getInnerWorldsMap());
        }

        return score;
    }

    CCWorld *CCSoomlaLevelUp::getWorld(const char *worldId) {
        if (mInitialWorld->getId()->compare(worldId) == 0) {
            return mInitialWorld;
        }

        return fetchWorld(worldId, mInitialWorld->getInnerWorldsMap());
    }

    CCLevel *CCSoomlaLevelUp::getLevel(char const *levelId) {
        return dynamic_cast<CCLevel *>(getWorld(levelId));
    }

    /// <summary>
    /// Counts all levels in all worlds and inner worlds.
    /// </summary>
    /// <returns>The number of levels in all worlds and their inner worlds</returns>
    int CCSoomlaLevelUp::getLevelCount() {
        return getLevelCountInWorld(mInitialWorld);
    }

    /// <summary>
    /// Counts all levels in the given world and its inner worlds.
    /// </summary>
    /// <param name="world">The world to examine</param>
    /// <returns>The number of levels in the given world and its inner worlds</returns>
    int CCSoomlaLevelUp::getLevelCountInWorld(CCWorld *world) {
        int count = 0;

        CCDictionary *innerWorldsMap = world->getInnerWorldsMap();
        CCDictElement *el;
        CCDICT_FOREACH(innerWorldsMap, el) {
                count += getRecursiveCount(mInitialWorld, &ifLevel);
            }
        return count;
    }

    /// <summary>
    /// Counts all worlds and their inner worlds with or without their levels.
    /// </summary>
    /// <param name="withLevels">Indicates whether to count also levels</param>
    /// <returns>The number of worlds and their inner worlds, and optionally their inner levels</returns>
    int CCSoomlaLevelUp::getWorldCount(bool withLevels) {
        return getRecursiveCount(mInitialWorld, &(withLevels ? ifWorldOrLevel : ifWorld));
    }

    /// <summary>
    /// Counts all completed levels.
    /// </summary>
    /// <returns>The number of completed levels and their inner completed levels</returns>
    int CCSoomlaLevelUp::getCompletedLevelCount() {
        return getRecursiveCount(mInitialWorld, &ifCompletedLevel);
    }

    /// <summary>
    /// Counts the number of completed worlds.
    /// </summary>
    /// <returns>The number of completed worlds and their inner completed worlds</returns>
    int CCSoomlaLevelUp::getCompletedWorldCount() {
        return getRecursiveCount(mInitialWorld, &ifCompletedWorld);
    }


    void CCSoomlaLevelUp::save() {
        CCString *key = CCString::createWithFormat("%s%s", DB_KEY_PREFIX, "model");
        const char *keyS = key->getCString();
        json_t *metadata = CCJsonHelper::getJsonFromCCObject(toDictionary());
        char *metadataS = json_dumps(metadata, JSON_COMPACT | JSON_ENSURE_ASCII);

        CCKeyValueStorage::getInstance()->setValue(keyS, metadataS);
    }

    CCScore *CCSoomlaLevelUp::fetchScoreFromWorlds(const char *scoreId, CCDictionary *worlds) {
        CCScore *retScore = NULL;

        CCDictElement *el;
        CCWorld *world;
        CCDICT_FOREACH(worlds, el) {
                world = (CCWorld *) el->getObject();
                retScore = dynamic_cast<CCScore *>(world->getScores()->objectForKey(scoreId));
                if (retScore == NULL) {
                    retScore = fetchScoreFromWorlds(scoreId, world->getInnerWorldsMap());
                }
                if (retScore != NULL) {
                    break;
                }
            }

        return retScore;
    }

    CCWorld *CCSoomlaLevelUp::fetchWorld(const char *worldId, CCDictionary *worlds) {
        CCWorld *retWorld;
        retWorld = dynamic_cast<CCWorld *>(worlds->objectForKey(worldId));
        if (retWorld == NULL) {
            CCDictElement *el;
            CCDICT_FOREACH(worlds, el) {
                    retWorld = fetchWorld(worldId, ((CCWorld *)el->getObject())->getInnerWorldsMap());
                    if (retWorld != NULL) {
                        break;
                    }
                }
        }

        return retWorld;
    }

    int CCSoomlaLevelUp::getRecursiveCount(CCWorld *world, bool (*isAccepted)(CCWorld *)) {
        int count = 0;

        // If the predicate is true, increment
        if (isAccepted(world)) {
            count++;
        }

        CCDictionary *innerWorldsMap = world->getInnerWorldsMap();
        CCDictElement *el;
        CCDICT_FOREACH(innerWorldsMap, el) {
            // Recursively count for inner world
            count += getRecursiveCount((CCWorld *) el->getObject(), isAccepted);
        }
        return count;
    }

    CCGate *CCSoomlaLevelUp::fetchGate(char const *gateId, CCDictionary *worlds) {
        if (worlds == NULL) {
            return NULL;
        }

        CCGate *retGate = NULL;

        CCDictElement *el;
        CCWorld *world;
        CCDICT_FOREACH(worlds, el) {
                world = (CCWorld *) el->getObject();
                CCGate *gate = world->getGate();
                retGate = fetchGateFromGate(gateId, gate);
                if (retGate != NULL) {
                    break;
                }
            }


        if (retGate == NULL) {
            CCDICT_FOREACH(worlds, el) {
                    world = (CCWorld *) el->getObject();

                    retGate = fetchGateFromMissions(gateId, world->getMissions());
                    if (retGate != NULL) {
                        break;
                    }

                    retGate = fetchGate(gateId, world->getInnerWorldsMap());
                    if (retGate != NULL) {
                        break;
                    }
                }
        }

        return retGate;

    }

    CCGate *CCSoomlaLevelUp::fetchGateFromMissions(char const *gateId, cocos2d::CCArray *missions) {
        CCGate *retGate = NULL;

        CCObject *ref;
        CCMission *mission;
        CCARRAY_FOREACH(missions, ref) {
                mission = (CCMission *) ref;
                retGate = fetchGateFromGate(gateId, mission->getGate());
                if (retGate != NULL) {
                    return retGate;
                }
            }

        if (retGate == NULL) {
            CCChallenge *challenge;
            CCARRAY_FOREACH(missions, ref) {
                    challenge = dynamic_cast<CCChallenge *>(ref);
                    if (challenge != NULL) {
                        retGate = fetchGateFromMissions(gateId, challenge->getMissions());
                        if (retGate != NULL) {
                            break;
                        }
                    }
                }
        }

        return retGate;
    }

    CCGate *CCSoomlaLevelUp::fetchGateFromGate(char const *gateId, CCGate *targetGate) {
        if (targetGate == NULL) {
            return NULL;
        }

        if ((targetGate != NULL) && (targetGate->getId()->compare(gateId) == 0)) {
            return targetGate;
        }

        CCGate *result = NULL;
        CCGatesList *gatesList = dynamic_cast<CCGatesList *>(targetGate);
        if (gatesList != NULL) {
            CCArray *gatesArray = gatesList->getGates();
            CCObject* gate = NULL;
            CCARRAY_FOREACH(gatesArray, gate) {
                CCGate *innerGate = dynamic_cast<CCGate *>(gate);
                result = fetchGateFromGate(gateId, innerGate);
                if (result != NULL) {
                    break;
                }
            }
        }

        return result;
    }

    CCMission *CCSoomlaLevelUp::fetchMission(char const *missionId, cocos2d::CCDictionary *worlds) {
        CCDictElement *el;
        CCWorld *world;
        CCMission *mission;
        CCDICT_FOREACH(worlds, el) {
                world = (CCWorld *) el->getObject();

                CCObject *ref;
                CCARRAY_FOREACH(world->getMissions(), ref) {
                        mission = dynamic_cast<CCMission *>(ref);
                        CC_ASSERT(mission);
                        if (mission->getId()->compare(missionId) == 0) {
                            return mission;
                        }
                    }

                mission = fetchMission(missionId, world->getInnerWorldsMap());

                if (mission) {
                    return mission;
                }
            }

        return NULL;
    }
}
