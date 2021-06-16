(function() {
    methodArr = [];
    settingsArr = [];
    eventArr = [];

    initApi('CC', 'new Downloader', '', '生成一个下载类', 'options, Object, 下载配置');
    initApi('MN', 'start', '', '开始下载');
    initApi('MN', 'resume', '', '恢复下载');
    initApi('MN', 'pause', '', '暂停下载');
    initApi('MN', 'cancel', '', '取消下载');

    initSettings('url', 'String', '需要下载的文件网络路径');
    initSettings('file', 'String', '保存文件的磁盘路径, 默认根据url自动命名');
    initSettings('autoDownload', 'Boolean', '是否自动下载，默认true');
    initSettings('forceReplace', 'Boolean', '昌否强制覆盖已存在的文件， 默认true');

    initEvent('start', '', '开始下载时触发');
    initEvent('resume', '', '恢复下载时触发');
    initEvent('pause', '', '暂停下载时触发');
    initEvent('cancel', '', '取消下载时触发');
    initEvent('canceled', '', '取消下载完成后时触发');
    initEvent('update', '', '下载数据更新时触发');
    initEvent('complete', '', '下载完成时触发');

    $(function() {
        createApiTable($('#method'), methodArr);
        createSettingsTable($('#settings'), settingsArr);
        createEventTable($('#event'), eventArr);
        
        includes('Downloader');
        console.dir(Downloader);

        $('#autoDownload').on('click', function() {
            var downloader = new Downloader({
                url: "https://dldir1.qq.com/qqfile/qq/TIM1.2.0/21645/TIM1.2.0.exe",
                //              file:'d:/TIM1.2.0.exe'
            });
            window.downloader = downloader;
            downloader.on('start', function(obj) {
                console.dir(obj);
            });
            downloader.on('update', function(obj) {
                var html = $('#downloadInfo').html();
                html = html.format(obj);
                $('.info').empty().append(html);
            });
            downloader.on('complete', function(obj) {
                alert('下载完成');
            });
            downloader.on('canceled', function(obj) {
                alert('下载取消');
            })
        });
        $('#download2').on('click', function() {
            var downloader = new Downloader({
                url: "https://dldir1.qq.com/qqfile/qq/TIM1.2.0/21645/TIM1.2.0.exe",
                autoDownload: false,
                //              file:'d:/TIM1.2.0.exe'
            });
            window.downloader = downloader;
            downloader.on('start', function(obj) {
                console.dir(obj);
            });
            downloader.on('update', function(obj) {
                var html = $('#downloadInfo').html();
                html = html.format(obj);
                $('.info').empty().append(html);
            });
            downloader.on('complete', function(obj) {
                alert('下载完成');
            });
            downloader.on('canceled', function(obj) {
                alert('下载取消');
            })
        });
        $('#start').on('click', function() {
            downloader.start();
        });
        $('#pause').on('click', function() {
            downloader.pause();
        });
        $('#resume').on('click', function() {
            downloader.resume();
        });
        $('#cancel').on('click', function() {
            downloader.cancel();
        })

    })
})();