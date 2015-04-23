/**
 * Created by vedi on 20/04/15.
 */
require('../lib/cocos2dx-env');

var
  chai = require('chai'),
  expect = chai.expect;

describe('Gate', function () {

beforeEach(function initWorldWithScore() {
  this.world = Soomla.Models.World.create({itemId: 'initial_world'});
  Soomla.soomlaLevelUp.initialize(this.world);
});

afterEach(function clearLocalStorage() {
  global.cc.sys.localStorage.clear();
});

  describe('#canStart', function () {
    it('returns false for closed gate', function () {
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var gate = Soomla.Models.ScheduleGate.create({itemID: 'unopened_gate', schedule: Soomla.Models.Schedule.createAnyTimeOnce()});
      var gateOnGateOpenedFired = false,
        gateOnGateOpened = function (eventGate) {
          gateOnGateOpenedFired = gateOnGateOpenedFired || (gate === eventGate);
        };
      Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_GATE_OPENED, gateOnGateOpened);

      initialWorld.gate = gate;

      gate.forceOpen(true);

      expect(gateOnGateOpenedFired).to.be.true;
      expect(initialWorld.canStart()).to.be.true;
    });
  });
});


