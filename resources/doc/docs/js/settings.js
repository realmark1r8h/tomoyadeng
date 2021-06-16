includes('BrowserWindow', 'rcedit');

var fileKeyMaps = {
    Comments: '评论',
    CompanyName: '公司名称',
    FileDescription: '文件描述',
    FileVersion: '文件版本',
    InternalName: '内部名称',
    LegalCopyright: '法律著作权',
    LegalTrademarks: '合法商标',
    OriginalFileName: '原始文件名称',
    ProductName: '产品名称',
    ProductVersion: '产品版本',
    PrivateBuild: '私人定制',
    SpecialBuild: '特殊定制',
    icon:'程序图标'
}

var appKeysMaps = {
    useNode: '使用NODEJS',
    useNodeProcess: '使用NODEJS进程',
    debugNode: '调试NODEJS',
    skinDir: '资源目录',
    webDir: 'WEB目录',
    homeDir: '数据主目录',
    downloadsDir: '下载目录',
    musicsDir: '音乐目录',
    picturesDir: '图片目录',
    videosDir: '视频目录',
    single_process: '单进程模式',
    locale:'语言',
    background_color:'背景颜色'

}
$(function() {

    rcedit.loadDiskSettings('rcedit.json');
    var strDefaultFileSettings = rcedit.getDefaultFileSettings();
    var strDefaultAppSettings = rcedit.getDefaultAppSettings();
    var strDefaultBrowserSettings = rcedit.getDefaultBrowserSettings();

    console.dir(strDefaultFileSettings);
    console.dir(strDefaultAppSettings);
    console.dir(strDefaultBrowserSettings);
    //      
    ////      var strDefaultAppSettings = '{\"single_instance\":true,\"single_process\":true,\"no_sandbox\":true,\"multi_threaded_message_loop\":false,\"command_line_args_disabled\":false,\"persist_session_cookies\":true,\"locale\":\"zh-CN\",\"log_severity\":99,\"pack_loading_disabled\":false,\"remote_debugging_port\":8088,\"uncaught_exception_stack_size\":1000,\"context_safety_implementation\":true,\"ignore_certificate_errors\":true,\"background_color\":4294967295}';

    var defaultFileSettings = JSON.parse(strDefaultFileSettings);
    var defaultAppSettings = JSON.parse(strDefaultAppSettings);
    var defaultBrowserSettings = JSON.parse(strDefaultBrowserSettings);

    console.dir(defaultFileSettings);
    console.dir(defaultAppSettings);
    console.dir(defaultBrowserSettings);

    function fillElement2($container, key, val, text) {
        var html = $('#templateInputGroup').html();
        console.log(html);
        console.log('----------------' + key + ', ' + val);
        html = html.format2([key, val, text]);
        console.log(html);
        $container.append(html);
        return true;
    }

    for(var p in defaultFileSettings) {
        fillElement2($('#fileSettings .with-padding'), p, defaultFileSettings[p], fileKeyMaps[p]);
        var str = defaultFileSettings[p] + ',';
        console.dir(p + "," + str);

    }

    for(var p in defaultAppSettings) {
        fillElement2($('#appSettings .with-padding'), p, defaultAppSettings[p], appKeysMaps[p]);
        var str = defaultAppSettings[p] + ',';
        console.dir(p + "," + str);

    }

    for(var p in defaultBrowserSettings) {
        fillElement2($('#browserSettings .with-padding'), p, defaultBrowserSettings[p], p);
        var str = defaultBrowserSettings[p] + ',';
        console.dir(p + "," + str);
    }

    $('#commit').click(function() {
        var d = {};
        var b = $('#fileSettings').find('input');
        var c = $('#appSettings').find('input');
        var d = $('#browserSettings').find('input');

        var a1 = {};
        var b1 = {};
        var c1 = {};
        var d1 = {};

        $.each(b, function() {
            b1[this.name] = this.value;
            console.log(this.name + ', ' + this.value);
        });
        $.each(c, function() {
            c1[this.name] = this.value;
            console.log(this.name + ', ' + this.value);
        });
        $.each(d, function() {
            d1[this.name] = this.value;
            console.log(this.name + ', ' + this.value);
        });

        
        var fileSettings = $.extend({}, defaultFileSettings, b1);
        var appSettings = $.extend({}, defaultAppSettings, c1);
        var browserSettings = $.extend({}, defaultBrowserSettings, d1);
        console.dir(fileSettings);
        console.dir(appSettings);
        console.dir(browserSettings);
        rcedit.commit(JSON.stringify(fileSettings), JSON.stringify(appSettings), JSON.stringify(browserSettings));
    });

    $('.multi-setting').on('change', function() {
        var item = '#' + $(this).data('id')
        var item_card = item + '-card';
        var item_detail = item + '-detail';
        var item_detail_container = item + '-detail-container';

        if($(this).is(':checked')) {
            $(item).appendTo($(item_detail_container));
            $(item_card).show();
            $(item_detail).show();

        } else {
            $(item).insertAfter($(item_card));
            $(item_card).hide();
            $(item_detail).hide();
        }

    });

    $('input[type="checkbox"]').on('change', function() {

        var $self = $(this);
        if($self[0].id == 'nodejs') {
            if($(this).is(':checked')) {
                $('#appSettings').hide();
                $('#borwserSettings').hide();
            } else {
                $('#appSettings').show();
                $('#borwserSettings').show();
            }
        }

        var group = $(this).data('group');
        if(group == undefined || group == '') return;

        $('input[type="checkbox"]').each(function(index, element) {
            if($(element).data('group') != group) return true;
            if($(element).is($self)) return true;
            $(element).removeAttr('checked');
        });

    });

    // Toggle
    $('input[name="resizeable"]').on('change', function() {
        if($(this).is(':checked')) {
            $('#min-rect').hide();
            $('#max-rect').hide();
            $('#sizebox').hide();
        } else {
            $('#min-rect').show();
            $('#max-rect').show();
            $('#sizebox').show();
        }
    });

    $('input[name="IDS_SIZEBOX"]').on('change', function() {
        if($(this).is(':checked')) {
            $('#sizebox-detail').hide();
        } else {
            $('#sizebox-detail').show();
        }
    });

    $('.minbtn').click(function() {
        var win = BrowserWindow.currentWindow;
        win.minimize();
    });

    $('.closebtn').click(function() {
        var win = BrowserWindow.currentWindow;
        win.close();
    });
});