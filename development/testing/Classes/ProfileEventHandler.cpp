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
// Created by Fedor Shubin on 6/14/14.
//

#include "ProfileEventHandler.h"

#define TAG "ProfileEventHandler >>>"

USING_NS_CC;

void ProfileEventHandler::onLoginFailed(soomla::CCProvider provider, cocos2d::__String *errorDescription) {
    log("%s Login to %s has failed: %s", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(), errorDescription->getCString());
}

void ProfileEventHandler::onLoginFinished(soomla::CCUserProfile *userProfile) {
    log("%s %s", TAG, "onLoginFinished");
    
    EventCustom customEvent(soomla::CCProfileConsts::EVENT_LOGIN_FINISHED);
    customEvent.setUserData(userProfile);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}

void ProfileEventHandler::onLoginStarted(soomla::CCProvider provider) {
    log("%s Login to %s has started", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onLoginCancelledEvent(soomla::CCProvider provider) {
    log("%s Login to %s has cancelled", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onLogoutFailed(soomla::CCProvider provider, cocos2d::__String *errorDescription) {
    log("%s Login to %s has FAILED: %s", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(), errorDescription->getCString());
}

void ProfileEventHandler::onLogoutFinished(soomla::CCProvider provider) {
    log("%s Logout from %s has finished", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
    
    EventCustom customEvent(soomla::CCProfileConsts::EVENT_LOGOUT_FINISHED);
    customEvent.setUserData(&provider);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}

void ProfileEventHandler::onLogoutStarted(soomla::CCProvider provider) {
    log("%s Logout from %s has started", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onGetContactsFailed(soomla::CCProvider provider, cocos2d::__String *errorDescription) {
    log("%s Get contacts from %s has FAILED: %s", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        errorDescription->getCString());
}

void ProfileEventHandler::onGetContactsFinished(soomla::CCProvider provider, cocos2d::__Array *contactsDict) {
    log("%s Get contacts from %s has finished", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
    
    for (int i = 0; i < contactsDict->count(); ++i){
        soomla::CCUserProfile * contact = dynamic_cast<soomla::CCUserProfile *>(contactsDict->getObjectAtIndex(i));
        
        log("%s CONTACT %s %s", TAG, contact->getFirstName()->getCString(), contact->getLastName()->getCString());
    }
}

void ProfileEventHandler::onGetContactsStarted(soomla::CCProvider provider) {
    log("%s Get contacts from %s has started", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onGetFeedFailed(soomla::CCProvider provider, cocos2d::__String *errorDescription) {
    log("%s Get feed from %s has FAILED: %s", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
         errorDescription->getCString());
}

void ProfileEventHandler::onGetFeedFinished(soomla::CCProvider provider, cocos2d::__Array *feedList) {
    log("%s Get feed from %s has finished", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
    
    for (int i = 0; i < feedList->count(); ++i){
        log("%s FEED %s", TAG, (dynamic_cast<__String *>(feedList->getObjectAtIndex(i))->getCString()));
    }
}

void ProfileEventHandler::onGetFeedStarted(soomla::CCProvider provider) {
    log("%s Get feed from %s has started", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onSocialActionFailedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType, cocos2d::__String *errorDescription) {
    log("%s Social action %s on %s has FAILED: %s", TAG, soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
        soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        errorDescription->getCString());
}

void ProfileEventHandler::onSocialActionFinishedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType) {
    log("%s Social action %s on %s has finished", TAG, soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
        soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onSocialActionStartedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType) {
    log("%s Social action %s on %s has started", TAG, soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
        soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onUserProfileUpdatedEvent(soomla::CCUserProfile *userProfile) {
    log("%s %s", TAG, "onUserProfileUpdatedEvent");
    
    EventCustom customEvent(soomla::CCProfileConsts::EVENT_USER_PROFILE_UPDATED);
    customEvent.setUserData(userProfile);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}
