/**
 * Created by vedi on 09/04/15.
 */

(function () {

  /**
   * LevelUpConsts
   */
  var LevelUpConsts = Soomla.Models.LevelUpConsts = {
    EVENT_LEVEL_UP_INITIALIZED: 'CCLevelUpEventHandler::onLevelUpInitialized',
    EVENT_SCORE_RECORD_CHANGED: 'CCLevelUpEventHandler::onScoreRecordChanged',
    EVENT_SCORE_RECORD_REACHED: 'CCLevelUpEventHandler::onScoreRecordReached',
    EVENT_LATEST_SCORE_CHANGED: 'CCLevelUpEventHandler::onLatestScoreChanged',
    EVENT_GATE_OPENED: 'CCLevelUpEventHandler::onGateOpened',
    EVENT_GATE_CLOSED: 'CCLevelUpEventHandler::onGateClosed',
    EVENT_MISSION_COMPLETED: 'CCLevelUpEventHandler::onMissionCompleted',
    EVENT_MISSION_COMPLETION_REVOKED: 'CCLevelUpEventHandler::onMissionCompletionRevoked',
    EVENT_WORLD_COMPLETED: 'CCLevelUpEventHandler::onWorldCompleted',
    EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED: 'CCLevelUpEventHandler::onLastCompletedInnerWorldChanged',
    EVENT_WORLD_REWARD_ASSIGNED: 'CCLevelUpEventHandler::onWorldRewardAssigned',
    EVENT_LEVEL_STARTED: 'CCLevelUpEventHandler::onLevelStarted',
    EVENT_LEVEL_ENDED: 'CCLevelUpEventHandler::onLevelEnded'
  };

  // Gates

  var Gate = Soomla.Models.Gate = function () {
    return Soomla.declareClass('Gate', {

      eventsRegistered: false,

      /**
       Attempts to open this `Gate`, if it has not been opened aready.
       */
      open: function open() {
        //  check in gate storage if it's already open
        if (Soomla.gateStorage.isOpen(this)) {
          return true;
        }
        return this.openInner();
      },

      /**
       Sets the `Gate` to open without checking if the `Gate` meets its criteria.
       @param open If set to `true` open the `Gate`.
       */
      forceOpen: function forceOpen(open) {
        if (this.isOpen() == open) {
          // if it's already open why open it again?
          return;
        }

        Soomla.gateStorage.setOpen(this, open);
        if (open) {
          this.unregisterEvents();
        } else {
          // we can do this here ONLY because we check 'isOpen == open' a few lines above.
          this.registerEvents();
        }
      },

      /**
       Determines whether this `Gate` is open.
       @return If this `Gate` is open returns `true`; otherwise, `false`.
       */
      isOpen: function isOpen() {
        return Soomla.gateStorage.isOpen(this);
      },

      /**
       Checks if this `Gate` meets its criteria for opening.
       @return Boolean If this `Gate` can be opened returns `true`; otherwise, `false`.
       */
      canOpen: function canOpen() {
        // check in gate storage if the gate is open
        if (Soomla.gateStorage.isOpen(this)) {
          return false;
        }

        return this.canOpenInner();
      },

      //***** INTERNAL *****//
      onAttached: function onAttached() {
        if (this.eventsRegistered) {
          return;
        }

        this.registerEvents();
        this.eventsRegistered = true;
      },
      onDetached: function onDetached() {
        if (!this.eventsRegistered) {
          return;
        }

        this.unregisterEvents();
        this.eventsRegistered = false;
      },

      //protected:

      /**
       Registers relevant events. Each specific type of `Gate` must implement
       this method.
       */
      registerEvents: function registerEvents() {
        Soomla.logError('IMPLEMENT ME!');
      },

      /**
       Unregisters relevant events. Each specific type of `Gate` must
       implement this method.
       */
      unregisterEvents: function unregisterEvents() {
        Soomla.logError('IMPLEMENT ME!');
      },

      /**
       Checks if this `Gate` meets its criteria for opening.
       Each specific type of `Gate` must implement this method to add
       specific `Gate` criteria.
       @return If the criteria is met for opening this `Gate` returns `true`;
       otherwise `false`.
       */
      canOpenInner: function canOpenInner() {
        Soomla.logError('IMPLEMENT ME!');
      },

      /**
       Opens this `Gate`.
       @return If this `Gate` was opened returns `true`; otherwise `false`.
       */
      openInner: function openInner() {
        Soomla.logError('IMPLEMENT ME!');
      }
    }, Soomla.Models.SoomlaEntity);
  }();

  var GatesList = Soomla.Models.GatesList = function () {
    var GatesList = Soomla.declareClass('GatesList', {
      eventListener: null,
      _gates: [],

      /**
       Retrieves the number of gates in this `Gateslist`.
       */
      count: function count() {
        return this._gates.length;
      },

      /**
       Adds the given gate to this gateslist.
       @param gate Gate to add.
       */
      add: function add(gate) {
        if (!gate) {
          return;
        }

        gate.onAttached();
        this._gates.push(gate);
      },

      /**
       Removes the given gate from this gateslist.
       @param gate Gate to remove.
       */
      remove: function remove(gate) {
        if (!gate) {
          return;
        }

        gate.onDetached();
        _.pull(this._gates, gate);
      },

      //protected:

      /**
       Opens this gateslist if it can be opened (its criteria has been met).
       @return boolean If the gate has been opened returns `true`; otherwise `false`.
       */
      openInner: function openInner() {
        if (this.canOpen()) {
          // There's nothing to do here... If CanOpen returns true it means that the gates list meets the condition for being opened.
          this.forceOpen(true);
          return true;
        }

        return false;
      },

      /**
       Registers relevant events: gate-opened event.
       */
      registerEvents: function registerEvents() {
        if (!this.isOpen()) {
          Soomla.addEventHandler(LevelUpConsts.EVENT_GATE_OPENED, this.onGateOpened, this);
        }
      },

      /**
       Unregisters relevant events: gate-opened event.
       */
      unregisterEvents: function unregisterEvents() {
        if (this.eventListener) {
          Soomla.removeEventHandler(LevelUpConsts.EVENT_GATE_OPENED, this.onGateOpened);
          this.eventListener = null;
        }
      },

      onGateOpened: function onGateOpened(gate) {
        if (!gate) {
          Soomla.logError('No gate data in event');
          return;
        }

        if (this._gates.indexOf(gate) >= 0) {
          if (this.canOpen()) {
            this.forceOpen(true);
          }
        }
      }

    }, Gate);
    Object.defineProperty(GatesList.prototype, 'gates', {
      get: function () {
        return this._gates;
      },
      set: function (gates) {
        gates = gates || [];
        _.invoke(this._gates, 'onDetached');
        this._gates = gates;
        _.invoke(this._gates, 'onAttached');
      }
    });
  }();

  var GatesListAnd = Soomla.Models.GatesListAnd = function () {
    /**
     @class `CCGatesListAnd`
     @brief A specific type of `GatesList` that can be opened only if ALL
     `Gate`s in its list are open.
     */
    var GatesListAnd = Soomla.declareClass('GatesListAnd', {
      /**
       Checks if this `GatesList` meets its criteria for opening, by checking
       that ALL `Gate`s in the list are open.
       @return If ALL `Gate`s in this `GatesList` are open returns `true`;
       otherwise `false`.
       */
      canOpenInner: function canOpenInner() {
        _.all(this._gates, function (gate) {
          return gate.isOpen();
        });
      }
    }, GatesList);
    return GatesListAnd;
  }();

  var GatesListOr = Soomla.Models.GatesListOr = function () {
    /**
     A specific type of `GatesList` that can be opened if AT LEAST ONE `Gate`
     in its list is open.
     */
    var GatesListOr = Soomla.declareClass('GatesListOr', {
      /**
       Checks if this `GatesList` meets its criteria for opening, by checking
       that AT LEAST ONE `Gate` in the list are open.
       @return If AT LEAST ONE `Gate` in this `GatesList` is open returns
       `true`; otherwise `false`.
       */
      canOpenInner: function canOpenInner() {
        _.any(this._gates, function (gate) {
          return gate.isOpen();
        });
      }
    }, GatesList);
    return GatesListOr;
  }();

  var RecordGate = Soomla.Models.RecordGate = function () {

    /**
     A specific type of `Gate` that has an associated score and a desired
     record. The `Gate` opens once the player achieves the desired record for
     the given score.
     */
    var RecordGate = Soomla.declareClass('Gate', {
      associatedScoreId: null,
      desiredRecord: null,
      eventListener: false,

      /**
       Checks if this `Gate` meets its criteria for opening, by checking if
       this `Gate`'s associated `Score` has reached the desired record.
       @return Boolean If the `Gate` can be opened returns `true`; otherwise `false`.
       */
      canOpenInner: function canOpenInner() {
        var score = Soomla.soomlaLevelUp.getScore(this.associatedScoreId);
        if (!score) {
          Soomla.logError('(canOpenInner) couldn\'t find score with scoreId: ', this.associatedScoreId);
          return false;
        }

        return score.hasRecordReached(this.desiredRecord);
      },

      /**
       Opens this `Gate` if it can be opened (its criteria has been met).
       @return boolean Upon success of opening returns `true`; otherwise `false`.
       */
      openInner: function openInner() {
        if (this.canOpen()) {
          // There's nothing to do here... If the DesiredRecord was reached then the gate is just open.
          this.forceOpen(true);
          return true;
        }

        return false;
      },

      /**
       Registers relevant events: score-record changed event.
       */
      registerEvents: function registerEvents() {
        if (!this.isOpen()) {
          Soomla.addEventHandler(LevelUpConsts.EVENT_SCORE_RECORD_CHANGED, this.onScoreRecordChanged, this);
          this.eventListener = true;
        }
      },

      /**
       Unregisters relevant events: score-record changed event.
       */
      unregisterEvents: function unregisterEvents() {
        if (this.eventListener) {
          Soomla.removeEventHandler(LevelUpConsts.EVENT_SCORE_RECORD_CHANGED, this.onScoreRecordChanged);
          this.eventListener = false;
        }
      },

      /**
       Opens this `Gate` if the score-record-changed event causes the `Gate`'s
       criteria to be met.
       */
      onScoreRecordChanged: function onScoreRecordChanged(score) {
        if (score.itemId === this.associatedScoreId &&
          score.hasRecordReached(this.desiredRecord)) {

          // We were thinking what will happen if the score's record will be broken over and over again.
          // It might have made this function being called over and over again.
          // It won't be called b/c ForceOpen(true) calls 'unregisterEvents' inside.
          this.forceOpen(true);
        }
      }

    }, Gate);

    return RecordGate;
  }();

  var ScheduleGate = Soomla.Models.ScheduleGate = function () {
    /**
     A specific type of `Gate` that has a schedule that defines when the `Gate`
     can be opened. The `Gate` opens once the player tries to open it in the
     time frame of the defined schedule.
     */
    var ScheduleGate = Soomla.declareClass('ScheduleGate', {
      schedule: null,

      /**
       Registers relevant events: In this case there are none.
       */
      registerEvents: function () {
        // Not listening to any events
      },

      /**
       Unregisters relevant events: In this case there are none.
       */
      unregisterEvents: function () {
        // Not listening to any events
      },

      /**
       Checks if this `Gate` meets its criteria for opening.
       @return If this `Gate` can be opened returns `true`; otherwise `false`.
       */
      canOpenInner: function () {
        // gates don't have activation times. they can only be activated once.
        // We kind of ignoring the activation limit of Schedule here.
        return this.schedule.approve(Soomla.gateStorage.isOpen(this) ? 1 : 0);
      },

      /**
       Opens this `Gate` if it can be opened (its criteria has been met).
       @return boolean Upon success of opening returns `true`; otherwise `false`.
       */
      openInner: function () {
        if (this.canOpen()) {
          // There's nothing to do here... If the DesiredRecord was reached then the gate is just open.
          this.forceOpen(true);
          return true;
        }

        return false;
      }
    }, Gate);

    return ScheduleGate;
  }();

  var WorldCompletionGate = Soomla.Models.WorldCompletionGate = function () {
    /**
     A specific type of `Gate` that has an associated world. The `Gate` opens
     once the `World` has been completed.
     */
    var WorldCompletionGate = Soomla.declareClass('WorldCompletionGate', {
      associatedWorldId: null,
      eventListener: false,

      /**
       Registers relevant events: world-completed event.
       */
      registerEvents: function () {
        if (!this.isOpen()) {
          Soomla.addEventHandler(LevelUpConsts.EVENT_WORLD_COMPLETED, this.onWorldCompleted, this);
          this.eventListener = true;
        }
      },

      /**
       Unregisters relevant events: world-completed event.
       */
      unregisterEvents: function () {
        if (!this.isOpen()) {
          Soomla.removeEventHandler(LevelUpConsts.EVENT_WORLD_COMPLETED, this.onWorldCompleted);
          this.eventListener = true;
        }
      },

      /**
       Checks if this `Gate` meets its criteria for opening, by checking that
       the associated world is not null and has been completed.
       @return If this `World` can be opened returns `true`; otherwise `false`.
       */
      canOpenInner: function () {
        var world = Soomla.soomlaLevelUp.getWorld(this.associatedWorldId);
        return world && world.isCompleted();
      },

      /**
       Opens this `Gate` if it can be opened (its criteria has been met).
       @return boolean Upon success of opening returns `true`; otherwise `false`.
       */
      openInner: function () {
        if (this.canOpen()) {
          this.forceOpen(true);
          return true;
        }

        return false;
      },

      onWorldCompleted: function (world) {
        if (!world) {
          Soomla.logError('No world data in event');
          return;
        }

        if (world.itemId === this.associatedWorldId) {
          this.forceOpen(true);
        }
      }
    }, Gate);
    return WorldCompletionGate;
  }();

  // Profile Gates

  var SocialActionGate = Soomla.Models.SocialActionGate = function () {
    /**
     NOTE: Social `Gate`s require the user to perform a specific social
     action in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     This is an abstract class that all social `Gate`s must implement.
     */
    var SocialActionGate = Soomla.declareClass('SocialActionGate', {
      provider: Soomla.Models.Provider.FACEBOOK,
      eventListener: false,

      /**
       Checks if this `Gate` meets its criteria for opening.
       @return boolean Always `true`.
       */
      canOpenInner: function () {
        return true;
      },

      /**
       Registers relevant events: social-action-finished event.
       */
      registerEvents: function () {
        if (!this.isOpen()) {
          Soomla.addEventHandler(Soomla.ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED, this.onSocialActionFinishedEvent, this);
          this.eventListener = true;
        }
      },

      /**
       Unregisters relevant events: social-action-finished event.
       */
      unregisterEvents: function () {
        if (!this.isOpen()) {
          Soomla.removeEventHandler(Soomla.ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED, this.onSocialActionFinishedEvent);
          this.eventListener = true;
        }
      },

      onSocialActionFinishedEvent: function (payload) {
        if (payload === this.itemId) {
          this.forceOpen(true);
        }
      }
    }, Gate);
    return SocialActionGate;
  }();

  var SocialLikeGate = Soomla.Models.SocialLikeGate = function () {
    /**
     NOTE: Social `Gate`s require the user to perform a specific social action
     in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     A specific type of `Gate` that has an associated page name.
     The `Gate` opens once the player 'Likes' the associated page.
     */
    var SocialLikeGate = Soomla.declareClass('SocialLikeGate', {
      pageName: null,

      /**
       Opens this `Gate` by 'liking' the associated page.
       @return Boolean If the page was successfully 'liked' returns `true`; otherwise
       `false`.
       */
      openInner: function openInner() {
        if (this.canOpen()) {
          Soomla.soomlaProfile.like(this.provider, this.pageName);
          return true;
        }

        return false;
      }
    }, SocialActionGate);
    return SocialLikeGate;
  }();

  var SocialStatusGate = Soomla.Models.SocialStatusGate = function () {
    /**
     NOTE: Social `Gate`s require the user to perform a specific social
     action in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     A specific type of `Gate` that has an associated status. The `Gate`
     is opened once the player posts the status.
     */
    var SocialStatusGate = Soomla.declareClass('SocialStatusGate', {
      status: null,

      /**
       Opens this `Gate` by posting the associated status.
       @return Boolean If the status was successfully posted returns `true`;
       otherwise `false`.
       */
      openInner: function openInner() {
        if (this.canOpen()) {
          Soomla.soomlaProfile.updateStatus(this.provider, this.itemId, this.status);
          return true;
        }
        return false;
      }
    }, SocialActionGate);
    return SocialStatusGate;
  }();

  var SocialStoryGate = Soomla.Models.SocialStoryGate = function () {
    /**
     NOTE: Social `Gate`s require the user to perform a specific social action
     in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     A specific type of `Gate` that has an associated story. The `Gate`
     is opened once the player posts the story.
     */
    var SocialStoryGate = Soomla.declareClass('SocialStoryGate', {
      message: null,
      storyName: null,
      caption: null,
      link: null,
      imgUrl: null,

      /**
       Opens this `Gate` by posting the associated story.
       @return If the story was successfully posted returns `true`;
       otherwise `false`.
       */
      openInner: function openInner() {
        Soomla.soomlaProfile.updateStory(this.provider,this.message, this.storyName, this.caption, '',
          this.link, this.itemId, this.imgUrl);
      }
    }, SocialActionGate);
    return SocialStoryGate;
  }();

  var SocialUploadGate = Soomla.Models.SocialUploadGate = function () {
    /**
     NOTE: Social `Gate`s require the user to perform a specific social
     action in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     A specific type of `Gate` that has an associated image. The `Gate`
     is opened once the player uploads the image.
     */
    var SocialUploadGate = Soomla.declareClass('SocialUploadGate', {
      message: null,
      fileName: null,

      /**
       Opens this `Gate` by uploading the associated image.
       @return boolean If the image was successfully uploaded returns `true`;
       otherwise `false`.
       */
      openInner: function openInner() {
        if (this.canOpen()) {
          Soomla.soomlaProfile.uploadImage(this.provider, this.itemId, this.message, this.fileName);
          return true;
        }
        return false;
      }
    }, SocialActionGate);

    return SocialUploadGate;
  }();

  var BalanceGate = Soomla.Models.BalanceGate = function () {

    /**
     A specific type of `Gate` that has an associated virtual item and a desired
     balance. The `Gate` opens once the item's balance reaches the desired
     balance.
     */
    var BalanceGate = Soomla.declareClass('BalanceGate', {
      associatedItemId: null,
      desiredBalance: null,
      currencyBalanceChangedListener: false,
      goodBalanceChangedListener: false,

      /**
       Checks if this `Gate` meets its criteria for opening, by checking if
       the item's balance has reached the desired balance.
       @return Boolean If the `Gate` meets the criteria to be opened returns `true`;
       otherwise `false`.
       */
      canOpenInner: function () {
        var balance = Soomla.storeInventory.getItemBalance(this.associatedItemId);
        if (error) {
          Soomla.logError('(canOpenInner) Couldn\'t find itemId. itemId: ' + this.associatedItemId);
          Soomla.logError(error.info);
          return false;
        }
        return (balance >= this.desiredBalance);
      },

      /**
       Opens the `Gate` if the criteria has been met.
       @return Boolean If the `Gate` is opened returns `true`; otherwise `false`.
       */
      openInner: function () {
        if (this.canOpen()) {
          // There's nothing to do here... If the DesiredBalance was reached then the gate is just open.
          this.forceOpen(true);
          return true;
        }

        return false;
      },

      /**
       Registers relevant events: currency-balance and good-balance changed
       events.
       */
      registerEvents: function () {
        if (!this.isOpen()) {
          Soomla.addEventHandler(Soomla.StoreConsts.EVENT_CURRENCY_BALANCE_CHANGED, this.onCurrencyBalanceChanged, this);
          this.currencyBalanceChangedListener = true;

          Soomla.addEventHandler(Soomla.StoreConsts.EVENT_GOOD_BALANCE_CHANGED, this.onGoodBalanceChanged, this);
          this.goodBalanceChangedListener = true;
        }
      },

      /**
       Unregisters relevant events: currency-balance and good-balance changed
       events.
       */
      unregisterEvents: function () {
        if (this.currencyBalanceChangedListener) {
          Soomla.removeEventHandler(Soomla.StoreConsts.EVENT_CURRENCY_BALANCE_CHANGED, this.onCurrencyBalanceChanged);
          this.currencyBalanceChangedListener = false;
        }

        if (this.goodBalanceChangedListener) {
          Soomla.removeEventHandler(Soomla.StoreConsts.EVENT_GOOD_BALANCE_CHANGED, this.onGoodBalanceChanged);
          this.goodBalanceChangedListener = false;
        }
      },

      /**
       Opens this `Gate` if the currency-balance changed event causes the `Gate`'s
       criteria to be met.
       */
      onCurrencyBalanceChanged: function (virtualCurrency, balance) {
        this.checkItemIdBalance(virtualCurrency.itemId, balance);
      },

      /**
       Opens this `Gate` if the good-balance changed event causes the `Gate`'s
       criteria to be met.
       */
      onGoodBalanceChanged: function (virtualGood, balance) {
        this.checkItemIdBalance(virtualGood.itemId, balance);
      },

      // private:
      checkItemIdBalance: function checkItemIdBalance(itemId, balance) {
        if (this.associatedItemId === itemId && balance >= this.desiredBalance) {
          this.forceOpen(true);
        }
      }
    }, Gate);

    return BalanceGate;
  }();

  var PurchasableGate = Soomla.Models.PurchasableGate = function () {
    /**
     A specific type of `Gate` that has an associated virtual item. The `Gate`
     opens once the item has been purchased.
     */
    var PurchasableGate = Soomla.declareClass('PurchasableGate', {
      associatedItemId: null,
      eventListener: false,

      /**
       Registers relevant events: item-purchased event.
       */
      registerEvents: function () {
        if (!this.isOpen()) {
          Soomla.addEventHandler(Soomla.StoreConsts.EVENT_ITEM_PURCHASED, this.onItemPurchased, this);
          this.eventListener = true;
        }
      },

      /**
       Unregisters relevant events: item-purchased event.
       */
      unregisterEvents: function () {
        if (this.eventListener) {
          Soomla.removeEventHandler(Soomla.StoreConsts.EVENT_ITEM_PURCHASED, this.onItemPurchased);
          this.eventListener = false;
        }
      },

      /**
       Checks if this `Gate` meets its criteria for opening.
       @return Boolean Always `true`.
       */
      canOpenInner: function () {
        return true;
      },

      /**
       Opens this `Gate` by buying its associated item.
       @return Boolean If purchase was successfully made returns `true`; otherwise
       `false`.
       */
      openInner: function () {
        Soomla.storeInventory.buyItem(this.associatedItemId, this.itemId);
        return true;
      },

      onItemPurchased: function (purchasableVirtualItem, payload) {
        if (purchasableVirtualItem.itemId === this.associatedItemId && payload === this.itemId) {
          this.forceOpen(true)
        }
      }
    }, Gate);
    return PurchasableGate;
  }();

  var Score = Soomla.Models.Score = function () {
    /**
     Represents a score in the game. A simple game usually has one generic
     numeric score which grows as the user progresses in the game. A game can
     also have multiple scores for different aspects such as time, speed,
     points etc. A `Score` can be ascending in nature such as regular points
     (higher is better) or can be descending such as time-to-complete level
     (lower is better).
     */
    var Score = Soomla.declareClass('Score', {
      startValue: 0.0,
      higherBetter: true,

      //protected:
      tempScore: 0,

      //private:
      scoreRecordReachedSent: false,

      /**
       Increases this `Score` by the given amount.
       @param amount Amount to increase by.
       */
      inc: function (amount) {
        this.setTempScore(this.tempScore + amount)
      },

      /**
       Decreases this `Score` by the given amount.
       @param amount Amount to decrease by.
       */
      dec: function (amount) {
        this.setTempScore(this.tempScore - amount)
      },

      /**
       Saves the current `Score` (and record if reached) and resets the score
       to its initial value. Use this method for example when a user restarts
       a level with a fresh score of 0.
       @param save If set to `true` save.
       */
      reset: function (save) {
        if (save) {
          Soomla.scoreStorage.setLatestScore(this, this.tempScore);

          var record = Soomla.scoreStorage.getRecordScore(this);
          if ((record == -1) || this.hasTempReached(record)) {
            Soomla.scoreStorage.setRecordScore(this, this.tempScore);
            this.scoreRecordReachedSent = false;
          }

          this.performSaveActions();
        }

        this.setTempScore(this.startValue);
      },

      /**
       Checks if the `Score` in the current game session has reached the given
       value.
       @return If this `Score` has reached the given scoreVal returns `true`;
       otherwise `false`.
       @param scoreVal numeric score value.
       */
      hasTempReached: function (scoreVal) {
        return this.hasScoreReached(this.tempScore, scoreVal);
      },

      /**
       Determines if this `Score` has reached a record value of the given
       `scoreVal`.
       @param scoreVal numeric score value.
       @return Boolean If this score has reached the given record returns `true`;
       otherwise `false`.
       */
      hasRecordReached: function (scoreVal) {
        var record = Soomla.scoreStorage.getRecordScore(this);
        return this.hasScoreReached(record, scoreVal);
      },

      /**
       Sets the temp score to be the given `score`, and checks if the given
       `score` breaks a record - if so, triggers the score-record-reached
       event.
       @param score Score to compare to temp score.
       @param onlyIfBetter set score only if the given value is better then the existing one
       */
      setTempScore: function (score, onlyIfBetter) {
        onlyIfBetter = onlyIfBetter || !_.isUndefined(onlyIfBetter)


        if (onlyIfBetter && !this.hasScoreReached(score, this.tempScore)) {
          return;
        }
        if (!this.scoreRecordReachedSent && this.hasScoreReached(score, this.tempScore)) {
          Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_SCORE_RECORD_REACHED, [this]);
          this.scoreRecordReachedSent = true;
        }
        this.tempScore = score;
      },

      /**
       Retrieves the record of this `Score`.
       @return The record.
       */
      getRecord: function () {
        return Soomla.scoreStorage.getRecordScore(this);
      },

      /**
       Retrieves the most recently saved value of this `Score`.
       @return The latest score.
       */
      getLatest: function () {
        return Soomla.scoreStorage.getLatestScore(this);
      },

      //protected:

      /**
       `Score` can sometimes have additional actions associated with
       reaching/saving it. Override this method to add specific `Score`
       behavior.
       */
      performSaveActions: function () {
        // empty
      },

      //private:
      hasScoreReached: function (score1, score2) {
        return this.higherBetter ?
          (score1 >= score2) :
          (score1 <= score2);
      }

    }, Soomla.Models.SoomlaEntity);

    return Score;
  }();

  var RangeScore = Soomla.Models.RangeScore = function () {
    /**
     A specific type of `Score` that has an associated range. The `Score`'s
     value can be only inside the range of values. For example, a shooting
     `Score` can be on a scale of 10 to 100 according to the user's performance
     in the game.
     */
    var RangeScore = Soomla.declareClass('RangeScore', {
      range: null,

      /**
       Increases this `Score` by the given amount after checking that it will
       stay within the range.
       @param amount Amount to increase by.
       */
      inc: function (amount) {
        // Don't increment if we've hit the range's highest value
        if (this.tempScore >= this.range.high) {
          return;
        }

        if ((this.tempScore + amount) > this.range.high) {
          amount = this.range.high - this.tempScore;
        }

        this.__super__.inc.call(this, amount);
      },

      /**
       Decreases this `Score` by the given amount after checking that the
       `Score` will stay within the range.
       @param amount Amount to decrease by.
       */
      dec: function (amount) {
        // Don't decrement if we've hit the range's lowest value
        if (this.tempScore <= this.range.low) {
          return;
        }

        if ((this.tempScore-amount) < this.range.low) {
          amount = this.tempScore - this.range.low;
        }

        this.__super__.dec.call(this, amount);
      },

      /**
       Sets the temp score to be the given `score`, after making sure that the
       it will stay within the range.
       @param score Score.
       @param onlyIfBetter If `Score` is better than the given `score` then
       this value should be `true`.
       */
      setTempScore: function (score, onlyIfBetter) {
        if (score > this.range.high) {
          score = this.range.high;
        }
        if (score < this.range.low) {
          score = this.range.low;
        }

        this.__super__.setTempScore.call(this, score, onlyIfBetter);
      }

    }, Score);
    return RangeScore;
  }();

  var VirtualItemScore = Soomla.Models.VirtualItemScore = function () {
    /**
     A specific type of `Score` that has an associated virtual item.
     The score is related to the specific item ID. For example: a game
     that has an 'energy' virtual item can have energy points.
     */
    var VirtualItemScore = Soomla.declareClass('VirtualItemScore', {
      associatedItemId: null,

      /**
       Gives your user the temp-score amount of the associated item.
       */
      performSaveActions: function () {
        this.__super__.performSaveActions.call(this);

        var amount = this.tempScore;
        Soomla.storeInventory.giveItem(this.associatedItemId, amount);
      }
    }, Score);
    return VirtualItemScore;
  }();

  // Challenges

  var Mission = Soomla.Models.Mission = function () {
    /**
     @class `CCMission`
     @brief A `Mission` is a task your users need to complete in your game.
     Each `Mission`s is associated with a `Gate` that defines the criteria for
     completing the `Mission`. You can optionally choose to give a `Reward` for
     users that complete your `Mission`. Create `Mission`s and use them as
     single, independent, entities OR you can create a `Challenge` to handle
     several `Mission`s and monitor their completion.
     NOTE: `Mission`s can be completed multiple times.
     */
    var Mission = Soomla.declareClass('Mission', {
      rewards: null,
      schedule: null,
      eventListener: false,

      _gate: null,

      /**
       Generates a gate ID for this `Mission`.
       @return 'gate_' followed by this `Mission`'s ID.
       */
      autoGateId: function () {
        return 'gate_' + this.itemId;
      },

      /**
       Determines whether this `Mission` is available by checking the criteria
       that makes the specific `Mission` available.
       @return If this instance is available returns `true`; otherwise `false`.
       */
      isAvailable: function () {
        return this._gate.canOpen() && this.schedule.approve(Soomla.missionStorage.getTimesCompleted(this));
      },

      /**
       Checks if this `Mission` has ever been completed.
       @return If this instance is completed returns `true`; otherwise `false`.
       */
      isCompleted: function () {
        // check if completed in Mission Storage
        // this checks if the mission was ever completed... no matter how many times.
        return Soomla.missionStorage.isCompleted(this);
      },

      /**
       Completes this `Mission`'s by opening its `Gate`.
       @return Boolean If `Schedule` doesn't approve, the mission cannot be completed
       and thus returns `false`; otherwise opens this `Mission`'s `Gate` and
       returns `true` if successful.
       */
      complete: function () {
        if (!this.schedule.approve(Soomla.missionStorage.getTimesCompleted(this))) {
          Soomla.logDebug('missions cannot be completed b/c Schedule doesn\'t approve.');
          return false;
        }
        Soomla.logDebug('trying opening gate to complete mission: ' + this.itemId);
        return this._gate.open();
      },

      /**
       Forces completion of this `Mission`. This function should not be used
       in standard scenarios.
       */
      forceComplete: function () {
        this._gate.forceOpen(true);
      },


      //protected:

      /**
       Registers relevant events: `OnGateOpened`.
       */
      registerEvents: function () {
        if (!this.isCompleted() && this._gate) {
          Soomla.addEventHandler(LevelUpConsts.EVENT_GATE_OPENED, this.onGateOpened, this);
          this.eventListener = true;
        }
      },

      /**
       Unregisters relevant events: `OnGateOpened`.
       */
      unregisterEvents: function () {
        if (this.eventListener) {
          Soomla.removeEventHandler(LevelUpConsts.EVENT_GATE_OPENED, this.onGateOpened);
          this.eventListener = false;
        }
      },

      /**
       Sets this `Mission` as completed and gives or takes `Reward`s according
       to the given `completed` value.
       @param completed If set to `true` gives rewards.
       */
      setCompletedInner: function (completed) {
        // set completed in Mission Storage
        Soomla.missionStorage.setCompleted(this, completed);

        if (completed) {
          this.giveRewards();
        } else {
          this.takeRewards();
        }
      },

      onGateOpened: function (gate) {
        if (this._gate === gate) {
          this._gate.forceOpen(false);
          this.setCompletedInner(true);
        }
      },

      //private:

      takeRewards: function () {
        if (this.rewards) {
          _.invoke(this.rewards, 'take');
        }
      },

      giveRewards: function () {
        if (this.rewards) {
          _.invoke(this.rewards, 'give');
        }
      },

      onCreate: function () {
        this.schedule = Soomla.Models.Schedule.createAnyTimeOnce();
        this.registerEvents();
      }

    }, Soomla.Models.SoomlaEntity);

    Object.defineProperty(Mission.prototype, 'gate', {
      get: function () {
        return this._gate;
      },
      set: function (gate) {
        if (this._gate !== gate) {
          if (this._gate) {
            this._gate.onDetached();
          }

          this._gate = gate;

          if (this._gate) {
            this._gate.onAttached();
          }
        }
      }
    });

    return Mission;
  }();

  var RecordMission = Soomla.Models.RecordMission = function () {
    /**
     @class `CCRecordMission`
     @brief A specific type of `Mission` that has an associated score and a desired
     record. The `Mission` is complete once the player achieves the desired
     record for the given score.
     */
    var RecordMission = Soomla.declareClass('RecordMission', {
      associatedScoreId: null,
      desiredRecord: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = RecordGate.create({
            itemId: this.autoGateId(),
            associatedScoreId: this.associatedScoreId,
            desiredRecord: this.desiredRecord
          });
        }
        this.__super__.onCreate.call(this);
      }

    }, Mission);
    return RecordMission;
  }();

  var WorldCompletionMission = Soomla.Models.WorldCompletionMission = function () {
    /**
     @class `CCWorldCompletionMission`
     @brief A specific type of `Mission` that has an associated `World`.
     The `Mission` is complete once the `World` has been completed.
     */
    var WorldCompletionMission = Soomla.declareClass('WorldCompletionMission', {
      associatedWorldId: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = WorldCompletionGate.create({
            itemId: this.autoGateId(),
            associatedWorldId: this.associatedWorldId
          });
        }
        this.__super__.onCreate.call(this);
      }

    }, Mission);
    return WorldCompletionMission;
  }();

  var Challenge = Soomla.Models.Challenge = function () {
    /**
     @class CCChallenge
     @brief A challenge is a specific type of `Mission` which holds a collection
     of `Mission`s. The user is required to complete all these `Mission`s in
     order to earn the `Reward` associated with the `Challenge`.
     */
    var Challenge = Soomla.declareClass('Challenge', {
      missions: null,
      missionCompletionRevokedListener: false,

      /**
       Checks if this `CCChallenge` is completed.
       @return Boolean If this instance is completed returns `true`; otherwise `false`.
       */
      isCompleted: function () {
        // could happen in construction
        // need to return false in order to register for child events
        if (!this.missions || this.missions.length === 0) {
          return false;
        }

        _.all(this.missions, function (mission) {
          return mission.isCompleted();
        });

        return true;
      },

      //protected:

      /**
       Registers relevant events: `OnMissionCompleted` and
       `OnMissionCompletionRevoked`.
       */
      registerEvents: function () {
        Soomla.logDebug ('registerEvents called');
        if (!this.isCompleted()) {
          Soomla.logDebug ('registering!');
          // register for events
          Soomla.addEventHandler(LevelUpConsts.EVENT_MISSION_COMPLETED, this.onMissionCompleted, this);
          this.eventListener = true;

          Soomla.addEventHandler(LevelUpConsts.EVENT_MISSION_COMPLETION_REVOKED, this.onMissionCompletionRevoked, this);
          this.missionCompletionRevokedListener = true;
        }
      },

      /**
       Unregisters relevant events: `OnMissionCompleted` and
       `OnMissionCompletionRevoked`.
       */
      unregisterEvents: function () {
        if (this.eventListener) {
          Soomla.removeEventHandler(LevelUpConsts.EVENT_MISSION_COMPLETED, this.onMissionCompleted);
          this.eventListener = false;
        }
        if (this.missionCompletionRevokedListener) {
          Soomla.removeEventHandler(LevelUpConsts.EVENT_MISSION_COMPLETION_REVOKED, this.onMissionCompletionRevoked);
          this.missionCompletionRevokedListener = false;
        }
      },

      onMissionCompleted: function (mission) {
        Soomla.logDebug ('onMissionCompleted');

        if (_.indexOf(this.missions, completedMission) >= 0) {
          Soomla.logDebug('Mission ' + completedMission.itemId + ' is part of challenge ' + this.itemId + ' (' + this.missions.length + ') total');
          var completed = true;
          var incompletedMission = _.find(this.missions, function (mission) {
            return !mission.isCompleted();
          });
          if (incompletedMission) {
            Soomla.logDebug('challenge mission not completed?=' + incompletedMission.itemId);
            completed = false;
          }

          if (completed) {
            Soomla.logDebug('Challenge ' + this.itemId + ' completed!');
            this.setCompletedInner(true);
          }
        }
      },

      onMissionCompletionRevoked: function (mission) {
        if (_.indexOf(this.missions, mission) >= 0) {
          if (Soomla.missionStorage.isCompleted(this)) {
            this.setCompletedInner(false);
          }
        }
      }

    }, Mission);
    return Challenge;
  }();

  var SocialLikeMission = Soomla.Models.SocialLikeMission = function () {
    /**
     @class `CCSocialLikeMission`
     @brief NOTE: Social `Mission`s require the user to perform a specific
     social action in order to receive a `Reward`. Currently, the social
     provider that's available is Facebook, so the `Mission`s are FB-oriented.
     In the future, more social providers will be added.
     A specific type of `Mission` that has an associated page name.
     The `Mission` is complete once the player 'Likes' the page.
     */
    var SocialLikeMission = Soomla.declareClass('SocialLikeMission', {
      provider: null,
      pageName: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = SocialLikeGate.create({
            itemId: this.autoGateId(),
            provider: this.provider,
            pageName: this.pageName
          });
        }
        this.__super__.onCreate.call(this);
      }
    }, Mission);
    return SocialLikeMission;
  }();

  var SocialStatusMission = Soomla.Models.SocialStatusMission = function () {
    /**
     @class `CCSocialStatusMission`
     @brief NOTE: Social `Mission`s require the user to perform a specific
     social action in order to receive a `Reward`. Currently, the social
     provider that's available is Facebook, so the `Mission`s are FB-oriented.
     In the future, more social providers will be added.

     A specific type of `Mission` that has an associated status. The `Mission`
     s complete once the player posts the status.
     */
    var SocialStatusMission = Soomla.declareClass('SocialStatusMission', {
      provider: null,
      status: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = SocialStatusGate.create({
            itemId: this.autoGateId(),
            provider: this.provider,
            status: this.status
          });
        }
        this.__super__.onCreate.call(this);
      }
    }, Mission);
    return SocialStatusMission;
  }();

  var SocialStoryMission = Soomla.Models.SocialStoryMission = function () {
    /**
     @class `CCSocialStoryMission`
     @brief NOTE: Social `Mission`s require the user to perform a specific
     social action in order to receive a `Reward`. Currently, the social
     provider that's available is Facebook, so the `Mission`s are FB-oriented.
     In the future, more social providers will be added.
     A specific type of `Mission` that has an associated story that includes a
     message, storyname, caption, link, and image. The `Mission` is complete
     once the player posts the story.
     */
    var SocialStoryMission = Soomla.declareClass('SocialStoryMission', {
      provider: null,
      message: null,
      storyName: null,
      caption: null,
      link: null,
      imgUrl: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = SocialStoryGate.create({
            itemId: this.autoGateId(),
            provider: this.provider,
            message: this.message,
            storyName: this.storyName,
            caption: this.caption,
            link: this.link,
            imgUrl: this.imgUrl
          });
        }
        this.__super__.onCreate.call(this);
      }
    }, Mission);
    return SocialStoryMission;
  }();

  var SocialUploadMission = Soomla.Models.SocialUploadMission = function () {
    /**
     @class `CCSocialUploadMission`
     @brief NOTE: Social `Mission`s require the user to perform a specific
     social action in order to receive a `Reward`. Currently, the social
     provider that's available is Facebook, so the `Mission`s are FB-oriented.
     In the future, more social providers will be added.

     A specific type of `Mission` that has an associated filename and message.
     The `Mission` is complete once the player uploads the image.
     */
    var SocialUploadMission = Soomla.declareClass('SocialUploadMission', {
      provider: null,
      message: null,
      fileName: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = SocialUploadGate.create({
            itemId: this.autoGateId(),
            provider: this.provider,
            message: this.message,
            fileName: this.fileName
          });
        }
        this.__super__.onCreate.call(this);
      }
    }, Mission);
    return SocialUploadMission;
  }();

  var BalanceMission = Soomla.Models.BalanceMission = function () {
    /**
     @class `CCBalanceMission`
     @brief A specific type of `Mission` that has an associated virtual
     item and a desired balance. The `Mission` is complete once the item's
     balance reaches the desired balance.
     */
    var BalanceMission = Soomla.declareClass('BalanceMission', {
      associatedItemId: null,
      desiredBalance: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = BalanceGate.create({
            itemId: this.autoGateId(),
            associatedItemId: this.associatedItemId,
            desiredBalance: this.desiredBalance
          });
        }
        this.__super__.onCreate.call(this);
      }
    }, Mission);
    return BalanceMission;
  }();

  var PurchasingMission = Soomla.Models.PurchasingMission = function () {
    /**
     @class `CCPurchasingMission`
     @brief A specific type of `Mission` that has an associated virtual
     item. The `Mission` is complete once the item has been purchased.
     */
    var PurchasingMission = Soomla.declareClass('PurchasingMission', {
      associatedItemId: null,

      onCreate: function () {
        if (!this.gate) {
          this.gate = PurchasableGate.create({
            itemId: this.autoGateId(),
            associatedItemId: this.associatedItemId
          });
        }
        this.__super__.onCreate.call(this);
      }
    }, Mission);
    return PurchasingMission;
  }();

  //
  var World = Soomla.Models.World = function () {
    /**
     A game can have multiple `World`s or a single one, and `World`s can also
     contain other `World`s in them. A `World` can contain a set of `Level`s,
     or multiple sets of `Level`s. A `World` can also have a `Gate` that defines
     the criteria to enter it. Games that don’t have the concept of `World`s can
     be modeled as single `World` games.

     Real Game Example: "Candy Crush" uses `World`s.
     */
    var World = Soomla.declareClass('World', {
      _innerWorldsMap: {},
      _scores: {},
      missions: [],
      parentWorld: null,
      _gate: null,

      /**
       Adds the given inner `World` to this `World`.
       @param world World to be added.
       */
      addInnerWorld: function (world) {
        this._innerWorldsMap[world.itemId] = world;
        world.parentWorld = this;
      },

      /**
       Adds the given `Mission` to this `World`.
       @param mission Mission to be added.
       */
      addMission: function (mission) {
        this.missions.push(mission);
      },

      /**
       Adds the given `Score` to this `World`.
       @param score Score to be added.
       */
      addScore: function (score) {
        this._scores[score.itemId] = score;
      },

      /**
       Retrieves the inner `World` with the given index.
       @param index The index of the `World` to be retrieved.
       @return the `World` that was fetched.
       */
      getInnerWorldAt: function (index) {
        var innerWorlds = _.values(this._innerWorldsMap);
        if (index >= 0 && index < innerWorlds.length) {
          return innerWorlds[i];
        } else {
          return null;
        }
      },

      /**
       Creates a batch of `Level`s and adds them to this `World`. This
       function will save you a lot of time - instead of creating many levels
       one by one, you can create them all at once.
       @param numLevels The number of `Level`s to be added to this `World`.
       @param gateTemplate The `Gate` for the levels.
       @param scoreTemplates `Score` template for the `Level`s.
       @param missionTemplates `Mission` template for the `Level`s.
       */
      batchAddLevelsWithTemplates: function (numLevels, gateTemplate, scoreTemplates, missionTemplates) {
        if (scoreTemplates && !_.isArray(scoreTemplates)) {
          scoreTemplates = [scoreTemplates];
        }
        if (missionTemplates && !_.isArray(missionTemplates)) {
          missionTemplates = [missionTemplates];
        }

        for (var i = 0; i < numLevels; i++) {
          var lvlId = this.getIdForAutoGeneratedLevel(this.itemId, i);
          var aLvl = Soomla.Models.Level.create({itemId: lvlId});

          var gate = gateTemplate ? gateTemplate.clone(this.getIdForAutoGeneratedGate(lvlId)) : null;

          this.createAddAutoLevel(lvlId, aLvl, gate, scoreTemplates, missionTemplates);
        }

      },

      batchAddDependentLevelsWithTemplates: function (numLevels, scoreTemplates, missionTemplates) {
        if (scoreTemplates && !_.isArray(scoreTemplates)) {
          scoreTemplates = [scoreTemplates];
        }
        if (missionTemplates && !_.isArray(missionTemplates)) {
          missionTemplates = [missionTemplates];
        }

        var previousLvlId = null;
        for (var i = 0; i < numLevels; i++) {
          var lvlId = this.getIdForAutoGeneratedLevel(this.itemId, i);
          var aLvl = Soomla.Models.Level.create({itemId: lvlId});

          var completeGate = previousLvlId ?
            WorldCompletionGate.create({
              itemId: this.getIdForAutoGeneratedCompleteGate(lvlId, previousLvlId),
              associatedWorldId: previousLvlId
            }) : null;

          this.createAddAutoLevel(lvlId, aLvl, completeGate, scoreTemplates, missionTemplates);
          previousLvlId = lvlId;
        }
      },

      /**
       Sets the single `Score` value to the given amount.
       @param amount Amount to set.
       */
      setSingleScoreValue: function (amount) {
        var keys = _.keys(this._scores);
        if (keys.length === 0) {
          return;
        }

        var firstScoreId = keys[0];
        this.setScoreValue(firstScoreId, amount);
      },

      /**
       Decreases the single `Score` value by the given amount.
       @param amount Amount to decrease by.
       */
      decSingleScore: function (amount) {
        var keys = _.keys(this._scores);
        if (keys.length === 0) {
          return;
        }

        var firstScoreId = keys[0];
        this.decScore(firstScoreId, amount);
      },

      /**
       Increases the single `Score` value by the given amount.
       @param amount Amount to increase by.
       */
      incSingleScore: function (amount) {
        var keys = _.keys(this._scores);
        if (keys.length === 0) {
          return;
        }

        var firstScoreId = keys[0];
        this.incScore(firstScoreId, amount);
      },

      /**
       Retrieves the single `Score` value.
       @return The single score.
       */
      getSingleScore: function () {
        var keys = _.keys(this._scores);
        if (keys.length === 0) {
          return null;
        }

        var firstScoreId = keys[0];
        return this._scores[firstScoreId];
      },

      /**
       Resets the `Score`s for this `World`.
       @param save If set to `true` save.
       */
      resetScores: function (save) {

        if (!this._scores || _.isEmpty(this._scores)) {
          Soomla.logError('(ResetScores) You don\'t have any scores defined in this world. World id: ' + this.itemId);
          return;
        }

        _.invoke(this._scores, 'reset', save);
      },

      /**
       Decreases the `Score` with the given ID by the given amount.
       @param scoreId ID of the `Score` to be decreased.
       @param amount Amount to decrease by.
       */
      decScore: function (scoreId, amount) {
        this._scores[scoreId].dec(amount);
      },

      /**
       Increases the `Score` with the given ID by the given amount.
       @param scoreId ID of the `Score` to be increased.
       @param amount Amount.
       */
      incScore: function (scoreId, amount) {
        this._scores[scoreId].inc(amount);
      },

      /**
       Retrieves the record `Score`s.
       @return The record `Score`s - each `Score` ID with its record.
       */
      getRecordScores: function () {
        return _.mapValues(this._scores, function (score) {
          return score.getRecord();
        });
      },

      /**
       Retrieves the latest `Score`s.
       @return The latest `Score`s - each `Score` ID with its record.
       */
      getLatestScores: function () {
        return _.mapValues(this._scores, function (score) {
          return score.getLatest();
        });
      },

      /**
       Sets the `Score` with the given ID to have the given value.
       @param id ID of the `Score` whose value is to be set.
       @param scoreVal Value to set.
       @param onlyIfBetter
       */
      setScoreValue: function (id, scoreVal, onlyIfBetter) {
        onlyIfBetter = !!onlyIfBetter;

        var score = this._scores[id];
        if (!score) {
          Soomla.logError('(setScore) Can\'t find score id: ' + id + ' world id: ' + this.itemId);
          return;
        }
        score.setTempScore(scoreVal, onlyIfBetter);
      },

      /**
       Determines whether this `World` is completed.
       @return Boolean `true` if this instance is completed; otherwise, `false`.
       */
      isCompleted: function () {
        return Soomla.worldStorage.isCompleted(this);
      },

      /**
       Sets this `World` as completed.
       @param completed If set to `true` completed.
       */
      setCompleted: function (completed, recursive) {
        recursive = !!recursive;
        if (recursive) {
          _.forEach(this._innerWorldsMap, function (world) {
            world.setCompleted(completed, true);
          });
        }

        var alreadyCompleted = Soomla.worldStorage.isCompleted(this);

        Soomla.worldStorage.setCompleted(this, completed);

        if (!alreadyCompleted && completed && this.parentWorld) {
          this.parentWorld.notifyInnerWorldFirstCompleted(this);
        }
      },

      /**
       Assigns the given reward to this `World`.
       @param reward Reward to assign.
       */
      assignReward: function (reward) {
        var olderReward = this.getAssignedRewardId();
        if (olderReward && olderReward.length > 0) {
          var oldReward = Soomla.soomlaLevelUp.getReward(olderReward);
          if (oldReward) {
            oldReward.take();
          }
        }

        // We have to make sure the assigned reward can be assigned unlimited times.
        // There's no real reason why it won't be.
        if (reward.schedule.schedApprovals > 0) {
          reward.schedule.schedApprovals = 0;
        }

        reward.give();
        Soomla.worldStorage.setReward(this, reward.itemId);
      },

      /**
       Retrieves the assigned reward ID.
       @return The assigned reward ID.
       */
      getAssignedRewardId: function () {
        return Soomla.worldStorage.getAssignedReward(this);
      },

      /**
       Retrieves the last completed inner world ID.
       @return The the last completed inner world ID.
       */
      getLastCompletedInnerWorld: function () {
        return Soomla.worldStorage.getLastCompletedInnerWorld(this);
      },

      /**
       Determines if this world is available for starting, based on either if
       there is no `Gate` for this `World`, or if the `Gate` is open.
       @return `true` if this instance can start; otherwise, `false`.
       */
      canStart: function () {
        return !this._gate || this._gate.isOpen();
      },

      //private:
      getIdForAutoGeneratedLevel: function (id, idx) {
        return id + '_level' + idx;
      },

      getIdForAutoGeneratedScore: function (id, idx) {
        return id + '_score' + idx;
      },

      getIdForAutoGeneratedGate: function (id) {
        return id + '_gate';
      },

      getIdForAutoGeneratedCompleteGate: function (id, previousId) {
        return id + '_complete_' + previousId;
      },

      getIdForAutoGeneratedMission: function (id, idx) {
        return id + '_mission' + idx;
      },

      applyParentToInnerWorlds: function () {
        _.forEach(this._innerWorldsMap, function (world) {
          world.parentWorld = this;
        }, this)
      },

      notifyInnerWorldFirstCompleted: function (innerWorld) {
        if (innerWorld) {
          Soomla.worldStorage.setLastCompletedInnerWorld(this, innerWorld.itemId);
        }
      },

      sumInnerWorldsRecords: function sumInnerWorldsRecords() {
        return this.sumInnerWorldSingleRecords();
      },

      sumWorldScoreRecords: function sumWorldScoreRecords() {
        return _.reduce(this._scores, function (sum, score) {
          var record = score.getRecord();
          if (record > 0) {
            return sum + record;
          }

          return sum;
        });

      },

      sumInnerWorldSingleRecords: function sumInnerWorldSingleRecords() {
        return _.reduce(this._innerWorldsMap, function (sum, world) {
          var singleScore = world.getSingleScore();
          if (!_.isUndefined(singleScore)) {
            var record = singleScore.getRecord();
            if (record > -1) {
              return sum + record;
            }
          }

          return sum;
        });
      },

      sumAllInnerWorldsRecords: function sumAllInnerWorldsRecords() {
        return _.reduce(this._innerWorldsMap, function (sum, world) {
          sum += world.sumWorldScoreRecords();
          sum += world.sumAllInnerWorldsRecords();

          return sum;
        });
      },

      createAddAutoLevel: function (id, target, targetGate, scoreTemplates, missionTemplates) {
        if (targetGate) {
          target.gate = targetGate;
        }

        if (scoreTemplates) {
          for (var k = 0; k < scoreTemplates.length; k++) {
            var score = scoreTemplates[k];
            target.addScore(score.clone(this.getIdForAutoGeneratedScore(id, k)));
          }
        }

        if (missionTemplates) {
          for (var k = 0; k < missionTemplates.length; k++) {
            var mission = missionTemplates[k];
            target.addMission(mission.clone(this.getIdForAutoGeneratedMission(id, k)));
          }
        }

        this._innerWorldsMap[id] = target;

        target.parentWorld = this;
      },
      toJSON: function () {
        return _.omit(this, 'parentWorld');
      }

    }, Soomla.Models.SoomlaEntity);

    Object.defineProperty(World.prototype, 'gate', {
      get: function () {
        return this._gate;
      },
      set: function (gate) {
        if (this._gate !== gate) {
          if (this._gate) {
            this._gate.onDetached();
          }

          this._gate = gate;

          if (this._gate) {
            this._gate.onAttached();
          }
        }
      }
    });

    Object.defineProperty(World.prototype, 'innerWorldsMap', {
      get: function () {
        return this._innerWorldsMap;
      },
      set: function (innerWorldsMap) {
        this._innerWorldsMap = innerWorldsMap;
        if (this._innerWorldsMap) {
          this.applyParentToInnerWorlds();
        }
      }
    });

    Object.defineProperty(World.prototype, 'worlds', {
      get: function () {
        return _.values(this._innerWorldsMap);
      },
      set: function (worlds) {
        this._innerWorldsMap = {};
        _.forEach(worlds, function (world) {
          world.parentWorld = this;
          this._innerWorldsMap[world.itemId] = world;
        }, this);
      }
    });

    Object.defineProperty(World.prototype, 'scores', {
      get: function () {
        return this._scores;
      },
      set: function (scores) {
        if (_.isArray(scores)) {
          this._scores = {};
          _.forEach(scores, function (score) {
            this._scores[score.itemId] = score;
          }, this);
        } else {
          this._scores = scores;
        }
      }
    }, Soomla.Models.SoomlaEntity);

    return World;
  }();

  var Level = Soomla.Models.Level = function () {

    var LevelState = {
      Idle: 0,
      Running: 1,
      Paused: 2,
      Ended: 3,
      Completed: 4
    };

    /**
     @class CCLevel
     @brief A `Level` is a type of `World`, while a `World` contains
     a set of `Level`s. Each `Level` always has a state that is one
     of: idle, running, paused, ended, or completed.

     Real Game Examples: "Candy Crush" and "Angry Birds" use `Level`s.
     */
    var Level = Soomla.declareClass('Level', {
      // Start time of this `Level`.
      startTime: 0,
      // The elapsed time this `Level` is being played.
      elapsed: 0,

      /**
       The state of this `Level`. The initial state is idle, later in the
       game can be any of: running, paused, ended, or completed.
       */
      state: LevelState.Idle,

      /**
       Gets the number of times this `Level` was started.
       @return The number of times started.
       */
      getTimesStarted: function getTimesStarted() {
        return Soomla.levelStorage.getTimesStarted(this);
      },

      /**
       Gets the number of times this `Level` was played.
       @return The number of times played.
       */
      getTimesPlayed: function getTimesPlayed() {
        return Soomla.levelStorage.getTimesPlayed(this);
      },

      /**
       Gets the slowest duration in millis that this `Level` was played.
       @return The slowest duration in millis.
       */
      getSlowestDurationMillis: function getSlowestDurationMillis() {
        return Soomla.levelStorage.getSlowestDurationMillis(this);
      },

      /**
       Gets the fastest duration in millis that this `Level` was played.
       @return The fastest duration in millis.
       */
      getFastestDurationMillis: function getFastestDurationMillis() {
        return Soomla.levelStorage.getFastestDurationMillis(this);
      },

      /**
       Gets the play duration of this `Level` in millis.
       @return The play duration in millis.
       */
      getPlayDurationMillis: function getPlayDurationMillis() {

        var now = this.getCurrentTimeMs();
        var duration = this.elapsed;
        if (this.startTime !== 0) {
          duration += now - this.startTime;
        }

        return duration;
      },

      /**
       Starts this `Level`.
       */
      start: function () {
        if (this.state === LevelState.Running) {
          Soomla.logError('Can\'t start a level that is already running.');
          return false;
        }

        Soomla.logDebug('Starting level with world id: ' + this.itemId);

        if (!this.canStart()) {
          return false;
        }

        if (this.state != LevelState.Paused) {
          this.elapsed = 0;
          return Soomla.levelStorage.incTimesStarted(this);
        }

        this.startTime = this.getCurrentTimeMs();
        this.state = LevelState.Running;
        return true;
      },

      /**
       Pauses this `Level`.
       */
      pause: function () {
        if (this.state !== LevelState.Running) {
          Soomla.logError('Can\'t pause a level that is not running.');
          return;
        }

        var now = this.getCurrentTimeMs();
        this.elapsed += now - this.startTime;
        this.startTime = 0;

        this.state = LevelState.Paused;
      },

      /**
       Ends this `Level`.
       @param completed If set to `true` completed.
       */
      end: function (completed) {
        // check end() called without matching start(),
        // i.e, the level is not running nor paused
        if(this.state !== LevelState.Running && this.state != LevelState.Paused) {
          Soomla.logError('end() called without prior start()! ignoring.');
          return;
        }

        this.state = LevelState.Ended;

        if (completed) {
          var duration = this.getPlayDurationMillis();

          // Calculate the slowest \ fastest durations of level play

          if (duration > this.getSlowestDurationMillis()) {
            Soomla.levelStorage.setSlowestDurationMillis(this, duration);
          }

          // We assume that levels' duration is never 0
          var fastest = this.getFastestDurationMillis();
          if ((fastest === 0) || (duration < this.getFastestDurationMillis())) {
            Soomla.levelStorage.setFastestDurationMillis(this, duration);
          }

          _.forEach(this._scores, function (score) {
            score.reset(true);
          });

          // Count number of times this level was played
          Soomla.levelStorage.incTimesPlayed(this);

          this.setCompleted(true);
        }

        // reset timers
        this.startTime = 0;
        this.elapsed = 0;
      },

      /**
       Restarts this `Level`.
       @param completed If set to `true` completed.
       */
      restart: function (completed) {
        if (this.state === LevelState.Running || this.state == LevelState.Paused) {
          this.end(completed);
        }
        this.start();
      },

      /**
       Sets this `Level` as completed.
       @param completed If set to `true` completed.
       */
      setCompleted: function (completed) {
        if (completed) {
          this.state = LevelState.Completed;
          Soomla.levelStorage.incTimesCompleted(this);
        }
        else {
          this.state = LevelState.Idle;
        }
        this.__super__.setCompleted.call(this, completed);
      },

      //protected:
      getCurrentTimeMs: function () {
        return Date.now();
      }
    }, World);

    /**
     The state of this `Level`. Every level must have one of the below
     states.
     */
    Level.LevelState = LevelState;

    return Level;
  }();

  var LevelUpBridge = Soomla.LevelUpBridge = function () {
    /**
     This class calls the bridge functions that call the relative native
     functions.
     */
    var LevelUpBridge = Soomla.declareClass('LevelUpBridge', {

      ctor: function () {
        this.bindNative();
      },

      init: function init() {
        return true;
      },

      initLevelUp: function initLevelUp() {
        Soomla.logDebug('call init');

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::initLevelUp',
          metadata: {}
        });

        return result['return'];
      },

      gateIsOpen: function (gate) {
        Soomla.logDebug('call gateIsOpen with gate: ' + gate.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::gateIsOpen',
          gateId: gate.itemId
        });

        return result['return'];
      },

      gateSetOpen: function (gate, open, notify) {
        Soomla.logDebug('call gateSetOpen with gate: ' + gate.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::gateSetOpen',
          gateId: gate.itemId,
          open: open,
          notify: notify
        });
      },

      levelSetSlowestDurationMillis: function (level, duration) {
        Soomla.logDebug('call levelSetSlowestDurationMillis with level: ' + level.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::levelSetSlowestDurationMillis',
          levelId: level.itemId,
          duration: duration
        });
      },
      levelGetSlowestDurationMillis: function (level) {
        Soomla.logDebug('call levelGetSlowestDurationMillis with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelGetSlowestDurationMillis',
          levelId: level.itemId
        });

        return result['return'];
      },

      levelSetFastestDurationMillis: function (level, duration) {
        Soomla.logDebug('call levelSetFastestDurationMillis with level: ' + level.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::levelSetFastestDurationMillis',
          levelId: level.itemId,
          duration: duration
        });
      },
      levelGetFastestDurationMillis: function (level) {
        Soomla.logDebug('call levelGetFastestDurationMillis with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelGetFastestDurationMillis',
          levelId: level.itemId
        });

        return result['return'];
      },

      levelIncTimesStarted: function (level) {
        Soomla.logDebug('call levelIncTimesStarted with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelIncTimesStarted',
          levelId: level.itemId
        });

        return result['return'];
      },
      levelDecTimesStarted: function (level) {
        Soomla.logDebug('call levelDecTimesStarted with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelDecTimesStarted',
          levelId: level.itemId
        });

        return result['return'];
      },
      levelGetTimesStarted: function (level) {
        Soomla.logDebug('call levelGetTimesStarted with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelGetTimesStarted',
          levelId: level.itemId
        });

        return result['return'];
      },

      levelGetTimesPlayed: function (level) {
        Soomla.logDebug('call levelGetTimesPlayed with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelGetTimesPlayed',
          levelId: level.itemId
        });

        return result['return'];
      },
      levelIncTimesPlayed: function (level) {
        Soomla.logDebug('call levelIncTimesPlayed with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelIncTimesPlayed',
          levelId: level.itemId
        });

        return result['return'];
      },
      levelDecTimesPlayed: function (level) {
        Soomla.logDebug('call levelDecTimesPlayed with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelDecTimesPlayed',
          levelId: level.itemId
        });

        return result['return'];
      },

      levelGetTimesCompleted: function (level) {
        Soomla.logDebug('call levelGetTimesCompleted with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelGetTimesCompleted',
          levelId: level.itemId
        });

        return result['return'];
      },
      levelIncTimesCompleted: function (level) {
        Soomla.logDebug('call levelIncTimesCompleted with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelIncTimesCompleted',
          levelId: level.itemId
        });

        return result['return'];
      },
      levelDecTimesCompleted: function (level) {
        Soomla.logDebug('call levelDecTimesCompleted with level: ' + level.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::levelDecTimesCompleted',
          levelId: level.itemId
        });

        return result['return'];
      },

      missionSetCompleted: function (mission, completed, notify) {
        Soomla.logDebug('call missionSetCompleted with mission: ' + mission.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::missionSetCompleted',
          missionId: mission.itemId,
          completed: completed,
          notify: notify
        });
      },
      missionGetTimesCompleted: function (mission) {
        Soomla.logDebug('call missionGetTimesCompleted with mission: ' + mission.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::missionGetTimesCompleted',
          missionId: mission.itemId
        });

        return result['return'];
      },

      scoreSetLatestScore: function (score, newValue) {
        Soomla.logDebug('call scoreSetLatestScore with score: ' + score.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::scoreSetLatestScore',
          scoreId: score.itemId,
          newValue: newValue
        });
      },
      scoreGetLatestScore: function (score) {
        Soomla.logDebug('call scoreGetLatestScore with score: ' + score.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::scoreGetLatestScore',
          scoreId: score.itemId
        });

        return result['return'];
      },
      scoreSetRecordScore: function (score, newValue) {
        Soomla.logDebug('call scoreSetRecordScore with score: ' + score.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::scoreSetRecordScore',
          scoreId: score.itemId,
          newValue: newValue
        });
      },
      scoreGetRecordScore: function (score) {
        Soomla.logDebug('call scoreGetRecordScore with score: ' + score.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::scoreGetRecordScore',
          scoreId: score.itemId
        });

        return result['return'];
      },


      worldSetCompleted: function (world, completed, notify) {
        Soomla.logDebug('call worldSetCompleted with world: ' + world.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::worldSetCompleted',
          worldId: world.itemId,
          completed: completed,
          notify: notify
        });
      },
      worldIsCompleted: function (world) {
        Soomla.logDebug('call worldIsCompleted with world: ' + world.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::worldIsCompleted',
          worldId: world.itemId
        });

        return result['return'];
      },

      worldSetReward: function (world, rewardId) {
        Soomla.logDebug('call worldSetReward with world: ' + world.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::worldSetReward',
          worldId: world.itemId,
          rewardId: rewardId
        });
      },
      worldGetAssignedReward: function (world) {
        Soomla.logDebug('call worldGetAssignedReward with world: ' + world.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::worldGetAssignedReward',
          worldId: world.itemId
        });

        return result['return'];
      },

      worldSetLastCompletedInnerWorld: function (world, innerWorldId) {
        Soomla.logDebug('call worldSetLastCompletedInnerWorld with world: ' + world.itemId);

        Soomla.callNative({
          method: 'CCLevelUpBridge::worldSetLastCompletedInnerWorld',
          worldId: world.itemId,
          innerWorldId: innerWorldId
        });
      },
      worldGetLastCompletedInnerWorld: function (world) {
        Soomla.logDebug('call worldGetLastCompletedInnerWorld with world: ' + world.itemId);

        var result = Soomla.callNative({
          method: 'CCLevelUpBridge::worldGetLastCompletedInnerWorld',
          worldId: world.itemId
        });

        return result['return'];
      },
      //private:
      bindNative: function bindNative() {
        Soomla.logDebug('Binding to native platform bridge...');
        if (platform.isAndroid()) {
          jsb.reflection.callStaticMethod('com/soomla/cocos2dx/levelup/LevelUpBridgeBinder', 'bind', '()V');
        } else if (platform.isIos()) {
          jsb.reflection.callStaticMethod('LevelUpBridge', 'initShared');
        } else {
          Soomla.logError('Unsupported platform: ' + platform.name);
        }
      }
    });

    LevelUpBridge.initShared = function () {
      var ret = LevelUpBridge.create();
      if (ret.init()) {
        Soomla.levelUpBridge = ret;
      } else {
        Soomla.levelUpBridge = null;
      }
    };


    return LevelUpBridge;
  }();

  var SoomlaLevelUp = Soomla.Models.SoomlaLevelUp = function () {


    function ifLevel(innerWorld) {
      return innerWorld.className === 'Level';
    }

    function ifCompletedLevel(innerWorld) {
      return innerWorld.className === 'Level' && innerWorld.isCompleted();
    }

    function ifWorld(innerWorld) {
      return innerWorld.className === 'World';
    }

    function ifCompletedWorld(innerWorld) {
      return innerWorld.className === 'World' && innerWorld.isCompleted();
    }

    function ifWorldOrLevel(innerWorld) {
      return ifWorld(innerWorld) || ifLevel(innerWorld);
    }


    /**
     @class SoomlaLevelUp
     @brief This is the top level container for the cocos2dx-levelup model and
     definitions. It stores the configurations of the game's world-hierarchy and
     provides lookup functions for levelup model elements.
     */
    var SoomlaLevelUp = Soomla.declareClass('SoomlaLevelUp', {
      DB_KEY_PREFIX: 'soomla.levelup.',

      mainWorld: null,
      rewards: null,

      /**
       Initializes the specified `InitialWorld` and rewards.
       @param initialWorld Initial `World` to begin the game.
       @param rewards Rewards for the initial `World`.
       */
      initialize: function initialize(initialWorld, rewards) {
        this.initialWorld = initialWorld;

        if (rewards) {
          this.rewards = _.inject(rewards, function (result, reward) {
            result[reward.itemId] =  reward;
            return result;
          }, {});
        }

        this.save();

        Soomla.LevelUpEventDispatcher.initShared();

        Soomla.worldStorage.initLevelUp();
      },

      /**
       Retrieves the reward with the given ID.
       @param rewardId ID of the `Reward` to be fetched.
       @return The reward that was fetched.
       */
      getReward: function getReward(rewardId) {
        return this.rewards ? this.rewards[rewardId] : null;
      },

      /**
       Retrieves the `Score` with the given score ID.
       @param scoreId ID of the `Score` to be fetched.
       @return The score.
       */
      getScore: function (scoreId) {
        var scores = this.initialWorld.scores;
        var score = scores[scoreId];
        if (!score) {
          score = this.fetchScoreFromWorlds(scoreId, this.initialWorld.innerWorldsMap);
        }

        return score;
      },

      /**
       Retrieves the `World` with the given world ID.
       @param worldId ID of the `World` to be fetched.
       @return The world.
       */
      getWorld: function (worldId) {
        if (this.initialWorld.itemId === worldId) {
          return this.initialWorld;
        }

        return this.fetchWorld(worldId, this.initialWorld.innerWorldsMap);
      },

      /**
       Retrieves the `Level` with the given level ID.
       @param levelId ID of the `Level` to be fetched.
       @return Level The world.
       */
      getLevel: function (levelId) {
        var result = this.getWorld(levelId);
        return result instanceof Level ? result : null;
      },

      /**
       Retrieves the `Gate` with the given ID.
       @param gateId ID of the `Gate` to be fetched.</param>
       @return The gate.
       */
      getGate: function (gateId) {
        var gate = this.fetchGateFromGate(gateId, this.initialWorld.gate);
        if (gate) {
          return gate;
        }

        gate = this.fetchGateFromMissions(gateId, this.initialWorld.missions);
        if (gate) {
          return gate;
        }

        return this.fetchGate(gateId, this.initialWorld.innerWorldsMap);
      },

      /**
       Retrieves the `Mission` with the given ID.
       @param missionId ID of the `Mission` to be fetched.
       @return The mission.
       */
      getMission: function (missionId) {
        var retMission = this.fetchMissionInMissions(missionId, this.initialWorld.missions);

        if (!retMission ) {
          return this.fetchMissionInWorlds(missionId, this.initialWorld.innerWorldsMap);
        }

        return retMission;
      },

      /**
       Counts all the `Level`s in all `World`s and inner `World`s
       starting from the `InitialWorld`.
       @return The number of levels in all worlds and their inner worlds.
       */
      getLevelCount: function () {
        return this.getLevelCountInWorld(this.initialWorld);
      },

      /**
       Counts all the `Level`s in all `World`s and inner `World`s
       starting from the given `World`.
       @param world The world to examine.
       @return The number of levels in the given world and its inner worlds.
       */
      getLevelCountInWorld: function (world) {
        var innerWorldsMap = world.innerWorldsMap;
        return _.reduce(innerWorldsMap, function (result, innerWorld) {
          return result + this.getRecursiveCount(innerWorld, ifLevel);
        }, this);
      },

      /**
       Counts all `World`s and their inner `World`s with or without their
       `Level`s according to the given `withLevels`.
       @param withLevels Indicates whether to count `Level`s also.
       @return The number of `World`s, and optionally their inner `Level`s.
       */
      getWorldCount: function (withLevels) {
        return this.getRecursiveCount(this.initialWorld, withLevels ? ifWorldOrLevel : ifWorld);
      },

      /**
       Counts all completed `Level`s.
       @return The number of completed `Level`s and their inner completed
       `Level`s.
       */
      getCompletedLevelCount: function () {
        return this.getRecursiveCount(this.initialWorld, ifCompletedLevel);
      },

      /**
       Counts the number of completed `World`s.
       @return The number of completed `World`s and their inner completed
       `World`s.
       */
      getCompletedWorldCount: function () {
        return this.getRecursiveCount(this.initialWorld, ifCompletedWorld);
      },

      //private:
      fetchWorld: function (worldId, worlds) {
        var retWorld = worlds[worldId];
        if (!retWorld) {
          _.any(worlds, function (world) {
            retWorld = this.fetchWorld(worldId, world.innerWorldsMap);
            return !!retWorld;
          }, this);
        }

        return retWorld;
      },

      fetchScoreFromWorlds: function (scoreId, worlds) {
        var retScore = null;

        _.any(worlds, function (world) {
          retScore = world.scores[scoreId];
          if (!retScore) {
            retScore = this.fetchScoreFromWorlds(scoreId, world.innerWorldsMap);
          }
          return !!retScore;
        }, this);

        return retScore;
      },

      fetchGate: function (gateId, worlds) {
        if (!worlds) {
          return null;
        }

        var retGate;
        _.any(worlds, function (world) {
          retGate = this.fetchGateFromGate(gateId, world.gate);
          return !!retGate;
        }, this);


        if (!retGate) {
          retGate = _.any(worlds, function (world) {
            retGate = this.fetchGateFromMissions(gateId, world.missions);
            if (!retGate) {
              retGate = this.fetchGate(gateId, world.innerWorldsMap);
            }
            return !!retGate;
          }, this);

        }

        return retGate;
      },

      fetchGateFromMissions: function (gateId, missions) {
        var retGate = null;

        _.any(missions, function (mission) {
          retGate = this.fetchGateFromGate(gateId, mission.gate);
          return !!retGate;
        }, this);

        if (!retGate) {
          _.any(missions, function (challenge) {
            if (challenge.className === 'Challenge') {
              retGate = this.fetchGateFromMissions(gateId, challenge.missions);
            }
            return !!retGate;
          }, this);
        }

        return retGate;
      },

      fetchGateFromGate: function (gateId, targetGate) {
        if (!targetGate) {
          return null;
        }

        if (targetGate.itemId === gateId) {
          return targetGate;
        }

        var result = null;
        // Duck typing to check GateList
        if (targetGate.gates !== undefined) {
          _.any(targetGate.gates, function (innerGate) {
            result = this.fetchGateFromGate(gateId, innerGate);

            return !!result;
          }, this);
        }

        return result;
      },

      getRecursiveCount: function (world, isAccepted) {
        var count = 0;

        // If the predicate is true, increment
        if (isAccepted(world)) {
          count++;
        }

        _.forEach(world.innerWorldsMap, function (innerWorld) {
          count += this.getRecursiveCount(innerWorld, isAccepted);
        }, this);

        return count;
      },

      fetchMissionInWorlds: function fetchMissionInWorlds(missionId, worlds) {
        var mission = null;
        _.any(worlds, function (world) {
          mission = this.fetchMissionInMissions(missionId, world.missions);

          if (!mission) {
            mission = this.fetchMissionInWorlds(missionId, world.innerWorldsMap);
          }

          return !!mission;
        }, this);

        return mission;
      },

      fetchMissionInMissions: function fetchMissionInMissions(missionId, missions) {
        if (!missions) {
          return null;
        }

        var retMission = null;

        _.any(missions, function (mission) {
          retMission = this.fetchMission(missionId, mission);
          return !!retMission;
        }, this);

        return retMission;
      },

      fetchMission: function (missionId, targetMission) {
        if (!targetMission) {
          return null;
        }

        if (targetMission.itemId === missionId) {
          return targetMission;
        }

        if (targetMission.className === 'Challenge') {
          return this.fetchMissionInMissions(missionId, targetMission.missions);
        } else {
          return null;
        }
      },

      clearCurrentState: function () {
        var allKeys = Soomla.keyValueStorage.getEncryptedKeys();
        if (allKeys) {
          _.each(function (key) {
            if (key.indexOf(Soomla.gateStorage.getKeyGatePrefix()) === 0  ||
              key.indexOf(Soomla.levelStorage.getKeyLevelPrefix()) === 0 ||
              key.indexOf(Soomla.missionStorage.getKeyMissionPrefix()) === 0 ||
              key.indexOf(Soomla.scoreStorage.getKeyScorePrefix()) === 0 ||
              key.indexOf(Soomla.worldStorage.getKeyWorldPrefix()) === 0) {

              Soomla.keyValueStorage.deleteKeyValue(key);
            }
          });
        }

      },

      save: function () {
        var key = this.DB_KEY_PREFIX + 'model';
        Soomla.keyValueStorage.setValue(key, JSON.stringify(this));
      }

    });

    Object.defineProperty(SoomlaLevelUp.prototype, 'initialWorld', {
      get: function () {
        return this.mainWorld;
      },
      set: function (initialWorld) {
        this.mainWorld = initialWorld;
      }
    });

    return SoomlaLevelUp;
  }();

  Soomla.soomlaLevelUp = SoomlaLevelUp.create();

  ///////////

  var GateStorage = Soomla.GateStorage = function () {
    /**
     @class
     @brief A utility class for persisting and querying the state of `Gate`s.
     Use this class to check if a certain `Gate` is open, or to open it.
     */
    return Soomla.declareClass('GateStorage', {
      DB_GATE_KEY_PREFIX: 'soomla.levelup.gates.',

      /**
       Determines if the given `Gate` is open.
       @param gate `Gate` to check if is open.
       @return If the given `Gate` is open returns `true`; otherwise, `false`.
       */
      isOpen: function (gate) {
        var key = this.keyGateOpen(gate.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0);
      },

      /**
       Sets the given `Gate` as open if the given parameter `open` is `true`;
       otherwise sets as closed.
       @param gate The `Gate` to open/close.
       @param open If set to `true` set the `Gate` to open;
       @param notify If set to `true` trigger event.
       */
      setOpen: function (gate, open, notify) {
        notify = notify || _.isUndefined(notify);

        var key = this.keyGateOpen(gate.itemId);

        if (open) {
          Soomla.keyValueStorage.setValue(key, 'yes');

          if (notify) {
            Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_GATE_OPENED, [gate]);
          }
        } else {
          Soomla.keyValueStorage.deleteKeyValue(key);

          if (notify) {
            Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_GATE_CLOSED, [gate]);
          }
        }
      },

      // private
      keyGatesWithGateId: function (gateId, postfix) {
        return this.DB_GATE_KEY_PREFIX + gateId + '.' + postfix;
      },

      keyGateOpen: function (gateId) {
        return this.keyGatesWithGateId(gateId, 'open');
      },

      getKeyGatePrefix: function () {
        return this.DB_GATE_KEY_PREFIX;
      }
    });
  }();

  var NativeGateStorage = Soomla.NativeGateStorage = function () {
    /**
     @class
     @brief A utility class for persisting and querying the state of `Gate`s.
     Use this class to check if a certain `Gate` is open, or to open it.
     */
    return Soomla.declareClass('NativeGateStorage', {
      /**
       Determines if the given `Gate` is open.
       @param gate `Gate` to check if is open.
       @return If the given `Gate` is open returns `true`; otherwise, `false`.
       */
      isOpen: function (gate) {
        return Soomla.levelUpBridge.gateIsOpen(gate);
      },

      /**
       Sets the given `Gate` as open if the given parameter `open` is `true`;
       otherwise sets as closed.
       @param gate The `Gate` to open/close.
       @param open If set to `true` set the `Gate` to open;
       @param notify If set to `true` trigger event.
       */
      setOpen: function (gate, open, notify) {
        notify = notify || _.isUndefined(notify);
        Soomla.levelUpBridge.gateSetOpen(gate, open, notify);
      }
    }, GateStorage);
  }();
  Soomla.gateStorage = Soomla.platform.isNativeSupported() ? NativeGateStorage.create() : GateStorage.create();

  var ScoreStorage = Soomla.ScoreStorage = function () {
    /**
     @class `CCScoreStorage`
     @brief A utility class for persisting and querying `Score`s and records.
     Use this class to get or set the values of `Score`s and records.
     */
    return Soomla.declareClass('ScoreStorage', {
      DB_SCORE_KEY_PREFIX: 'soomla.levelup.scores.',

      /**
       Sets the given `Score` to the given value.
       @param score `Score` to set.
       @param newValue The value to set for the `Score`.
       */
      setLatestScore: function (score, newValue) {
        var key = this.keyLatestScoreWithScoreId(score.itemId);
        Soomla.keyValueStorage.setValue(key, newValue);

        Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_LATEST_SCORE_CHANGED, [score]);
      },

      /**
       Retrieves the most recently saved value of the given `Score`.
       @param score Score whose most recent value it to be retrieved.
       @return Number The latest `Score`.
       */
      getLatestScore: function (score) {
        var key = this.keyLatestScoreWithScoreId(score.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseFloat(val) : -1;
      },

      /**
       Sets the given record for the given `Score`.
       @param score `Score` whose record is to change.
       @param newValue The new record.
       */
      setRecordScore: function (score, newValue) {
        var key = this.keyRecordScoreWithScoreId(score.itemId);
        Soomla.keyValueStorage.setValue(key, newValue);

        Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_SCORE_RECORD_CHANGED, [score]);
      },

      /**
       Retrieves the record of the given `Score`.
       @param score `Score` whose record is to be retrieved.
       @return Number The record value of the given `Score`.
       */
      getRecordScore: function (score) {
        var key = this.keyRecordScoreWithScoreId(score.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseFloat(val) : -1;
      },

      keyLatestScoreWithScoreId: function (scoreId) {
        return this.keyScoresWithScoreId(scoreId, "latest");
      },

      keyRecordScoreWithScoreId: function (scoreId) {
        return this.keyScoresWithScoreId(scoreId, "record");
      },

      keyScoresWithScoreId: function (scoreId, postfix) {
        return this.DB_SCORE_KEY_PREFIX + scoreId + '.' + postfix;
      },

      getKeyScorePrefix: function () {
        return this.DB_SCORE_KEY_PREFIX;
      }

    });
  }();

  var NativeScoreStorage = Soomla.NativeScoreStorage = function () {
    /**
     @class `CCScoreStorage`
     @brief A utility class for persisting and querying `Score`s and records.
     Use this class to get or set the values of `Score`s and records.
     */
    return Soomla.declareClass('NativeScoreStorage', {
      /**
       Sets the given `Score` to the given value.
       @param score `Score` to set.
       @param newValue The value to set for the `Score`.
       */
      setLatestScore: function (score, newValue) {
        Soomla.levelUpBridge.scoreSetLatestScore(score, newValue);
      },

      /**
       Retrieves the most recently saved value of the given `Score`.
       @param score Score whose most recent value it to be retrieved.
       @return The latest `Score`.
       */
      getLatestScore: function (score) {
        return Soomla.levelUpBridge.scoreGetLatestScore(score);
      },

      /**
       Sets the given record for the given `Score`.
       @param score `Score` whose record is to change.
       @param newValue The new record.
       */
      setRecordScore: function (score, newValue) {
        Soomla.levelUpBridge.scoreSetRecordScore(score, newValue);
      },

      /**
       Retrieves the record of the given `Score`.
       @param score `Score` whose record is to be retrieved.
       @return The record value of the given `Score`.
       */
      getRecordScore: function (score) {
        return Soomla.levelUpBridge.scoreGetRecordScore(score);
      }
    }, ScoreStorage);
  }();

  Soomla.scoreStorage = Soomla.platform.isNativeSupported() ? NativeScoreStorage.create() : ScoreStorage.create();

  var MissionStorage = Soomla.MissionStorage = function () {
    /**
     @class
     @brief A utility class for persisting and querying the state of `Mission`s.
     Use this class to check if a certain `Mission` is complete, or to set its
     completion status.
     */
    return Soomla.declareClass('MissionStorage', {

      DB_MISSION_KEY_PREFIX: 'soomla.levelup.missions.',

      /**
       Increases the number of times the given `Mission` has been completed
       if the given paramter `up` is `true`; otherwise decreases the number
       of times completed.
       @param mission `Mission` to set as completed.
       @param completed If set to `true` add 1 to the number of times completed,
       otherwise subtract 1.
       @param notify If set to `true` trigger the relevant event according
       to the value of `up`.
       */
      setCompleted: function setCompleted(mission, completed, notify) {
        notify = notify || _.isUndefined(notify);

        var total = this.getTimesCompleted(mission) + (completed ? 1 : -1);
        if (total < 0) {
          total = 0;
        }

        this.setTimesCompleted(mission, total);

        if (notify) {
          if (completed) {
            Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_MISSION_COMPLETED, [mission]);
          } else {
            Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_MISSION_COMPLETION_REVOKED, [mission]);
          }
        }
      },

      /**
       Determines if the given `Mission` is complete.
       @param mission `Mission` to determine if complete.
       @return Boolean If the given `Mission` is completed returns `true`;
       otherwise `false`.
       */
      isCompleted: function (mission) {
        return this.getTimesCompleted(mission) > 0;
      },

      /**
       Retrieves the number of times the given `Mission` has been completed.
       @param mission Mission.
       @return The number of times the given mission has been completed.
       */
      getTimesCompleted: function (mission) {
        var key = this.keyMissionTimesCompletedWithMissionId(mission.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseInt(val) : 0;
      },

      setTimesCompleted: function (mission, timesCompleted) {
        var key = this.keyMissionTimesCompletedWithMissionId(mission.itemId);
        Soomla.keyValueStorage.setValue(key, timesCompleted);
      },

      keyMissionTimesCompletedWithMissionId: function (missionId) {
        return this.keyMissionsWithMissionId(missionId, 'timesCompleted');
      },

      keyMissionsWithMissionId: function (missionId, postfix) {
        return this.DB_MISSION_KEY_PREFIX + missionId + '.' + postfix;
      },

      getKeyMissionPrefix: function () {
        return this.DB_MISSION_KEY_PREFIX;
      }
    });
  }();

  var NativeMissionStorage = Soomla.NativeMissionStorage = function () {
    /**
     @class
     @brief A utility class for persisting and querying the state of `Mission`s.
     Use this class to check if a certain `Mission` is complete, or to set its
     completion status.
     */
    return Soomla.declareClass('NativeMissionStorage', {
      /**
       Increases the number of times the given `Mission` has been completed
       if the given paramter `up` is `true`; otherwise decreases the number
       of times completed.
       @param mission `Mission` to set as completed.
       @param completed If set to `true` add 1 to the number of times completed,
       otherwise subtract 1.
       @param notify If set to `true` trigger the relevant event according
       to the value of `up`.
       */
      setCompleted: function setCompleted(mission, completed, notify) {
        notify = notify || _.isUndefined(notify);
        Soomla.levelUpBridge.missionSetCompleted(mission, completed, notify);
      },

      /**
       Retrieves the number of times the given `Mission` has been completed.
       @param mission Mission.
       @return The number of times the given mission has been completed.
       */
      getTimesCompleted: function (mission) {
        return Soomla.levelUpBridge.missionGetTimesCompleted(mission);
      }
    }, MissionStorage);
  }();

  Soomla.missionStorage = Soomla.platform.isNativeSupported() ? NativeMissionStorage.create() : MissionStorage.create();

  var WorldStorage = Soomla.WorldStorage = function () {
    /**
     @class `CCWorldStorage`
     @brief A utility class for persisting and querying `World`s.
     Use this class to get or set the completion of `World`s and assign rewards.
     */
    return Soomla.declareClass('WorldStorage', {
      DB_WORLD_KEY_PREFIX: 'soomla.levelup.worlds.',

      initLevelUp: function () {
        Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_LEVEL_UP_INITIALIZED);
      },

      /**
       Sets the given `World` as completed if `completed` is `true`.
       @param world `World` to set as completed.
       @param completed If set to `true` the `World` will be set
       as completed.
       @param notify If set to `true` trigger events.
       */
      setCompleted: function (world, completed, notify) {
        notify = notify || _.isUndefined(notify);

        var key = this.keyWorldCompletedWithWorldId(world.itemId);

        if (completed) {
          Soomla.keyValueStorage.setValue(key, 'yes');

          if (notify) {
            Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_WORLD_COMPLETED, [world]);
          }
        } else {
          Soomla.keyValueStorage.deleteKeyValue(key);
        }
      },

      /**
       Determines if the given `World` is completed.
       @param world `World` to determine if completed.
       @return If the given `World` is completed returns `true`;
       otherwise `false`.
       */
      isCompleted: function (world) {
        var key = this.keyWorldCompletedWithWorldId(world.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0);
      },

      /**
       Assigns the reward with the given reward ID to the given `World`.
       @param world `World` to assign a reward to.
       @param rewardId ID of reward to assign.
       */
      setReward: function (world, rewardId) {
        var key = this.keyRewardWithWorldId(world.itemId);

        if (rewardId && rewardId.length > 0) {
          Soomla.keyValueStorage.setValue(key, rewardId);
        } else {
          Soomla.keyValueStorage.deleteKeyValue(key);
        }
      },

      /**
       Retrieves the given `World`'s assigned reward.
       @param world `World` whose reward is to be retrieved.
       @return The assigned reward to retrieve.
       */
      getAssignedReward: function (world) {
        var key = this.keyRewardWithWorldId(world.itemId);
        return Soomla.keyValueStorage.getValue(key);
      },

      /**
       Sets the given inner world ID as the last completed inner world
       for the given `World`.
       @param world `World` to set inner completed world ID.
       @param innerWorldId the inner world ID that was last completed.
       */
      setLastCompletedInnerWorld: function (world, innerWorldId) {
        var key = this.keyLastCompletedInnerWorldWithWorldId(world.itemId);

        if (innerWorldId && innerWorldId.length > 0) {
          Soomla.keyValueStorage.setValue(key, innerWorldId);
        } else {
          Soomla.keyValueStorage.deleteKeyValue(key);
        }
      },

      /**
       Retrieves the given `World`'s last completed inner world.
       @param world `World` whose last completed inner world is to be retrieved.
       @return The last completed inner world ID.
       */
      getLastCompletedInnerWorld: function (world) {
        var key = this.keyLastCompletedInnerWorldWithWorldId(world.itemId);
        return Soomla.keyValueStorage.getValue(key);
      },

      keyWorldCompletedWithWorldId: function (worldId) {
        return this.keyWorldsWithWorldId(worldId, 'completed');
      },

      keyWorldsWithWorldId: function (worldId, postfix) {
        return this.DB_WORLD_KEY_PREFIX + worldId + '.' + postfix;
      },

      keyRewardWithWorldId: function (worldId) {
        return this.keyWorldsWithWorldId(worldId, 'assignedReward');
      },

      keyLastCompletedInnerWorldWithWorldId: function (worldId) {
        return this.keyWorldsWithWorldId(worldId, 'lastCompletedInnerWorld');
      },

      getKeyWorldPrefix: function () {
        return this.DB_WORLD_KEY_PREFIX;
      }
    });
  }();

  var NativeWorldStorage = Soomla.NativeWorldStorage = function () {
    /**
     @class `CCWorldStorage`
     @brief A utility class for persisting and querying `World`s.
     Use this class to get or set the completion of `World`s and assign rewards.
     */
    return Soomla.declareClass('NativeWorldStorage', {

      initLevelUp: function () {
        Soomla.LevelUpBridge.initShared();
        Soomla.levelUpBridge.initLevelUp();
      },

      /**
       Sets the given `World` as completed if `completed` is `true`.
       @param world `World` to set as completed.
       @param completed If set to `true` the `World` will be set
       as completed.
       @param notify If set to `true` trigger events.
       */
      setCompleted: function (world, completed, notify) {
        notify = notify || _.isUndefined(notify);

        Soomla.levelUpBridge.worldSetCompleted(world, completed, notify);
      },

      /**
       Determines if the given `World` is completed.
       @param world `World` to determine if completed.
       @return If the given `World` is completed returns `true`;
       otherwise `false`.
       */
      isCompleted: function (world) {
        return Soomla.levelUpBridge.worldIsCompleted(world);
      },

      /**
       Assigns the reward with the given reward ID to the given `World`.
       @param world `World` to assign a reward to.
       @param rewardId ID of reward to assign.
       */
      setReward: function (world, rewardId) {
        Soomla.levelUpBridge.worldSetReward(world, rewardId);
      },

      /**
       Retrieves the given `World`'s assigned reward.
       @param world `World` whose reward is to be retrieved.
       @return The assigned reward to retrieve.
       */
      getAssignedReward: function (world) {
        return Soomla.levelUpBridge.worldGetAssignedReward(world);
      },

      /**
       Sets the given inner world ID as the last completed inner world
       for the given `World`.
       @param world `World` to set inner completed world ID.
       @param innerWorldId the inner world ID that was last completed.
       */
      setLastCompletedInnerWorld: function (world, innerWorldId) {
        Soomla.levelUpBridge.worldSetLastCompletedInnerWorld(world, innerWorldId);
      },

      /**
       Retrieves the given `World`'s last completed inner world.
       @param world `World` whose last completed inner world is to be retrieved.
       @return The last completed inner world ID.
       */
      getLastCompletedInnerWorld: function (world) {
        return Soomla.levelUpBridge.worldGetLastCompletedInnerWorld(world);
      }

    }, WorldStorage);
  }();

  Soomla.worldStorage = Soomla.platform.isNativeSupported() ? NativeWorldStorage.create() : WorldStorage.create();

  var LevelStorage = Soomla.LevelStorage = function () {
    /**
     @class `CCLevelStorage`
     @brief A utility class for persisting and querying the state of `Level`s.
     Use this class to get or set information about a `Level`, such as the play
     duration, start or end time, etc.
     */
    return Soomla.declareClass('LevelStorage', {
      DB_LEVEL_KEY_PREFIX: 'soomla.levelup.levels.',

      /**
       Sets the slowest (given) duration for the given level.
       @param level `Level` to set slowest duration.</param>
       @param duration Duration to set.
       */
      setSlowestDurationMillis: function (level, duration) {
        var key = this.keySlowestDurationWithLevelId(level.itemId);
        Soomla.keyValueStorage.setValue(key, duration);
      },

      /**
       Retrieves the slowest duration for the given level.
       @param level `Level` to get slowest duration.
       @return Number The slowest duration of the given `Level`.
       */
      getSlowestDurationMillis: function (level) {
        var key = this.keySlowestDurationWithLevelId(level.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseInt(val) : 0;
      },

      /**
       Sets the fastest (given) duration for the given `Level`.
       @param level `Level` to set fastest duration.
       @param duration Duration to set.
       */
      setFastestDurationMillis: function (level, duration) {
        var key = this.keyFastestDurationWithLevelId(level.itemId);
        Soomla.keyValueStorage.setValue(key, duration);
      },

      /**
       Retrieves the fastest duration for the given `Level`.
       @param level `Level` to get fastest duration.
       @return The fastest duration of the given `Level`.
       */
      getFastestDurationMillis: function (level) {
        var key = this.keyFastestDurationWithLevelId(level.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseInt(val) : 0;
      },

      /**
       Increases by 1 the number of times the given `Level` has been started.
       @param level `Level` to increase its times started.
       @return Number The number of times started after increasing.
       */
      incTimesStarted: function (level) {
        var started = this.getTimesStarted(level);
        if (started < 0) { /* can't be negative */
          started = 0;
        }
        started++;

        this.setTimesStarted(level, started);

        // Notify level has started
        Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_LEVEL_STARTED, [level]);

        return started;
      },

      /**
       Decreases by 1 the number of times the given `Level` has been started.
       @param level `Level` to decrease its times started.
       @return Number The number of times started after decreasing.
       */
      decTimesStarted: function (level) {
        var started = this.getTimesStarted(level);
        if (started <= 0) { /* can't be negative or zero */
          started = 0;
        }
        started--;

        this.setTimesStarted(level, started);

        return started;
      },

      /**
       Retrieves the number of times this `Level` has been started.
       @param level `Level` whose times started is to be retrieved.
       @return Number The number of times started.
       */
      getTimesStarted: function (level) {
        var key = this.keyTimesStartedWithLevelId(level.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseInt(val) : 0;
      },

      /**
       Retrieves the number of times this `Level` has been played.
       @param level `Level` whose times played is to be retrieved.
       @return Number The number of times played.
       */
      getTimesPlayed: function (level) {
        var key = this.keyTimesPlayedWithLevelId(level.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseInt(val) : 0;
      },

      /**
       Increases by 1 the number of times the given `Level` has been played.
       @param level `Level` to increase its times played.
       @return Number The number of times played after increasing.
       */
      incTimesPlayed: function (level) {
        var played = this.getTimesPlayed(level);
        if (played < 0) { /* can't be negative */
          played = 0;
        }
        played++;

        this.setTimesPlayed(level, played);

        // Notify level has ended
        Soomla.fireSoomlaEvent(LevelUpConsts.EVENT_LEVEL_ENDED, [level]);

        return played;
      },

      /**
       Decreases by 1 the number of times the given `Level` has been played.
       @param level `Level` to decrease its times played.
       @return Number The number of times played after decreasing.
       */
      decTimesPlayed: function (level) {
        var played = this.getTimesPlayed(level);
        if (played <= 0) { /* can't be negative or zero */
          return 0;
        }
        played--;

        this.setTimesPlayed(level, played);
        return played;
      },

      /**
       Retrieves the number of times this `Level` has been completed.
       @param level `Level` whose times completed is to be retrieved.
       @return Number The number of times completed.
       */
      getTimesCompleted: function (level) {
        var key = this.keyTimesCompletedWithLevelId(level.itemId);
        var val = Soomla.keyValueStorage.getValue(key);
        return !!(val && val.length > 0) ? parseInt(val) : 0;
      },

      /**
       Increases by 1 the number of times the given `Level` has been completed.
       @param level `Level` to increase its times completed.
       @return Number The number of times completed after increasing.
       */
      incTimesCompleted: function (level) {
        var played = this.getTimesCompleted(level);
        if (played < 0) { /* can't be negative */
          played = 0;
        }
        played++;

        this.setTimesCompleted(level, played);

        return played;
      },

      /**
       Decreases by 1 the number of times the given `Level` has been completed.
       @param level `Level` to decrease its times completed.
       @return Number The number of times completed after decreasing.
       */
      decTimesCompleted: function (level) {
        var played = this.getTimesCompleted(level);
        if (played <= 0) { /* can't be negative or zero */
          played = 0;
        }
        played--;

        this.setTimesCompleted(level, played);

        return played;
      },

      // private
      setTimesStarted: function (level, started) {
        var key = this.keyTimesCompletedWithLevelId(level.itemId);
        Soomla.keyValueStorage.setValue(key, started);
      },

      setTimesPlayed: function (level, played) {
        var key = this.keyTimesPlayedWithLevelId(level.itemId);
        Soomla.keyValueStorage.setValue(key, played);
      },

      setTimesCompleted: function (level, timesCompleted) {
        var key = this.keyTimesCompletedWithLevelId(level.itemId);
        Soomla.keyValueStorage.setValue(key, timesCompleted);
      },

      keySlowestDurationWithLevelId: function (levelId) {
        return this.keyLevelsWithLevelId(levelId, "slowest");
      },

      keyFastestDurationWithLevelId: function (levelId) {
        return this.keyLevelsWithLevelId(levelId, "fastest");
      },

      keyTimesCompletedWithLevelId: function (levelId) {
        return this.keyLevelsWithLevelId(levelId, "timesCompleted");
      },

      keyTimesStartedWithLevelId: function (levelId) {
        return this.keyLevelsWithLevelId(levelId, "started");
      },

      keyTimesPlayedWithLevelId: function (levelId) {
        return this.keyLevelsWithLevelId(levelId, "played");
      },

      keyLevelsWithLevelId: function (levelId, postfix) {
        return this.DB_LEVEL_KEY_PREFIX + levelId + '.' + postfix;
      },

      getKeyLevelPrefix: function () {
        return this.DB_GATE_KEY_PREFIX;
      }

    });
  }();

  var NativeLevelStorage = Soomla.NativeLevelStorage = function () {
    /**
     @class `CCLevelStorage`
     @brief A utility class for persisting and querying the state of `Level`s.
     Use this class to get or set information about a `Level`, such as the play
     duration, start or end time, etc.
     */
    return Soomla.declareClass('NativeLevelStorage', {
      /**
       Sets the slowest (given) duration for the given level.
       @param level `Level` to set slowest duration.</param>
       @param duration Duration to set.
       */
      setSlowestDurationMillis: function (level, duration) {
        Soomla.levelUpBridge.levelSetSlowestDurationMillis(level, duration);
      },

      /**
       Retrieves the slowest duration for the given level.
       @return The slowest duration of the given `Level`.
       @param level `Level` to get slowest duration.
       */
      getSlowestDurationMillis: function (level) {
        return Soomla.levelUpBridge.levelGetSlowestDurationMillis(level);
      },

      /**
       Sets the fastest (given) duration for the given `Level`.
       @param level `Level` to set fastest duration.
       @param duration Duration to set.
       */
      setFastestDurationMillis: function (level, duration) {
        Soomla.levelUpBridge.levelSetFastestDurationMillis(level, duration);
      },

      /**
       Retrieves the fastest duration for the given `Level`.
       @param level `Level` to get fastest duration.
       @return The fastest duration of the given `Level`.
       */
      getFastestDurationMillis: function (level) {
        return Soomla.levelUpBridge.levelGetFastestDurationMillis(level);
      },

      /**
       Increases by 1 the number of times the given `Level` has been started.
       @param level `Level` to increase its times started.
       @return The number of times started after increasing.
       */
      incTimesStarted: function (level) {
        return Soomla.levelUpBridge.levelIncTimesStarted(level);
      },

      /**
       Decreases by 1 the number of times the given `Level` has been started.
       @param level `Level` to decrease its times started.
       @return The number of times started after decreasing.
       */
      decTimesStarted: function (level) {
        return Soomla.levelUpBridge.levelDecTimesStarted(level);
      },

      /**
       Retrieves the number of times this `Level` has been started.
       @param level `Level` whose times started is to be retrieved.
       @return The number of times started.
       */
      getTimesStarted: function (level) {
        return Soomla.levelUpBridge.levelGetTimesStarted(level);
      },

      /**
       Retrieves the number of times this `Level` has been played.
       @param level `Level` whose times played is to be retrieved.
       @return The number of times played.
       */
      getTimesPlayed: function (level) {
        return Soomla.levelUpBridge.levelGetTimesPlayed(level);
      },

      /**
       Increases by 1 the number of times the given `Level` has been played.
       @param level `Level` to increase its times played.
       @return The number of times played after increasing.
       */
      incTimesPlayed: function (level) {
        return Soomla.levelUpBridge.levelIncTimesPlayed(level);
      },

      /**
       Decreases by 1 the number of times the given `Level` has been played.
       @param level `Level` to decrease its times played.
       @return The number of times played after decreasing.
       */
      decTimesPlayed: function (level) {
        return Soomla.levelUpBridge.levelDecTimesPlayed(level);
      },

      /**
       Retrieves the number of times this `Level` has been completed.
       @param level `Level` whose times completed is to be retrieved.
       @return The number of times completed.
       */
      getTimesCompleted: function (level) {
        return Soomla.levelUpBridge.levelGetTimesCompleted(level);
      },

      /**
       Increases by 1 the number of times the given `Level` has been completed.
       @param level `Level` to increase its times completed.
       @return The number of times completed after increasing.
       */
      incTimesCompleted: function (level) {
        return Soomla.levelUpBridge.levelIncTimesCompleted(level);
      },

      /**
       Decreases by 1 the number of times the given `Level` has been completed.
       @param level `Level` to decrease its times completed.
       @return The number of times completed after decreasing.
       */
      decTimesCompleted: function (level) {
        return Soomla.levelUpBridge.levelDecTimesCompleted(level);
      }
    }, NativeLevelStorage);
  }();

  Soomla.levelStorage = Soomla.platform.isNativeSupported() ? NativeLevelStorage.create() : LevelStorage.create();


  var LevelUpEventDispatcher = Soomla.LevelUpEventDispatcher = function () {

    var LevelUpEventDispatcher = Soomla.declareClass('LevelUpEventDispatcher', {
      init: function () {
        var eventDispatcher = Soomla.soomlaEventDispatcher;

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_LEVEL_UP_INITIALIZED, _.bind(function (parameters) {
          Soomla.fireSoomlaEvent(parameters.method, []);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_LATEST_SCORE_CHANGED, _.bind(function (parameters) {
          var score = Soomla.soomlaLevelUp.getScore(parameters.scoreId);
          Soomla.fireSoomlaEvent(parameters.method, [score]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_SCORE_RECORD_REACHED, _.bind(function (parameters) {
          var score = Soomla.soomlaLevelUp.getScore(parameters.scoreId);
          Soomla.fireSoomlaEvent(parameters.method, [score]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_SCORE_RECORD_CHANGED, _.bind(function (parameters) {
          var score = Soomla.soomlaLevelUp.getScore(parameters.scoreId);
          Soomla.fireSoomlaEvent(parameters.method, [score]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_GATE_OPENED, _.bind(function (parameters) {
          var gate = Soomla.soomlaLevelUp.getGate(parameters.gateId);
          Soomla.fireSoomlaEvent(parameters.method, [gate]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_GATE_CLOSED, _.bind(function (parameters) {
          var gate = Soomla.soomlaLevelUp.getGate(parameters.gateId);
          Soomla.fireSoomlaEvent(parameters.method, [gate]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_MISSION_COMPLETED, _.bind(function (parameters) {
          var mission = Soomla.soomlaLevelUp.getMission(parameters.missionId);
          Soomla.fireSoomlaEvent(parameters.method, [mission]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_MISSION_COMPLETION_REVOKED, _.bind(function (parameters) {
          var mission = Soomla.soomlaLevelUp.getMission(parameters.missionId);
          Soomla.fireSoomlaEvent(parameters.method, [mission]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_WORLD_COMPLETED, _.bind(function (parameters) {
          var world = Soomla.soomlaLevelUp.getWorld(parameters.worldId);
          Soomla.fireSoomlaEvent(parameters.method, [world]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED, _.bind(function (parameters) {
          var world = Soomla.soomlaLevelUp.getWorld(parameters.worldId);
          var innerWorldId = parameters.innerWorldId;
          Soomla.fireSoomlaEvent(parameters.method, [world, innerWorldId]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_WORLD_REWARD_ASSIGNED, _.bind(function (parameters) {
          var world = Soomla.soomlaLevelUp.getWorld(parameters.worldId);
          Soomla.fireSoomlaEvent(parameters.method, [world]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_LEVEL_STARTED, _.bind(function (parameters) {
          var level = Soomla.soomlaLevelUp.getWorld(parameters.levelId);
          Soomla.fireSoomlaEvent(parameters.method, [level]);
        }, this));

        eventDispatcher.registerEventHandler(LevelUpConsts.EVENT_LEVEL_ENDED, _.bind(function (parameters) {
          var level = Soomla.soomlaLevelUp.getWorld(parameters.levelId);
          Soomla.fireSoomlaEvent(parameters.method, [level]);
        }, this));

        return true;
      }
    });

    LevelUpEventDispatcher.initShared = function () {
      var ret = LevelUpEventDispatcher.create();
      if (ret.init()) {
        Soomla.levelUpEventDispatcher = ret;
      } else {
        Soomla.levelUpEventDispatcher = null;
      }
    };

    return LevelUpEventDispatcher;
  }();

  /**
   * LevelUpEventHandler
   * Here for documentation reasons only, shows signatures for level up event handlers
   */
  var LevelUpEventHandler = Soomla.LevelUpEventHandler = function () {
    return Soomla.declareClass("LevelUpEventHandler", {
      /**
       * Fired when initialization has been completed.
       * Event Name - Soomla.LevelUpConsts.EVENT_LEVEL_UP_INITIALIZED
       */
      onLevelUpInitialized: function () {
      },

      /**
       * Fired when a Gate has been opened.
       * Event Name - Soomla.LevelUpConsts.EVENT_GATE_OPENED
       * @param gate The gate which was opened
       */
      onGateOpened: function (gate) {
      },
      /**
       * Fired when a CCGate has been closed.
       * Event Name - Soomla.LevelUpConsts.EVENT_GATE_CLOSED
       * @param gate The gate which was closed
       */
      onGateClosed: function (gate) {
      },

      /**
       * Fired when a CCMission has been completed.
       * Event Name - Soomla.LevelUpConsts.EVENT_MISSION_COMPLETED
       * @param mission the mission that was completed.
       */
      onMissionCompleted: function (mission) {
      },

      /**
       * Fired when CCMission completion has been revoked.
       * For example, you can decide to revoke a mission if the condition for completing it is no longer valid
       * Event Name - Soomla.LevelUpConsts.EVENT_MISSION_COMPLETION_REVOKED
       * @param mission the mission to be revoked.
       */
      onMissionCompletionRevoked: function (mission) {
      },

      /**
       * Fired when a latest score is changed.
       * Event Name - Soomla.LevelUpConsts.EVENT_SCORE_RECORD_CHANGED
       * @param score the score which has been changed.
       */
      onLatestScoreChanged: function (score) {
      },

      /**
       * Fired when a new record has been reached for a score.
       * Event Name - Soomla.LevelUpConsts.EVENT_SCORE_RECORD_REACHED
       * @param score the score which has reached a new record.
       */
      onScoreRecordReached: function (score) {
      },

      /**
       * Fired when a score's record is changed.
       * Event Name - Soomla.LevelUpConsts.EVENT_SCORE_RECORD_CHANGED
       * @param score the score which has been changed.
       */
      onScoreRecordChanged: function (score) {
      },

      /**
       * Fired when a CCWorld has been completed.
       * Event Name - Soomla.LevelUpConsts.EVENT_WORLD_COMPLETED
       * @param world the world which was completed.
       */
      onWorldCompleted: function (world) {
      },

      /**
       * Fired when the last completed world inside a world has changed.
       * Event Name - Soomla.LevelUpConsts.EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED
       * @param world the world which had last completed world changed.
       * @param innerWorldId  The inner world ID which was last completed.
       */
      onLastCompletedInnerWorldChanged: function (world, innerWorldId) {
      },

      /**
       * Fired when a CCWorld is being assigned a reward.
       * Event Name - Soomla.LevelUpConsts.EVENT_WORLD_REWARD_ASSIGNED
       * @param world the World whose reward has changed.
       */
      onWorldRewardAssigned: function (world) {
      },

      /**
       * Fired when a level has started, i.e. when start is called on an instance of Level
       * Event Name - Soomla.LevelUpConsts.EVENT_GOOD_BALANCE_CHANGED
       * @param level the level which just started.
       */
      onLevelStarted: function (level) {
      },

      /**
       * Fired when a level has ended, i.e. when end is called on an instance of Level
       * Event Name - Soomla.LevelUpConsts.EVENT_LEVEL_ENDED
       * @param level the level which just ended.
       */
      onLevelEnded: function (level) {
      }
    });
  }();

  return true;
})();