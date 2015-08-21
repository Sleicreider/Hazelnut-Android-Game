LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/ui)



LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/InGameController.cpp \
                   ../../Classes/InGameScene.cpp \
                   ../../Classes/Loader.cpp \
                   ../../Classes/FrameworkTimer.cpp \
		   ../../Classes/TutorialScene.cpp \
		   ../../Classes/FUtil.cpp \
		   ../../Classes/FrameworkScene.cpp \
			../../Classes/FSprite.cpp \
		   ../../Classes/FPopup.cpp \
		   ../../Classes/TutorialPopup.cpp \
		   ../../Classes/GamePausePopup.cpp \
                   ../../Classes/AI.cpp \
                   ../../Classes/AIDropObject.cpp \
                   ../../Classes/CollisionBox.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/MenuPopup.cpp \
                   ../../Classes/LevelSystem.cpp \
                   ../../Classes/TextFieldExtended.cpp \
                   ../../Classes/GameUtil.cpp \
                   ../../Classes/FileOperation.cpp \
                   ../../Classes/HighscoreScene.cpp \
					../../Classes/AdmobHelper.cpp
                   
                   
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_CFLAGS := -std=gnu++11

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
