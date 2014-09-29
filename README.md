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

cocos2dx-levelup is the implementation of the LevelUp module for the Cocos2d-x framework, using the C++ flavour.

<!-- Check out our [Wiki] (https://github.com/soomla/android-store/wiki) for more information about the project and how to use it better. -->

## Model Overview

<!-- attach UML style simple diagram -->


Generally, the Soomla sources contain detailed documentation on the different entities and how to use them, but here's a quick glance:

###World/Level

A _Level_ is pretty clear, and most games have them.
A simple example is an Angry Birds single level, where you need to knock out all the pigs.
It measures specific things, such as duration it takes to complete, and can be started and ended.

A _World_ is a more general concept than a Level (a Level **Is-a** World), and can have innerWorlds to create hierarchies. Another example from Angry Birds is level pages and episodes, which contain the actual levels.

The _Initial World_ is a container world for all worlds and levels in the game. We use the _Initial World_ to intialize the LevelUp module.

###Score

A _Score_ is something which can be accumulated or measured within a _World_ (or _Level_ of course).
It can be incremented or decremented based on user actions, and recorded at the completion of the _World/Level_.

This, in turn, can later be applied to high scores or best times, or treated as collectibles that can be awarded upon completion.

###Gate

A _Gate_ is a closed portal from one _World_ to the next. It can be unlocked in many different ways (according to _Gate_ type), and can also be combined into _GatesList_ to build more complex _Gates_.

###Mission/Challenge

A _Mission_ is a single task a player can complete in a game, usually for a _Reward_.

A _Challenge_ is a set of _Missions_ that need to be completed, so it's a big _Mission_ built out of several smaller _Missions_.

###Reward

A _Reward_ is some kind of perk or status a player can achieve in the game.
This can be either a badge, a virtual item from the game's economy (sword, coins etc.) or anything you can think of, really (unlocking game content or levels comes to mind).

![Model Overview](http://know.soom.la/img/tutorial_img/soomla_diagrams/levelup.png)

##Getting Started (With pre-built libraries - RECOMMENDED)

*If you want to develop with sources, refer to the [Working with sources](#working-with-sources) section below*.

> NOTE: LevelUp depends on SOOMLA's other modules: Core, Store, and Profile. This document assumes that you are new to SOOMLA and have not worked with any of the other SOOMLA modules. If this is not the case, and you already *have* some or all of the other modules, please follow these directions only for the modules you are missing and of course, for the **LevelUp** module.

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

	// initialWorld - should be created here and contain all worlds and levels of the game
	// rewards - should contain a list of all rewards that are given through LevelUp
	soomla::CCLevelUp::getInstance()->initialize(initialWorld, rewards);

	```
	- NOTE: *Custom Secret* - is an encryption secret you provide that will be used to secure your data. Choose this secret wisely, you can't change it after you launch your game!
	> Initialize `CCLevelUpService` ONLY ONCE when your application loads.

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

1. For each of the following XCode projects:
	- `Cocos2dXCore.xcodeproj` (**extensions/soomla-cocos2dx-core/**).  
	- `Cocos2dXStore.xcodeproj` (**extensions/cocos2dx-store/**).
	- `Cocos2dXProfile.xcodeproj` (**extensions/soomla-cocos2dx-profile/**).  
	- `Cocos2dXLevelUp.xcodeproj` (**extensions/cocos2dx-levelup/**).

	Perform the following:
		- Drag the project into your project
		- Add its targets to your **Build Phases->Target Dependencies**
		- Add the Products (\*.a) of the project to **Build Phases->Link Binary With Libraries**.

1. Add the following directories to **Build Settings->Header Search Paths** (with `recursive` option):
 - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/soomla-cocos2dx-core/build/ios/headers/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-store/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-store/build/ios/headers/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-profile/build/ios/headers/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-levelup/Soomla/**`
 - `$(SRCROOT)/../cocos2d/extensions/cocos2dx-levelup/build/ios/headers/**`

1. To register services on the native application (`AppController`):

  1. Import the following headers:
    ```cpp
		#import "ServiceManager.h"
		#import "StoreService.h"
		#import "ProfileService.h"
		#import "LevelUpService.h"
    ```

  1. Register the native `StoreService`, `ProfileService`, and `LevelUpService` by adding:
    ```cpp
		[[ServiceManager sharedServiceManager] registerService:[StoreService sharedStoreService]];
		[[ServiceManager sharedServiceManager] registerService:[ProfileService sharedProfileService]];
		[[ServiceManager sharedServiceManager] registerService:[LevelUpService sharedLevelUpService]];
    ```
    at the beginning of the method `application: didFinishLaunchingWithOptions:` of `AppController`.

1. Make sure you have these 3 Frameworks linked to your XCode project: **Security, libsqlite3.0.dylib, StoreKit**.

1. See the last step of [cocos2dx-profile instructions for iOS](https://github.com/soomla/cocos2dx-profile#instructions-for-ios) in order to connect the Profile module to a social network provider (in this case Facebook).

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

1. Add the following jars to your android project's classpath:
    - From `extensions/soomla-cocos2dx-core/build/android`
		1. SoomlaAndroidCore.jar
		1. Cocos2dxAndroidCore.jar
		1. square-otto-1.3.2.jar

    - From `extensions/cocos2dx-store/build/android`
		1. AndroidStore.jar
		1. Cocos2dxAndroidStore.jar

    - From `extensions/cocos2dx-profile/build/android`
		1. AndroidProfile.jar
		1. Cocos2dxAndroidProfile.jar

		- From `extensions/cocos2dx-levelup/build/android`
		1. AndroidLevelUp.jar
		1. Cocos2dxAndroidLevelUp.jar

1. In your game's main `Cocos2dxActivity`, call the following in the `onCreateView` method:

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

1. Override `onPause`, `onResume`:

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

1. Update your AndroidManifest.xml to include permissions and the SoomlaApp:

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
1. See the last step in [cocos2dx-store instructions for Android](https://github.com/soomla/cocos2dx-store#instructions-for-android) in order to connect the Store module to the desired billing service
1. See the last step in [cocos2dx-profile instructions for Android](https://github.com/soomla/cocos2dx-profile#instructions-for-android) in order to connect the Profile module to a social network provider (in this case Facebook).

That's it! Don't forget to run the **build_native.py** script so cocos2dx-levelup sources will be built with cocos2d-x.

### Integration with Soomla cocos2dx-store

Please follow steps in [cocos2dx-store](https://github.com/soomla/cocos2dx-store) for the _Store_ part of the setup.
Then, you can use the **store-related _LevelUp_ classes**, such as _CCVirtualItemScore_ or _CCVirtualItemReward_ or _CCBalanceGate_.

### Integration with Soomla cocos2dx-profile

Please follow steps in [cocos2dx-profile](https://github.com/soomla/cocos2dx-profile) for the _Profile_ part of the setup.
Then, you can use the **profile-related _LevelUp_ classes**, such as _CCSocialLikeMission_.

## Debugging

You can enable debug logging in cocos2dx-levelup by setting `SOOMLA_DEBUG` in `CCSoomlaUtils.h` (which is located in `soomla-cocos2dx-core` submodule) to `true`. Debug logging can also be enabled at build time by adding `-DSOOMLA_DEBUG=1` to `APP_CPPFLAGS` in your `Application.mk` on Android, or by setting `SOOMLA_DEBUG=1` in your Build Settings' `Preprocessor Macros` on iOS.

If you want to see debug messages from _android-levelup_, set the `logDebug` variable in `com.soomla.SoomlaConfig` to `true`.

To see debug messages on iOS, make sure you have also `DEBUG=1` in your Build Settings' `Preprocessor Macros` (for Debug only).

##**Working with sources**

**SOOMLA appreciates code contributions!** You are more than welcome to extend the capabilities of cocos2dx-levelup.

NOTE: If you would like to contribute, please follow our [Documentation Guidelines](https://github.com/soomla/cocos2dx-store/blob/master/documentation.md). Clear, consistent comments will make our code easy to understand.

To integrate cocos2dx-levelup into your game, follow these steps:

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

2. For iOS: Use sourced versions of Linked projects:
	1. `extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.xcodeproj`
	1. `extensions/cocos2dx-store/development/Cocos2dxStoreFromSources.xcodeproj`
	1. `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.xcodeproj`
	1. `extensions/cocos2dx-levelup/development/Cocos2dxLevelUpFromSources.xcodeproj`

3. For Android: You can use our "sourced" modules for Android Studio (or IntelliJ IDEA):
	1. `extensions/soomla-cocos2dx-core/development/Cocos2dxCoreFromSources.iml`
	1. `extensions/cocos2dx-store/development/Cocos2dxStoreFromSources.iml`
	1. `extensions/cocos2dx-profile/development/Cocos2dxProfileFromSources.iml`
	1. `extensions/cocos2dx-levelup/development/Cocos2dxLevelUpFromSources.iml`

## Example Usages

  > Examples using virtual items are dependent on cocos2dx-store module, with proper CCSoomlaStore initialization and CCStoreAssets definitions. See the cocos2dx-store integration section for more details.

* CCMission with CCReward (collect 5 stars to get 1 mega star)

	```cpp
  CCVirtualItemReward *virtualItemReward = CCVirtualItemReward::create(__String::create("mega_star_reward_id"),
                                                                    __String::create("MegaStarReward"),
                                                                    __Bool::create(false),
                                                                    __Integer::create(1),
                                                                    megaStarItemId);
	__Array *rewards = __Array::create(virtualItemReward, NULL);
  CCBalanceMission *balanceMission = CCBalanceMission::create(__String::create("star_balance_mission_id"),
                                                              __String::create("StarBalanceMission"),
                                                              rewards,
                                                              starItemId,
                                                              __Integer::create(5));

  // use the store to give the items out, usually this will be called from in-game events
  // such as player collecting the stars
  CCStoreInventory::sharedStoreInventory()->giveItem(starItemId->getCString(), 5, &error);

  // events posted:
  // 1. onGoodBalanceChanged (Store events)
  // 2. onMissionCompleted (LevelUp events)
  // 3. onRewardGivenEvent (Core events)

  // now the mission is complete, and reward given
  balanceMission->isCompleted(); // true
  virtualItemReward->isOwned(); // true
	```

* CCRecordGate with CCRangeScore

	```cpp
  CCLevel *lvl1 = CCLevel::create(__String::create("lvl1_recordgate_rangescore"));
  CCLevel *lvl2 = CCLevel::create(__String::create("lvl2_recordgate_rangescore"));

  __String *scoreId = __String::create("range_score");
  CCRangeScore *rangeScore = CCRangeScore::create(scoreId, CCSRange::create(0.0, 100.0));
  __String *recordGateId = __String::create("record_gate");

  CCRecordGate *recordGate = CCRecordGate::create(recordGateId, scoreId, __Double::create(100.0));
  lvl1->addScore(rangeScore);

  // Lock level 2 with record gate
  lvl2->setGate(recordGate);

  // the initial world
  world->addInnerWorld(lvl1);
  world->addInnerWorld(lvl2);

  CCLevelUp::getInstance()->initialize(world);

  lvl1->start();

  // events posted:
  // onLevelStarted (LevelUp events)

  rangeScore->inc(100);

  lvl1->end(true);

  // events posted:
  // onLevelEnded (LevelUp events)
  // onWorldCompleted (lvl1) (LevelUp events)
  // onGateOpened (LevelUp events)
  // [onScoreRecordReached] - if record was broken (LevelUp events)

  recordGate->isOpen(); // true

  lvl2->canStart(); // true
  lvl2->start();
  lvl2->end(true);

  // events posted:
  // onWorldCompleted (lvl2) (LevelUp events)

  lvl2->isCompleted(); // true
	```

* CCVirtualItemScore

	```cpp
  CCLevel *lvl1 = CCLevel::create(__String::create("lvl1_viscore"));
  __String *itemId = __String::create(ITEM_ID_VI_SCORE);
  __String *scoreId = __String::create("vi_score");
  CCVirtualItemScore *virtualItemScore = CCVirtualItemScore::create(scoreId, itemId);
  lvl1->addScore(virtualItemScore);

  world->addInnerWorld(lvl1);

  CCLevelUp::getInstance()->initialize(world);

  lvl1->start();
  // events posted:
  // onLevelStarted (LevelUp events)

  virtualItemScore->inc(2.0);
  // events posted:
  // onGoodBalanceChanged (Store events)

  lvl1->end(true);
  // events posted:
  // onLevelEnded (LevelUp events)
  // onWorldCompleted (lvl1) (LevelUp events)
  // [onScoreRecordChanged] - if record was broken (LevelUp events)

  int currentBalance = CCStoreInventory::sharedStoreInventory()->getItemBalance(ITEM_ID_VI_SCORE, &error);
  // currentBalance == 2
	```

* CCChallenge (Multi-Mission)

  ```cpp
  __String *scoreId = __String::create("main_score");
  CCScore *score = CCScore::create(scoreId);

  CCMission *mission1 = CCRecordMission::create(__String::create("record1_mission"),
                                                __String::create("Record 1 mission"),
                                                scoreId,
                                                __Double::create(10.0));

  CCMission *mission2 = CCRecordMission::create(__String::create("record2_mission"),
                                                __String::create("Record 2 mission"),
                                                scoreId,
                                                __Double::create(100.0));

  __Array *missions = __Array::create(mission1, mission2, NULL);

  CCBadgeReward *badgeReward = CCBadgeReward::create(__String::create("challenge_badge_reward_id"),
                                                     __String::create("ChallengeBadgeRewardId"));
  __Array *rewards = __Array::create(badgeReward, NULL);

  CCChallenge *challenge = CCChallenge::create(__String::create("challenge_id"),
                                               __String::create("Challenge"),
                                               missions,
                                               rewards);

  challenge->isCompleted(); //false

  CCWorld *world = CCWorld::create(__String::create("initial_world"));
  world->addMission(challenge);
  world->addScore(score);

  CCLevelUp::getInstance()->initialize(world);

  score->setTempScore(20.0);
  score->reset(true);

  // events:
  // onMissionCompleted (mission1) (LevelUp events)
  // [onScoreRecordReached] - if record is broken

  score->setTempScore(120.0);
  score->reset(true);

  // events:
  // onMissionCompleted (mission2) (LevelUp events)
  // onMissionCompleted (challenge) (LevelUp events)
  // onRewardGivenEvent (badgeReward) (Core events)

  challenge->isCompleted(); // true
  badgeReward->isOwned(); // true
  ```

* CCGatesList
> Note that currently a `GatesList` gate is automatically opened when sub-gates fulfill the `GatesList` requirement.

  ```cpp
  __String *recordGateId1 = __String::create("gates_list_record_gate_id1");
  __String *scoreId1 = __String::create("gates_list_score_id1");
  __Double *desiredRecord1 = __Double::create(10.0);
  __String *recordGateId2 = __String::create("gates_list_record_gate_id2");
  __String *scoreId2 = __String::create("gates_list_score_id2");
  __Double *desiredRecord2 = __Double::create(20.0);

  CCScore *score1 = CCScore::create(scoreId1);
  CCScore *score2 = CCScore::create(scoreId2);

  CCWorld *world = CCWorld::create(__String::create("initial_world"));
  CCLevel *lvl1 = CCLevel::create(__String::create("level1_id"));
  lvl1->addScore(score1);
  lvl1->addScore(score2);
  world->addInnerWorld(lvl1);

  CCRecordGate *recordGate1 = CCRecordGate::create(recordGateId1, scoreId1, desiredRecord1);
  CCRecordGate *recordGate2 = CCRecordGate::create(recordGateId2, scoreId2, desiredRecord2);

  __Array *gates = __Array::create(recordGate1, recordGate2, NULL);

  CCGatesListOr *gatesListOR = CCGatesListOr::create(__String::create("gate_list_OR_id"),
                                                    gates);

  CCGatesListAnd *gatesListAND = CCGatesListAnd::create(__String::create("gate_list_AND_id"),
                                                        gates);

  CCLevelUp::getInstance()->initialize(world);

  score1->setTempScore(desiredRecord1->getValue());
  score1->reset(true);

  recordGate1->isOpen(); // true
  gatesListOR->isOpen(); // true

  gatesListAND->canOpen(); // false (all sub-gates need to be open for AND)
  gatesListAND->isOpen(); // false

  score2->setTempScore(desiredRecord2->getValue());
  score2->reset(true);

  recordGate2->isOpen(); // true
  gatesListOR->isOpen(); // still true
  gatesListAND->isOpen(); // true
  ```

# Contribution

We want you!

Fork -> Clone -> Implement -> Insert Comments -> Test -> Pull-Request.

We have great RESPECT for contributors.

# Code Documentation

cocos2dx-levelup follows strict code documentation conventions. If you would like to contribute please read our [Documentation Guidelines](https://github.com/soomla/cocos2dx-store/blob/master/documentation.md) and follow them. Clear, consistent  comments will make our code easy to understand.

# SOOMLA, Elsewhere ...

+ [Framework Website](http://www.soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376).
+ [On AngelList](https://angel.co/the-soomla-project)

# License

Apache License. Copyright (c) 2012-2014 SOOMLA. http://www.soom.la
+ http://opensource.org/licenses/Apache-2.0
