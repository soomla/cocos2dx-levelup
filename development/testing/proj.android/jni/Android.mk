LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

CLASSES_FILES   := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
CLASSES_FILES   := $(CLASSES_FILES:$(LOCAL_PATH)/%=%)

UNITTESTCPP_FILES := $(wildcard $(LOCAL_PATH)/../../cocos2d/external/unittest-cpp/UnitTest++/*.cpp)
UNITTESTCPP_FILES += $(wildcard $(LOCAL_PATH)/../../cocos2d/external/unittest-cpp/UnitTest++/Posix/*.cpp)
UNITTESTCPP_FILES   := $(UNITTESTCPP_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := hellocpp/main.cpp
LOCAL_SRC_FILES += $(CLASSES_FILES)
LOCAL_SRC_FILES += $(UNITTESTCPP_FILES)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/external/unittest-cpp/UnitTest++
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/external/unittest-cpp/UnitTest++/Posix

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_store_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_profile_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_levelup_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,ui)
$(call import-module,audio/android)

# $(call import-module,Box2D)
$(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)

$(call import-module,extensions/cocos2dx-store)
$(call import-module,extensions/cocos2dx-profile)
$(call import-module,extensions/cocos2dx-levelup)
