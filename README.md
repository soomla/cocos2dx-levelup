*This project is a part of [The SOOMLA Project](http://project.soom.la) which is a series of open source initiatives with a joint goal to help mobile game developers get better stores and more in-app purchases.*

<!-- insert short code teaser if you have it
Haven't you ever wanted an in-app purchase one liner that looks like this!?

end short code teaser -->

# cocos2dx-levelup

<!-- updates when you have any -->
<!-- end updates -->

cocos2dx-levelup is an open code initiative as part of The SOOMLA Project. It organizes and simplifies structuring of games for user progress.

It acts as sort of a 'blueprint' for the game, modeling worlds/levels, gates to levels, missions and rewards that can be completed and achieved.
All this is backed by Soomla's core tools, and can be easily integrated with more Soomla modules, like cocos2dx-store for IAP, or cocos2dx-profile for social related functions.

<!-- Check out our [Wiki] (https://github.com/soomla/android-store/wiki) for more information about the project and how to use it better. -->


##**Getting Started (With pre-built libraries - RECOMMENDED)**

*If you want to develop with sources, refer to the [Working with sources](#working-with-sources) section below*.

	NOTE: LevelUp depends on SOOMLA's other modules: Core, Store, and Profile. This document assumes that you are new to SOOMLA and have not worked with any of the other SOOMLA modules. If this is not the case, and you already *have* some or all of the other modules, please follow these directions only for the modules you are missing and of course, for the **LevelUp** module.

1. If you didn't already, clone the Cocos2d-x framework from [here](https://github.com/cocos2d/cocos2d-x), or download it from the [Cocos2d-x website](http://www.cocos2d-x.org/download). Make sure the version you clone is supported by cocos2dx-levelup (the tag is the version).

2. Clone [soomla-cocos2dx-core](https://github.com/soomla/soomla-cocos2dx-core), [cocos2dx-store](https://github.com/soomla/cocos2dx-store), [cocos2dx-profile](https://github.com/soomla/cocos2dx-profile), and **cocos2dx-levelup** into the `extensions` directory located at the root of your Cocos2d-x framework:

    ```
    $ git clone git@github.com:soomla/soomla-cocos2dx-core.git extensions/soomla-cocos2dx-core

	$ git clone git@github.com:soomla/cocos2dx-store.git extensions/cocos2dx-store

	$ git clone git@github.com:soomla/cocos2dx-profile.git extensions/cocos2dx-profile

	$ git clone git@github.com:soomla/cocos2dx-levelup.git extensions/cocos2dx-levelup
    ```

3. We use a [fork](https://github.com/vedi/jansson) of the jansson library for JSON parsing, clone our fork into the `external` directory at the root of your framework:

    ```
    $ git clone git@github.com:vedi/jansson.git external/jansson
    ```

4. Implement your `CCLevelUpEventHandler` class in order to be notified about LevelUp-related events. 

5. Initialize `CCServiceManager`, `CCStoreService`, `CCProfileService`, and `CCLevelUpService` with the class you just created, a `customSecret` and other params:

    	
	```cpp
    __Dictionary *commonParams = __Dictionary::create();
	commonParams->setObject(__String::create("ExampleCustomSecret"), "customSecret");

	__Dictionary *storeParams = __Dictionary::create();
	storeParams->setObject(__String::create("ExamplePublicKey"), "androidPublicKey");

	__Dictionary *profileParams = __Dictionary::create();

    soomla::CCServiceManager::getInstance()->setCommonParams(commonParams);
    
	soomla::CCStoreService::initShared(assets, storeParams);
	
	soomla::CCProfileService::initShared(profileParams);
	
    soomla::CCLevelUpService::initShared();
    soomla::CCLevelUp::getInstance()->initialize(ExampleWorldFactory::createWorld(), NULL);
    	
	```

	NOTE: *Custom Secret* - is an encryption secret you provide that will be used to secure your data. Choose this secret wisely, you can't change it after you launch your game! Initialize `CCLevelUpService` ONLY ONCE when your application loads.

6. Make sure to include the `Cocos2dxLevelUp.h` header whenever you use any of the **cocos2dx-levelup** functions:
    
    ```cpp
    #include "Cocos2dxLevelUp.h"
    ```

7. Add an instance of your event handler to `CCLevelUpEventDispatcher` after `CCLevelUpService` initialization:

    ```cpp
    soomla::CCLevelUpEventDispatcher::getInstance()->addEventHandler(handler);
    ```

**The next steps are different according to which platform you're using.**

####**Instructions for iOS**

In your XCode project, perform the following steps:

1. Add `jansson` (**external/jansson/**) to your project (just add it as a source folder).

2. For each of the following XCode projects:
	- `Cocos2dXCore.xcodeproj` (**extensions/soomla-cocos2dx-core/**).  
	- `Cocos2dXStore.xcodeproj` (**extensions/cocos2dx-store/**).
	- `Cocos2dXProfile.xcodeproj` (**extensions/soomla-cocos2dx-profile/**).  
	- `Cocos2dXLevelUp.xcodeproj` (**extensions/cocos2dx-levelup/**).

	Perform the following: a) Drag the project into your project, b) Add its targets to your **Build Phases->Target Dependencies**, c) Add the Products (\*.a) of the project to **Build Phases->Link Binary With Libraries**.

3. Add the following directories to **Build Settings->Header Search Paths** (with `recursive` option):
 - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/build/ios/headers/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-store/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-store/build/ios/headers/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/build/ios/headers/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-levelup/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-levelup/build/ios/headers/**`

4. Register the native `StoreService`, `ProfileService`, and `LevelUpService` by adding:

    ```cpp
    [[ServiceManager sharedServiceManager] registerService:[StoreService sharedStoreService]];
    [[ServiceManager sharedServiceManager] registerService:[ProfileService sharedProfileService]];
    [[ServiceManager sharedServiceManager] registerService:[LevelUpService sharedLevelUpService]];
    ```

    at the beginning of the method `application: didFinishLaunchingWithOptions:` of `AppController`.

5. Make sure you have these 3 Frameworks linked to your XCode project: **Security, libsqlite3.0.dylib, StoreKit**.

6. See the last step of [cocos2dx-profile instructions for iOS](https://github.com/soomla/cocos2dx-profile#instructions-for-ios) in order to connect the Profile module to a social network provider (in this case Facebook).

That's it! Now all you have to do is build your XCode project and run your game with cocos2dx-levelup.

####**Instructions for Android**

1. Import cocos2dx-store, cocos2dx-profile, and cocos2dx-levelup module into your project's Android.mk by adding the following:

    ```
    LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_store_static # add this line along with your other LOCAL_WHOLE_STATIC_LIBRARIES
    $(call import-module, extensions/cocos2dx-store) # add this line at the end of the file, along with the other import-module calls

    LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_profile_static # add this line along with your other LOCAL_WHOLE_STATIC_LIBRARIES
    $(call import-module, extensions/cocos2dx-profile) # add this line at the end of the file, along with the other import-module calls

    LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_levelup_static # add this line along with your other LOCAL_WHOLE_STATIC_LIBRARIES
    $(call import-module, extensions/cocos2dx-levelup) # add this line at the end of the file, along with the other import-module calls
    ```

2. Add the following jars to your android project's classpath:
    - from `extensions/soomla-cocos2dx-core/build/android`
        1. SoomlaAndroidCore.jar
        2. Cocos2dxAndroidCore.jar
        3. square-otto-1.3.2.jar

    - from `extensions/cocos2dx-store/build/android`
        1. AndroidStore.jar
        2. Cocos2dxAndroidStore.jar

    - from `extensions/cocos2dx-profile/build/android`
    	1. AndroidProfile.jar
        2. Cocos2dxAndroidProfile.jar

	From `extensions/cocos2dx-levelup/build/android`
        - AndroidLevelUp.jar
        - Cocos2dxAndroidLevelUp.jar

3. In your game's main `Cocos2dxActivity`, call the following in the `onCreateView` method:

	``` java
	public Cocos2dxGLSurfaceView onCreateView() {
		// initialize services
		final ServiceManager serviceManager = ServiceManager.getInstance();
		serviceManager.setActivity(this);
		serviceManager.setGlSurfaceView(glSurfaceView);
		serviceManager.registerService(StoreService.getInstance());
		serviceManager.registerService(ProfileService.getInstance());
		serviceManager.registerService(LevelUpService.getInstance());
	}
	```

4. Override `onPause`, `onResume`:

	``` java
    @Override
    protected void onPause() {
        super.onPause();
        ServiceManager.getInstance().onPause();
    }

    @Override
    protected void onResume() {
        ServiceManager.getInstance().onResume();
        super.onResume();
    }
	```

5. Update your AndroidManifest.xml to include permissions and the SoomlaApp:

    ``` xml
    <uses-permission android:name="android.permission.INTERNET"/>
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />

    <!-- optional: required for uploadImage from SD card -->
    <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />

    <application ...
    	       android:name="com.soomla.SoomlaApp">
    	       ...
    </application>
    ```

6. See the last step of [cocos2dx-profile instructions for Android](https://github.com/soomla/cocos2dx-profile#instructions-for-android) in order to connect the Profile module to a social network provider (in this case Facebook).

That's it! Don't forget to run the **build_native.sh** script so cocos2dx-levelup sources will be built with cocos2d-x.

##**Working with sources**

**SOOMLA appreciates code contributions!** You are more than welcome to extend the capabilities of cocos2dx-levelup.

NOTE: If you would like to contribute, please follow our [Documentation Guidelines](https://github.com/soomla/cocos2dx-store/blob/master/documentation.md). Clear, consistent comments will make our code easy to understand.

To integrate cocos2dx-profile into your game, follow these steps:

1. **Recursively** clone soomla-cocos2dx-core, cocos2dx-store, cocos2dx-profile, and cocos2dx-levelup.

    ```
    $ git clone --recursive git@github.com:soomla/soomla-cocos2dx-core.git extensions/soomla-cocos2dx-core

    $ git clone --recursive git@github.com:soomla/cocos2dx-store.git extensions/cocos2dx-store

    $ git clone --recursive git@github.com:soomla/cocos2dx-profile.git extensions/cocos2dx-profile

    $ git clone --recursive git@github.com:soomla/cocos2dx-levelup.git extensions/cocos2dx-levelup
    ```

    **OR:** If you have already cloned the repositories, to obtain submodules, use command:

    ```
    $ git submodule update --init --recursive
    ```
	
    **NOTE:** You should run this command in every repository.

2. For iOS: Use sourced versions of Linked projects (`extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.xcodeproj`, `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.xcodeproj`)

3. For Android: You can use our "sourced" modules for Android Studio (or IntelliJ IDEA) (`extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.iml`, `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.iml`), just including them to your project.


## Model Overview

<!-- attach UML style simple diagram -->


Generally, the Soomla sources contain detailed documentation on the different entities and how to use them, but here's a quick glance:

** World/Level **

A _Level_ is pretty clear, and most games have them.
A simple example is an Angry Birds single level, where you need to knock out all the pigs.
It measures specific things, such as duration it takes to complete, and can be started and ended.


A _World_ is a more general concept than a Level (a Level **Is-a** World), and can have innerWorlds to create hierarchies. Another example from Angry Birds is level pages and episodes, which contain the actual levels.

** Score **

A _Score_ is something which can be accumulated or measured within a _World_ (or _Level_ of course).
It can be incremented or decremented based on user actions, and recorded at the completion of the _World/Level_.

This, in turn, can later be applied to high scores or best times, or treated as collectibles that can be awarded upon completion.

** Gate **

A _Gate_ is closed portal from one _World_ to the next. It can be unlocked in many different ways (according to Gate type), and can also be combined into _GatesList_ to build more complex _Gates_.

** Mission/Challenge **

A _Mission_ is a single task a player can complete in a game, usually for a _Reward_.

A _Challenge_ is a set of _Missions_ that need to be completed, so it's a big _Mission_ built out of several smaller _Missions_.

** Reward **

A _Reward_ is some kind of perk or status a player can achieve in the game.
This can be either a badge, a virtual item from the game's economy (sword, coins etc.) or anything you can think of, really (unlocking game content or levels comes to mind).







