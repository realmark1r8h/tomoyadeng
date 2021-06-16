includes('BrowserWindow', 'system');

$(function() {
	var info = system.screen.getScreenInfo();
		console.dir(info);
	$('.login-but').click(function() {
		
		var nWidth = 280;
		var nHeight = 700;
		var top = info.rcWork.top +  (info.rcWork.height - nHeight) / 2;
		var left = info.rcWork.right - nWidth - 50;
		if(top > 100) top = 100;
		
		var win3 = new BrowserWindow({
			roundcorner: 5,
			windowColor: 0x0,
			width: nWidth,
			height: nHeight,
			minWidth: nWidth,
			minHeight: nHeight,
			maxWidth: nWidth,
			maxHeight: nHeight,
			maximizable: false,
			x: left,
			y: top,
			center: false,
			alwaysOnTop: true,
			url: "http://127.0.0.1:8020/example/QQ/main.html"
		});
		BrowserWindow.currentWindow.close();
	})
});