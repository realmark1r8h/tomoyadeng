(function() {

	methodArr = [];
	settingsArr = [];

 initApi('SS', 'IsValid', '', '强制退出程序');
       initApi('SS', 'Undo', '', '强制退出程序');
       initApi('SS', 'Redo', '', '强制退出程序');
       initApi('SS', 'Cut', '', '强制退出程序');
       initApi('SS', 'Copy', '', '强制退出程序');
       initApi('SS', 'Paste', '', '强制退出程序');
       initApi('SS', 'Delete', '', '强制退出程序');
       initApi('SS', 'SelectAll', '', '强制退出程序');
       initApi('SS', 'ViewSource', '', '强制退出程序');
       initApi('SS', 'GetSource', '', '强制退出程序');
       initApi('SS', 'GetText', '', '强制退出程序');
       initApi('SS', 'LoadRequest', '', '强制退出程序');
       initApi('SS', 'LoadURL', '', '强制退出程序');
       initApi('SS', 'LoadString', '', '强制退出程序');
       initApi('SS', 'IsMain', '', '强制退出程序');
       initApi('SS', 'IsFocused', '', '强制退出程序');
       initApi('SS', 'GetName', '', '强制退出程序');
       initApi('SS', 'GetIdentifier', '', '强制退出程序');
       initApi('SS', 'GetParent', '', '强制退出程序');
       initApi('SS', 'GetURL', '', '强制退出程序');
       initApi('SS', 'GetBrowser', '', '强制退出程序');
         

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		includes('BrowserWindow');
		console.dir(BrowserWindow);

		var win = BrowserWindow.currentWindow;
		console.log(30001);
		console.dir(win);
		var browser = win.getBrowser();
		var frame = browser.currentFrame();
		console.dir(browser);

		$('#selectAll').on('click', function() {
			frame.SelectAll();
		});
		$('#loadUrl').on('click', function() {
			frame.LoadURL('https://www.baidu.com');
		});

	})
})();