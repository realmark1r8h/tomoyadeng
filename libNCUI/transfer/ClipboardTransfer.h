// Created by amoylel on 14/11/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBNCUI_CLIPBOARDTRANSFER_7CB74BAD_E5C1_4CE6_B3D2_E9CA9C435548_H__
#define LIBNCUI_CLIPBOARDTRANSFER_7CB74BAD_E5C1_4CE6_B3D2_E9CA9C435548_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
    * @class	clipboard
    *
    * @brief	������.
    */
    class ClipboardTransfer
        : public ClassTransfer
        , public amo::singleton<ClipboardTransfer> {
    public:
        ClipboardTransfer();
        
        /**
        * @fn	Any ClipboardTransfer::writeText(IPCMessage::SmartType msg);
        * @tag static sync
        * @brief	���������д���ַ���.
        *
        * @param	#String Ҫд����ַ���.
        *
        * @return	#Undefined.
        *
        * @example
        ```
        	include('clipboard');
        	console.assert(clipboard.writeText('NCUI Clipboard Text ����') == true);
        ```
        *
        */
        
        Any writeText(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::writeImage(IPCMessage::SmartType msg);
         * @tag static sync
         *
         * @brief	д��ͼƬ��������.
         *
         * @param	#String ͼƬ���� base64�����ͼƬ.
         *
         * @return	#Boolean.
         */
        
        /**
        * @fn	Any ClipboardTransfer::writeImage(IPCMessage::SmartType msg);
        * @tag static sync
        *
        * @brief	д��ͼƬ��������.
        *
        * @param	#String ͼƬ·���������ļ�·����,(Ҳ������һ��BigStr��װ�Ķ������ͼƬ̫�����ʹ��BigStr��װ�����̼�ͨ�ŵĹܵ�ֻ��2M�����������С�����ݲ��ܱ���ȷ�ʹ�).
        *
        * @return	#Boolean.
        * @html <div id="example" class="example code" contenteditable="true"><img id="ncuiImg_writeImage" src="@file:///%appDir%images/splash.jpg"></img> </div>
        * @example
        *
        ```
        	include('clipboard');
        	clipboard.writeImage('');
        	//��ͼƬת����base64
        	function convertImgToBase64(url, callback, outputFormat) {
        		var canvas = document.createElement('CANVAS'),
        	��  ctx = canvas.getContext('2d'),
        	  ��img = new Image;����
        		img.crossOrigin = 'Anonymous';����
        		img.onload = function() {����
        			canvas.height = img.height;����
        			canvas.width = img.width;����
        			ctx.drawImage(img, 0, 0);����
        			var dataURL = canvas.toDataURL(outputFormat || 'image/jpeg');����
        			callback.call(this, dataURL);����
        			canvas = null;
        		};
        		img.src = url;
        	}
        
        	var url = "@file:///%appDir%images/splash.jpg"; //����վ�ڵ�һ��ͼƬ��Դ�����õ����·��
        	convertImgToBase64(url, function(base64Img) {
        		//ת�����base64
        		clipboard.writeImage(base64Img);
        
        		include('BigStr');
        		// Ҳ����ʹ��BigStr��������
        		clipboard.writeImage(new BigStr(base64Img));
        	});
        
        
        
        ```
        */
        Any writeImage(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ClipboardTransfer::writeImageFromFile(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	��һ������ͼƬ�ļ�����д�뵽������.
         *
         * @param	#String �ļ�·��.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('clipboard');
        	console.assert(clipboard.writeImageFromFile('%appDir%images/splash.jpg') == true);
         ```
         */
        
        Any writeImageFromFile(IPCMessage::SmartType msg);
        
        /**
        * @fn	Any ClipboardTransfer::writeFiles(IPCMessage::SmartType msg);
        * @tag static sync
        *
        * @brief	д���ļ���������.
        *
        * @param	#String �ļ�·��.
        *
        * @return	#Boolean.
        *
        * @example
        *
        ```
        	include('clipboard');
        	console.assert(clipboard.writeFiles('manifest.json') == true);
        ```
        */
        
        
        /**
         * @fn	Any ClipboardTransfer::writeFiles(IPCMessage::SmartType msg);
         * @tag static sync
         *
         * @brief	д���ļ���������.
         *
         * @param	#Array �ļ�·��.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('clipboard');
        	console.assert(clipboard.writeFiles(['skin', 'manifest.json']) == true);
         ```
         */
        
        Any writeFiles(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::readText(IPCMessage::SmartType msg);
         * @tag static sync
         *
         * @brief	��ȡ�������е��ַ���.
         *
         * @return	#String.
         *
         * @example
         ```
        	include('clipboard');
        	console.assert(clipboard.writeText('NCUI Clipboard Text ����') == true);
        	var str = clipboard.readText();
        	console.log(str);
        	console.assert(str == 'NCUI Clipboard Text ����');
         ```
         *
         */
        
        Any readText(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::readImage(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	��ȡͼƬ,��ȡ����ͼƬ��Base64���뷵��
         *
         * @param	#String="jpeg" ͼƬ��ʽ.
         *
         * @return	#String ͼƬ����.
         * @html <div id="example" class="example code" contenteditable="true"><img id="ncuiImg" src="http:://127.0.0.1:8030/@file:///%skinDir%logo.ico"></img> </div>
         * @example
         *
         ```
        	include('clipboard');
        	clipboard.writeImageFromFile('%appDir%images/splash.jpg');
        	var str = clipboard.readImage('.jpeg');
        	$('#ncuiImg').attr("src", str);
         ```
         */
        
        Any readImage(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::readFiles(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	��ȡ�ļ�.
         *
         * @param	#Boolean=false �Ƿ����Ŀ¼.
         *
         * @return	#Array ����һ�������ļ�·�����ַ���.
         * @example
         *
         ```
        	include('clipboard');
        	var arr = clipboard.readFiles();
        	console.log(arr);
        	console.log(arr.length);
         ```
         */
        
        Any readFiles(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ClipboardTransfer::saveText(IPCMessage::SmartType msg);
         *
         * @brief	����������е��ı����ݵ�����.
         *
         * @param	#String �ļ�·��.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('clipboard');
        	clipboard.writeText('1111111111111111111111����');
        	console.assert(clipboard.saveText('test3.json') == true);
        	include('Path');
        	console.assert(Path.Remove('test3.json') == true);
         ```
         */
        
        Any saveText(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ClipboardTransfer::saveImage(IPCMessage::SmartType msg);
         *
         * @brief	����������е��ı����ݵ�����.
         *
         * @param	#String �ļ�·��.
         *
         * @return	#Boolean.
         * @html <div id="example" class="example code" contenteditable="true"><img id="ncuiImg4" src=""></img> </div>
         * @example
         *
         ```
        	includes( 'clipboard');
        	console.assert(clipboard.screenshot() == true);
        	console.assert(clipboard.saveImage('test2/screen.jpg') == true);
        	console.assert(clipboard.saveImage('test2/screen.bmp') == true);
        	console.assert(clipboard.saveImage('test2/screen.png') == true);
        	$('#ncuiImg4').attr('src', '');
        	$('#ncuiImg4').attr('src', '@file:///%appDir%test2/screen.jpg');
         ```
         */
        
        Any saveImage(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	Any ClipboardTransfer::saveFiles(IPCMessage::SmartType msg);
        *
        * @brief	����������е��ļ����ݵ����̣������ļ���.
        *
        * @param	#String �ļ�·��.
        *
        * @return	#Boolean.
        * @example
        *
        ```
        	include('clipboard');
        	clipboard.empty();
        	console.assert(clipboard.saveFiles('%appDir%test2.json') == false);
        	clipboard.writeFiles('manifest.json');
        	console.assert(clipboard.saveFiles('%appDir%test2.json') == true);
        	include('Path');
        	console.assert(Path.Remove('test2.json') == true);
        ```
        */
        
        /*!
         * @fn	Any ClipboardTransfer::saveFiles(IPCMessage::SmartType msg);
         *
         * @brief	����������е��ı����ݵ�����.
         *
         * @param	#JsonArray �ļ�·��.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('clipboard');
        	clipboard.empty();
        	console.assert(clipboard.saveFiles('%appDir%test2.json') == false);
        	clipboard.writeFiles(['manifest.json', 'libcef.dll', 'C:/windows/notepad.exe']);
        	console.assert(clipboard.saveFiles([
        		{src: 'manifest.json', dst:'%appDir%test2/test2.json'},
        		{src: 'libcef.dll', dst:'%appDir%test2/libcef.dll'},
        		{src: 'C:/windows/notepad.exe', dst:'%appDir%test2/nodepad.exe'}
        	]) == true);
        	include('Path');
        	Path.Remove('test2.json');
        	Path.RemoveAll('test2');
         ```
         */
        
        Any saveFiles(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::hasFormat(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	�鿴���������Ƿ����ָ����ʽ������.
         *
         * @param	#Int ��Ҫ�жϵĸ�ʽ.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('clipboard');
        	clipboard.hasFormat(clipboard.CF_TEXT);
         ```
         */
        
        Any hasFormat(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::empty(IPCMessage::SmartType msg)
         * @tag static sync
         * @brief	��ռ�����.
         *
         *
         * @return	#Boolean.
         *
         * @example
         ```
        	 include('clipboard');
        	 clipboard.empty();
        	 console.assert(clipboard.isEmpty() == true);
        	 clipboard.writeText('1232');
        	 console.assert(clipboard.isEmpty() == false);
         ```
         */
        
        Any empty(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::isEmpty(IPCMessage::SmartType msg)
         * @tag static sync
         * @brief	�жϼ������Ƿ�Ϊ��.
         *
         *
         * @return	#Boolean.
         * @example
         ```
        	 include('clipboard');
        	 clipboard.empty();
        	 console.assert(clipboard.isEmpty() == true);
        	 clipboard.writeText('1232');
        	 console.assert(clipboard.isEmpty() == false);
         ```
         */
        
        Any isEmpty(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::getFormats(IPCMessage::SmartType msg);
         * @tag static sync
         *
         * @brief	��ȡ�����������е����ݸ�ʽ.
         *
         * @return	#Array.
         *
         * @example
         ```
        	 include('clipboard');
        	 clipboard.empty();
        	 var arr = clipboard.getFormats();
        	 var len = arr.length;
        	 console.log(arr);
        	 console.log(len);
        	 console.assert(len == 0);
        	 clipboard.writeText('1232');
        	 arr = clipboard.getFormats();
        	 len = arr.length;
        	 console.log(arr);
        	 console.log(len);
         ```
         */
        
        Any getFormats(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ClipboardTransfer::effect(IPCMessage::SmartType msg);
         * @tag static sync
         *
         * @brief	�жϼ������е������Ǹ��ƵĻ���ճ����(ֻ����Դ�������е��ļ�������Ч).
         *
         * @return	#Int δ֪(0) ����(1) ����(2) ����(4).
         *
         * @example
         *
         ```
        	 include('clipboard');
        	 clipboard.empty();
        	 console.assert(clipboard.effect() == 0);
        	 clipboard.writeFiles('manifest.json');
        	 console.assert(clipboard.effect() == 1);
         ```
        
         */
        
        Any effect(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	Any ClipboardTransfer::screenshot(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief	����,�����ݱ��浽�������У�JPG��ʽ��.
        *
        * @return	#Boolean
        * @example
        *
        ```
        	include('clipboard');
        	console.assert(clipboard.screenshot() == true);
        	var img = clipboard.readImage();
        	$('#ncuiImg3').attr("src", img);
        
        ```
        */
        
        /*!
        * @fn	Any ClipboardTransfer::screenshot(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief	����,�����ݱ��浽�������У�JPG��ʽ��.
        *
        * @param	#Array ָ����������Int���� [left,top, width, height].
        *
        *
        * @return	#Boolean.
        * @html <div id="example" class="example code" contenteditable="true"><img id="ncuiImg3" src=""></img> </div>
        * @example
        *
        ```
        	includes('clipboard', 'BrowserWindow');
        	var win = BrowserWindow.current;
        	var winInfo = win.getWindowRect();
        	console.log(winInfo);
        	console.assert(clipboard.screenshot([winInfo.x, winInfo.y, winInfo.width, winInfo.height]) == true);
        	var img = clipboard.readImage();
        	$('#ncuiImg3').attr("src", img);
        
        
        ```
        */
        Any screenshot(IPCMessage::SmartType msg);
        
        
        Any test(IPCMessage::SmartType msg);
        
        /**
        * @event	Any ClipboardTransfer::copy(IPCMessage::SmartType msg);
        *
        * @brief	�����������¼�ʱ���� .
        *
        * @example
        *
        ```
        	include('clipboard');
        	clipboard.unique('copy', function(){
        		console.log('trigger copy event');
        	});
        ```
        */
        
        /**
        * @event	Any ClipboardTransfer::cut(IPCMessage::SmartType msg);
        *
        * @brief	�����������¼�ʱ������ֻ���ļ�����ʱ������ .
        * @example
        *
        ```
        	include('clipboard');
        	clipboard.unique('cut', function(){
        		console.log('trigger cut event');
        	});
        ```
        */
        
        /**
        * @event	Any ClipboardTransfer::empty(IPCMessage::SmartType msg);
        *
        * @brief	��ռ�����ʱ���� .
        * @example
        *
        ```
        	include('clipboard');
        	clipboard.unique('empty', function(){
        		console.log('trigger empty event');
        	});
        ```
        */
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ClipboardTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(writeText, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(writeImage, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(writeImageFromFile,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(writeFiles, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(readText, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(readImage, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(readFiles, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(saveText, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(saveImage, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(saveFiles, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(hasFormat, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(empty, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isEmpty, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFormats, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(effect, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(screenshot, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(test, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(CF_TEXT, (int)CF_TEXT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(CF_UNICODETEXT, (int)CF_UNICODETEXT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(CF_BITMAP, (int)CF_BITMAP)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(CF_HDROP, (int)CF_HDROP)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
    };
}



#endif //LIBNCUI_CLIPBOARDTRANSFER_7CB74BAD_E5C1_4CE6_B3D2_E9CA9C435548_H__
