LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Util.cpp \
                   ../../Classes/CrossHelper.cpp \
                   ../../Classes/CrossAndroid.cpp \
                   ../../Classes/Common/Block.cpp \
                   ../../Classes/Common/DraggableBlock.cpp \
                   ../../Classes/Common/ScalableSprite.cpp \
                   ../../Classes/Common/BaseScene.cpp \
                   ../../Classes/About/AboutScene.cpp \
                   ../../Classes/Game/GameScene.cpp \
                   ../../Classes/Game/LevelLayer.cpp \
                   ../../Classes/Home/HomeScene.cpp \
                   ../../Classes/Levels/ChapterScene.cpp \
                   ../../Classes/Levels/LevelsScene.cpp \
                   ../../Classes/Splash/SplashScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
