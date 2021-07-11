(function() {
	methodArr = [];

	initApi('SS', 'show', '', '显示启动窗口,之前未关闭的启动窗口会被关闭，', 'options, Object, 窗口显示参数');
	initApi('SS', 'hide', '', '关闭启动窗口');
	initApi('SS', 'isVisible', '', '启动窗口是否可见');

	$(function() {
		createApiTable($('#method'), methodArr);
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

	})
})();