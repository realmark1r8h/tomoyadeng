;
(function() {
	methodArr = [];
	settingsArr = [];

	initApi('MN', 'execute', 'Integer', '执行SQL, 返回受影响的行数', 'sql, String, 要执行的SQL语句', '[arr], Array, SQL格式化参数');
	initApi('MN', 'query', 'Array', '查找数据, 返回所查找到的数据，带有分页功能', 'sql, String, 要执行的SQL语句', '[arr], Array, SQL格式化参数', '[pagging], Object, 分页参数');
	initApi('MN', 'backup', 'Boolean', '备份数据库', 'dstPath, String, 要备份的目标位置');

	$(function() {
		createApiTable($('#method'), methodArr);
		includes('Sqlite');
		console.dir(Sqlite);

		$('#open').on('click', function() {
			db = new Sqlite('E:/amoylel/test.db');

		});

		$('#execute').on('click', function() {
			var val = db.execute('select * from abc');
			alert(val.length);
			console.dir(val);
		});

		$('#insert').on('click', function() {
			var str = new Date().toString();
			var val = db.execute(`insert into abc (a, b, c) values('{0}', {1}, {2});`, [str, 1, 33.22]);
			if(val == 1) {
				alert('插入成功');
			}
		});

		$('#remove').on('click', function() {
			var val = db.execute(`DELETE FROM abc where b='{0}'`, [1]);
			alert('删除' + val + '条数据');
		});

		$('#update').on('click', function() {
			var val = db.execute(`UPDATE abc SET a='{0}' where b = {1}`, [new Date().toString(), 2]);
			alert('更新' + val + '条数据');
		});

		$('#query').on('click', function() {
			var val = db.query('select * from abc where b={0}', [1], {rows:2, page:1});
			console.dir(val);
		});
		$('#backup').on('click', function() {
			var val = db.backup('test2.db');
			console.dir(val);
		});
		 
	})
})();