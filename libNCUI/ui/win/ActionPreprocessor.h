// Created by amoylel on 08/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_ACTIONPREPROCESSOR_H__
#define AMO_ACTIONPREPROCESSOR_H__

#include <amo/stdint.hpp>

namespace amo {
    class ActionPreprocessor {
    public:
        ActionPreprocessor(int32_t nBrowserID = -9999, int64_t nFrameID = -1);
        
        /*!
         * @fn	bool ActionPreprocessor::process(const std::string& action);
         *
         * @brief	Process the given action.
         *
         * @param	action	The action.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool process(const std::string& action);
        
    private:
        /*! @brief	Identifier for the browser. */
        int32_t m_nBrowserID;
        /*! @brief	Identifier for the frame. */
        int64_t m_nFrameID;
    };
}

#endif // AMO_ACTIONPREPROCESSOR_H__

