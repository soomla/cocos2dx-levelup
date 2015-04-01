package com.soomla.cocos2dx.levelup;

import android.opengl.GLSurfaceView;
import com.soomla.BusProvider;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.levelup.events.*;
import com.squareup.otto.Subscribe;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * This bridge is used to populate events from the store to cocos2dx (through JNI).
 */
public class LevelUpEventHandlerBridge {

    private GLSurfaceView mGLThread;

    public LevelUpEventHandlerBridge() {
        BusProvider.getInstance().register(this);
    }

    @Subscribe
    public void LevelUpInitialized(final LevelUpInitializedEvent levelUpInitializedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onLevelUpInitialized");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLatestScoreChanged(final LatestScoreChangedEvent latestScoreChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onLatestScoreChanged");
                    parameters.put("scoreId", latestScoreChangedEvent.ScoreId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onScoreRecordReached(final ScoreRecordReachedEvent scoreRecordReachedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onScoreRecordReached");
                    parameters.put("scoreId", scoreRecordReachedEvent.ScoreId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onScoreRecordChanged(final ScoreRecordChangedEvent scoreRecordChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onScoreRecordChanged");
                    parameters.put("scoreId", scoreRecordChangedEvent.ScoreId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGateOpened(final GateOpenedEvent gateOpenedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onGateOpened");
                    parameters.put("gateId", gateOpenedEvent.GateId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGateClosed(final GateClosedEvent gateClosedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onGateClosed");
                    parameters.put("gateId", gateClosedEvent.GateId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onMissionCompleted(final MissionCompletedEvent missionCompletedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onMissionCompleted");
                    parameters.put("missionId", missionCompletedEvent.MissionId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onMissionCompletionRevoked(final MissionCompletionRevokedEvent missionCompletionRevokedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onMissionCompletionRevoked");
                    parameters.put("missionId", missionCompletionRevokedEvent.MissionId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onWorldCompleted(final WorldCompletedEvent worldCompletedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onWorldCompleted");
                    parameters.put("worldId", worldCompletedEvent.WorldId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLastCompletedInnerWorldChanged(final LastCompletedInnerWorldChanged lastCompletedInnerWorldChanged) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onLastCompletedInnerWorldChanged");
                    parameters.put("worldId", lastCompletedInnerWorldChanged.WorldId);
                    parameters.put("innerWorldId", lastCompletedInnerWorldChanged.InnerWorldId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onWorldRewardAssigned(final WorldAssignedRewardEvent worldAssignedRewardEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onWorldRewardAssigned");
                    parameters.put("worldId", worldAssignedRewardEvent.WorldId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLevelStarted(final LevelStartedEvent levelStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onLevelStarted");
                    parameters.put("levelId", levelStartedEvent.LevelId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLevelEnded(final LevelEndedEvent levelEndedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = createJsonObjectForMethod("CCLevelUpEventHandler::onLevelEnded");
                    parameters.put("levelId", levelEndedEvent.LevelId);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    private JSONObject createJsonObjectForMethod(String method) throws JSONException {
        JSONObject parameters = new JSONObject();
        parameters.put("method", method);
        return parameters;
    }

    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        this.mGLThread = glSurfaceView;
    }
}
