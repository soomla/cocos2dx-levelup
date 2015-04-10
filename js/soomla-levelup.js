/**
 * Created by vedi on 09/04/15.
 */

(function () {

  /**
   * LevelUpConsts
   */
  var LevelUpConsts = Soomla.Models.LevelUpConsts = {
    EVENT_LEVEL_UP_INITIALIZED: "CCLevelUpEventHandler::onLevelUpInitialized",
    EVENT_SCORE_RECORD_CHANGED: "CCLevelUpEventHandler::onScoreRecordChanged",
    EVENT_SCORE_RECORD_REACHED: "CCLevelUpEventHandler::onScoreRecordReached",
    EVENT_LATEST_SCORE_CHANGED: "CCLevelUpEventHandler::onLatestScoreChanged",
    EVENT_GATE_OPENED: "CCLevelUpEventHandler::onGateOpened",
    EVENT_GATE_CLOSED: "CCLevelUpEventHandler::onGateClosed",
    EVENT_MISSION_COMPLETED: "CCLevelUpEventHandler::onMissionCompleted",
    EVENT_MISSION_COMPLETION_REVOKED: "CCLevelUpEventHandler::onMissionCompletionRevoked",
    EVENT_WORLD_COMPLETED: "CCLevelUpEventHandler::onWorldCompleted",
    EVENT_WORLD_LAST_COMPLETED_INNER_WORLD_CHANGED: "CCLevelUpEventHandler::onLastCompletedInnerWorldChanged",
    EVENT_WORLD_REWARD_ASSIGNED: "CCLevelUpEventHandler::onWorldRewardAssigned",
    EVENT_LEVEL_STARTED: "CCLevelUpEventHandler::onLevelStarted",
    EVENT_LEVEL_ENDED: "CCLevelUpEventHandler::onLevelEnded"
  };

  // Gates

  var Gate = Soomla.Models.Gate = function () {
    return Soomla.declareClass("Gate", {

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
       @return If this `Gate` can be opened returns `true`; otherwise, `false`.
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
    var GatesList = Soomla.declareClass("GatesList", {
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
    Object.defineProperty(GatesList.prototype, "gates", {
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
    var GatesListAnd = Soomla.declareClass("GatesListAND", {
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
    var GatesListOr = Soomla.declareClass("GatesListOR", {
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
    var RecordGate = Soomla.declareClass("Gate", {
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
          logError("(canOpenInner) couldn't find score with scoreId: ", this.associatedScoreId);
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

        if (score.id === this.associatedScoreId &&
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
    var ScheduleGate = Soomla.declareClass("ScheduleGate", {
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
    var WorldCompletionGate = Soomla.declareClass("WorldCompletionGate", {
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

        if (world.id === this.associatedWorldId) {
          this.forceOpen(true);
        }
      }
    });
    return Gate;
  }();

  // Profile Gates

  /**
   NOTE: Social `Gate`s require the user to perform a specific social
   action in order to open the `Gate`. Currently, the social provider that's
   available is Facebook, so the `Gates`s are FB-oriented. In the future,
   more social providers will be added.

   This is an abstract class that all social `Gate`s must implement.
   */
  var SocialActionGate = Soomla.Models.SocialActionGate = function () {
    var SocialActionGate = Soomla.declareClass("SocialActionGate", {
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

        if (payload === this.id) {
          this.forceOpen(true);
        }
      }
    }, Gate);
    return SocialActionGate;
  }();

  /**
   NOTE: Social `Gate`s require the user to perform a specific social action
   in order to open the `Gate`. Currently, the social provider that's
   available is Facebook, so the `Gates`s are FB-oriented. In the future,
   more social providers will be added.

   A specific type of `Gate` that has an associated page name.
   The `Gate` opens once the player "Likes" the associated page.
   */
  var SocialLikeGate = Soomla.Models.SocialLikeGate = function () {
    var SocialLikeGate = Soomla.declareClass("SocialLikeGate", {
      pageName: null,

      /**
       Opens this `Gate` by "liking" the associated page.
       @return Boolean If the page was successfully "liked" returns `true`; otherwise
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

  /**
   NOTE: Social `Gate`s require the user to perform a specific social
   action in order to open the `Gate`. Currently, the social provider that's
   available is Facebook, so the `Gates`s are FB-oriented. In the future,
   more social providers will be added.

   A specific type of `Gate` that has an associated status. The `Gate`
   is opened once the player posts the status.
   */
  var SocialStatusGate = Soomla.Models.SocialStatusGate = function () {
    var SocialStatusGate = Soomla.declareClass("SocialStatusGate", {
      status: null,

      /**
       Opens this `Gate` by posting the associated status.
       @return Boolean If the status was successfully posted returns `true`;
       otherwise `false`.
       */
      openInner: function openInner() {
        if (this.canOpen()) {
          Soomla.soomlaProfile.updateStatus(this.provide, this.id, this.status);
          return true;
        }
        return false;
      }
    }, SocialActionGate);
    return SocialStatusGate;
  }();

  /**
   NOTE: Social `Gate`s require the user to perform a specific social action
   in order to open the `Gate`. Currently, the social provider that's
   available is Facebook, so the `Gates`s are FB-oriented. In the future,
   more social providers will be added.

   A specific type of `Gate` that has an associated story. The `Gate`
   is opened once the player posts the story.
   */
  var SocialStoryGate = Soomla.Models.SocialStoryGate = function () {
    var SocialStoryGate = Soomla.declareClass("SocialStoryGate", {
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
        Soomla.soomlaProfile.updateStory(this.provider,this.message, this.storyName, this.caption, "",
          this.link, this.id, this.imgUrl);
      }
    }, SocialActionGate);
    return SocialStoryGate;
  }();

  /**
   NOTE: Social `Gate`s require the user to perform a specific social
   action in order to open the `Gate`. Currently, the social provider that's
   available is Facebook, so the `Gates`s are FB-oriented. In the future,
   more social providers will be added.

   A specific type of `Gate` that has an associated image. The `Gate`
   is opened once the player uploads the image.
   */
  var SocialUploadGate = Soomla.Models.SocialUploadGate = function () {
    var SocialUploadGate = Soomla.declareClass("SocialUploadGate", {
      message: null,
      fileName: null,

      /**
       Opens this `Gate` by uploading the associated image.
       @return boolean If the image was successfully uploaded returns `true`;
       otherwise `false`.
       */
      openInner: function openInner() {
        if (this.canOpen()) {
          Soomla.soomlaProfile.uploadImage(this.provider, this.id, this.message, this.fileName);
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
    var BalanceGate = Soomla.declareClass("BalanceGate", {
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
    var PurchasableGate = Soomla.declareClass("PurchasableGate", {
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
        Soomla.storeInventory.buyItem(this.associatedItemId, this.id);
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

        if (purchasableVirtualItem.itemId === this.associatedItemId && payload === this.id) {
          this.forceOpen(true)
        }
      }
    }, Gate);
    return PurchasableGate;
  }();

  ///////////

  //var Gate = Soomla.Models.Gate = function () {
  //  var Gate = Soomla.declareClass("Gate", {});
  //  return Gate;
  //}();
  //

  var GateStorage = Soomla.GateStorage = Soomla.declareClass("GateStorage", {});
  Soomla.gateStorage = GateStorage.create();

  var SoomlaLevelUp = Soomla.SoomlaLevelUp = Soomla.declareClass("SoomlaLevelUp", {});
  Soomla.soomlaLevelUp = SoomlaLevelUp.create();


  return true;
})();