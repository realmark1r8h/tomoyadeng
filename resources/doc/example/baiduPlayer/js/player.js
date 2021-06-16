;(function(){
    $(function(){
       
       $('div, body, html').addClass('drag');
       $('button, input, a, textarea, span, ul').removeClass('drag');
       $('button, input, a, textarea, span, ul').addClass('no-drag');
       $('iframe, .container, .fm-aside').removeClass('drag');
       $('.fm-aside').addClass('no-drag');
       $('.fm-header').append(`<span class="close-btn2 no-drag" style="position: absolute; top: -12px; right: -12px; display: inline-block; width: 49px; height: 49px; text-indent: -999em; overflow: hidden;  background: url('//mu8.bdstatic.com/player/t/i/4nVuIeH5.png') no-repeat 0 0;  cursor: pointer;"></span>`);
 
      include('BrowserWindow');
       var win = BrowserWindow.currentWindow;
	    win.on('maximize', function() {
	        $('.restorebtn').removeClass('hidden');
	        $('.maxbtn').addClass('hidden');
	    });
	
	    win.on('restore', function() {
	        $('.maxbtn').removeClass('hidden');
	        $('.restorebtn').addClass('hidden');
	    });
	
	    $('.minbtn').click(function() {
	        win.minimize();
	    });
	
	    $('.maxbtn').click(function() {
	        win.maximize();
	    });
	
	    $('.restorebtn').click(function() {
	        win.restore();
	    });
	
	    $('.close-btn2').click(function(event) { 
	        win.close();
	    })
    });
})();
