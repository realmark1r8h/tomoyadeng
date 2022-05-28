// Created by amoylel on 08/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DESKTOPTRANSFER_H__
#define AMO_DESKTOPTRANSFER_H__



#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
     * @class	desktop
     *
     * @brief	用于获取桌面的基本信息.
     */
    
    class DesktopTransfer
        : public ClassTransfer
        , public amo::singleton < DesktopTransfer > {
    public:
        DesktopTransfer();
        
        
        
        /*!
         * @fn	Any DesktopTransfer::getScreenInfo(IPCMessage::SmartType msg);
         *
         * @tag sync static
         *
         * @brief	获取屏幕信息,包括屏幕大小和工作区域大小.
         *
         * @return	#JsonObject.
         *
         * 			|#Int width  桌面宽度
         * 			|#Int height 桌面高度
         * 			|#JsonObject rcWork 桌面工作区域信息
         * 				||#Int left 工作区域左上角坐标X
         * 				||#Int top 工作区域左上角坐标Y
         * 				||#Int right 工作区域右下角坐标X
         * 				||#Int bottom 工作区域右下角坐标Y
         * 				||#Int width 工作区域宽度
         * 				||#Int height 工作区域高度
         *
         * @example
         *
        			 ```
        				include('desktop');
        				var desktopInfo = desktop.getScreenInfo();
        				console.log(desktopInfo);
        			 ```
         */
        
        Any getScreenInfo(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DesktopTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getScreenInfo, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
    };
}

#endif // AMO_DESKTOPTRANSFER_H__

