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



#ifndef __CCSocialUploadGate_H_
#define __CCSocialUploadGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

    /**
     NOTE: Social `Gate`s require the user to perform a specific social
     action in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     A specific type of `Gate` that has an associated image. The `Gate`
     is opened once the player uploads the image.
     */
    class CCSocialUploadGate: public CCSocialActionGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mMessage, Message, CCLevelUpConsts::JSON_LU_MESSAGE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mFileName, FileName, CCLevelUpConsts::JSON_LU_FILE_NAME);
    public:
        CCSocialUploadGate(): CCSocialActionGate(), mMessage(NULL), mFileName(NULL) {
        }

        /**
         Creates an instance of `CCSocialUploadGate`.
         @param id `Gate` ID.
         @param provider Social provider.
         @param fileName Name of file to upload.
         @param message Message.
         */
        static CCSocialUploadGate *create(cocos2d::__String *id, CCProvider provider,
                cocos2d::__String *fileName, cocos2d::__String *message);

        SL_CREATE_WITH_DICTIONARY(CCSocialUploadGate);

        virtual bool init(cocos2d::__String *id, CCProvider provider,
                cocos2d::__String *fileName, cocos2d::__String *message);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const override;

        /**
         Converts this `SocialUploadGate` to a Dictionary.
         @return The Dictionary representation of this `SocialUploadGate`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCSocialUploadGate();

    protected:

        /**
         Opens this `Gate` by uploading the associated image.
         @return If the image was successfully uploaded returns `true`;
         otherwise `false`.
         */
        virtual bool openInner();
    };

}

#endif //__CCSocialUploadGate_H_
