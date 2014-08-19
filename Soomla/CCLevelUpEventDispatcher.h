//
// Created by Fedor Shubin on 6/19/14.
//

#ifndef __CCLevelUpEventDispatcher_H_
#define __CCLevelUpEventDispatcher_H_

#include "CCLevelUpEventHandler.h"
#include "CCAbstractAggregatedEventHandler.h"

namespace soomla {
    class CCLevelUpEventDispatcher
            : public CCAbstractAggregatedEventHandler<CCLevelUpEventHandler>, public CCLevelUpEventHandler {
    public:
        /**
        This class is singleton, access it with this function.
        */
        static CCLevelUpEventDispatcher *getInstance();

        bool init();

        virtual void onGateOpened(CCGate *gate);


        virtual void onMissionCompleted(CCMission *mission);

        virtual void onMissionCompletionRevoked(CCMission *mission);
    };
}


#endif //__CCLevelUpEventDispatcher_H_
