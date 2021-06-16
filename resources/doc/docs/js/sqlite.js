;
(function() {
	methodArr = [];
	settingsArr = [];

	initApi('SN', 'info', '', '强制退出程序');
	initApi('SN', 'screen', '', '强制退出程序');
	initApi('SN', 'mouse', '', '强制退出程序');
	initApi('SN', 'keyboard', '', '强制退出程序');

	$(function() {
		createApiTable($('#method'), methodArr);
		includes('Sqlite');
		console.dir(Sqlite);

		$('#open').on('click', function() {
			sqlite = new Sqlite('E:/amoylel/test.db');

		});

		$('#insert').on('click', function() {
			var str = new Date().toString();
			var val = sqlite.insert('insert into abc (a, b, c) values(\"' + str + '\", 1, 33.22);');
			if(val == 1) {
				alert('插入成功');
			}
		});

		$('#select').on('click', function() {

			var val = sqlite.select('select * from abc');
			alert(val.length);
			console.dir(val);
		});
	})
})();