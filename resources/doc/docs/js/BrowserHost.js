(function() {

	methodArr = [];
	settingsArr = [];

  initApi('SN', 'GetBrowser', '', '强制退出程序');
        initApi('SN', 'CloseBrowser', '', '强制退出程序');
        initApi('SN', 'SetFocus', '', '强制退出程序');
        initApi('SN', 'SetWindowVisibility', '', '强制退出程序');
        initApi('SN', 'GetWindowHandle', '', '强制退出程序');
        initApi('SN', 'GetOpenerWindowHandle', '', '强制退出程序');
        initApi('SN', 'GetClient', '', '强制退出程序');
        initApi('SN', 'GetRequestContext', '', '强制退出程序');
        initApi('SN', 'GetZoomLevel', '', '强制退出程序');
        initApi('SN', 'SetZoomLevel', '', '强制退出程序');
        initApi('SN', 'RunFileDialog', '', '强制退出程序');
        initApi('SN', 'StartDownload', '', '强制退出程序');
        initApi('SN', 'Print', '', '强制退出程序');
        initApi('SN', 'PrintToPDF', '', '强制退出程序');
        initApi('SN', 'Find', '', '强制退出程序');
        initApi('SN', 'StopFinding', '', '强制退出程序');
        initApi('SN', 'ShowDevTools', '', '强制退出程序');
        initApi('SN', 'CloseDevTools', '', '强制退出程序');
        initApi('SN', 'GetNavigationEntries', '', '强制退出程序');
        initApi('SN', 'SetMouseCursorChangeDisabled', '', '强制退出程序');
        initApi('SN', 'IsMouseCursorChangeDisabled', '', '强制退出程序');
        initApi('SN', 'ReplaceMisspelling', '', '强制退出程序');
        initApi('SN', 'AddWordToDictionary', '', '强制退出程序');
        initApi('SN', 'NotifyScreenInfoChanged', '', '强制退出程序');
        initApi('SN', 'Invalidate', '', '强制退出程序');
        initApi('SN', 'SendKeyEvent', '', '强制退出程序');
        initApi('SN', 'SendMouseClickEvent', '', '强制退出程序');
        initApi('SN', 'SendMouseMoveEvent', '', '强制退出程序');
        initApi('SN', 'SendMouseWheelEvent', '', '强制退出程序');
        initApi('SN', 'SendFocusEvent', '', '强制退出程序');
        initApi('SN', 'SendCaptureLostEvent', '', '强制退出程序');
        initApi('SN', 'NotifyMoveOrResizeStarted', '', '强制退出程序');
        initApi('SN', 'GetWindowlessFrameRate', '', '强制退出程序');
        initApi('SN', 'SetWindowlessFrameRate', '', '强制退出程序');
        initApi('SN', 'HandleKeyEventBeforeTextInputClient', '', '强制退出程序');
        initApi('SN', 'HandleKeyEventAfterTextInputClient', '', '强制退出程序');
        initApi('SN', 'IsWindowRenderingDisabled', '', '强制退出程序');
     

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