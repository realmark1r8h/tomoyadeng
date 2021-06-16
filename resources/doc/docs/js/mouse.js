(function() {
	methodArr = [];
	initApi('SN', 'leftClick', '', '单击左键', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'leftDown', '', '按下左键', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'leftUp', '', '弹起大键',  'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'leftDoubleClick', '', '双击左键', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'rightClick', '', '单击右键', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'rightDown', '', '按下右键', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'rightUp', '', '弹起右键', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'middleClick', '', '单击中键', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'moveTo', '', '移动鼠标到指定位置', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'moveR', '', '移动鼠标到当前位置的相对位置', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'mouseWheel', '', '鼠标滚轮', 'delta, Integer, 偏移量, 正数向上滚动、负数向下滚动');
	initApi('SN', 'saveMousePos', '', '保存鼠标位置,如果不输入位置将使用当前鼠标所在位置', '[x], Integer, X坐标', '[y], Integer, Y坐标');
	initApi('SN', 'restoreMousePos', '', '恢复上次保存的鼠标位置');
	initApi('SN', 'lockMouse', '', '锁定鼠标位置');
	initApi('SN', 'unlockMouse', '', '解除鼠标锁定');
	initApi('SS', 'waitClick', '', '等待鼠标事件');
	initApi('SS', 'getLastClick', '', '检测上次按过的鼠标键');

	initApi('SS', 'getCursorPos', 'Object', '获取当前鼠标在屏幕中的位置，返回对象{x:100, y:100}');
	initApi('SN', 'setCursorPos', '', '设置鼠标在屏幕中的位置，同moveTo', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SS', 'screenToClient', 'Object', '将屏幕位置转换为窗口位置, 返回对象{x:100, y:100}', 'id, String, 窗口ID', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SS', 'clientToScreen', 'Object', '将窗口位置转换为屏幕位置, 返回对象{x:100, y:100}', 'id, String, 窗口ID', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'click', '', '单击左键，同leftClick', 'x, Integer, X坐标', 'y, Integer, Y坐标');
	initApi('SN', 'hideCursor', '', '隐藏鼠标，当前窗口有效');
	initApi('SN', 'showCursor', '', '显示鼠标，当前窗口有效');

 
	$(function() {
		createApiTable($('#method'), methodArr);
		include('mouse');

		console.dir(mouse);
		var x = 100;
		var y = 200;
		$('#leftClick').on('click', function() {
			var val = mouse.leftClick(x, y);
		});
		$('#leftDown').on('click', function() {
			var val = mouse.leftDown(x, y);
		});
		$('#leftUp').on('click', function() {
			var val = mouse.leftUp(x, y);
		});
		$('#leftDoubleClick').on('click', function() {
			var val = mouse.leftDoubleClick(x, y);
		});
		$('#rightClick').on('click', function() {
			var val = mouse.rightClick(x, y);
		});
		$('#rightDown').on('click', function() {
			var val = mouse.rightDown(x, y);
		});
		$('#rightUp').on('click', function() {
			var val = mouse.rightUp(x, y);
		});
		$('#middleClick').on('click', function() {
			var val = mouse.middleClick(x, y);
		});
		$('#moveTo').on('click', function() {
			var val = mouse.moveTo(x, y);
		});
		$('#moveR').on('click', function() {
			var val = mouse.moveR(x, y);
		});
		$('#mouseWheelUp').on('click', function() {
			mouse.click(x, y);
			var val = mouse.mouseWheel(120);
		});
		$('#mouseWheelDown').on('click', function() {

			mouse.click(x, y);
			var val = mouse.mouseWheel(-120);
		});
		$('#saveMousePos').on('click', function() {
			var val = mouse.saveMousePos();
		});
		$('#restoreMousePos').on('click', function() {
			var val = mouse.restoreMousePos();
		});
		$('#lockMouse').on('click', function() {
			var val = mouse.lockMouse();
		});
		$('#unlockMouse').on('click', function() {
			var val = mouse.unlockMouse();
		});
		$('#waitClick').on('click', function() {
			var val = mouse.waitClick();
		});
		$('#getLastClick').on('click', function() {
			var val = mouse.getLastClick();
		});

		$('#getCursorPos').on('click', function() {
			var val = mouse.getCursorPos();
			console.dir(val);
		});

		$('#setCursorPos').on('click', function() {
			var val = mouse.setCursorPos(100, 500);
			console.dir(val);
		});

		$('#sendClick').on('click', function() {
			var val = mouse.click(300, 80);
		});

		$('#screenToClient').on('click', function() {
			var val = mouse.screenToClient(BrowserWindow.currentWindow, 300, 80);
			console.dir(val);
		});

		$('#clientToScreen').on('click', function() {
			var val = mouse.clientToScreen(BrowserWindow.currentWindow, 300, 80);
			console.dir(val);
		});

		$('#hideCursor').on('click', function() {
			var val = mouse.hideCursor();
		});

		$('#showCursor').on('click', function() {
			var val = mouse.showCursor();
		});
	})
})();