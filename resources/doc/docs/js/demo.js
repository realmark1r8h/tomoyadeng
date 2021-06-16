includes('BrowserWindow');

(function() {
    $(function() {
        $('#youdao').on('click', function() {
            var win1 = new BrowserWindow({
                hasShadow: true,
                titleBar: false,
                offscreen: true,
                transparent: true,
                width: 960,
                height: 650,
                sizebox: "4,4,6,6",
                url: "http://127.0.0.1:8020/example/youdao/main.html"
            });
        });
        $('#qq').on('click', function() {
            var win3 = new BrowserWindow({

                offscreen: true,
                transparent: true,
                minimizable: false,
                resizeable: false,
                windowColor: 0x0,
                roundcorner: 5,
                hasShadow: true,
                width: 430,
                height: 330,
                minWidth: 430,
                minHeight: 330,
                maxinfo: "",
                url: "http://127.0.0.1:8020/example/QQ/login.html"
            });
        });
        $('#photo').on('click', function() {
            var win1 = new BrowserWindow({
                parent: BrowserWindow.currentWindow,
                hasShadow: true,
                titleBar: false,
                offscreen: true,
                transparent: true,
                windowColor: 0x0,
                roundcorner: 3,
                width: 760,
                height: 500,
                sizebox: "4,4,6,6",
                url: "http://127.0.0.1:8020/example/photo/jquery-photo-gallery/gallery.html"
            });
        });

        $('#musicPlayer').on('click', function() {
            var win1 = new BrowserWindow({
                alwaysOnTop: true,
                hasShadow: false,
                titleBar: false,
                offscreen: true,
                transparent: true,
                windowColor: 0x0,
                roundcorner: 5,
                resizeable: false,
                width: 300,
                height: 565,
                minWidth: 300,
                minHeight: 565,
                maxWidth: 300,
                maxHeight: 565,
                maxinfo: "",
                url: "http://127.0.0.1:8020/example/musicPlayer/player.html"
            });
        });
        
        $('#appCreator').on('click', function() {
            var win1 = new BrowserWindow({
                alwaysOnTop: false,
                hasShadow: true,
                titleBar: false,
                offscreen: false,  
                roundcorner: 5,
                resizeable: false,
                maxizable:false,
                width:420,
                height: 650,
                minWidth: 420,
                minHeight: 650,
                maxWidth: 420,
                maxHeight: 650,
                maxinfo: "",
                title:"程序生成器",
                url: "http://127.0.0.1:8020/example/appCreator/setting.html"
            });
        });
        $('#baiduPlayer').on('click', function() {
             winBaidu = new BrowserWindow({ 
                width: 1000,
                height: 700,
                minWidth: 1000,
                minHeight: 700,
               	title:"百度音乐",
                maxinfo: "",
                url: "http://fm.baidu.com"
            });
            winBaidu.on('LoadEnd', function(event){
            	console.dir(event);
            	if(event.data[1].IsMain())
            	
//          	event.data[1].injectSrcipt('http://apps.bdimg.com/libs/jquery/2.1.4/jquery.min.js');
        		event.data[1].injectSrcipt('http://127.0.0.1:8020/example/baiduPlayer/js/player.js');
            	
            	
            	 console.log(3333999);
            });
        });
        
    })
})();