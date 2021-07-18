(function() {
	methodArr = [];
	settingsArr = [];
	initApi('SS', 'show', '', '显示启动窗口,之前未关闭的启动窗口会被关闭，', 'options, Object, 窗口显示参数');
	initApi('SS', 'hide', '', '关闭启动窗口', '[fadeout], Integer, 关闭动画时间，如果无此参数，默认会使用fadeout的值');
	initApi('SS', 'isVisible', 'Boolean', '启动窗口是否可见');

	initSettings('image', 'String', '需要显示的图片路径');
	initSettings('duration', 'Integer', '窗口显示时间，默认为0（不关闭窗口）');
	initSettings('fadeout', 'Integer', '窗口关闭时的动画时间，默认1000ms');
	
	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		includes('splash');

		console.dir(splash);
		$('#show').on('click', function() {
			splash.show({
				image: 'skin/2.jpg'
			});

		});

		$('#showWithDelay').on('click', function() {
			// 5秒后自动关闭
			splash.show({
				image: 'skin/2.jpg',
				duration: 5000
			});
		});

		$('#hide').on('click', function() {
			splash.hide();
		});

		$('#hideWithDelay').on('click', function() {
			splash.hide(3000);
		});
	})
})();