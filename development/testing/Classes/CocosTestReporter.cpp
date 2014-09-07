 /*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CocosTestReporter.h"

#define TAG "SOOMLA Testing"

void CocosTestReporter::ReportTestStart(TestDetails const& test) {
//    cocos2d::log("%s Test %s STARTED", TAG, test.testName);
}

void CocosTestReporter::ReportFailure(TestDetails const& test, char const* failure){
    cocos2d::log("%s Test %s:%s FAILED (%s:%d) : %s", TAG, test.suiteName, test.testName, test.filename, test.lineNumber, failure);
}

void CocosTestReporter::ReportTestFinish(TestDetails const& test, float secondsElapsed){
    cocos2d::log("%s Test %s:%s FINISHED", TAG, test.suiteName, test.testName);
}

void CocosTestReporter::ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed){
    if (failureCount > 0)
        cocos2d::log("FAILURE: %d out of %d tests failed (%d failures).", failedTestCount, totalTestCount, failureCount);
    else
        cocos2d::log("Success: %d tests passed.", totalTestCount);
    
    cocos2d::log("Test time: %.2f seconds.", secondsElapsed);
}