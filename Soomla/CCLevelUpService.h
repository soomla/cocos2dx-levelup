//
// Created by Fedor Shubin on 6/19/14.
//


#ifndef __CCLevelUpService_H_
#define __CCLevelUpService_H_


#include "cocos2d.h"
#include "CCStoreAssets.h"

namespace soomla {

    class CCLevelUpService : public cocos2d::Ref {
    public:
        /**
        This class is singleton, use this function to access it.
        */
        static CCLevelUpService *getInstance();

        /**
        Initializes StoreController on native side and allows using its
        functions.
        @param storeAssets An instance of your store's assets class.
        @param storeParams A CCDictionary containing parameters for
        CCSoomlaLevelUp (These were previously found in CCSoomla).
        This dictionary can contain the following:
        "soomSec": __String - The value of the primary encryption key.
        "customSecret": __String - The value of the secondary encryption
        key.
        "androidPublicKey": __String - Your Android public key.
        "SSV": CCBool - Whether or not to enable server side
        verification of purchases.
        */
        static void initShared(CCStoreAssets *gameAssets, cocos2d::__Dictionary *storeParams);

        CCLevelUpService();

        virtual bool init(CCStoreAssets *gameAssets, cocos2d::__Dictionary *storeParams);

        void checkParams(cocos2d::__Dictionary *storeParams);
    };
}

#endif //__CCLevelUpService_H_
