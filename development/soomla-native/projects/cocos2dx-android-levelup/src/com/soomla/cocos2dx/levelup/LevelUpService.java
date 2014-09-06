package com.soomla.cocos2dx.levelup;

import android.opengl.GLSurfaceView;
import com.soomla.cocos2dx.common.AbstractSoomlaService;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.levelup.data.*;
import org.json.JSONObject;

import java.lang.ref.WeakReference;

/**
 * @author vedi
 *         date 6/10/14
 *         time 11:08 AM
 */
public class LevelUpService extends AbstractSoomlaService {

    private static LevelUpService INSTANCE = null;

    private boolean inited = false;

    public static LevelUpService getInstance() {
        if (INSTANCE == null) {
            synchronized (LevelUpService.class) {
                if (INSTANCE == null) {
                    INSTANCE = new LevelUpService();
                }
            }
        }
        return INSTANCE;
    }

    @SuppressWarnings("FieldCanBeLocal")
    private LevelUpEventHandlerBridge levelUpEventHandlerBridge;

    public LevelUpService() {
        levelUpEventHandlerBridge = new LevelUpEventHandlerBridge();

        final NdkGlue ndkGlue = NdkGlue.getInstance();

        ndkGlue.registerCallHandler("CCLevelUpService::initLevelUp", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                LevelUpService.getInstance().init();
                JSONObject metadata = retParams.optJSONObject("metadata");
                WorldStorage.initLevelUp(metadata != null ? metadata.toString() : "{}");
                retParams.put("return", true);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::gateIsOpen", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String gateId = params.getString("gateId");
                retParams.put("return", GateStorage.isOpen(gateId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::gateSetOpen", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String gateId = params.getString("gateId");
                boolean open = params.getBoolean("open");
                boolean notify = params.getBoolean("notify");
                GateStorage.setOpen(gateId, open, notify);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelSetSlowestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                long duration = params.getLong("duration");
                LevelStorage.setSlowestDurationMillis(levelId, duration);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelGetSlowestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getSlowestDurationMillis(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelSetFastestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                long duration = params.getLong("duration");
                LevelStorage.setFastestDurationMillis(levelId, duration);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelGetFastestDurationMillis", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getFastestDurationMillis(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelIncTimesStarted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.incTimesStarted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelDecTimesStarted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.decTimesStarted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelGetTimesStarted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getTimesStarted(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelGetTimesPlayed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.getTimesPlayed(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelIncTimesPlayed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.incTimesPlayed(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::levelDecTimesPlayed", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String levelId = params.getString("levelId");
                retParams.put("return", LevelStorage.decTimesPlayed(levelId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::missionSetCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String missionId = params.getString("missionId");
                boolean completed = params.getBoolean("completed");
                boolean notify = params.getBoolean("notify");
                MissionStorage.setCompleted(missionId, completed, notify);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::missionGetTimesCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String missionId = params.getString("missionId");
                retParams.put("return", MissionStorage.getTimesCompleted(missionId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::scoreSetLatestScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                double newValue = params.getDouble("newValue");
                ScoreStorage.setLatestScore(scoreId, newValue);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::scoreGetLatestScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                retParams.put("return", ScoreStorage.getLatestScore(scoreId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::scoreSetRecordScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                double newValue = params.getDouble("newValue");
                ScoreStorage.setRecordScore(scoreId, newValue);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::scoreGetRecordScore", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String scoreId = params.getString("scoreId");
                retParams.put("return", ScoreStorage.getRecordScore(scoreId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::worldSetCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                boolean completed = params.getBoolean("completed");
                boolean notify = params.getBoolean("notify");
                WorldStorage.setCompleted(worldId, completed, notify);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::worldIsCompleted", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                retParams.put("return", WorldStorage.isCompleted(worldId));
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::worldSetReward", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                String rewardId = params.getString("rewardId");
                WorldStorage.setReward(worldId, rewardId);
            }
        });

        ndkGlue.registerCallHandler("CCLevelUpService::worldGetAssignedReward", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String worldId = params.getString("worldId");
                retParams.put("return", WorldStorage.getAssignedReward(worldId));
            }
        });

    }

    public void init() {
        final GLSurfaceView glSurfaceView = glSurfaceViewRef.get();
        if (glSurfaceView != null) {
            levelUpEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }

        inited = true;
    }

    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        if (inited) {
            levelUpEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        } else {
            glSurfaceViewRef = new WeakReference<GLSurfaceView>(glSurfaceView);
        }
    }
}
