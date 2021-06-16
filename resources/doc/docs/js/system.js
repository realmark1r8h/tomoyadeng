includes('system');

(function() {
	methodArr = [];
	settingsArr = [];

	initApi('SN', 'info', '', '强制退出程序');
	initApi('SN', 'screen', '', '强制退出程序');
	initApi('SN', 'mouse', '', '强制退出程序');
	initApi('SN', 'keyboard', '', '强制退出程序');

	$(function() {
		createApiTable($('#method'), methodArr);
		includes('system');
		console.dir(system);
		$('#info').on('click', function() {
			console.dir(system.info);
		});
		$('#screen').on('click', function() {
			console.dir(system.screen);
		});
		$('#keyboard').on('click', function() {
			console.dir(system.keyboard);
		});
		$('#mouse').on('click', function() {
			console.dir(system.mouse);
		});
	})
})();