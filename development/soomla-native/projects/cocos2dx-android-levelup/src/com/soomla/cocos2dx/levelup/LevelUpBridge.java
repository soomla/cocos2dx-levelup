package com.soomla.cocos2dx.levelup;

import android.opengl.GLSurfaceView;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.levelup.data.*;
import org.json.JSONObject;

/**
 * @author vedi
 *         date 6/10/14
 *         time 11:08 AM
 */
public class LevelUpBridge {

    private static LevelUpBridge INSTANCE = null;

    public static LevelUpBridge getInstance() {
        if (INSTANCE == null) {
            synchronized (LevelUpBridge.class) {
                if (INSTANCE == null) {
                    INSTANCE = new LevelUpBridge();
                }
            }
        }
        return INSTANCE;
    }

    @SuppressWarnings("FieldCanBeLocal")
    private LevelUpEventHandlerBridge levelUpEventHandlerBridge;

    public LevelUpBridge() {
        levelUpEventHandlerBridge = new LevelUpEventHandlerBridge();

        final NdkGlue ndkGlue = NdkGlue.getInstance();

        ndkGlue.registerCallHandler("CCLevelUpBridge::initLevelUp", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                LevelUpBridge.getInstance().init();
                WorldStorage.initLevelUp();
                retParams.put("return", true);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::gateIsOpen", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String gateId = params.getString("gateId");
                retParams.put("return", GateStorage.isOpen(gateId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::gateSetOpen", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String gateId = params.getString("gateId");
                boolean open = params.getBoolean("open");
                boolean notify = params.getBoolean("notify");
                GateStorage.setOpen(gateId, open, notify);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelSetSlowestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                long duration = params.getLong("duration");
                LevelStorage.setSlowestDurationMillis(levelId, duration);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelGetSlowestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getSlowestDurationMillis(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelSetFastestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                long duration = params.getLong("duration");
                LevelStorage.setFastestDurationMillis(levelId, duration);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelGetFastestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getFastestDurationMillis(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelIncTimesStarted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.incTimesStarted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelDecTimesStarted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.decTimesStarted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelGetTimesStarted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getTimesStarted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelGetTimesPlayed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getTimesPlayed(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelIncTimesPlayed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.incTimesPlayed(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelDecTimesPlayed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.decTimesPlayed(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelGetTimesCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getTimesCompleted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelIncTimesCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.incTimesCompleted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::levelDecTimesCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.decTimesCompleted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::missionSetCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String missionId = params.getString("missionId");
                boolean completed = params.getBoolean("completed");
                boolean notify = params.getBoolean("notify");
                MissionStorage.setCompleted(missionId, completed, notify);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::missionGetTimesCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String missionId = params.getString("missionId");
                retParams.put("return", MissionStorage.getTimesCompleted(missionId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::scoreSetLatestScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                double newValue = params.getDouble("newValue");
                ScoreStorage.setLatestScore(scoreId, newValue);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::scoreGetLatestScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                retParams.put("return", ScoreStorage.getLatestScore(scoreId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::scoreSetRecordScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                double newValue = params.getDouble("newValue");
                ScoreStorage.setRecordScore(scoreId, newValue);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::scoreGetRecordScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                retParams.put("return", ScoreStorage.getRecordScore(scoreId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::worldSetCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                boolean completed = params.getBoolean("completed");
                boolean notify = params.getBoolean("notify");
                WorldStorage.setCompleted(worldId, completed, notify);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::worldIsCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                retParams.put("return", WorldStorage.isCompleted(worldId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::worldSetReward", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                String rewardId = params.getString("rewardId");
                WorldStorage.setReward(worldId, rewardId);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::worldGetAssignedReward", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                retParams.put("return", WorldStorage.getAssignedReward(worldId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::worldSetLastCompletedInnerWorld", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                String innerWorldId = params.getString("innerWorldId");
                WorldStorage.setLastCompletedInnerWorld(worldId, innerWorldId);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpBridge::worldGetLastCompletedInnerWorld", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                retParams.put("return", WorldStorage.getLastCompletedInnerWorld(worldId));
            }
        });

    }

    public void init() {
        final GLSurfaceView glSurfaceView = NdkGlue.getInstance().getGlSurfaceRef().get();
        if (glSurfaceView != null) {
            levelUpEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }
    }
}
