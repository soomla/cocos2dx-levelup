/**
 * Created by vedi on 20/04/15.
 */
module.exports = function () {
  global.window = global;
  global.cc = {
    sys: {
      os: 'testing',
      localStorage: require('localStorage')
    }
  };

  global._ = require('../../../../soomla-cocos2dx-core/js/lodash');
  require('../../../../soomla-cocos2dx-core/js/soomla-core');
  require('../../../../cocos2dx-store/js/soomla-store');
  require('../../../../cocos2dx-profile/js/soomla-profile');
  require('../../../../cocos2dx-levelup/js/soomla-levelup');
}();