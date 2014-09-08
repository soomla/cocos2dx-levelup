//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//

#include "CCWorld.h"
#include "CCDomainHelper.h"
#include "CCDomainFactory.h"
#include "CCLevel.h"
#include "CCSoomlaUtils.h"
#include "CCWorldStorage.h"
#include "CCLevelUp.h"

#define TAG "SOOMLA World"

namespace soomla {

    USING_NS_CC;

    CCWorld *CCWorld::create(cocos2d::__String *id) {
        CCWorld *ret = new CCWorld();
        if (ret->init(id)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    CCWorld *CCWorld::create(cocos2d::__String *id, CCGate *gate, cocos2d::__Dictionary *innerWorldsMap, cocos2d::__Dictionary *scores, cocos2d::__Array *missions) {
        CCWorld *ret = new CCWorld();
        if (ret->init(id, gate, innerWorldsMap, scores, missions)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCWorld::init(cocos2d::__String *id) {
        bool result = CCSoomlaEntity::init(id);
        setInnerWorldsMap(__Dictionary::create());
        setScores(__Dictionary::create());
        setMissions(__Array::create());
        if (result) {
            return true;
        }
        return result;
    }

    bool CCWorld::init(cocos2d::__String *id, CCGate *gate, cocos2d::__Dictionary *innerWorldsMap, cocos2d::__Dictionary *scores, cocos2d::__Array *missions) {
        bool result = CCSoomlaEntity::init(id);
        if (result) {
            setGate(gate);
            setInnerWorldsMap(innerWorldsMap);
            setScores(scores);
            setMissions(missions);

            return true;
        }
        return result;
    }

    bool CCWorld::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCSoomlaEntity::initWithDictionary(dict);
        if (result) {

            Ref *ref;

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_GATE);
            if (ref) {
                __Dictionary *gateDict = dynamic_cast<__Dictionary *>(ref);
                CC_ASSERT(gateDict);
                setGate((CCGate *) CCDomainFactory::getInstance()->createWithDictionary(gateDict));
            }

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_WORLDS);
            if (ref) {
                __Array *worldDictArray = dynamic_cast<__Array *>(ref);
                CC_ASSERT(worldDictArray);
                __Array *worldArray = CCDomainHelper::getInstance()->getDomainsFromDictArray(worldDictArray);
                __Dictionary *worldsMap = __Dictionary::create();
                CCWorld *world;
                CCARRAY_FOREACH(worldArray, ref) {
                        world = dynamic_cast<CCWorld *>(ref);
                        CC_ASSERT(world);
                        worldsMap->setObject(world, world->getId()->getCString());
                    }
            }

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORES);
            if (ref) {
                __Array *scoreDictArray = dynamic_cast<__Array *>(ref);
                CC_ASSERT(scoreDictArray);
                __Array *scoreArray = CCDomainHelper::getInstance()->getDomainsFromDictArray(scoreDictArray);
                __Dictionary *scoresMap = __Dictionary::create();
                CCScore *score;
                CCARRAY_FOREACH(scoreArray, ref) {
                        score = dynamic_cast<CCScore *>(ref);
                        CC_ASSERT(score);
                        scoresMap->setObject(score, score->getId()->getCString());
                    }
            }

            ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_MISSIONS);
            if (ref) {
                __Array *missionsDict = dynamic_cast<__Array *>(ref);
                setMissions(CCDomainHelper::getInstance()->getDomainsFromDictArray(missionsDict));
            }

            return true;
        }

