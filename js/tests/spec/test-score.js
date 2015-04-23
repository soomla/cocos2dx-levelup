/**
 * Created by vedi on 20/04/15.
 */
require('../lib/cocos2dx-env');

var
  chai = require('chai'),
  expect = chai.expect,
  scoreId = 'testScore';

describe('Score', function () {

  beforeEach(function initWorldWithScore() {
    this.world = Soomla.Models.World.create({itemId: 'initial_world'});
    this.world.addScore(Soomla.Models.Score.create({itemId: scoreId}));
    Soomla.soomlaLevelUp.initialize(this.world);
  });

  afterEach(function clearLocalStorage() {
    global.cc.sys.localStorage.clear();
  });

  it('should have defaults set', function () {
    var score = Soomla.soomlaLevelUp.getScore(scoreId);

    expect(score.startValue).equal(0);
    expect(score.getRecord()).equal(-1);
    expect(score.higherBetter).to.be.true;
  });

  it('can be incremented', function () {
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    // when
    score.inc(10);
    // then
    expect(score.tempScore).equal(10);
    expect(score.hasTempReached(10)).to.be.true;
  });

  it('can be decremented', function () {
    // given
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    score.tempScore = 10;
    // when
    score.dec(5);
    // then
    expect(score.tempScore).equal(5);
    expect(score.hasTempReached(5)).to.be.true;
  });

  it('can be reset to their start values', function () {
    // given
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    var startValue = score.startValue;
    // when
    score.inc(10);
    score.reset(false);
    // then
    expect(score.startValue).equal(startValue);
  });

  it('changes the record, if it was reset with saving', function () {
    // given
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    // then
    score.inc(10);
    score.reset(true);
    // then
    expect(score.getRecord()).equal(10);
  });

  it('does not changes the latest score and record, if it was reset without saving', function () {
    // given
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    score.inc(10);
    score.reset(true);
    // when
    score.inc(15);
    score.reset(false);
    // then
    expect(score.getLatest()).equal(10);
    expect(score.getRecord()).equal(10);
  });

  it('changes record, if an user gets more scores', function () {
    // given
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    score.tempValue = 10;
    score.reset(true);
    // when
    score.inc(15);
    score.reset(true);
    // then
    expect(score.getRecord()).equal(15);
  });

  it('does not change record, if an user does not get more scores', function () {
    // given
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    score.inc(15);
    score.reset(true);
    // when
    score.inc(10);
    score.reset(true);
    // then
    expect(score.getRecord()).equal(15);
  });

  it('changes the latest score regardless getting the record', function () {
    // given
    var score = Soomla.soomlaLevelUp.getScore(scoreId);
    score.tempValue = 15;
    score.reset(true);
    // when
    score.inc(10);
    score.reset(true);
    // then
    expect(score.getLatest()).equal(10);
  });

  describe('#hasTempReached', function () {
    it('returns true for reached values only', function () {
      // given
      var score = Soomla.soomlaLevelUp.getScore(scoreId);
      // when
      score.inc(10);
      // then
      expect(score.hasTempReached(5)).to.be.true;
      expect(score.hasTempReached(10)).to.be.true;
      expect(score.hasTempReached(15)).to.be.false;
    });
  });

  describe('#hasRecordReached', function () {
    it('returns false, if user increments without resetting the score', function () {
      // given
      var score = Soomla.soomlaLevelUp.getScore(scoreId);
      // when
      score.inc(10);
      // then
      expect(score.hasRecordReached(5)).to.be.false;
    });

    it('returns false, if user increments without resetting the score', function () {
      // given
      var score = Soomla.soomlaLevelUp.getScore(scoreId);
      // when
      score.inc(10);
      score.reset(true);
      // then
      expect(score.hasRecordReached(5)).to.be.true;
      expect(score.hasRecordReached(10)).to.be.true;
      expect(score.hasRecordReached(15)).to.be.false;
    });
  });
});

