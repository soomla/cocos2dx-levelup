LOCAL_PATH := $(call my-dir)

# cocos2dx-levelup
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_levelup_static
LOCAL_MODULE_FILENAME := libcocos2dxlevelup
LOCAL_SRC_FILES := Soomla/CCLevel.cpp \
	Soomla/CCLevelUp.cpp \
	Soomla/CCLevelUpConsts.cpp \
	Soomla/CCLevelUpEventDispatcher.cpp \
	Soomla/CCLevelUpService.cpp \
	Soomla/CCSimpleLevelUpEventHandler.cpp \
	Soomla/CCWorld.cpp \
	Soomla/challenges/CCChallenge.cpp \
	Soomla/challenges/CCMission.cpp \
	Soomla/challenges/CCRecordMission.cpp \
	Soomla/challenges/CCWorldCompletionMission.cpp \
	Soomla/challenges/profile/CCSocialLikeMission.cpp \
	Soomla/challenges/profile/CCSocialStatusMission.cpp \
	Soomla/challenges/profile/CCSocialStoryMission.cpp \
	Soomla/challenges/profile/CCSocialUploadMission.cpp \
	Soomla/challenges/store/CCBalanceMission.cpp \
	Soomla/challenges/store/CCPurchasingMission.cpp \
	Soomla/data/CCGateStorage.cpp \
	Soomla/data/CCLevelStorage.cpp \
	Soomla/data/CCMissionStorage.cpp \
	Soomla/data/CCScoreStorage.cpp \
	Soomla/data/CCWorldStorage.cpp \
	Soomla/gates/CCGate.cpp \
	Soomla/gates/CCGatesList.cpp \
	Soomla/gates/CCGatesListAnd.cpp \
	Soomla/gates/CCGatesListOr.cpp \
	Soomla/gates/CCRecordGate.cpp \
	Soomla/gates/CCScheduleGate.cpp \
	Soomla/gates/CCWorldCompletionGate.cpp \
	Soomla/gates/profile/CCSocialActionGate.cpp \
	Soomla/gates/profile/CCSocialLikeGate.cpp \
	Soomla/gates/profile/CCSocialStatusGate.cpp \
	Soomla/gates/profile/CCSocialStoryGate.cpp \
	Soomla/gates/profile/CCSocialUploadGate.cpp \
	Soomla/gates/store/CCBalanceGate.cpp \
	Soomla/gates/store/CCPurchasableGate.cpp \
	Soomla/scoring/CCScore.cpp \
	Soomla/scoring/CCVirtualItemScore.cpp \
	Soomla/scoring/CCRangeScore.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/Soomla
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/challenges
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/challenges/profile
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/challenges/store
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/gates
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/gates/profile
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/gates/store
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/scoring
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../lib

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_soomla_common_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_store_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_profile_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/challenges
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/gates
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/scoring

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions/soomla-cocos2dx-core)
$(call import-module,extensions/cocos2dx-store)
$(call import-module,extensions/cocos2dx-profile)
