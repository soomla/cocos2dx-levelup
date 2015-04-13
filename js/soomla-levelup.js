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
        logError('IMPLEMENT ME!');
      },

      /**
       Unregisters relevant events. Each specific type of `Gate` must
       implement this method.
       */
      unregisterEvents: function unregisterEvents() {
        logError('IMPLEMENT ME!');
      },

      /**
       Checks if this `Gate` meets its criteria for opening.
       Each specific type of `Gate` must implement this method to add
       specific `Gate` criteria.
       @return If the criteria is met for opening this `Gate` returns `true`;
       otherwise `false`.
       */
      canOpenInner: function canOpenInner() {
        logError('IMPLEMENT ME!');
      },

      /**
       Opens this `Gate`.
       @return If this `Gate` was opened returns `true`; otherwise `false`.
       */
      openInner: function openInner() {
        logError('IMPLEMENT ME!');
      }
    }, SoomlaEntity);
  }();

  var GatesList = Soomla.Models.Gate = function () {
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

      onGateOpened: function onGateOpened(event) {
        var gate = event.gate; // TODO: check this field
        if (!gate) {
          logError('No gate data in event');
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
    var GatesListAnd = Soomla.declareClass('GatesListAND', {
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
    var GatesListOr = Soomla.declareClass('GatesListOR', {
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
       @return boolean If the `Gate` can be opened returns `true`; otherwise `false`.
       */
      canOpenInner: function canOpenInner() {
        var score = Soomla.soomlaLevelUp.getScore(this.associatedScoreId);
        if (!score) {
          logError('(canOpenInner) couldn\'t find score with scoreId: ', this.associatedScoreId);
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
      onScoreRecordChanged: function onScoreRecordChanged(event) {
        var score = event.score; // TODO: check this field
        if (!score) {
          logError('No score data in event');
          return;
        }

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
    });
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

      onWorldCompleted: function (event) {
        var world = event.world; // TODO: check this field
        if (!world) {
          logError('No world data in event');
          return;
        }

        if (world.itemId === this.associatedWorldId) {
          this.forceOpen(true);
        }
      }
    });
    return Gate;
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
      provider: Soomla.Models.Provider.FACEBOOK, // TODO: Solve convertion <-> providerId
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
          Soomla.addEventHandler(ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED, this.onSocialActionFinishedEvent, this);
          this.eventListener = true;
        }
      },

      /**
       Unregisters relevant events: social-action-finished event.
       */
      unregisterEvents: function () {
        if (!this.isOpen()) {
          Soomla.removeEventHandler(ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED, this.onSocialActionFinishedEvent);
          this.eventListener = true;
        }
      },

      onSocialActionFinishedEvent: function (event) {
        var payload = event.payload; // TODO: check this field
        if (!payload) {
          logError('No payload data in event');
          return;
        }

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
          logError('(canOpenInner) Couldn\'t find itemId. itemId: ' + this.associatedItemId);
          logError(error.info);
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
      onCurrencyBalanceChanged: function (event) {
        var virtualCurrency = event['VirtualCurrency']; // TODO: check this field
        if (!virtualCurrency) {
          logError('No virtualCurrency data in event');
          return;
        }

        var balance = event.balance;
        if (!balance) {
          logError('No balance data in event');
          return;
        }
        this.checkItemIdBalance(virtualCurrency.itemId, balance);
      },

      /**
       Opens this `Gate` if the good-balance changed event causes the `Gate`'s
       criteria to be met.
       */
      onGoodBalanceChanged: function (event) {
        var virtualGood = event['VirtualGood']; // TODO: check this field
        if (!virtualGood) {
          logError('No virtualGood data in event');
          return;
        }

        var balance = event.balance;
        if (!balance) {
          logError('No balance data in event');
          return;
        }
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
       @return Always `true`.
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

      onItemPurchased: function (event) {
        var purchasableVirtualItem = event['PurchasableVirtualItem']; // TODO: check this field
        if (!purchasableVirtualItem) {
          logError('No purchasableVirtualItem data in event');
          return;
        }

        var payload = event['DeveloperPayload'];
        if (!payload) {
          logError('No payload data in event');
          return;
        }

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
      startValue: null,
      higherBetter: null,

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
       @return If this score has reached the given record returns `true`;
       otherwise `false`.
       @param scoreVal numeric score value.
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
        Soomla.scoreStorage.getRecordScore(this);
      },

      /**
       Retrieves the most recently saved value of this `Score`.
       @return The latest score.
       */
      getLatest: function () {
        Soomla.scoreStorage.getLatestScore(this);
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

    }, SoomlaEntity);

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

        this.__super__.inc(amount);
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

        this.__super__.dec(amount);
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

        this.__super__.setTempScore(score, onlyIfBetter);
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
        this.__super__.performSaveActions();

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
       @return If `Schedule` doesn't approve, the mission cannot be completed
       and thus returns `false`; otherwise opens this `Mission`'s `Gate` and
       returns Boolean `true` if successful.
       */
      complete: function () {
        if (!this.schedule.approve(Soomla.missionStorage.getTimesCompleted(this))) {
          logDebug('missions cannot be completed b/c Schedule doesn\'t approve.');
          return false;
        }
        logDebug('trying opening gate to complete mission: ' + this.itemId);
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

      onGateOpened: function (event) {
        var gate = event.gate; // TODO: check this field
        if (!gate) {
          logError('No gate data in event');
          return;
        }

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

    }, SoomlaEntity);

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
        this.__super__.onCreate();
        if (!this.gate) {
          this.gate = RecordGate.create({
            itemId: this.autoGateId(),
            associatedScoreId: this.associatedScoreId,
            desiredRecord: this.desiredRecord
          });
        }
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
        this.__super__.onCreate();
        if (!this.gate) {
          this.gate = WorldCompletionGate.create({
            itemId: this.autoGateId(),
            associatedWorldId: this.associatedWorldId
          });
        }
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
        logDebug ('registerEvents called');
        if (!this.isCompleted()) {
          logDebug ('registering!');
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

      onMissionCompleted: function (event) {
        var completedMission = event.mission; // TODO: check this field
        if (!completedMission) {
          logError('No mission data in event');
          return;
        }

        logDebug ('onMissionCompleted');

        if (_.indexOf(this.missions, completedMission) >= 0) {
          logDebug('Mission ' + completedMission.itemId + ' is part of challenge ' + this.itemId + ' (' + this.missions.length + ') total');
          var completed = true;
          var incompletedMission = _.find(this.missions, function (mission) {
            return !mission.isCompleted();
          });
          if (incompletedMission) {
            logDebug('challenge mission not completed?=' + incompletedMission.itemId);
            completed = false;
          }

          if (completed) {
            logDebug('Challenge ' + this.itemId + ' completed!');
            this.setCompletedInner(true);
          }
        }
      },

      onMissionCompletionRevoked: function (event) {
        var mission = event.mission; // TODO: check this field
        if (!mission) {
          logError('No mission data in event');
          return;
        }
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
        this.__super__.onCreate();
        if (!this.gate) {
          this.gate = SocialLikeGate.create({
            itemId: this.autoGateId(),
            provider: this.provider,
            pageName: this.pageName
          });
        }
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
        this.__super__.onCreate();
        if (!this.gate) {
          this.gate = SocialStatusGate.create({
            itemId: this.autoGateId(),
            provider: this.provider,
            status: this.status
          });
        }
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
        this.__super__.onCreate();
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
        this.__super__.onCreate();
        if (!this.gate) {
          this.gate = SocialUploadGate.create({
            itemId: this.autoGateId(),
            provider: this.provider,
            message: this.message,
            fileName: this.fileName
          });
        }
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
        this.__super__.onCreate();
        if (!this.gate) {
          this.gate = BalanceGate.create({
            itemId: this.autoGateId(),
            associatedItemId: this.associatedItemId,
            desiredBalance: this.desiredBalance
          });
        }
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
        this.__super__.onCreate();
        if (!this.gate) {
          this.gate = PurchasableGate.create({
            itemId: this.autoGateId(),
            associatedItemId: this.associatedItemId
          });
        }
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
       @param scoreTemplate `Score` template for the `Level`s.
       @param missionTemplate `Mission` template for the `Level`s.
       */
      batchAddLevelsWithTemplates: function (numLevels, gateTemplate, scoreTemplates, missionTemplates) {
        if (!_.isArray(scoreTemplates)) {
          scoreTemplates = [scoreTemplates];
        }
        if (!_.isArray(missionTemplates)) {
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
        if (!_.isArray(scoreTemplates)) {
          scoreTemplates = [scoreTemplates];
        }
        if (!_.isArray(missionTemplates)) {
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
          logError('(ResetScores) You don\'t have any scores defined in this world. World id: ' + this.itemId);
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
       */
      setScoreValue: function (id, scoreVal, onlyIfBetter) {
        onlyIfBetter = !!onlyIfBetter;

        var score = this._scores[id];
        if (!score) {
          logError('(setScore) Can\'t find score id: ' + id + ' world id: ' + this.itemId);
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
        Soomla.worldStorage.getAssignedReward(this);
      },

      /**
       Retrieves the last completed inner world ID.
       @return The the last completed inner world ID.
       */
      getLastCompletedInnerWorld: function () {
        Soomla.worldStorage.getLastCompletedInnerWorld(this);
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

      sumInnerWorldsRecords: function () {
        return _.reduce(this._innerWorldsMap, function (sum, world) {
          return sum + world.getSingleScore().getRecord();
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
      }

    }, SoomlaEntity);

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
    });

    return World;
  }();


  ///////////

  //var Gate = Soomla.Models.Gate = function () {
  //  var Gate = Soomla.declareClass('Gate', {});
  //  return Gate;
  //}();


  var GateStorage = Soomla.GateStorage = Soomla.declareClass('GateStorage', {});
  Soomla.gateStorage = GateStorage.create();

  var ScoreStorage = Soomla.ScoreStorage = Soomla.declareClass('ScoreStorage', {});
  Soomla.scoreStorage = ScoreStorage.create();

  var MissionStorage = Soomla.MissionStorage = Soomla.declareClass('MissionStorage', {});
  Soomla.missionStorage = MissionStorage.create();

  var WorldStorage = Soomla.WorldStorage = Soomla.declareClass('WorldStorage', {});
  Soomla.worldStorage = WorldStorage.create();

  var SoomlaLevelUp = Soomla.SoomlaLevelUp = Soomla.declareClass('SoomlaLevelUp', {});
  Soomla.soomlaLevelUp = SoomlaLevelUp.create();


  return true;
})();