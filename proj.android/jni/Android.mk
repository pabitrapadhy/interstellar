LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/CCParallaxScrollNode.cpp \
                   ../../Classes/CCParallaxScrollOffset.cpp \
                   ../../Classes/Models/Asteroid.cpp \
                   ../../Classes/Models/Bullet.cpp \
                   ../../Classes/Models/SpaceShip.cpp \
                   ../../Classes/Views/MainMenuScene.cpp \
                   ../../Classes/Controllers/GameObjectPool.cpp \
                   ../../Classes/Controllers/AsteroidController.cpp \
                   ../../Classes/Controllers/BulletController.cpp \
                   ../../Classes/Controllers/SpaceShipController.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Models \
					$(LOCAL_PATH)/../../Classes/Views \
					$(LOCAL_PATH)/../../Classes/Controllers \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
