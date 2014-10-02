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


#ifndef __CCLevel_H_
#define __CCLevel_H_

#include "CCWorld.h"

namespace soomla {

    /**
     @class CCLevel
     @brief A `Level` is a type of `World`, while a `World` contains
     a set of `Level`s. Each `Level` always has a state that is one
     of: idle, running, paused, ended, or completed.
     
     Real Game Examples: "Candy Crush" and "Angry Birds" use `Level`s.
     */
    class CCLevel : public CCWorld {
        
    public:

        /**
         The state of this `Level`. Every level must have one of the below
         states.
         */
        enum LevelState {
            Idle,
            Running,
            Paused,
            Ended,
            Completed
        };
        
    private:
        // Start time of this `Level`.
        long mStartTime;
        
        // The elapsed time this `Level` is being played.
        long mElapsed;
        
        /**
         The state of this `Level`. The initial state is idle, later in the
         game can be any of: running, paused, ended, or completed.
         */
        LevelState mState;
        
    public:

        CCLevel() : CCWorld(), mStartTime(0), mElapsed(0), mState(Idle) {
        }

        /**
         Creates an instance of `CCLevel` using the provided information.
         @param ID of this `Level`.
         */
        static CCLevel *create(cocos2d::CCString *id);
        
        /**
         Creates an instance of `CCLevel` using the provided information.
         @param id ID of this `Level`.
         @param gate `Gate` to open this `Level`.
         @param scores `Score`s of this `Level`.
         @param missions `Mission`s of this `Level`.
         */
        static CCLevel *create(cocos2d::CCString *id,
                CCGate *gate, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions);
        
        /**
         Creates an instance of `CCLevel` using the provided information.
         @param id ID of this `Level`.
         @param gate `Gate` to open this `Level`.
         @param innerWorlds Inner `World`s of this `Level`.
         @param scores `Score`s of this `Level`.
         @param missions `Mission`s of this `Level`.
         */
        static CCLevel *create(cocos2d::CCString *id,
                CCGate *gate, cocos2d::CCDictionary *innerWorlds, cocos2d::CCDictionary *scores, cocos2d::CCArray *missions);

        SL_CREATE_WITH_DICTIONARY(CCLevel);

        virtual char const *getType() const;

        virtual ~CCLevel();
        
        /**
         Gets the number of times this `Level` was started.
         @return The number of times started.
         */
        virtual int getTimesStarted();
        
        /**
         Gets the number of times this `Level` was played.
         @return The number of times played.
         */
        virtual int getTimesPlayed();
        
        /**
         Gets the slowest duration in millis that this `Level` was played.
         @return The slowest duration in millis.
         */
        virtual long getSlowestDurationMillis();
        
        /**
         Gets the fastest duration in millis that this `Level` was played.
         @return The fastest duration in millis.
         */
        virtual long getFastestDurationMillis();
        
        /**
         Gets the play duration of this `Level` in millis.
         @return The play duration in millis.
         */
        virtual long getPlayDurationMillis();
        
        /**
         Starts this `Level`.
         */
        virtual bool start();
        
        /**
         Pauses this `Level`.
         */
        virtual void pause();
        
        /**
         Ends this `Level`.
         @param completed If set to `true` completed.
         */
        virtual void end(bool completed);
        
        /**
         Restarts this `Level`.
         @param completed If set to `true` completed.
         */
        virtual void restart(bool completed);
        
        /**
         Sets this `Level` as completed.
         @param completed If set to `true` completed.
         */
        virtual void setCompleted(bool completed);
        
    protected:
        long getCurrentTimeMs();
    };
}

#endif //__CCLevel_H_
