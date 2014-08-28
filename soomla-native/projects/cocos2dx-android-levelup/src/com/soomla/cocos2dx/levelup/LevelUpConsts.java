package com.soomla.cocos2dx.levelup;

/**
 * @author vedi
 *         date 6/9/14
 *         time 6:49 PM
 */
public class LevelUpConsts {

    public static final String JSON_JSON_TYPE_MISSION = "mission";
    public static final String JSON_JSON_TYPE_BALANCE_MISSION = "balanceMission";
    public static final String JSON_JSON_TYPE_CHALLENGE = "challenge";
    public static final String JSON_JSON_TYPE_PURCHASE_MISSION = "purchaseMission";
    public static final String JSON_JSON_TYPE_RECORD_MISSION = "recordMission";
    public static final String JSON_JSON_TYPE_WORLD_COMPLETION_MISSION = "worldCompletionMission";

    public static final String JSON_JSON_TYPE_GATE = "gate";
    public static final String JSON_JSON_TYPE_BALANCE_GATE = "balanceGate";
    public static final String JSON_JSON_TYPE_GATES_LIST_AND = "gatesListAnd";
    public static final String JSON_JSON_TYPE_GATES_LIST_OR = "gatesListOr";
    public static final String JSON_JSON_TYPE_PURCHASABLE_GATE = "purchasableGate";
    public static final String JSON_JSON_TYPE_RECORD_GATE = "recordGate";
    public static final String JSON_JSON_TYPE_SCHEDULE_GATE = "scheduleGate";
    public static final String JSON_JSON_TYPE_WORLD_COMPLETION_GATE = "worldCompletionGate";

    public static final String JSON_JSON_TYPE_SCORE = "score";

    public static final String JSON_JSON_TYPE_WORLD = "world";
    public static final String JSON_JSON_TYPE_LEVEL = "level";

    public static final String EVENT_SCORE_RECORD_REACHED = "CCLevelUpEventHandler::onScoreRecordReached";
    public static final String EVENT_SCORE_RECORD_CHANGED = "CCLevelUpEventHandler::onScoreRecordChanged";
    public static final String EVENT_GATE_OPENED = "CCLevelUpEventHandler::onGateOpened";
    public static final String EVENT_MISSION_COMPLETED = "CCLevelUpEventHandler::onMissionCompleted";
    public static final String EVENT_MISSION_COMPLETION_REVOKED = "CCLevelUpEventHandler::onMissionCompletionRevoked";
    public static final String EVENT_WORLD_COMPLETED = "CCLevelUpEventHandler::onWorldCompleted";
    public static final String EVENT_WORLD_REWARD_ASSIGNED = "CCLevelUpEventHandler::onWorldRewardAssigned";
    public static final String EVENT_LEVEL_STARTED = "CCLevelUpEventHandler::onLevelStarted";
    public static final String EVENT_LEVEL_ENDED = "CCLevelUpEventHandler::onLevelEnded";
}
