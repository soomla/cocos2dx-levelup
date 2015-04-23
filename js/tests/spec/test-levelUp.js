/**
 * Created by vedi on 20/04/15.
 */
require('../lib/cocos2dx-env');

var
  chai = require('chai'),
  expect = chai.expect;

describe('LevelUp', function () {

  function initWorld(rewards) {
    this.world = Soomla.Models.World.create({itemId: 'initial_world'});
    Soomla.soomlaLevelUp.initialize(this.world, rewards);
  }

  afterEach(function clearLocalStorage() {
    global.cc.sys.localStorage.clear();
  });

  it('SanityInitializeNoRewards', function () {
    initWorld();
    var initialWorld = Soomla.soomlaLevelUp.initialWorld;

    expect(Soomla.soomlaLevelUp.getWorld(initialWorld.itemId)).to.be.equal(initialWorld);
  });

  it('SanityInitializeRewards', function () {

    var reward = Soomla.Models.BadgeReward.create({
      itemId: 'test_badge_reward',
      name: 'Test Badge Reward'
    });
    var secondReward = Soomla.Models.BadgeReward.create({
      itemId: 'rsecond_test_badge_reward',
      name: 'Second Test Badge Reward'
    });

    initWorld([reward, secondReward]);

    var initialWorld = Soomla.soomlaLevelUp.initialWorld;

    expect(Soomla.soomlaLevelUp.getWorld(initialWorld.itemId)).to.be.equal(initialWorld);
    expect(Soomla.soomlaLevelUp.getReward(reward.itemId)).to.be.equal(reward);
    expect(Soomla.soomlaLevelUp.getReward(secondReward.itemId)).to.be.equal(secondReward);
  });

  it('TestGetWorld', function () {
    initWorld();

    var initialWorld = Soomla.soomlaLevelUp.initialWorld;

    var level = Soomla.Models.Level.create({itemId: 'test_level'});
    var innerLevel = Soomla.Models.Level.create({itemId: 'test_inner_level'});
    level.addInnerWorld(innerLevel);

    initialWorld.addInnerWorld(level);


    expect(Soomla.soomlaLevelUp.getWorld(initialWorld.itemId)).to.be.equal(initialWorld);
    expect(Soomla.soomlaLevelUp.getWorld(level.itemId)).to.be.equal(level);
    expect(Soomla.soomlaLevelUp.getWorld(innerLevel.itemId)).to.be.equal(innerLevel);
  });

  it('TestGetLevel', function () {
    initWorld();

    var initialWorld = Soomla.soomlaLevelUp.initialWorld;

    var level = Soomla.Models.Level.create({itemId: 'test_level'});
    var innerLevel = Soomla.Models.Level.create({itemId: 'test_inner_level'});
    level.addInnerWorld(innerLevel);

    initialWorld.addInnerWorld(level);

    var innerWorld = Soomla.Models.World.create({itemId: 'test_world'});
    initialWorld.addInnerWorld(innerWorld);



    expect(Soomla.soomlaLevelUp.getWorld(initialWorld.itemId)).to.be.equal(initialWorld);
    expect(Soomla.soomlaLevelUp.getLevel(level.itemId)).to.be.equal(level);
    expect(Soomla.soomlaLevelUp.getLevel(innerLevel.itemId)).to.be.equal(innerLevel);
    expect(Soomla.soomlaLevelUp.getLevel(innerWorld.itemId)).to.be.null;
  });

  it('TestGetScore', function () {
    initWorld();

    var initialWorld = Soomla.soomlaLevelUp.initialWorld;

    var level = Soomla.Models.Level.create({itemId: 'test_level'});
    var score = Soomla.Models.Score.create({itemId: 'test_score'});
    var innerScore = Soomla.Models.Score.create({itemId: 'test_inner_score'});
    level.addScore(innerScore);
    initialWorld.addInnerWorld(level);
    initialWorld.addScore(score);

    expect(Soomla.soomlaLevelUp.getScore(score.itemId)).to.be.equal(score);
    expect(Soomla.soomlaLevelUp.getScore(innerScore.itemId)).to.be.equal(innerScore);
  });

  it('TestGetGate', function () {
    initWorld();

    var initialWorld = Soomla.soomlaLevelUp.initialWorld;

    var level = Soomla.Models.Level.create({itemId: 'test_level'});
    var gate = Soomla.Models.WorldCompletionGate.create({
      itemId: "test_level_complete_gate",
      associatedWorldId: level.itemId
    });
    var secondLevel = Soomla.Models.Level.create({itemId: 'test_second_level', gate: gate});

    initialWorld.addInnerWorld(level);
    initialWorld.addInnerWorld(secondLevel);

    expect(Soomla.soomlaLevelUp.getGate(gate.itemId)).to.be.equal(gate);
  });

  it('TestGetMission', function () {
    initWorld();

    var initialWorld = Soomla.soomlaLevelUp.initialWorld;

    var level = Soomla.Models.Level.create({itemId: 'test_level'});
    var mission = Soomla.Models.WorldCompletionMission.create({
      itemId: 'test_level_complete_gate',
      name: 'Test Complete Mission',
      associatedWorldId: level.itemId
    });
    var secondLevel = Soomla.Models.Level.create({itemId: 'test_second_level'});

    initialWorld.addInnerWorld(level);
    initialWorld.addInnerWorld(secondLevel);
    initialWorld.addMission(mission);

    expect(Soomla.soomlaLevelUp.getMission(mission.itemId)).to.be.equal(mission);
  });
});


