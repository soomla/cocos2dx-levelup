LOCAL_PATH := $(call my-dir)

# cocos2dx-levelup
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_levelup_static
LOCAL_MODULE_FILENAME := libcocos2dxlevelup

LEVELUP_SRC_LIST := $(wildcard $(LOCAL_PATH)/Soomla/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/challenges/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/challenges/profile/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/challenges/store/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/data/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/gates/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/gates/profile/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/gates/store/*.cpp)
LEVELUP_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/scoring/*.cpp)
LOCAL_SRC_FILES := $(LEVELUP_SRC_LIST)

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
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/challenges/profile
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/challenges/store
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/gates
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/gates/profile
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/gates/store
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/scoring

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions/soomla-cocos2dx-core)
$(call import-module,extensions/cocos2dx-store)
$(call import-module,extensions/cocos2dx-profile)
