//
// Created by Shubin Fedor on 21/08/14.
// Copyright (c) 2014 SOOMLA. All rights reserved.
//


#ifndef __CCSocialUploadGate_H_
#define __CCSocialUploadGate_H_

#include "CCGate.h"
#include "CCSocialActionGate.h"


namespace soomla {

    class CCSocialUploadGate: public CCSocialActionGate {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mMessage, Message, CCLevelUpConsts::JSON_LU_MESSAGE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mFileName, FileName, CCLevelUpConsts::JSON_LU_FILE_NAME);
    public:
        CCSocialUploadGate(): CCSocialActionGate(), mMessage(NULL), mFileName(NULL) {
        }

        static CCSocialUploadGate *create(cocos2d::__String *id, CCProvider provider,
                cocos2d::__String *fileName, cocos2d::__String *message);

        SL_CREATE_WITH_DICTIONARY(CCSocialUploadGate);

        virtual bool init(cocos2d::__String *id, CCProvider provider,
                cocos2d::__String *fileName, cocos2d::__String *message);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const override;

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCSocialUploadGate();

    protected:
        virtual bool openInner();
    };

}

#endif //__CCSocialUploadGate_H_
