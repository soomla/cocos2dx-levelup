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
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCWorld_H_
#define __CCWorld_H_

#include "CCSoomlaEntity.h"
#include "CCGate.h"
#include "CCScore.h"
#include "CCMission.h"
#include "CCReward.h"

namespace soomla {

    /**
     A game can have multiple `World`s or a single one, and `World`s can also 
     contain other `World`s in them. A `World` can contain a set of `Level`s, 
     or multiple sets of `Level`s. A `World` can also have a `Gate` that defines 
     the criteria to enter it. Games that don’t have the concept of `World`s can 
     be modeled as single `World` games.

     Real Game Example: "Candy Crush" uses `World`s.
     */
    class CCWorld: public CCSoomlaEntity {
        CC_SYNTHESIZE_RETAIN(CCGate *, mGate, Gate);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, mInnerWorldsMap, InnerWorldsMap);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, mScores, Scores);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, mMissions, Missions);
    public:
        
        CCWorld(): CCSoomlaEntity(), mGate(NULL), mInnerWorldsMap(NULL), mScores(NULL), mMissions(NULL) {
        }

        /**
         Creates an instance of `CCWorld` using the provided information.
         @param id ID of this `World`.
         */
        static CCWorld *create(cocos2d::CCString *id);
        
        /**
         Creates an instance of `CCWorld` using the provided information.
         @param id ID of this `World`.
         @param gate A `Gate` that needs to be opened in order to enter 
         this `World`
         @param innerWorldsMap A list of `World`s contained within this one.
         @param scores `Score`s of this `World`.
         @param missions `Mission`s of this `World`.
         */
        static CCWorld *create(cocos2d::CCString *id, CCGate *gate,
                cocos2d::CCDictionary *innerWorldsMap, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions);

        SL_CREATE_WITH_DICTIONARY(CCWorld);

        virtual bool init(cocos2d::CCString *id);
        virtual bool init(cocos2d::CCString *id, CCGate *gate,
                cocos2d::CCDictionary *innerWorldsMap, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual char const *getType() const;

        virtual ~CCWorld();

    public:
        
        /**
         Adds the given inner `World` to this `World`.
         @param world World to be added.
         */
        void addInnerWorld(CCWorld *world);
        
        /**
         Adds the given `Mission` to this `World`.
         @param mission Mission to be added.
         */
        void addMission(CCMission *mission);
        
        /**
         Adds the given `Score` to this `World`.
         @param score Score to be added.
         */
        void addScore(CCScore *score);
        
        /**
         Retrieves the inner `World` with the given index.
         @param index The index of the `World` to be retrieved. 
         @return the `World` that was fetched.
         */
        CCWorld *getInnerWorldAt(int index);
        
        /**
         Creates a batch of `Level`s and adds them to this `World`. This 
         function will save you a lot of time - instead of creating many levels 
         one by one, you can create them all at once.
         @param numLevels The number of `Level`s to be added to this `World`.
         @param gateTemplate The `Gate` for the levels.
         @param scoreTemplate `Score` template for the `Level`s.
         @param missionTemplate `Mission` template for the `Level`s.
         */
        void batchAddLevelsWithTemplates(int numLevels, CCGate *gateTemplate, CCScore *scoreTemplate, CCMission *missionTemplate);
        void batchAddLevelsWithTemplates(int numLevels, CCGate *gateTemplate, cocos2d::CCArray *scoreTemplates, cocos2d::CCArray *missionTemplates);
        void batchAddDependentLevelsWithTemplates(int numLevels, CCScore *scoreTemplate, CCMission *missionTemplate);

        void batchAddDependentLevelsWithTemplates(int numLevels, cocos2d::CCArray *scoreTemplates, cocos2d::CCArray *missionTemplates);
        
        /**
         Sets the single `Score` value to the given amount.
         @param amount Amount to set.
         */
        void setSingleScoreValue(double amount);
        
        /**
         Decreases the single `Score` value by the given amount.
         @param amount Amount to decrease by.
         */
        void decSingleScore(double amount);
        
        /**
         Increases the single `Score` value by the given amount.
         @param amount Amount to increase by.
         */
        void incSingleScore(double amount);
        
        /**
         Retrieves the single `Score` value.
         @return The single score.
         */
        CCScore *getSingleScore();
        
        /**
         Resets the `Score`s for this `World`.
         @param save If set to `true` save.
         */
        void resetScores(bool save);
        
        /**
         Decreases the `Score` with the given ID by the given amount.
         @param scoreId ID of the `Score` to be decreased.
         @param amount Amount to decrease by.
         */
        void decScore(char const *scoreId, double amount);
        
        /**
         Increases the `Score` with the given ID by the given amount.
         @param scoreId ID of the `Score` to be increased.
         @param amount Amount.
         */
        void incScore(char const *scoreId, double amount);
        
        /**
         Retrieves the record `Score`s.
         @return The record `Score`s - each `Score` ID with its record.
         */
        cocos2d::CCDictionary *getRecordScores();
        
        /**
         Retrieves the latest `Score`s.
         @return The latest `Score`s - each `Score` ID with its record.
         */
        cocos2d::CCDictionary *getLatestScores();
        
        /**
         Sets the `Score` with the given ID to have the given value.
         @param id ID of the `Score` whose value is to be set.
         @param scoreVal Value to set.
         */
        void setScoreValue(char const *id, double scoreVal);
        void setScoreValue(char const *id, double scoreVal, bool onlyIfBetter);
        
        /**
         Determines whether this `World` is completed.
         @return `true` if this instance is completed; otherwise, `false`.
         */
        bool isCompleted();
        
        /**
         Sets this `World` as completed.
         @param completed If set to `true` completed.
         */
        virtual void setCompleted(bool completed);
        virtual void setCompleted(bool completed, bool recursive);
        
        /**
         Assigns the given reward to this `World`.
         @param reward Reward to assign.
         */
        void assignReward(CCReward *reward);

        /**
         Retrieves the assigned reward ID.
         @return The assigned reward ID.
         */
        cocos2d::CCString *getAssignedRewardId();
        
        /**
         Determines if this world is available for starting, based on either if 
         there is no `Gate` for this `World`, or if the `Gate` is open.
         @return `true` if this instance can start; otherwise, `false`.
         */
        bool canStart();
        
    private:
        char const *getIdForAutoGeneratedLevel(char const *id, int idx);
        char const *getIdForAutoGeneratedScore(char const *id, int idx);
        char const *getIdForAutoGeneratedGate(char const *id);
        char const *getIdForAutoGeneratedCompleteGate(char const *id, char const *previousId);
        char const *getIdForAutoGeneratedMission(char const *id, int idx);

        double sumInnerWorldsRecords();
        void createAddAutoLevel(const char *id, CCLevel *target, CCGate *targetGate, cocos2d::CCArray *scoreTemplates, cocos2d::CCArray *missionTemplates);
    };
}

#endif //__CCWorld_H_
