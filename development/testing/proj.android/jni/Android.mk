LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

CLASSES_FILES   := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
CLASSES_FILES   := $(CLASSES_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := hellocpp/main.cpp
LOCAL_SRC_FILES += $(CLASSES_FILES)
LOCAL_SRC_FILES += ../../cocos2d/external/unittest-cpp/UnitTest++/AssertException.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/Checks.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/CompositeTestReporter.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/CurrentTest.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/DeferredTestReporter.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/DeferredTestResult.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/MemoryOutStream.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/ReportAssert.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/Test.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/TestDetails.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/TestList.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/TestReporter.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/TestReporterStdout.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/TestResults.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/TestRunner.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/TimeConstraint.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/XmlTestReporter.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/Posix/SignalTranslator.cpp \
    ../../cocos2d/external/unittest-cpp/UnitTest++/Posix/TimeHelpers.cpp \

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
