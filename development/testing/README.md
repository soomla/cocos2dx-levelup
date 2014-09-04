# cocos2dx-profile-example

**cocos2dx-profile-example** is an example project demonstrating usage and implementation of SOOMLA's [cocos2dx-profile](http://github.com/soomla/cocos2dx-profile).

This project contains examples for implementing all of SOOMLA's interfaces and using SOOMLA's various services related to the Profile project.

The example project uses the [cocos2dx-store](https://github.com/soomla/cocos2dx-store) project as well, but this only to create a virtual economy and hand out meaningful rewards. The dependency to cocos2dx-store is completely optional.

![SOOMLA's Profile Module](http://know.soom.la/img/tutorial_img/soomla_diagrams/Profile.png)

## Facebook
This example integrates to **Facebook** out-of-the-box, and provides a good example of how simple it is to integrate a social network into your game with the Profile module.

## Getting started

1. Obtain the Cocos2d-x framework either from [Github](https://github.com/cocos2d/cocos2d-x) or from the [Cocos2d-x website](http://www.cocos2d-x.org/download). Make sure to use the latest stable 3rd version of cocos2d-x (we tested with v3.2).
    ```
    $ git clone git@github.com:cocos2d/cocos2d-x.git
    ```

2. Clone our [soomla-cocos2dx-core](https://github.com/soomla/soomla-cocos2dx-core), [cocos2dx-store](https://github.com/soomla/cocos2dx-store) and [cocos2dx-profile](https://github.com/soomla/cocos2dx-profile) libraries into the `extensions` directory in the root of your Cocos2d-x framework.
    ```
    $ cd cocos2dx
    $ git clone git@github.com:soomla/soomla-cocos2dx-core.git extensions/soomla-cocos2dx-core
    $ git clone git@github.com:soomla/cocos2dx-store.git extensions/cocos2dx-store
    $ git clone git@github.com:soomla/cocos2dx-profile.git extensions/cocos2dx-profile
    ```

3. Clone our [fork](https://github.com/vedi/jansson) of the janssen library into the `external` directory in the root of your Cocos2d-x framework.
    ```
    $ git clone git@github.com:vedi/jansson.git external/jansson
    ```

4. Clone cocos2dx-profile-example into the `projects` directory at the root of the Cocos2d-x framework.
    ```
    $ git clone git@github.com:soomla/cocos2dx-profile-example.git projects/cocos2dx-profile-example
    ```

**Note**: We use a symlink to cocos2d-x in our example project. It relies on cocos2d-x availability in the relative path. If you want to use the project from a different location, update the symlink, or completely replace it with the cocos2d-x folder.

#### Build instructions for Android

1. Run the `build_native.sh` script located in projects/cocos2dx-profile-example/proj.android. This step should take a while.
    ```
    $ cd projects/cocos2dx-profile-example/proj.android
    $ ./build_native.py
    ```

2. Finally, open the `proj.android` directory located in `cocos2dx-profile-example` in Android Studio (IntelliJ IDEA). `proj.android` is an Android Studio project.
3. Build the project, run example activity, and you're ready to go! The application should launch in an emulator or on your device.

Take a look around, and get a feel for all you can do with cocos2dx-profile. Be sure to take a look in `Logcat` since some of the results are printed there (like `getFeed` and `getContacts`).


#### Build instructions for iOS

1. Open the XCode project under `proj.ios_mac`.
2. Build the project, run it, and you're ready to go! The application should launch in the simulator or on your device.

Take a look around, and get a feel for all you can do with cocos2dx-profile. Be sure to take a look in `Log Navigator` since some of the results are printed there (like `getFeed` and `getContacts`).

#### Scenes

This project contains a single main scene:
- **ProfileScreen**: contains a social interaction window, in which the user can login and then perform various social network actions.

#### Store Dependency

A good example of how to define an economy model can be found in [MuffinRushAssets](https://github.com/soomla/cocos2dx-profile-example/blob/master/Classes/MuffinRushAssets.cpp).

This economy model is defined only to provide a way of granting meaningful rewards. In case you have no need for virtual economy rewards, or you don't want to grant rewards, you are not obligated to create any virtual economy.


## Contribution

We want you!

Fork -> Clone -> Implement -> Insert Comments -> Test -> Pull-Request.

We have great RESPECT for contributors.

## Code Documentation

cocos2dx-profile follows strict code documentation conventions. If you would like to contribute please read our [Documentation Guidelines](https://github.com/soomla/cocos2dx-profile/blob/master/documentation.md) and follow them. Clear, consistent  comments will make our code easy to understand.


## SOOMLA, Elsewhere ...

+ [Website](http://soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376)
+ [On AngelList](https://angel.co/the-soomla-project)

## License

MIT License. Copyright (c) 2014 SOOMLA. http://project.soom.la
+ http://www.opensource.org/licenses/MIT
