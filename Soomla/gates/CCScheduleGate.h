//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCScheduleGate_H_
#define __CCScheduleGate_H_

#include "CCGate.h"
#include "CCSchedule.h"

namespace soomla {

    class CCScheduleGate: public CCGate {
        CC_SYNTHESIZE_RETAIN(CCSchedule *, mSchedule, Schedule);
    public:
        static CCScheduleGate *create(cocos2d::__String *id, CCSchedule *schedule);

        SL_CREATE_WITH_DICTIONARY(CCScheduleGate);

        virtual bool init(cocos2d::__String *id, CCSchedule *schedule);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const override;

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCScheduleGate();

    protected:
        virtual void registerEvents();

        virtual void unregisterEvents();

        virtual bool canOpenInner();

        virtual bool openInner();
    };

}

#endif //__CCScheduleGate_H_
