//
// Created by Fedor Shubin on 6/19/14.
//

#include "CCLevelUpService.h"
#include "CCDomainFactory.h"
#include "CCLevelUpConsts.h"
#include "CCVirtualItem.h"
#include "CCMarketItem.h"
#include "CCNonConsumableItem.h"
#include "CCVirtualCategory.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCEquippableVG.h"
#include "CCSingleUsePackVG.h"
#include "CCUpgradeVG.h"
#include "CCSingleUseVG.h"
#include "CCDomainHelper.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"
#include "CCStoreInfo.h"
#include "CCLevelUpEventDispatcher.h"
#include "CCVirtualItemReward.h"

USING_NS_CC;


namespace soomla {

#define TAG "SOOMLA CCLevelUpService"

    static CCLevelUpService *sInstance = nullptr;

    soomla::CCLevelUpService *soomla::CCLevelUpService::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCLevelUpService();
            sInstance->retain();
        }
        return sInstance;
    }

    void soomla::CCLevelUpService::initShared(CCStoreAssets *gameAssets, cocos2d::__Dictionary *storeParams) {
        CCLevelUpService *storeService = CCLevelUpService::getInstance();
        if (!storeService->init(gameAssets, storeParams)) {
            exit(1);
        }
    }

    soomla::CCLevelUpService::CCLevelUpService() {

    }

    bool soomla::CCLevelUpService::init(CCStoreAssets *gameAssets, cocos2d::__Dictionary *storeParams) {

        CCLevelUpEventDispatcher::getInstance();    // to get sure it's inited

        CCDomainFactory *domainFactory = CCDomainFactory::getInstance();
//        domainFactory->registerCreator(CCLevelUpConsts::JSON_JSON_TYPE_VIRTUAL_ITEM, CCVirtualItem::createWithDictionary);


        return true;
    }

}
