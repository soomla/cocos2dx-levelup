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

#include "CCWorld.h"
#include "CCDomainHelper.h"
#include "CCDomainFactory.h"
#include "CCLevel.h"
#include "CCSoomlaUtils.h"
#include "CCWorldStorage.h"
#include "CCSoomlaLevelUp.h"
#include "CCWorldCompletionGate.h"

#define TAG "SOOMLA World"

namespace soomla {

    USING_NS_CC;

    CCWorld *CCWorld::create(cocos2d::CCString *id) {
        CCWorld *ret = new CCWorld();
        if (ret->init(id)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    CCWorld *CCWorld::create(cocos2d::CCString *id, CCGate *gate, cocos2d::CCDictionary *innerWorldsMap, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions) {
        CCWorld *ret = new CCWorld();
        if (ret->init(id, gate, innerWorldsMap, scores, missions)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCWorld::init(cocos2d::CCString *id) {
        bool result = CCSoomlaEntity::init(id);
        setInnerWorldsMap(CCDictionary::create());
        setScores(CCDictionary::create());
        setMissions(CCArray::create());
        if (result) {
            return true;
        }
        return result;
    }

    bool CCWorld::init(cocos2d::CCString *id, CCGate *gate, cocos2d::CCDictionary *innerWorldsMap, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions) {
        bool result = CCSoomlaEntity::init(id);
        if (result) {
            setGate(gate);
            if (innerWorldsMap) {
                setInnerWorldsMap(innerWorldsMap);
            }
            else {
                setInnerWorldsMap(CCDictionary::create());
            }

            if (scores) {
                setScores(scores);
            }
            else {
                setScores(CCDictionary::create());
            }

            if (missions) {
                setMissions(missions);
            }
            else {
                setMissions(CCArray::create());
            }

            return true;
        }
        return result;
    }

    bool CCWorld::initWithDictionary(cocos2d::CCDictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);
        if (result) {

            CCObject *ref;

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_GATE);
            if (ref) {
                CCDictionary *gateDict = dynamic_cast<CCDictionary *>(ref);
                CC_ASSERT(gateDict);
                setGate((CCGate *) CCDomainFactory::getInstance()->createWithDictionary(gateDict));
            }

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_WORLDS);
            if (ref) {
                CCArray *worldDictArray = dynamic_cast<CCArray *>(ref);
                CC_ASSERT(worldDictArray);
                CCArray *worldArray = CCDomainHelper::getInstance()->getDomainsFromDictArray(worldDictArray);
                CCDictionary *worldsMap = CCDictionary::create();
                CCWorld *world;
                CCARRAY_FOREACH(worldArray, ref) {
                        world = dynamic_cast<CCWorld *>(ref);
                        CC_ASSERT(world);
                        worldsMap->setObject(world, world->getId()->getCString());
                    }
            }

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORES);
            if (ref) {
                CCArray *scoreDictArray = dynamic_cast<CCArray *>(ref);
                CC_ASSERT(scoreDictArray);
                CCArray *scoreArray = CCDomainHelper::getInstance()->getDomainsFromDictArray(scoreDictArray);
                CCDictionary *scoresMap = CCDictionary::create();
                CCScore *score;
                CCARRAY_FOREACH(scoreArray, ref) {
                        score = dynamic_cast<CCScore *>(ref);
                        CC_ASSERT(score);
                        scoresMap->setObject(score, score->getId()->getCString());
                    }
            }

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_MISSIONS);
            if (ref) {
                CCArray *missionsDict = dynamic_cast<CCArray *>(ref);
                setMissions(CCDomainHelper::getInstance()->getDomainsFromDictArray(missionsDict));
            }

            return true;
        }

