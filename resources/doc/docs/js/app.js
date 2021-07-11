(function() {

	methodArr = [];
	settingsArr = [];

	initApi('SS', 'getConfig', 'Object', '获取程序配置信息', '[key], String(可选), 配置项');
	initApi('SN', 'setConfig', '', '更新程序配置信息', 'options, Object, 需要更新的键值');
	initApi('SP', 'gloabl', '', '获取全局数据');
	initApi('SN', 'setGlobal', '', '设置全局数据，用法与setConfig相同，只是两者使用不同的变量保存数据');
	initApi('SN', 'getGlobal', '', '获取全局数据，用法与getConfig相同');

	initApi('SS', 'toAbsolutePath', 'String', '获取程序配置信息', 'path, String, 路径');
	initApi('SN', 'addUrlMapping', 'Boolean',
		`将一个网络路径映射为本地路径，URL必须是一个完整的绝对路径(以网络协议开头，
                                如：http://、file:///)， 本地路径可以是一个目录，也可以是一个文件`,
		'url, String, 网络路径', 'path, String, 本地路径');
	initApi('SN', 'removeUrlMapping', 'Boolean', '取消URL的本地路径映射', 'url, String, 网络路径');
	initApi('SS', 'urlToNativeFile', '', '将URL转换为本地路径', 'url, String, 网络路径', '[needExist], Boolean, 是否要求文件存在,默认为false');
	initApi('SN', 'quit', '', '正常退出程序，页面可以阻止程序退出');
	initApi('SN', 'exit', '', '强制退出程序');

	initSettings('single_process', 'Boolean', '是否在单进程中使用CEF, 默认true');
	initSettings('locale', 'String', 'CEF语言环境, 默认中文"zh-CN"');
	initSettings('useNode', 'Boolean', '是否使用NodeJS, 默认false');
	initSettings('useNodeProcess', 'Boolean', '是否在单独的进程中使用NodeJS, 默认false');
	initSettings('debugNode', 'Boolean', '是否允许调试NodeJs, 默认false, 如果需要调试NodeJs需要在控制台模式下进行');
	initSettings('appPath', 'String', '程序所在磁盘的完整路径');
	initSettings('appDir', 'String', '程序所在磁盘目录');
	initSettings('appName', 'String', '程序名称');
	initSettings('skinDir', 'String', '资源文件所在目录,默认%appDir%skin');
	initSettings('workDir', 'String', '程序工作目录，默认%appDir%');
	initSettings('webDir', 'String', 'Web代码所在目录，默认%appDir%web');
	initSettings('homeDir', 'String', '用户数据根目录，默认%appDataDir%appName');
	initSettings('downloadsDir', 'String', '文件下载目录，默认%homeDir%downloads');
	initSettings('musicsDir', 'String', '音乐目录，默认%homeDir%musics');
	initSettings('picturesDir', 'String', '图片目录，默认%homeDir%pictures');
	initSettings('videosDir', 'String', '视频目录，默认%homeDir%videos');
	initSettings('dragClassName', 'String', '允许拖拽移动窗口的元素类名，默认"drag"。（&lt;div class="drag"&gt;&lt;/div&gt;,如果鼠标在当前元素或其子元素上，按下左键可以移动整个窗口）');
	initSettings('noDragClassName', 'String', '不允许拖拽移动窗口的元素类名，默认"no-drag"');

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		include('app');
		console.dir(app);

		$('#getConfig').on('click', function() {
			var val = app.getConfig();
			console.dir(val);
		});

		$('#setConfig').on('click', function() {
			app.setConfig({
				downloads: '%appDir%download',
				musics: 'ddddd',
				urlMap: [
					{ '322323': '44444' },
					{ '5555': '5555' }
				],
				videos: '%appDir%/中文目录'
			});

		});

		$('#getOne').on('click', function() {
			var val = app.getConfig('appDir');
			console.dir(val);
		});
		
		$('#getGlobal').on('click', function() {
			var val = app.getGlobal();
			console.dir(val);
		});

		$('#setGlobal').on('click', function() {
			app.setGlobal({
				downloads: '%appDir%download',
				musics: 'ddddd',
				urlMap: [
					{ '322323': '44444' },
					{ '5555': '5555' }
				],
				videos: '%appDir%/中文目录'
			});

		});

		$('#global2').on('click', function() {
			var val = app.data;
			console.dir(val);
		});


		$('#toAbsolutePath').on('click', function() {
			alert(app.toAbsolutePath('%appDir%download'));
		});

		$('#addUrlMapping').on('click', function() {
			app.addUrlMapping('http://www.baidu.com', '%webDir%');
		});

		$('#removeUrlMapping').on('click', function() {
			app.removeUrlMapping('http://www.baidu.com');
		});

		$('#urlToNativePath').on('click', function() {
			alert(app.urlToNativePath('http://www.baidu.com/test.html'));
		});

		$('#quit').on('click', function() {
			app.quit();
		});
		$('#exit').on('click', function() {
			app.exit();
		});

	})
})();