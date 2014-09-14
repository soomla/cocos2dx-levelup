//
// Created by Shubin Fedor on 25/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCLevelUp.h"

#include "CCWorld.h"
#include "CCLevel.h"
#include "CCChallenge.h"
#include "CCLevelUpService.h"

namespace soomla {

#define DB_KEY_PREFIX "soomla.levelup."
#define TAG "SOOMLA LevelUp"

    USING_NS_CC;

    static CCLevelUp *sInstance = NULL;

    CCLevelUp *CCLevelUp::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCLevelUp();
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

    cocos2d::__Dictionary *CCLevelUp::toDictionary() {
        cocos2d::__Dictionary *dict = cocos2d::__Dictionary::create();

        dict->setObject(mInitialWorld, CCLevelUpConsts::JSON_LU_MAIN_WORLD);

        return dict;
    }

    CCLevelUp::~CCLevelUp() {
        CC_SAFE_RELEASE(mInitialWorld);
        CC_SAFE_RELEASE(mRewards);
    }

    void CCLevelUp::initialize(CCWorld *initialWorld, __Array *rewards) {
        if (mInitialWorld) {
            mInitialWorld->release();
        }
        mInitialWorld = initialWorld;
        if (mInitialWorld) {
            mInitialWorld->retain();
        }
//			save();

        if (rewards != NULL) {
            __Dictionary *rewardMap = __Dictionary::create();
            Ref *ref;
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

        CCLevelUpService::getInstance()->initLevelUp(initialWorld, rewards);
    }

    CCReward *CCLevelUp::getReward(const char *rewardId) {
        return dynamic_cast<CCReward *>(mRewards->objectForKey(rewardId));
    }

    CCGate *CCLevelUp::getGate(char const *gateId) {
        if (mInitialWorld->getGate() != NULL && mInitialWorld->getGate()->getId()->compare(gateId) == 0) {
            return mInitialWorld->getGate();
        }

        CCGate *gate = fetchGateFromMissions(gateId, mInitialWorld->getMissions());
        if (gate != NULL) {
            return gate;
        }

        return this->fetchGate(gateId, mInitialWorld->getInnerWorldsMap());
    }
    CCMission *CCLevelUp::getMission(char const *missionId) {
        CCMission *retMission = NULL;

        Ref *ref;
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

    CCScore *CCLevelUp::getScore(const char *scoreId) {
        __Dictionary *scores = mInitialWorld->getScores();
        CCScore *score = dynamic_cast<CCScore *>(scores->objectForKey(scoreId));
        if (score == NULL) {
            score = fetchScoreFromWorlds(scoreId, mInitialWorld->getInnerWorldsMap());
        }

        return score;
    }

    CCWorld *CCLevelUp::getWorld(const char *worldId) {
        if (mInitialWorld->getId()->compare(worldId) == 0) {
            return mInitialWorld;
        }

        return fetchWorld(worldId, mInitialWorld->getInnerWorldsMap());
    }
    
    CCLevel *CCLevelUp::getLevel(char const *levelId) {
        return dynamic_cast<CCLevel *>(getWorld(levelId));
    }

    /// <summary>
    /// Counts all levels in all worlds and inner worlds.
    /// </summary>
    /// <returns>The number of levels in all worlds and their inner worlds</returns>
    int CCLevelUp::getLevelCount() {
        return getLevelCountInWorld(mInitialWorld);
    }

    /// <summary>
    /// Counts all levels in the given world and its inner worlds.
    /// </summary>
    /// <param name="world">The world to examine</param>
    /// <returns>The number of levels in the given world and its inner worlds</returns>
    int CCLevelUp::getLevelCountInWorld(CCWorld *world) {
        int count = 0;

        __Dictionary *innerWorldsMap = world->getInnerWorldsMap();
        DictElement *el;
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
    int CCLevelUp::getWorldCount(bool withLevels) {
        return getRecursiveCount(mInitialWorld, &(withLevels ? ifWorldOrLevel : ifWorld));
    }

    /// <summary>
    /// Counts all completed levels.
    /// </summary>
    /// <returns>The number of completed levels and their inner completed levels</returns>
    int CCLevelUp::getCompletedLevelCount() {
        return getRecursiveCount(mInitialWorld, &ifCompletedLevel);
    }

    /// <summary>
    /// Counts the number of completed worlds.
    /// </summary>
    /// <returns>The number of completed worlds and their inner completed worlds</returns>
    int CCLevelUp::getCompletedWorldCount() {
        return getRecursiveCount(mInitialWorld, &ifCompletedWorld);
    }

    // NOTE: Not sure we need a save function.

//		private void save() {
//			string lu_json = toJSONObject().print();
//			SoomlaUtils.LogDebug(TAG, "saving LevelUp to DB. json is: " + lu_json);
//			string key = DB_KEY_PREFIX + "model";
//
//			// TODO: save on Android and iOS with KeyValueStorage
//			// KeyValueStorage.setValue(key, lu_json);
//		}

    CCScore *CCLevelUp::fetchScoreFromWorlds(const char *scoreId, __Dictionary *worlds) {
        CCScore *retScore = NULL;

        DictElement *el;
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

    CCWorld *CCLevelUp::fetchWorld(const char *worldId, __Dictionary *worlds) {
        CCWorld *retWorld;
        retWorld = dynamic_cast<CCWorld *>(worlds->objectForKey(worldId));
        if (retWorld == NULL) {
            DictElement *el;
            CCDICT_FOREACH(worlds, el) {
                    retWorld = fetchWorld(worldId, ((CCWorld *)el->getObject())->getInnerWorldsMap());
                    if (retWorld != NULL) {
                        break;
                    }
                }
        }

        return retWorld;
    }

    int CCLevelUp::getRecursiveCount(CCWorld *world, bool (*isAccepted)(CCWorld *)) {
        int count = 0;

        // If the predicate is true, increment
        if (isAccepted(world)) {
            count++;
        }

        __Dictionary *innerWorldsMap = world->getInnerWorldsMap();
        DictElement *el;
        CCDICT_FOREACH(innerWorldsMap, el) {
            // Recursively count for inner world
            count += getRecursiveCount((CCWorld *) el->getObject(), isAccepted);
        }
        return count;
    }

    CCGate *CCLevelUp::fetchGate(char const *gateId, __Dictionary *worlds) {
        if (worlds == NULL) {
            return NULL;
        }

        CCGate *retGate = NULL;

        DictElement *el;
        CCWorld *world;
        CCDICT_FOREACH(worlds, el) {
                world = (CCWorld *) el->getObject();
                CCGate *gate = world->getGate();
                if (gate != NULL && gate->getId()->compare(gateId) == 0) {
                    retGate = gate;
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

    CCGate *CCLevelUp::fetchGateFromMissions(char const *gateId, cocos2d::__Array *missions) {
        CCGate *retGate = NULL;

        Ref *ref;
        CCMission *mission;
        CCARRAY_FOREACH(missions, ref) {
                mission = (CCMission *) ref;
                if (mission->getGate() != NULL && mission->getGate()->getId()->compare(gateId) == 0) {
                    retGate = mission->getGate();
                    break;
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

    CCMission *CCLevelUp::fetchMission(char const *missionId, cocos2d::__Dictionary *worlds) {
        DictElement *el;
        CCWorld *world;
        CCMission *mission;
        CCDICT_FOREACH(worlds, el) {
                world = (CCWorld *) el->getObject();

                Ref *ref;
                CCARRAY_FOREACH(mInitialWorld->getMissions(), ref) {
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
