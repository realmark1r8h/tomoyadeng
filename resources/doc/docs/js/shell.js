(function() {
	methodArr = [];
	settingsArr = [];
	initApi('SS', 'exec', 'Array', '完整的ShellExecute',
		'operator, String, 指定动作, 譬如: open、runas、print、edit、explore、find',
		'file, String, 指定要打开的文件或程序',
		'param, String, 给要打开的程序指定参数; 如果打开的是文件这里应该是 ""',
		'dir, String, 缺省目录',
		'[showCmd], Integer, 打开选项, 默认SW_SHOWNORMAL'
	);
	
	initApi('SS', 'open', '', '打开文件');
	initApi('SS', 'print', '', '打印文件');
	initApi('SS', 'showItemInFolder', '', '在文件夹中显示文件');

	initSettings('SW_HIDE', 'Integer', 'SW_HIDE');
	initSettings('SW_MINIMIZE', 'Integer', 'SW_MINIMIZE');
	initSettings('SW_RESTORE', 'Integer', 'SW_RESTORE');
	initSettings('SW_SHOW', 'Integer', 'SW_SHOW');
	initSettings('SW_SHOWMAXIMIZED', 'Integer', ' SW_SHOWMAXIMIZED');
	initSettings('SW_SHOWMINIMIZED', 'Integer', 'SW_SHOWMINIMIZED');
	initSettings('SW_SHOWMINNOACTIVE', 'Integer', 'SW_SHOWMINNOACTIVE');
	initSettings('SW_SHOWNA', 'Integer', 'SW_SHOWNA');
	initSettings('SW_SHOWNOACTIVATE', 'Integer', 'SW_SHOWNOACTIVATE');
	initSettings('SW_SHOWNORMAL', 'Integer', 'SW_SHOWNORMAL');

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		include('shell');

		console.dir(shell);
		$('#open').on('click', function() {
			shell.open("www.baidu.com");
		});
		$('#print').on('click', function() {
			shell.print("images\\2.jpg");
		});
		$('#exec').on('click', function() {
			shell.exec("open", "D:/pic");
		});
		$('#showItemInFolder').on('click', function() {
			shell.showItemInFolder('images\\2.jpg');
		});
		$('#location').on('click', function() {
			shell.exec("open", "explorer", "/e, /select, images\\2.jpg", "", shell.SW_SHOWNORMAL);
		});
	})

})();