/*
Copyright (c) 2014 Mudafar
GPLv3
*/


#include "AdmobHelper.h"
#include "cocos2d.h"


bool AdmobHelper::isAdShowing = true;
bool AdmobHelper::isAdBottomShowing = true;
bool AdmobHelper::isAdScreenShowing = true;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include <android/log.h>


const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";

void AdmobHelper::hideAd()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAd", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = false;
    }
}

void AdmobHelper::hideAdBottom()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAdBottom", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdBottomShowing = false;
    }
}

void AdmobHelper::hideAdScreen()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAdScreen", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdScreenShowing = false;
    }
}



void AdmobHelper::showAd()
{

    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAd", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = true;
    }

}

void AdmobHelper::showAdBottom()
{

    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAdBottom", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdBottomShowing = true;
    }

}

void AdmobHelper::showAdScreen()
{

    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAdScreen", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdScreenShowing = true;
    }

}


#else


void AdmobHelper::hideAd()
{
    CCLOG("hideAd() called");
    isAdShowing = false;
    return; //nothing
}

void AdmobHelper::hideAdBottom()
{
    CCLOG("hideAdBottom() called");
    isAdBottomShowing = false;
    return; //nothing
}

void AdmobHelper::hideAdScreen()
{
    CCLOG("hideAdScreen() called");
    isAdScreenShowing = false;
    return; //nothing
}


void AdmobHelper::showAd()
{
    CCLOG("showAd() called");
    isAdShowing = true;
    return; //nothing;

}

void AdmobHelper::showAdBottom()
{
    CCLOG("showAdBottom() called");
    isAdBottomShowing = true;
    return; //nothing;

}

void AdmobHelper::showAdScreen()
{
    CCLOG("showAdScreen() called");
    isAdScreenShowing = true;
    return; //nothing;

}

#endif