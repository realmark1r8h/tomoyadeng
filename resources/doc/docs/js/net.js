

(function() {
    methodArr = [];
    settingsArr = [];

     
    initApi('SN', 'download', 'Object', '下载文件，返回一个Downloader对象，用法与Downloader相同');
    initApi('SN', 'request', 'Object', '下载文件，返回一个URLRequest对象，用法与URLRequest相同');
 

    $(function() {
        createApiTable($('#method'), methodArr); 
        includes('net'); 
        
    	console.dir(net);
        $('#downloader').on('click', function() {
            var downloader = net.download({ 
                url: "https://dldir1.qq.com/qqfile/qq/TIM1.2.0/21645/TIM1.2.0.exe"
            });
            downloader.on('update', function(obj){
            	 var html = $('#downloadInfo').html();
            	 html = html.format(obj);
            	 $('.info').empty().append(html);
            });
            downloader.on('complete', function(obj){
            	alert('下载完成');
            })
        });
        
    })
})();