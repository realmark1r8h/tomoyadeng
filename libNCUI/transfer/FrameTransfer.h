// Created by amoylel on 07/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_FRAMETRANSFER_H__
#define AMO_FRAMETRANSFER_H__

#include <amo/singleton.hpp>
#include "handler/CefHeader.hpp"
#include "transfer/ClassTransfer.hpp"


namespace amo {

    /*!
     * @class	Frame
     *
     * @chapter cef
     *
     * @extend Object
     *
     * @brief	CEF Frame ��װ.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class FrameTransfer
        : public ClassTransfer
        , public amo::singleton < FrameTransfer > {
    public:
        FrameTransfer();
        FrameTransfer(CefRefPtr<CefFrame> pFrame);
        
        
        Any current(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::injectSrcipt(IPCMessage::SmartType msg);
         *
         * @brief	��ҳ��ע��JS����.
         *
         * @param	#String JS����.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any injectSrcipt(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::injectCSS(IPCMessage::SmartType msg);
         *
         * @brief	��ҳ��ע��CSS����.
         *
         * @param	#String CSS����.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any injectCSS(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::IsValid(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ǰҳ���Ƿ���Ч.
         *
         *
         * @return	#Boolean true��Ч/false��Ч.
         * @example
         *
         ```
        	includes('Frame');
        	var frame = Frame.current;
        	console.log(frame.IsValid());
        
         ```
         */
        
