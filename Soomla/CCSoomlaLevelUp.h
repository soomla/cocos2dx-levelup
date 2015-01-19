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


#ifndef __CCSoomlaLevelUp_H_
#define __CCSoomlaLevelUp_H_

#include "cocos2d.h"
#include "CCGate.h"
#include "CCMission.h"

namespace soomla {

    class CCWorld;
    class CCReward;
    class CCScore;
    class CCGate;
    class CCMission;
    class CCLevel;

    /**
     @class CCSoomlaLevelUp
     @brief This is the top level container for the cocos2dx-levelup model and
     definitions. It stores the configurations of the game's world-hierarchy and
     provides lookup functions for levelup model elements.
     */
    class CCSoomlaLevelUp: public cocos2d::CCObject {

    private:
        // Initial `World` to begin the game.
        CCWorld *mInitialWorld;

        // Potential rewards of the `InitialWorld`.
        cocos2d::CCDictionary *mRewards;

        CCSoomlaLevelUp(): mInitialWorld(NULL), mRewards(NULL) {
        }

    public:
        // The instance of `LevelUp` for this game.
        static CCSoomlaLevelUp *getInstance();

        /**
         Converts this instance of `LevelUp` to a `Dictionary`.
         */
        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCSoomlaLevelUp();

        /**
         Initializes the specified `InitialWorld` and rewards.
         @param initialWorld Initial `World` to begin the game.
         @param rewards Rewards for the initial `World`.
         */
        void initialize(CCWorld *initialWorld, cocos2d::CCArray *rewards = NULL);

        /**
         Retrieves the reward with the given ID.
         @param rewardId ID of the `Reward` to be fetched.
         @return The reward that was fetched.
         */
        CCReward *getReward(char const *rewardId);

        /**
         Retrieves the `Score` with the given score ID.
         @param scoreId ID of the `Score` to be fetched.
         @return The score.
         */
        CCScore *getScore(char const *scoreId);

        /**
         Retrieves the `World` with the given world ID.
         @param worldId ID of the `World` to be fetched.
         @return The world.
         */
        CCWorld *getWorld(char const *worldId);

        /**
         Retrieves the `Level` with the given level ID.
         @param levelId ID of the `Level` to be fetched.
         @return The world.
         */
        CCLevel *getLevel(char const *levelId);

        /**
         Retrieves the `Gate` with the given ID.
         @param gateId ID of the `Gate` to be fetched.</param>
         @return The gate.
         */
        CCGate *getGate(char const *gateId);

        /**
         Retrieves the `Mission` with the given ID.
         @param missionId ID of the `Mission` to be fetched.
         @return The mission.
         */
        CCMission *getMission(char const *missionId);

        /**
         Counts all the `Level`s in all `World`s and inner `World`s
         starting from the `InitialWorld`.
         @return The number of levels in all worlds and their inner worlds.
         */
        int getLevelCount();

        /**
         Counts all the `Level`s in all `World`s and inner `World`s
         starting from the given `World`.
         @param world The world to examine.
         @return The number of levels in the given world and its inner worlds.
         */
        int getLevelCountInWorld(CCWorld *world);

        /**
         Counts all `World`s and their inner `World`s with or without their
         `Level`s according to the given `withLevels`.
         @param withLevels Indicates whether to count `Level`s also.
         @return The number of `World`s, and optionally their inner `Level`s.
         */
        int getWorldCount(bool withLevels);

        /**
         Counts all completed `Level`s.
         @return The number of completed `Level`s and their inner completed
         `Level`s.
         */
        int getCompletedLevelCount();

        /**
         Counts the number of completed `World`s.
         @return The number of completed `World`s and their inner completed
         `World`s.
         */
        int getCompletedWorldCount();

    private:
        CCWorld *fetchWorld(char const *worldId, cocos2d::CCDictionary *worlds);

        CCScore *fetchScoreFromWorlds(char const *scoreId, cocos2d::CCDictionary *worlds);

        CCGate *fetchGate(char const *gateId, cocos2d::CCDictionary *worlds);

        CCGate *fetchGateFromMissions(char const *gateId, cocos2d::CCArray *missions);

        CCGate *fetchGateFromGate(char const *gateId, CCGate *targetGate);

        int getRecursiveCount(CCWorld *world, bool (*isAccepted)(CCWorld *));

        CCMission *fetchMission(char const *missionId, cocos2d::CCDictionary *worlds);
        
        CCMission *fetchMission(char const *missionId, cocos2d::CCArray *missions);
        
        CCMission *fetchMission(char const *missionId, CCMission *targetMission);

        void save();
    };

}


#endif //__CCSoomlaLevelUp_H_
