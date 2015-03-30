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
using namespace soomla;

ProfileEventHandler::ProfileEventHandler() {
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_PROFILE_INITIALIZED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onProfileInitialized, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_USER_RATING,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onUserRatingEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_LOGIN_FAILED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onLoginFailed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_LOGIN_FINISHED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onLoginFinished, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_LOGIN_STARTED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onLoginStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_LOGIN_CANCELLED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onLoginCancelledEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_LOGOUT_FAILED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onLogoutFailed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_LOGOUT_FINISHED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onLogoutFinished, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_LOGOUT_STARTED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onLogoutStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_GET_CONTACTS_FAILED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onGetContactsFailed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_GET_CONTACTS_FINISHED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onGetContactsFinished, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_GET_CONTACTS_STARTED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onGetContactsStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_GET_FEED_FAILED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onGetFeedFailed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_GET_FEED_FINISHED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onGetFeedFinished, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_GET_FEED_STARTED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onGetFeedStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onSocialActionFailedEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onSocialActionFinishedEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onSocialActionStartedEvent, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCProfileConsts::EVENT_USER_PROFILE_UPDATED,
                                                                          CC_CALLBACK_1(ProfileEventHandler::onUserProfileUpdatedEvent, this));
}

void ProfileEventHandler::onProfileInitialized(cocos2d::EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "Profile has initialized");
}

void ProfileEventHandler::onUserRatingEvent(cocos2d::EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "Market rating page has opened");
}

void ProfileEventHandler::onLoginFailed(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *errorDescription = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Login to %s has failed: %s (%s)", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onLoginFinished(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_USER_PROFILE));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("onLoginFinished %s (%s)", userProfile->getProvider()->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onLoginStarted(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Login to %s has started (%s)", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onLoginCancelledEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Login to %s has cancelled (%s)", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onLogoutFailed(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *errorDescription = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Login to %s has FAILED: %s", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString())->getCString());
}

void ProfileEventHandler::onLogoutFinished(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Logout from %s has finished",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString())->getCString());
}

void ProfileEventHandler::onLogoutStarted(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Logout from %s has started",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString())->getCString());
}

void ProfileEventHandler::onGetContactsFailed(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *errorDescription = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Get contacts from %s has FAILED: %s (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onGetContactsFinished(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    __Array *contactsArray = dynamic_cast<__Array *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_CONTACTS));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Get contacts from %s has finished (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
    
    for (int i = 0; i < contactsArray->count(); ++i){
        soomla::CCUserProfile * contact = dynamic_cast<soomla::CCUserProfile *>(contactsArray->getObjectAtIndex(i));
        
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("CONTACT %s %s",
                                                                contact->getFirstName()->getCString(),
                                                                contact->getLastName()->getCString())->getCString());
    }
}

void ProfileEventHandler::onGetContactsStarted(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Get contacts from %s has started (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onGetFeedFailed(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *errorDescription = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Get feed from %s has FAILED: %s (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onGetFeedFinished(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    __Array *feedList = dynamic_cast<__Array *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_FEEDS));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Get feed from %s has finished (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
    
    for (int i = 0; i < feedList->count(); ++i){
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("FEED %s",
                                                                (dynamic_cast<__String *>(feedList->getObjectAtIndex(i))->getCString()))->getCString());
    }
}

void ProfileEventHandler::onGetFeedStarted(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Get feed from %s has started (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onSocialActionFailedEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCSocialActionType socialActionType = CCSocialActionType((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE)))->getValue());
    __String *errorDescription = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Social action %s on %s has FAILED: %s (%s)",
                                                            soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onSocialActionFinishedEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCSocialActionType socialActionType = CCSocialActionType((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Social action %s on %s has finished (%s)",
                                                            soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onSocialActionStartedEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCProvider provider = CCProvider((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCSocialActionType socialActionType = CCSocialActionType((dynamic_cast<__Integer *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE)))->getValue());
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Social action %s on %s has started (%s)",
                                                            soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onUserProfileUpdatedEvent(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_USER_PROFILE));
    
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("onUserProfileUpdatedEvent %s",
                                                            userProfile->getProvider()->getCString())->getCString());
}
