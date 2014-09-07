//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#include "CCGate.h"
#include "CCSchedule.h"

#ifndef __CCScheduleGate_H_
#define __CCScheduleGate_H_

namespace soomla {

    class CCScheduleGate: public CCGate {
        CC_SYNTHESIZE_RETAIN(CCSchedule *, mSchedule, Schedule);
    public:
        static CCScheduleGate *create(cocos2d::CCString *id, CCSchedule *schedule);

        SL_CREATE_WITH_DICTIONARY(CCScheduleGate);

        virtual bool init(cocos2d::CCString *id, CCSchedule *schedule);

        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual const char *getType() const;

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCScheduleGate();

    protected:
        virtual void registerEvents();

        virtual void unregisterEvents();

        virtual bool canOpenInner();

        virtual bool openInner();
    };

}

#endif //__CCScheduleGate_H_
