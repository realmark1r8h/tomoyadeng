(function() {
	methodArr = [];
 
	initApi('SS', 'getScreenInfo', 'Object', '获取屏幕信息,包括屏幕大小和工作区域大小');
  
	$(function() {
		createApiTable($('#method'), methodArr);
		include('desktop');

		console.dir(desktop);

		$('#getScreenInfo').on('click', function() {
			var info = desktop.getScreenInfo();
			console.dir(info);
		});
		 
	})
})();