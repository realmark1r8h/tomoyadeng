(function() {

	methodArr = [];
	settingsArr = [];

	initApi('MN', 'IsValid', 'Boolean', '是否有效');
	initApi('MN', 'Undo', '', '撤销');
	initApi('MN', 'Redo', '', '重做');
	initApi('MN', 'Cut', '', '剪切');
	initApi('MN', 'Copy', '', '复制');
	initApi('MN', 'Paste', '', '粘贴');
	initApi('MN', 'Delete', '', '删除');
	initApi('MN', 'SelectAll', '', '全选');
	initApi('MN', 'ViewSource', '', '将当前框架的HTML源代码保存到一个临时文件中，并用默认文本查看应用程序打开');
	initApi('MN', 'GetSource', 'String', '获取前框架的HTML源代码');
	initApi('MN', 'GetText', 'String', '获取显示文本');
	initApi('MN', 'LoadRequest', '', '加载请求');
	initApi('MN', 'LoadURL', '', '加载URL');
	initApi('MN', 'LoadString', '', '加载字符串');
	initApi('MN', 'IsMain', 'Boolean', '是否为主框架');
	initApi('MN', 'IsFocused', 'Boolean', '是否获得焦点');
	initApi('MN', 'GetName', 'String', '获取框架名');
	initApi('MN', 'GetIdentifier', 'Integer', '获取框架ID');
	initApi('MN', 'GetParent', 'Object', '获取父框架');
	initApi('MN', 'GetURL', 'Sting', '获取URL');
	initApi('MN', 'GetBrowser', 'Object', '获取所属Browser');

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