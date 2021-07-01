;
(function() {
	methodArr = [];
	settingsArr = [];

	initApi('MN', 'execute', 'Integer', '执行SQL, 返回受影响的行数', 'sql, String, 要执行的SQL语句');
	initApi('MN', 'insert', 'Integer', '插入数据, 返回受影响的行数', 'sql, String, 要执行的SQL语句');
	initApi('MN', 'remove', 'Integer', '删除数据, 返回受影响的行数', 'sql, String, 要执行的SQL语句');
	initApi('MN', 'update', 'Integer', '更新数据, 返回受影响的行数', 'sql, String, 要执行的SQL语句');
	initApi('MN', 'select', 'Array', '查找数据, 返回所查找到的数据', 'sql, String, 要执行的SQL语句');
	initApi('MN', 'load', 'Object', '通过ID加载数据', 'sql, String, 要执行的SQL语句');
	initApi('MN', 'backup', 'Boolean', '备份数据库', 'dstPath, String, 要备份的目标位置');

	$(function() {
		createApiTable($('#method'), methodArr);
		includes('Sqlite');
		console.dir(Sqlite);

		$('#open').on('click', function() {
			db = new Sqlite('E:/amoylel/test.db');

		});

		$('#execute').on('click', function() {
			var val = db.select('select * from abc');
			alert(val.length);
			console.dir(val);
		});

		$('#insert').on('click', function() {
			var str = new Date().toString();
			var val = db.insert('insert into abc (a, b, c) values(\"' + str + '\", 1, 33.22);');
			if(val == 1) {
				alert('插入成功');
			}
		});

		$('#remove').on('click', function() {
			var val = db.select('select * from abc');
			alert(val.length);
			console.dir(val);
		});

		$('#update').on('click', function() {
			var val = db.select('select * from abc');
			alert(val.length);
			console.dir(val);
		});

		$('#select').on('click', function() {
			var val = db.select('select * from abc');
			alert(val.length);
			console.dir(val);
		});

		$('#load').on('click', function() {
			var val = db.select('select * from abc');
			alert(val.length);
			console.dir(val);
		});
	})
})();