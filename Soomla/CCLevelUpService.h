//
// Created by Fedor Shubin on 6/19/14.
//


#ifndef __CCLevelUpService_H_
#define __CCLevelUpService_H_


#include "cocos2d.h"
#include "CCGate.h"
#include "CCWorld.h"

namespace soomla {

    class CCGate;
    class CCLevel;
    class CCMission;
    class CCScore;
    class CCWorld;

    class CCLevelUpService : public cocos2d::CCObject {
    public:
        /**
        This class is singleton, use this function to access it.
        */
        static CCLevelUpService *getInstance();

        static void initShared();

        CCLevelUpService();

        virtual bool init();

        bool initLevelUp(CCWorld *initialWorld, cocos2d::CCArray *rewards);

        bool gateIsOpen(CCGate *gate);
        void gateSetOpen(CCGate *gate, bool open, bool b);

        void levelSetSlowestDurationMillis(CCLevel *level, long duration);
        long levelGetSlowestDurationMillis(CCLevel *level);

        void levelSetFastestDurationMillis(CCLevel *level, long duration);
        long levelGetFastestDurationMillis(CCLevel *level);

        int levelIncTimesStarted(CCLevel *level);
        int levelDecTimesStarted(CCLevel *level);
        int levelGetTimesStarted(CCLevel *level);

        int levelGetTimesPlayed(CCLevel *level);
        int levelIncTimesPlayed(CCLevel *level);
        int levelDecTimesPlayed(CCLevel *level);

        void missionSetCompleted(CCMission *mission, bool completed, bool notify);
        int missionGetTimesCompleted(CCMission *mission);

        void scoreSetLatestScore(CCScore *score, double newValue);
        double scoreGetLatestScore(CCScore *score);
        void scoreSetRecordScore(CCScore *score, double newValue);
        double scoreGetRecordScore(CCScore *score);


        void worldSetCompleted(CCWorld *world, bool completed, bool notify);
        bool worldIsCompleted(CCWorld *world);

        void worldSetReward(CCWorld *world, cocos2d::CCString *rewardId);
        cocos2d::CCString *worldGetAssignedReward(CCWorld *world);
    };
}

#endif //__CCLevelUpService_H_
