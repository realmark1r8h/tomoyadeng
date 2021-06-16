(function() {

	methodArr = [];
	settingsArr = [];

	initApi('SN', 'GetHost', '', '获取浏览器宿主对象');
	initApi('SN', 'CanGoBack', '', '是否可后退');
	initApi('SN', 'GoBack', '', '后退');
	initApi('SN', 'CanGoForward', '', '能否前进');
	initApi('SN', 'GoForward', '', '前进');
	initApi('SN', 'IsLoading', '', '是否正在加载页面');
	initApi('SN', 'Reload', '', '重新加载页面');
	initApi('SN', 'ReloadIgnoreCache', '', '重新加载页面，无视任何缓存数据');
	initApi('SN', 'StopLoad', '', '停止加载页面');
	initApi('SN', 'GetIdentifier', '', '获取浏览器ID');
	initApi('SN', 'IsSame', '', '与另一个Borwser对象比较是否相等');
	initApi('SN', 'IsPopup', '', '是否为一个弹出窗口');
	initApi('SN', 'HasDocument', '', '是否在浏览器中加载了文档');
	initApi('SN', 'GetMainFrame', '', '返回浏览器窗口的主（顶层）框架Frame');
	initApi('SN', 'GetFocusedFrame', '', '返回浏览器窗口的焦点框架Frame');
	initApi('SN', 'GetFrame', '', '通过名称或ID获取Frame');
	initApi('SN', 'GetFrameCount', '', '获取Frame个数');
	initApi('SN', 'GetFrameIdentifiers', '', '获取所有Frame的ID，返回一个数组[]');
	initApi('SN', 'GetFrameNames', '', '获取所有Frame的名称，返回一个数组[]');
	
	initApi('SN', 'currentFrame', '', '获取当前Frame');
 

	 

	$(function() {

		createApiTable($('#method'), methodArr); 
		includes('BrowserWindow');
		console.dir(BrowserWindow);

		var win = BrowserWindow.currentWindow;
		console.log(30001);
		console.dir(win);
		var browser = win.getBrowser();
		console.dir(browser);

		$('#reload').on('click', function() {
			browser.Reload();
		});
		$('#getFrameCount').on('click', function() {
			alert(browser.GetFrameCount());
		});

	})
})();