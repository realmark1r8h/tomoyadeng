(function() {

	methodArr = [];
	settingsArr = [];

  initApi('SN', 'GetBrowser', 'Obect', '获取Browser对象');
        initApi('SN', 'CloseBrowser', '', '关闭浏览器');
        initApi('SN', 'SetFocus', '', '设置焦点');
        initApi('SN', 'SetWindowVisibility', '', '');
        initApi('SN', 'GetWindowHandle', '', '');
        initApi('SN', 'GetOpenerWindowHandle', '', '');
        initApi('SN', 'GetClient', '', '');
        initApi('SN', 'GetRequestContext', '', '');
        initApi('SN', 'GetZoomLevel', '', '获取绽放级别');
        initApi('SN', 'SetZoomLevel', '', '设置绽放级别');
        initApi('SN', 'RunFileDialog', '', '打开文件框');
        initApi('SN', 'StartDownload', '', '下载文件');
        initApi('SN', 'Print', '', '打印');
        initApi('SN', 'PrintToPDF', '', '打印为PDF');
        initApi('SN', 'Find', '', '页面查找');
        initApi('SN', 'StopFinding', '', '停止查找');
        initApi('SN', 'ShowDevTools', '', '打开调试');
        initApi('SN', 'CloseDevTools', '', '关闭调试');
        initApi('SN', 'GetNavigationEntries', '', '');
        initApi('SN', 'SetMouseCursorChangeDisabled', '', '');
        initApi('SN', 'IsMouseCursorChangeDisabled', '', '');
        initApi('SN', 'ReplaceMisspelling', '', '');
        initApi('SN', 'AddWordToDictionary', '', '');
        initApi('SN', 'NotifyScreenInfoChanged', '', '');
        initApi('SN', 'Invalidate', '', '');
        initApi('SN', 'SendKeyEvent', '', '发送键盘消息');
        initApi('SN', 'SendMouseClickEvent', '', '发送鼠标点击消息');
        initApi('SN', 'SendMouseMoveEvent', '', '发送鼠标移动消息');
        initApi('SN', 'SendMouseWheelEvent', '', '发送鼠标滚轮击消息');
        initApi('SN', 'SendFocusEvent', '', '发送焦点消息');
        initApi('SN', 'SendCaptureLostEvent', '', '');
        initApi('SN', 'NotifyMoveOrResizeStarted', '', '');
        initApi('SN', 'GetWindowlessFrameRate', '', '获取帧率');
        initApi('SN', 'SetWindowlessFrameRate', '', '设置帧率');
        initApi('SN', 'HandleKeyEventBeforeTextInputClient', '', '');
        initApi('SN', 'HandleKeyEventAfterTextInputClient', '', '');
        initApi('SN', 'IsWindowRenderingDisabled', '', '');
     

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		includes('BrowserWindow');
		console.dir(BrowserWindow);

		var win = BrowserWindow.currentWindow;

		console.dir(win);
		var browser = win.getBrowser();
		var browserHost = browser.GetHost();
		console.dir(browserHost);

		$('#SendMouseClickEvent').on('click', function() {
			browserHost.SendMouseClickEvent();
		});

		$('#StartDownload').on('click', function() {
			browserHost.StartDownload('https://dldir1.qq.com/qqfile/qq/QQ8.9.4/21593/QQ8.9.4.exe');
		});

	})
})();