        Any IsValid(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Undo(IPCMessage::SmartType msg);
         *
         * @brief	�������༭������Ч.
         *
         * @return	��.
         *
         */
        
        Any Undo(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Redo(IPCMessage::SmartType msg);
         *
         * @brief	�������༭������Ч.
         *
         * @return	��.
         */
        
        Any Redo(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Cut(IPCMessage::SmartType msg);
         *
         * @brief	���У��༭������Ч.
         *
         *
         * @return	��.
         */
        
        Any Cut(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Copy(IPCMessage::SmartType msg);
         *
         * @brief	���ƣ��༭������Ч.
         *
         *
         * @return	��.
         */
        
        Any Copy(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Paste(IPCMessage::SmartType msg);
         *
         * @brief	ճ�����༭������Ч.
         *
         *
         * @return	��.
         */
        
        Any Paste(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Delete(IPCMessage::SmartType msg);
         *
         * @brief	ɾ�����༭������Ч.
         *
         *
         * @return	��.
         */
        
        Any Delete(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::SelectAll(IPCMessage::SmartType msg);
         *
         * @brief	ȫѡ.
         *
         * @return	��.
         * @example
         *
         ```
         includes('Frame');
         Frame.current.SelectAll();
        
         ```
         */
        
        Any SelectAll(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::ViewSource(IPCMessage::SmartType msg);
         * @ignore
         * @brief	�鿴��ҳԴ����.
         *
         * @return	��.
         */
        
        Any ViewSource(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetSource(IPCMessage::SmartType msg);
         *
         * @ignore
         *
         * @brief	��ȡ��ҳԴ����.
         *
         *
         * @return	#String.
         */
        
        Any GetSource(IPCMessage::SmartType msg);
        
        Any GetText(IPCMessage::SmartType msg);
        
        Any LoadRequest(IPCMessage::SmartType msg) ;
        
        /*!
         * @fn	Any FrameTransfer::LoadURL(IPCMessage::SmartType msg);
         *
         * @brief	����URL.
         *
         * @param	#String URL.
         *
         * @return	��.
         * @example
         *
         ```
        	include('Frame');
        	Frame.current.LoadURL('http://www.baidu.com');
         ```
         */
        
        Any LoadURL(IPCMessage::SmartType msg) ;
        
        /**
         * @fn	Any FrameTransfer::LoadString(IPCMessage::SmartType msg);
         *
         * @brief	����HTML����.
         *
         * @param	#String HTML����.
         * @param	#String="" URL,ѡ��
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	// vConsoleת���������⣬�����п�������ʹ��
        	include('Frame');
        	Frame.current.LoadString(`
        		<!DOCTYPE html>
        		<html lang="zh-CN">
        
        			<head>
        				<meta charset='utf-8'>
        				<script type="text/javascript">
        					includes('app', 'BrowserWindow');
        				</script>
        				<style>
        					html,
        					body {
        						width: 100%;
        						height: 100%;
        						overflow: hidden;
        					}
        					.container {
        						position: absolute;
        						top: 0;
        						left: 0;
        						right: 0;
        						bottom: 0;
        					}
        
        					.drag {
        						-webkit-app-region: drag;
        					}
        
        					.no-drag {
        						-webkit-app-region: no-drag;
        					}
        				</style>
        			</head>
        
        			<body>
        				<div class="container ">
        					<h1>����һ����ͨ���������<a href="#" onclick="recoveryManifest();">���һָ�manifest.json</a></h1>
        					<h1>����һ����ͨ���������<a href="#" onclick="app.restart();">��������APP</a></h1>
        				</div>
        			</body>
        			<script type="text/javascript">
        
        
        				function recoveryManifest() {
        					include('Path');
        					var path = new Path('manifest2.json');
        					if(!path.isExsit()) return;
        					path.copyTo('manifest.json');
        					path.remove();
        				}
        			</script>
        
        		</html>
        	`);
         ```
         */
        
        Any LoadString(IPCMessage::SmartType msg) ;
        
        /*!
         * @fn	Any FrameTransfer::IsMain(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ǰҳ���Ƿ�Ϊ��ҳ��.
         *
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('Frame');
        	console.assert(Frame.current.IsMain() == true);
         ```
         */
        
        Any IsMain(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::IsFocused(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ǰҳ���Ƿ��ý���.
         *
         * @return	#Boolean.
         *
         * @example
         *
         ```
        	 include('Frame');
        	 console.assert(Frame.current.IsFocused() == true);
         ```
         */
        
        Any IsFocused(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetName(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡ��ǰҳ�������.
         *
         * @return	#String ҳ������.
         *
         * @example
         *
         ```
        	 include('Frame');
        	 console.assert(Frame.current.GetName() == '');
         ```
         */
        
        Any GetName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetIdentifier(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	��ȡ��ǰҳ���ID.
         *
         * @return	#Int identifier.
         *
         * @example
         *
         ```
        	 include('Frame');
        	 console.log(Frame.current.GetIdentifier());
         ```
         */
        
        Any GetIdentifier(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetParent(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡ��ǰҳ��ĸ�ҳ��.
         *
         * @return	#Frame ��������ڷ���Undefined.
         *
         * @example
         *
         ```
        	include('Frame');
        	console.log(Frame.current.GetParent());
         ```
         */
        
        Any GetParent(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetURL(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡ��ǰҳ���URL.
         *
         * @return	#String url.
         *
         * @example
         *
         ```
        	 include('Frame');
        	 console.log(Frame.current.GetURL());
         ```
         */
        
        Any GetURL(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetBrowser(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡ��ǰҳ��������Browser����.
         *
         * @return	#Browser .
         * @example
         *
         ```
        	 include('Frame');
        	 console.log(Frame.current.GetBrowser().GetIdentifier());
         ```
         */
        
        Any GetBrowser(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(FrameTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(current,
                                      TransferFuncConstProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(injectSrcipt, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsValid, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Undo, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Redo, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Cut, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Copy, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Paste, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Delete, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SelectAll, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(ViewSource, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetSource, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetText, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadRequest, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadURL, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadString, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsMain, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsFocused, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetName, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetIdentifier, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetParent, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetURL, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetBrowser, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        CefRefPtr<CefFrame> m_pFrame;
    };
}

#endif // AMO_FRAMETRANSFER_H__
