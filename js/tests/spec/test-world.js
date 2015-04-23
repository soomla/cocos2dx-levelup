/**
 * Created by vedi on 20/04/15.
 */
require('../lib/cocos2dx-env');

var
  _ = require('lodash'),
  chai = require('chai'),
  expect = chai.expect;

describe('World', function () {

  beforeEach(function initWorldWithScore() {
    this.world = Soomla.Models.World.create({itemId: 'initial_world'});
    Soomla.soomlaLevelUp.initialize(this.world);
  });

  afterEach(function clearLocalStorage() {
    global.cc.sys.localStorage.clear();
  });

  it('should have defaults set', function () {
    // given
    var initialWorld = Soomla.soomlaLevelUp.initialWorld;
    // then
    expect(initialWorld.isCompleted()).to.be.false;
  });

  describe('#canStart', function () {

    it('returns false for closed gate', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var gate = Soomla.Models.ScheduleGate.create({itemId: 'unopened_gate', schedule: Soomla.Models.Schedule.createAnyTimeOnce()});
      initialWorld.gate = gate;
      // then
      expect(initialWorld.canStart()).to.be.false;
    });

    it('returns true for open gate', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var gate = Soomla.Models.ScheduleGate.create({itemId: 'unopened_gate', schedule: Soomla.Models.Schedule.createAnyTimeOnce()});
      initialWorld.gate = gate;
      // when
      gate.forceOpen(true);
      // then
      expect(initialWorld.canStart()).to.be.true;
    });
  });

  describe('#addInnerWorld', function () {
    it('adds level to innerWorldsMap', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var level = Soomla.Models.Level.create({itemId: 'test_level'});
      // when
      initialWorld.addInnerWorld(level);
      // then
      var innerWorldsMap = initialWorld.innerWorldsMap;
      expect(initialWorld.isCompleted()).to.be.false;
      expect(_.keys(innerWorldsMap)).to.have.length(1);
      expect(innerWorldsMap).to.contain.key(level.itemId);
      expect(innerWorldsMap[level.itemId]).to.be.equal(level);
    });
  });

  describe('#addScore', function () {
    it('adds score to scores', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      // when
      initialWorld.addScore(score);
      // then
      var scores = initialWorld.scores;
      expect(_.keys(scores)).to.have.length(1);
      expect(scores).to.contain.key(score.itemId);
      expect(scores[score.itemId]).to.be.equal(score);
    });
  });

  describe('#getSingleScore', function () {
    it('returns first score, if there are scores', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      // when
      initialWorld.addScore(score);
      // then
      var singleScore = initialWorld.getSingleScore();
      expect(singleScore).to.be.equal(score);
    });
  });

  describe('#incSingleScore', function () {
    it('increases score value', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      initialWorld.addScore(score);
      // when
      initialWorld.incSingleScore(2.0);
      // then
      expect(score.tempScore).to.be.equal(2);
    });
  });

  describe('#resetScores', function () {
    it('cleans up tempScore', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      initialWorld.addScore(score);
      initialWorld.incSingleScore(2.0);
      // when
      initialWorld.resetScores();
      // then
      expect(score.tempScore).not.to.be.equal(2);
    });
    it('changes latest, if `save` is true', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      initialWorld.addScore(score);
      initialWorld.setSingleScoreValue(2.0);
      // when
      initialWorld.resetScores(true);
      // then
      expect(score.getLatest()).to.be.equal(2);
    });
    it('changes record and EVENT_SCORE_RECORD_CHANGED is fired, if record was hit, and `save` is true', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      initialWorld.addScore(score);
      initialWorld.incSingleScore(2.0);
      var scoreOnRecordChangedFired = false,
        scoreOnRecordChanged = function (eventScore) {
          scoreOnRecordChangedFired = scoreOnRecordChangedFired || (score === eventScore);
        };
      Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_SCORE_RECORD_CHANGED, scoreOnRecordChanged);
      // when
      initialWorld.resetScores(true);
      // then
      expect(initialWorld.getSingleScore().getRecord()).to.be.equal(2);
      expect(scoreOnRecordChangedFired).to.be.true;
    });
    it('changes latest, but not the record of singleScore, and EVENT_SCORE_RECORD_CHANGED is not fired, if record was not hit, and `save` is true', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      initialWorld.addScore(score);
      initialWorld.incSingleScore(2.0);
      initialWorld.resetScores(true);
      var scoreOnRecordChangedFired = false,
        scoreOnRecordChanged = function (eventScore) {
          scoreOnRecordChangedFired = scoreOnRecordChangedFired || (score === eventScore);
        };
      Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_SCORE_RECORD_CHANGED, scoreOnRecordChanged);
      // when
      initialWorld.incSingleScore(3.0);
      initialWorld.decSingleScore(2.0);
      initialWorld.resetScores(true);
      // then
      expect(initialWorld.getSingleScore().getRecord()).to.be.equal(2);
      expect(initialWorld.getSingleScore().getLatest()).to.be.equal(1);
      expect(scoreOnRecordChangedFired).to.be.false;
    });

  });

  describe('#setSingleScoreValue', function () {
    it('changes tempScore', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      initialWorld.addScore(score);
      // when
      initialWorld.setSingleScoreValue(2.0);
      // then
      expect(score.tempScore).to.be.equal(2);
    });
  });

  describe('#setCompleted', function () {
    it('changes completed state of the world and fires event', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var level = Soomla.Models.Level.create({itemId: 'test_level'});
      initialWorld.addInnerWorld(level);
      var initialWorldCompletedFired = false,
        initialWorldOnCompleted = function (world) {
          initialWorldCompletedFired = initialWorldCompletedFired || (world === initialWorld);
        };
      Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_WORLD_COMPLETED, initialWorldOnCompleted);
      // when
      initialWorld.setCompleted(true);
      // then
      expect(initialWorld.isCompleted()).to.be.true;
      expect(initialWorldCompletedFired).to.be.true;
    });

    it('does not change completed state of inner worlds and does not fire event, if `recursive` is not set', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var level = Soomla.Models.Level.create({itemId: 'test_level'});
      initialWorld.addInnerWorld(level);
      var innerWorldCompletedFired = false,
        initialWorldOnCompleted = function (world) {
          innerWorldCompletedFired = innerWorldCompletedFired || (world === level);
        };
      Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_WORLD_COMPLETED, initialWorldOnCompleted);
      // when
      initialWorld.setCompleted(true);
      // then
      expect(level.isCompleted(), 'level completed').to.be.false;
      expect(innerWorldCompletedFired).to.be.false;
    });

    it('changes completed state of inner worlds and fires event, if `recursive` is set', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var level = Soomla.Models.Level.create({itemId: 'test_level'});
      initialWorld.addInnerWorld(level);
      var innerWorldCompletedFired = false,
        initialWorldOnCompleted = function (world) {
          innerWorldCompletedFired = innerWorldCompletedFired || (world === level);
        };
      Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_WORLD_COMPLETED, initialWorldOnCompleted);
      // when
      initialWorld.setCompleted(true, true);
      // then
      expect(level.isCompleted(), 'level completed').to.be.true;
      expect(innerWorldCompletedFired).to.be.true;
    });
  });

  describe('#incSingleScore', function () {
    it('increments tempScore', function () {
      // given
      var initialWorld = Soomla.soomlaLevelUp.initialWorld;
      var score = Soomla.Models.Score.create({itemId: 'test_score'});
      initialWorld.addScore(score);
      // when
      initialWorld.incSingleScore(2.0);
      // then
      expect(initialWorld.getSingleScore().tempScore).to.be.equal(2);
    });
  });

  it('should allow to change multiple scores', function () {
    // given
    var initialWorld = Soomla.soomlaLevelUp.initialWorld;
    var score = Soomla.Models.Score.create({itemId: 'test_score'});
    initialWorld.addScore(score);
    var scoreRecord = 2.0;
    var secondScore = Soomla.Models.Score.create({itemId: 'test_score_2'});
    initialWorld.addScore(secondScore);
    var secondScoreRecord = 4.0;

    var
      scoreAffected = null,
      scoresAffected = [],
      scoreOnRecordChanged = function (eventScore) {
        if (!scoreAffected) {
          scoreAffected = eventScore;
        }
        scoresAffected.push(eventScore);
      };
    Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_SCORE_RECORD_CHANGED, scoreOnRecordChanged);

    // Check increasing one does not affect the other
    initialWorld.incScore(score.itemId, scoreRecord);

    expect(score.tempScore).to.be.equal(scoreRecord);
    expect(secondScore.tempScore).not.to.be.equal(scoreRecord);

    // Save score
    initialWorld.resetScores(true);

    // New record was broken in one score
    expect(score.getRecord()).to.be.equal(scoreRecord);
    expect(score.getLatest()).to.be.equal(scoreRecord);
    expect(scoreAffected).to.be.equal(score);

    // Clear to isolate next events
    scoreAffected = null;

    // Check increasing second does not affect the first
    initialWorld.incScore(secondScore.itemId, secondScoreRecord);

    expect(secondScore.tempScore).to.be.equal(secondScoreRecord);
    expect(score.tempScore).not.to.be.equal(secondScoreRecord);

    // Save score
    initialWorld.resetScores(true);
    // New record was broken in second score
    expect(secondScore.getRecord()).to.be.equal(secondScoreRecord);
    expect(secondScore.getLatest()).to.be.equal(secondScoreRecord);
    expect(scoreAffected).to.be.equal(secondScore);

    scoreAffected = null;
    scoresAffected = [];

    // Check breaking two scores in parallel
    var newScoreRecord = scoreRecord + 1.0;
    var newSecondScoreRecord = secondScoreRecord + 1.0;

    initialWorld.incScore(score.itemId, newScoreRecord);
    initialWorld.incScore(secondScore.itemId, newSecondScoreRecord);
    initialWorld.resetScores(true);

    expect(score.getRecord()).to.be.equal(newScoreRecord);
    expect(secondScore.getRecord()).to.be.equal(newSecondScoreRecord);
    expect(scoresAffected).contain(score);
    expect(scoresAffected).contain(secondScore);

    // Testing if getting the records table works

    var records = initialWorld.getRecordScores();
    var scoreRecordInner = records[score.itemId];
    var secondScoreRecordInner = records[secondScore.itemId];

    // Test if the records are correct
    expect(scoreRecordInner).to.be.equal(newScoreRecord);
    expect(secondScoreRecordInner).to.be.equal(newSecondScoreRecord);

    scoreAffected = null;
    scoresAffected = [];

    // Check applying new non-record scores

    var latestScore = 1.0;
    var latestSecondScore = 1.5;

    initialWorld.setScoreValue(score.itemId, latestScore);
    initialWorld.setScoreValue(secondScore.itemId, latestSecondScore);
    initialWorld.resetScores(true);

    // Test that the records remain and events were not sent
    expect(score.getRecord()).to.be.equal(newScoreRecord);
    expect(secondScore.getRecord()).to.be.equal(newSecondScoreRecord);
    expect(scoresAffected).to.be.empty;

    // Test the records table still with old records
    records = initialWorld.getRecordScores();
    scoreRecordInner = records[score.itemId];
    secondScoreRecordInner = records[secondScore.itemId];

    expect(scoreRecordInner).to.be.equal(newScoreRecord);
    expect(secondScoreRecordInner).to.be.equal(newSecondScoreRecord);

    // Check if the latest scores are the new lower scores
    var latest = initialWorld.getLatestScores();
    var scoreLatestInner = latest[score.itemId];
    var secondScoreLatestInner = latest[secondScore.itemId];

    expect(latestScore).to.be.equal(scoreLatestInner);
    expect(latestSecondScore).to.be.equal(secondScoreLatestInner);

  });

  it('should allow to add missions', function () {
    var initialWorld = Soomla.soomlaLevelUp.initialWorld;
    var score = Soomla.Models.Score.create({itemId: 'test_score'});
    initialWorld.addScore(score);

    var mission = Soomla.Models.RecordMission.create({
        itemId: 'test_record_mission',
        name: 'Test Record Mission',
        associatedScoreId: score.itemId,
        desiredRecord: 20.0
      });

    expect(mission.isCompleted()).to.be.false;
    expect(mission.isAvailable()).to.be.false;

    initialWorld.addMission(mission);

    var missions = initialWorld.missions;

    expect(missions).to.have.length(1);
    expect(missions).contains(mission);
  });

  it('should allow to work with missions', function () {
    var initialWorld = Soomla.soomlaLevelUp.initialWorld;
    var score = Soomla.Models.Score.create({itemId: 'test_score'});
    initialWorld.addScore(score);

    var reward = Soomla.Models.BadgeReward.create({itemId: 'test_badge_reward', name: 'Test Badge Reward'});

    var mission = Soomla.Models.RecordMission.create({
      itemId: 'test_record_mission',
      name: 'Test Record Mission',
      rewards: [reward],
      associatedScoreId: score.itemId,
      desiredRecord: 20.0
    });

    var
      missionOnGateOpenedFired = false,
      missionOnMissionCompletedFired = false,
      rewardOnRewardGivenFired = false,
      missionOnGateOpened = function (eventGate) {
        missionOnGateOpenedFired = missionOnGateOpenedFired || (mission.gate === eventGate);
      },
      missionOnMissionCompleted = function (eventMission) {
        missionOnMissionCompletedFired = missionOnMissionCompletedFired || (mission === eventMission);
      },
      rewardOnRewardGiven = function (eventReward) {
        rewardOnRewardGivenFired = rewardOnRewardGivenFired || (reward === eventReward);
      };

    Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_GATE_OPENED, missionOnGateOpened);
    Soomla.addEventHandler(Soomla.Models.LevelUpConsts.EVENT_MISSION_COMPLETED, missionOnMissionCompleted);
    Soomla.addEventHandler(Soomla.Models.CoreConsts.EVENT_REWARD_GIVEN, rewardOnRewardGiven);



    expect(mission.isCompleted()).to.be.false;
    expect(reward.isOwned()).to.be.false;

    initialWorld.addMission(mission);

    initialWorld.setSingleScoreValue(35.0);
    expect(mission.isCompleted()).to.be.false;
    initialWorld.resetScores(true);
    expect(mission.isCompleted()).to.be.true;

    expect(missionOnGateOpenedFired).to.be.true;
    expect(missionOnMissionCompletedFired).to.be.true;
    expect(rewardOnRewardGivenFired).to.be.true;

    expect(reward.isOwned()).to.be.true;

  });

  it('should assign rewards', function () {
    var
      initialWorld = Soomla.soomlaLevelUp.initialWorld,
      reward = Soomla.Models.BadgeReward.create({itemId: 'test_badge_reward', name: 'Test Badge Reward'}),
      rewardOnRewardGivenFired = false,
      rewardOnRewardGiven = function (eventReward) {
        rewardOnRewardGivenFired = rewardOnRewardGivenFired || (reward === eventReward);
      };

    Soomla.addEventHandler(Soomla.Models.CoreConsts.EVENT_REWARD_GIVEN, rewardOnRewardGiven);

    initialWorld.assignReward(reward);

    expect(rewardOnRewardGivenFired).to.be.true;
    expect(reward.isOwned()).to.be.true;
  });

  it('should replace rewards', function () {

    var
      reward = Soomla.Models.BadgeReward.create({itemId: 'test_badge_reward', name: 'Test Badge Reward'}),
      replaceReward = Soomla.Models.BadgeReward.create({itemId: 'replace_test_badge_reward', name: 'Replace Test Badge Reward'});

    // reinitialize it
    this.world = Soomla.Models.World.create({itemId: 'initial_world'});
    Soomla.soomlaLevelUp.initialize(this.world, [reward, replaceReward]);

    var
      initialWorld = Soomla.soomlaLevelUp.initialWorld,
      lastRewardOnRewardGivenFired = null,
      lastRewardOnRewardTakenFired = null,
      rewardOnRewardGiven = function (eventReward) {
        lastRewardOnRewardGivenFired = eventReward;
      },
      rewardOnRewardTaken = function (eventReward) {
        lastRewardOnRewardTakenFired = eventReward;
      };

    Soomla.addEventHandler(Soomla.Models.CoreConsts.EVENT_REWARD_GIVEN, rewardOnRewardGiven);
    Soomla.addEventHandler(Soomla.Models.CoreConsts.EVENT_REWARD_TAKEN, rewardOnRewardTaken);

    initialWorld.assignReward(reward);

    expect(lastRewardOnRewardGivenFired).to.be.equal(reward);
    expect(reward.isOwned()).to.be.true;

    initialWorld.assignReward(replaceReward);

    expect(lastRewardOnRewardTakenFired).to.be.equal(reward);
    expect(reward.isOwned()).to.be.false;

    expect(lastRewardOnRewardGivenFired).to.be.equal(replaceReward);
    expect(replaceReward.isOwned()).to.be.true;
  });

  describe('#batchAddLevelsWithTemplates', function () {
    it('should work with nulls', function () {
      var
        initialWorld = Soomla.soomlaLevelUp.initialWorld,
        levelCount = 5;


      initialWorld.batchAddLevelsWithTemplates(levelCount, null, null, null);
      var innerWolds = initialWorld.innerWorldsMap;

      _.forEach(innerWolds, function (level) {
        expect(_.isEmpty(level.innerWorldsMap)).to.be.true;
        expect(level.gate).to.be.null;
        expect(level.missions).to.have.length(0);
        expect(_.isEmpty(level.scores)).to.be.true;
      });

      expect(_.keys(innerWolds)).to.have.length(levelCount);

    });

    it('should work with not nulls', function () {
      var
        initialWorld = Soomla.soomlaLevelUp.initialWorld,
        levelCount = 5;

      var testScore = Soomla.Models.Score.create({itemId: 'test_score'});
      var testMission = Soomla.Models.RecordMission.create({
        itemId: 'test_record_mission',
        name: 'Test Record Mission',
        associatedScoreId: testScore.itemId,
        desiredRecord: 20.0
      });
      var testGate = Soomla.Models.ScheduleGate.create({
        itemId: 'unopened_gate',
        schedule: Soomla.Models.Schedule.createAnyTimeOnce()}
      );


      initialWorld.batchAddLevelsWithTemplates(levelCount, testGate, testScore, testMission);
      var innerWolds = initialWorld.innerWorldsMap;

      _.forEach(innerWolds, function (level) {

        expect(_.isEmpty(level.innerWorldsMap)).to.be.true;

        expect(level.gate).not.to.be.null;
        expect(level.gate.className).to.be.equal(testGate.className);
        expect(level.gate.itemId).not.to.be.equal(testGate.itemId);
        expect(level.gate.isOpen()).to.be.equal(testGate.isOpen());

        expect(level.missions).to.have.length(1);

        _.forEach(level.missions, function (mission) {
          expect(mission.className).to.be.equal(testMission.className);
          expect(mission.itemId).not.to.be.equal(testMission.itemId);
        });


        expect(_.keys(level.scores)).to.have.length(1);

        _.forEach(level.scores, function (score) {
          expect(score.className).to.be.equal(testScore.className);
          expect(score.itemId).not.to.be.equal(testScore.itemId);
        });

      });

      expect(_.keys(innerWolds)).to.have.length(levelCount);

    });
  });

  describe('#batchAddDependentLevelsWithTemplates', function () {
    it('should work', function () {
      var
        initialWorld = Soomla.soomlaLevelUp.initialWorld,
        levelCount = 5;


      initialWorld.batchAddDependentLevelsWithTemplates(levelCount, null, null);
      var innerWolds = initialWorld.innerWorldsMap;

      var n = 0;
      _.forEach(innerWolds, function (level) {
        expect(_.isEmpty(level.innerWorldsMap)).to.be.true;
        expect(level.missions).to.have.length(0);
        expect(_.isEmpty(level.scores)).to.be.true;
        if (n === 0) {
          expect(level.canStart()).to.be.true;
        } else {
          expect(level.canStart()).to.be.false;
        }
        n++;
      });

      var
        prevLevel = undefined;

      _.forEach(innerWolds, function (level) {
        if (prevLevel) {
          prevLevel.setCompleted(true);
          expect(level.canStart()).to.be.true;
        }

        prevLevel = level;
      });

      expect(_.keys(innerWolds)).to.have.length(levelCount);
    });
  });

});