        return result;
    }

    cocos2d::CCDictionary *CCWorld::toDictionary() {
        CCDictionary *dict = CCSoomlaEntity::toDictionary();

        if (mGate) {
            dict->setObject(mGate->toDictionary(), CCLevelUpConsts::JSON_LU_GATE);
        }

        if (mInnerWorldsMap) {
            CCArray *worldArray = CCArray::create();
            CCDictElement* el = NULL;
            CCDICT_FOREACH(mInnerWorldsMap, el) {
                    worldArray->addObject(el->getObject());
                }
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(worldArray), CCLevelUpConsts::JSON_LU_WORLDS);
        }

        if (mScores) {
            CCArray *scoreArray = CCArray::create();
            CCDictElement* el = NULL;
            CCDICT_FOREACH(mScores, el) {
                    scoreArray->addObject(el->getObject());
                }
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(scoreArray), CCLevelUpConsts::JSON_LU_SCORES);
        }

        if (mMissions) {
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(mMissions), CCLevelUpConsts::JSON_LU_MISSIONS);
        }

        return dict;
    }

    char const *CCWorld::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_WORLD;
    }

    CCWorld::~CCWorld() {
        CC_SAFE_RELEASE(mGate);
        CC_SAFE_RELEASE(mInnerWorldsMap);
        CC_SAFE_RELEASE(mScores);
        CC_SAFE_RELEASE(mMissions);
    }

    /** Add elements to world. **/
    void CCWorld::addInnerWorld(CCWorld *world) {
        mInnerWorldsMap->setObject(world, world->getId()->getCString());
    }

    void CCWorld::addMission(CCMission *mission) {
        mMissions->addObject(mission);
    }

    void CCWorld::addScore(CCScore *score) {
        mScores->setObject(score, score->getId()->getCString());
    }

    CCWorld *CCWorld::getInnerWorldAt(int index) {
        if ((index < 0) || (index >= mInnerWorldsMap->count())) {
            return NULL;
        }

        CCDictElement *element = NULL;
        int i = 0;
        CCDICT_FOREACH(mInnerWorldsMap, element) {
            if (i == index) {
                return dynamic_cast<CCWorld *>(element->getObject());
            }
            ++i;
        }

        return NULL;
    }

    /** Automatic generation of levels. **/
    const char *CCWorld::getIdForAutoGeneratedLevel(const char *id, int idx) {
        return CCString::createWithFormat("%s_level%d", id, idx)->getCString();
    }

    const char *CCWorld::getIdForAutoGeneratedScore(const char *id, int idx) {
        return CCString::createWithFormat("%s_score%d", id, idx)->getCString();
    }

    const char *CCWorld::getIdForAutoGeneratedGate(const char *id) {
        return CCString::createWithFormat("%s_gate", id)->getCString();
    }

    char const *CCWorld::getIdForAutoGeneratedCompleteGate(char const *id, char const *previousId) {
        return getIdForAutoGeneratedGate(CCString::createWithFormat("%s_complete_%s", id, previousId)->getCString());
    }

    const char *CCWorld::getIdForAutoGeneratedMission(const char *id, int idx) {
        return CCString::createWithFormat("%s_mission%d", id, idx)->getCString();
    }

    void CCWorld::batchAddLevelsWithTemplates(int numLevels, CCGate *gateTemplate, CCScore *scoreTemplate, CCMission *missionTemplate) {
        CCArray *scoreTemplates = CCArray::create();
        if (scoreTemplate) {
            scoreTemplates->addObject(scoreTemplate);
        }
        CCArray *missionTemplates = CCArray::create();
        if (missionTemplate) {
            missionTemplates->addObject(missionTemplate);
        }

        batchAddLevelsWithTemplates(numLevels, gateTemplate, scoreTemplates, missionTemplates);
    }

    void CCWorld::batchAddLevelsWithTemplates(int numLevels, CCGate *gateTemplate, CCArray *scoreTemplates, CCArray *missionTemplates) {
        for (int i=0; i<numLevels; i++) {
            const char *lvlId = getIdForAutoGeneratedLevel(getId()->getCString(), i);
            CCLevel *aLvl = CCLevel::create(CCString::create(lvlId));

            CCGate *gate = NULL;
            if (gateTemplate) {
                gate = (CCGate *) gateTemplate->clone(getIdForAutoGeneratedGate(lvlId));
            }

            createAddAutoLevel(lvlId, aLvl, gate, scoreTemplates, missionTemplates);
        }
    }

    void CCWorld::batchAddDependentLevelsWithTemplates(int numLevels, CCScore *scoreTemplate, CCMission *missionTemplate) {
        CCArray *scoreTemplates = CCArray::create();
        if (scoreTemplate) {
            scoreTemplates->addObject(scoreTemplate);
        }
        CCArray *missionTemplates = CCArray::create();
        if (missionTemplate) {
            missionTemplates->addObject(missionTemplate);
        }

        batchAddDependentLevelsWithTemplates(numLevels, scoreTemplates, missionTemplates);
    }

    void CCWorld::batchAddDependentLevelsWithTemplates(int numLevels, cocos2d::CCArray *scoreTemplates, cocos2d::CCArray *missionTemplates) {
        const char *previousLvlId = NULL;
        for (int i=0; i<numLevels; i++) {
            const char *lvlId = getIdForAutoGeneratedLevel(getId()->getCString(), i);
            CCLevel *aLvl = CCLevel::create(CCString::create(lvlId));

            CCGate *completeGate = NULL;
            if (previousLvlId != NULL) {
                completeGate = CCWorldCompletionGate::create(CCString::create(getIdForAutoGeneratedCompleteGate(lvlId, previousLvlId)),
                                                             CCString::create(previousLvlId));
            }

            createAddAutoLevel(lvlId, aLvl, completeGate, scoreTemplates, missionTemplates);
            previousLvlId = lvlId;
        }
    }

    /** For Single Score **/
    void CCWorld::setSingleScoreValue(double amount) {
        if (mScores->count() == 0) {
            return;
        }

        char const *firstScoreId = ((cocos2d::CCString *)mScores->allKeys()->objectAtIndex(0))->getCString();
        setScoreValue(firstScoreId, amount);
    }

    void CCWorld::decSingleScore(double amount) {
        if (mScores->count() == 0) {
            return;
        }

        char const *firstScoreId = ((cocos2d::CCString *)mScores->allKeys()->objectAtIndex(0))->getCString();
        decScore(firstScoreId, amount);
    }

    void CCWorld::incSingleScore(double amount) {
        if (mScores->count() == 0) {
            return;
        }
        char const *firstScoreId = ((cocos2d::CCString *)mScores->allKeys()->objectAtIndex(0))->getCString();
        incScore(firstScoreId, amount);
    }

    CCScore *CCWorld::getSingleScore() {
        if (mScores->count() == 0) {
            return NULL;
        }
        char const *firstScoreId = ((cocos2d::CCString *)mScores->allKeys()->objectAtIndex(0))->getCString();
        return (CCScore *) mScores->objectForKey(firstScoreId);
    }

    double CCWorld::sumInnerWorldsRecords() {
        double ret = 0;

        CCWorld *world;
        CCDictElement* el = NULL;
        CCDICT_FOREACH(mInnerWorldsMap, el) {
                world = (CCWorld *) el->getObject();
                ret += world->getSingleScore()->getRecord();
            }

        return ret;
    }

    void CCWorld::createAddAutoLevel(const char *id, CCLevel *target, CCGate *targetGate,
                                     cocos2d::CCArray *scoreTemplates, cocos2d::CCArray *missionTemplates) {
        if (targetGate) {
            target->mGate = targetGate;
        }

        if (scoreTemplates != NULL) {
            for(int k=0; k<scoreTemplates->count(); k ++) {
                CCScore *score = (CCScore *)scoreTemplates->objectAtIndex(k);
                target->addScore((CCScore *) score->clone(getIdForAutoGeneratedScore(id, k)));
            }
        }

        if (missionTemplates != NULL) {
            for(int k=0; k<missionTemplates->count(); k++) {
                CCMission *mission = (CCMission *)missionTemplates->objectAtIndex(k);
                target->addMission((CCMission *) mission->clone(getIdForAutoGeneratedMission(id, k)));
            }
        }

        this->mInnerWorldsMap->setObject(target, id);
    }

    /** For more than one Score **/

    void CCWorld::resetScores(bool save) {
        if (mScores == NULL || mScores->count() == 0) {
            CCSoomlaUtils::logError(TAG, CCString::createWithFormat(
                    "(ResetScores) You don't have any scores defined in this world. World id: %s",
                    getId()->getCString())->getCString());
            return;
        }

        CCDictElement* el = NULL;
        CCDICT_FOREACH(mScores, el) {
                CCScore *score = (CCScore *) el->getObject();
                score->reset(save);
            }
    }

    void CCWorld::decScore(const char *scoreId, double amount) {
        CCScore *score = (CCScore *)mScores->objectForKey(scoreId);
        score->dec(amount);
    }

    void CCWorld::incScore(const char *scoreId, double amount) {
        CCScore *score = (CCScore *)mScores->objectForKey(scoreId);
        score->inc(amount);
    }

    CCDictionary *CCWorld::getRecordScores() {
        CCDictionary *records = CCDictionary::create();
        CCDictElement* el = NULL;
        CCDICT_FOREACH(mScores, el) {
                CCScore *score = (CCScore *) el->getObject();
                records->setObject(CCDouble::create(score->getRecord()), el->getStrKey());
            }
        return records;
    }

    CCDictionary *CCWorld::getLatestScores() {
        CCDictionary *records = CCDictionary::create();
        CCDictElement* el = NULL;
        CCDICT_FOREACH(mScores, el) {
                CCScore *score = (CCScore *) el->getObject();
                records->setObject(CCDouble::create(score->getLatest()), el->getStrKey());
            }
        return records;
    }

    void CCWorld::setScoreValue(const char *id, double scoreVal) {
        this->setScoreValue(id, scoreVal, false);
    }

    void CCWorld::setScoreValue(const char *id, double scoreVal, bool onlyIfBetter) {
        CCScore *score = (CCScore *) mScores->objectForKey(id);
        if (score == NULL) {
            CCSoomlaUtils::logError(TAG,
                    CCString::createWithFormat(
                            "(setScore) Can't find score id: %s world id: %s",
                            id,
                            this->getId()->getCString()
                    )->getCString());
            return;
        }
        score->setTempScore(scoreVal, onlyIfBetter);
    }


    /** Completion **/

    bool CCWorld::isCompleted() {
        return CCWorldStorage::getInstance()->isCompleted(this);
    }

    void CCWorld::setCompleted(bool completed) {
        this->setCompleted(completed, false);
    }

    void CCWorld::setCompleted(bool completed, bool recursive) {
        if (recursive) {
            CCDictElement* el = NULL;
            CCDICT_FOREACH(mInnerWorldsMap, el) {
                    CCWorld *world = (CCWorld *) el->getObject();
                    world->setCompleted(completed, true);
                }
        }
        CCWorldStorage::getInstance()->setCompleted(this, completed);
    }


    /** Reward Association **/

    void CCWorld::assignReward(CCReward *reward) {
        CCString *olderReward = this->getAssignedRewardId();
        if (olderReward != NULL && olderReward->length() > 0) {
            CCReward *oldReward = CCSoomlaLevelUp::getInstance()->getReward(olderReward->getCString());
            if (oldReward != NULL) {
                oldReward->take();
            }
        }

        // We have to make sure the assigned reward can be assigned unlimited times.
        // There's no real reason why it won't be.
        if (reward->getSchedule()->getActivationLimit() > 0) {
            reward->getSchedule()->setActivationLimit(CCInteger::create(0));
        }

        reward->give();
        CCWorldStorage::getInstance()->setReward(this, reward->getId());
    }

    cocos2d::CCString *CCWorld::getAssignedRewardId() {
        return CCWorldStorage::getInstance()->getAssignedReward(this);
    }

    bool CCWorld::canStart() {
        return mGate == NULL || mGate->isOpen();
    }

}
