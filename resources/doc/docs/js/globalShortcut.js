;(function() {
	methodArr = [];
	settingsArr = [];
	eventArr = [];

	initApi('SS', 'registerShortcut', 'Integer', '注册快捷键, 返回一个ID，如果为0则表示注册失败', '[options|keys], Object|String, 快捷键内容Object或者String(MOD_CONTROL+MOD_ALT+O)');
	initApi('SS', 'isRegistered', 'Boolean', '判断快捷键是否注册', '[id|keys], Integer|String, 快捷键ID或者String');
	initApi('SN', 'unregisterShortcut', '', '反注册快捷键', '[id|keys], Integer|String, <br>id: 快捷键ID <br>keys: 快捷键字符串内容');
	initApi('SN', 'unregisterAll', '', '反注册所有快捷键');

	initSettings('ctrl', 'Boolean', 'MOD_CTRL');
	initSettings('win', 'Boolean', 'MOD_WIN');
	initSettings('alt', 'Boolean', 'MOD_ALT');
	initSettings('shift', 'Boolean', 'MOD_SHIFT');
	//	
	initSettings('key', 'String', '字母或数字按键，一个字符');
	initSettings('action', 'String', '当前快捷键所触发的预定义事件');
	//
	initEvent('hotkeydown', '', '快捷键按下时触发');

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		createEventTable($('#eventSettings'), eventArr);
		includes('globalShortcut', 'BrowserWindow', 'dialog');
		console.dir(globalShortcut);
	alert(44);
		var win = BrowserWindow.currentWindow;

		$('#registerShortcut').on('click', function() {
			var result = globalShortcut.registerShortcut({ ctrl: true, alt: true, key: 'O', action: 'toggleVisible' });
			if(result == 0) {
				alert('注册失败')
			} else {
				alert('按下Ctrl+Alt+O显示或隐藏当前窗口');
			}
		});

		$('#isRegistered').on('click', function() {
			alert(globalShortcut.isRegistered('MOD_CONTROL+MOD_ALT+O'));
		});

		$('#unregisterShortcut').on('click', function() {
			globalShortcut.unregisterShortcut('MOD_CONTROL+MOD_ALT+O');
		});

		$('#unregisterAll').on('click', function() {
			globalShortcut.unregisterAll();
		});

		$('#registerShortcutForEvent').on('click', function() {
			var result = globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+P');
			if(result == 0) {
				alert('注册失败')
			} else {
				alert('按下Ctrl+Alt+P试试');
			}

		});

		globalShortcut.unique('hotkeydown', function(target) {
			console.dir('322323');
			console.dir(target);
			dialog.alert(JSON.stringify(target));
		});

	});
})();