;
(function() {
	methodArr = [];
	settingsArr = [];

	initApi('MN', 'execute', 'Integer', '执行SQL, 返回受影响的行数', 'sql, String, 要执行的SQL语句', '[arr], Array, SQL格式化参数');
	initApi('MN', 'query', 'Array', '查找数据, 返回所查找到的数据，带有分页功能', 'sql, String, 要执行的SQL语句', '[arr], Array, SQL格式化参数', '[pagging], Object, 分页参数');
	initApi('MN', 'backup', 'Boolean', '备份数据库', 'dstPath, String, 要备份的目标位置');

	$(function() {
		createApiTable($('#method'), methodArr);
		includes('Ext', 'Path');
		console.dir(Path);
 
		$('#open').on('click', function() {
			 include('Thread');
			 var thread = new Thread();
			 
			var path = new Path('E:/aaa.ab');
			path.attach(thread);
			path.toString();
		});
 
	})
})();