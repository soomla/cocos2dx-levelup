//
// Created by Shubin Fedor on 22/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCLevel_H_
#define __CCLevel_H_

#include "CCWorld.h"

namespace soomla {

    class CCLevel : public CCWorld {
    public:
        enum LevelState {
            Idle,
            Running,
            Paused,
            Ended,
            Completed
        };
    private:
        long mStartTime;
        long mElapsed;
        LevelState mState;
    public:

        CCLevel() : CCWorld(), mStartTime(0), mElapsed(0), mState(LevelState::Idle) {
        }

        static CCLevel *create(cocos2d::__String *id);

        static CCLevel *create(cocos2d::__String *id,
                CCGate *gate, cocos2d::__Dictionary *scores, cocos2d::__Array *missions);

        static CCLevel *create(cocos2d::__String *id,
                CCGate *gate, cocos2d::__Dictionary *innerWorlds, cocos2d::__Dictionary *scores, cocos2d::__Array *missions);

        SL_CREATE_WITH_DICTIONARY(CCLevel);

        virtual char const *getType() const;

        virtual ~CCLevel();

        virtual int getTimesStarted();

        virtual int getTimesPlayed();

        virtual long getSlowestDurationMillis();

        virtual long getFastestDurationMillis();

        virtual long getPlayDurationMillis();

        virtual bool start();
        virtual void pause();
        virtual void end(bool completed);
        virtual void restart(bool completed);

        virtual void setCompleted(bool completed);
    protected:
        long getCurrentTimeMs();
    };
}

#endif //__CCLevel_H_