        return result;
    }

    cocos2d::__Dictionary *CCWorld::toDictionary() {
        __Dictionary *dict = CCSoomlaEntity::toDictionary();

        if (mGate) {
            dict->setObject(mGate->toDictionary(), CCLevelUpConsts::JSON_LU_GATE);
        }

        if (mInnerWorldsMap) {
            __Array *worldArray = __Array::create();
            DictElement* el = NULL;
            CCDICT_FOREACH(mInnerWorldsMap, el) {
                    worldArray->addObject(el->getObject());
                }
            dict->setObject(CCDomainHelper::getInstance()->getDictArrayFromDomains(worldArray), CCLevelUpConsts::JSON_LU_WORLDS);
        }

        if (mScores) {
            __Array *scoreArray = __Array::create();
            DictElement* el = NULL;
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

    /** Automatic generation of levels. **/
    const char *CCWorld::getIdForAutoGeneratedLevel(const char *id, int idx) {
        return __String::createWithFormat("%s_level%d", id, idx)->getCString();
    }

    const char *CCWorld::getIdForAutoGeneratedScore(const char *id, int idx) {
        return __String::createWithFormat("%s_score%d", id, idx)->getCString();
    }

    const char *CCWorld::getIdForAutoGeneratedGate(const char *id) {
        return __String::createWithFormat("%s_gate", id)->getCString();
    }

    const char *CCWorld::getIdForAutoGeneratedMission(const char *id, int idx) {
        return __String::createWithFormat("%s_mission%d", id, idx)->getCString();
    }

    void CCWorld::batchAddLevelsWithTemplates(int numLevels, CCGate *gateTemplate, CCScore *scoreTemplate, CCMission *missionTemplate) {
        __Array *scoreTemplates = __Array::create();
        if (scoreTemplate) {
            scoreTemplates->addObject(scoreTemplate);
        }
        __Array *missionTemplates = __Array::create();
        if (missionTemplate) {
            missionTemplates->addObject(missionTemplate);
        }

        batchAddLevelsWithTemplates(numLevels, gateTemplate, scoreTemplates, missionTemplates);
    }

    void CCWorld::batchAddLevelsWithTemplates(int numLevels, CCGate *gateTemplate, __Array *scoreTemplates, __Array *missionTemplates) {
        for (int i=0; i<numLevels; i++) {
            const char *lvlId = getIdForAutoGeneratedLevel(getId()->getCString(), i);
            CCLevel *aLvl = CCLevel::create(__String::create(lvlId));

            if (gateTemplate) {
                aLvl->mGate = (CCGate *) gateTemplate->clone(getIdForAutoGeneratedGate(lvlId));
            }

            if (scoreTemplates != NULL) {
                for(int k=0; k<scoreTemplates->count(); k ++) {
                    CCScore *score = (CCScore *)scoreTemplates->getObjectAtIndex(k);
                    aLvl->addScore((CCScore *) score->clone(getIdForAutoGeneratedScore(lvlId, k)));
                }
            }

            if (missionTemplates != NULL) {
                for(int k=0; k<missionTemplates->count(); k++) {
                    CCMission *mission = (CCMission *)missionTemplates->getObjectAtIndex(k);
                    aLvl->addMission((CCMission *) mission->clone(getIdForAutoGeneratedMission(lvlId, k)));
                }
            }

            this->mInnerWorldsMap->setObject(aLvl, lvlId);
        }
    }

    /** For Single Score **/
    void CCWorld::setSingleScoreValue(double amount) {
        if (mScores->count() == 0) {
            return;
        }

        char const *firstScoreId = ((cocos2d::__String *)mScores->allKeys()->getObjectAtIndex(0))->getCString();
        setScoreValue(firstScoreId, amount);
    }

    void CCWorld::decSingleScore(double amount) {
        if (mScores->count() == 0) {
            return;
        }

        char const *firstScoreId = ((cocos2d::__String *)mScores->allKeys()->getObjectAtIndex(0))->getCString();
        decScore(firstScoreId, amount);
    }

    void CCWorld::incSingleScore(double amount) {
        if (mScores->count() == 0) {
            return;
        }
        char const *firstScoreId = ((cocos2d::__String *)mScores->allKeys()->getObjectAtIndex(0))->getCString();
        incScore(firstScoreId, amount);
    }

    CCScore *CCWorld::getSingleScore() {
        if (mScores->count() == 0) {
            return NULL;
        }
        char const *firstScoreId = ((cocos2d::__String *)mScores->allKeys()->getObjectAtIndex(0))->getCString();
        return (CCScore *) mScores->objectForKey(firstScoreId);
    }

    double CCWorld::sumInnerWorldsRecords() {
        double ret = 0;

        CCWorld *world;
        DictElement* el = NULL;
        CCDICT_FOREACH(mInnerWorldsMap, el) {
                world = (CCWorld *) el->getObject();
                ret += world->getSingleScore()->getRecord();
            }

        return ret;
    }

    /** For more than one Score **/

    void CCWorld::resetScores(bool save) {
        if (mScores == NULL || mScores->count() == 0) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat(
                    "(ResetScores) You don't have any scores defined in this world. World id: %s", 
                    getId()->getCString())->getCString());
            return;
        }

        DictElement* el = NULL;
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

    __Dictionary *CCWorld::getRecordScores() {
        __Dictionary *records = __Dictionary::create();
        DictElement* el = NULL;
        CCDICT_FOREACH(mScores, el) {
                CCScore *score = (CCScore *) el->getObject();
                records->setObject(__Double::create(score->getRecord()), el->getStrKey());
            }
        return records;
    }

    __Dictionary *CCWorld::getLatestScores() {
        __Dictionary *records = __Dictionary::create();
        DictElement* el = NULL;
        CCDICT_FOREACH(mScores, el) {
                CCScore *score = (CCScore *) el->getObject();
                records->setObject(__Double::create(score->getLatest()), el->getStrKey());
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
                    __String::createWithFormat(
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
            DictElement* el = NULL;
            CCDICT_FOREACH(mInnerWorldsMap, el) {
                    CCWorld *world = (CCWorld *) el->getObject();
                    world->setCompleted(completed, true);
                }
        }
        CCWorldStorage::getInstance()->setCompleted(this, completed);
    }


    /** Reward Association **/

    void CCWorld::assignReward(CCReward *reward) {
        __String *olderReward = this->getAssignedRewardId();
        if (olderReward != NULL && olderReward->length() > 0) {
            CCReward *oldReward = CCLevelUp::getInstance()->getReward(olderReward->getCString());
            if (oldReward != NULL) {
                oldReward->take();
            }
        }

        // We have to make sure the assigned reward can be assigned unlimited times.
        // There's no real reason why it won't be.
        if (reward->getSchedule()->getActivationLimit() > 0) {
            reward->getSchedule()->setActivationLimit(__Integer::create(0));
        }

        reward->give();
        CCWorldStorage::getInstance()->setReward(this, reward->getId());
    }

    cocos2d::__String *CCWorld::getAssignedRewardId() {
        return CCWorldStorage::getInstance()->getAssignedReward(this);
    }

    bool CCWorld::canStart() {
        return mGate == NULL || mGate->isOpen();
    }

}
