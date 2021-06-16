/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};

/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {

/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId])
/******/ 			return installedModules[moduleId].exports;

/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			exports: {},
/******/ 			id: moduleId,
/******/ 			loaded: false
/******/ 		};

/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);

/******/ 		// Flag the module as loaded
/******/ 		module.loaded = true;

/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}


/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;

/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;

/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";

/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(0);
/******/ })
/************************************************************************/
/******/ ({

/***/ 0:
/*!**********************!*\
  !*** multi editword ***!
  \**********************/
/***/ function(module, exports, __webpack_require__) {

	module.exports = __webpack_require__(/*! D:\WWW\dict_desk2\src\entrys\editword\main.js */215);


/***/ },

/***/ 2:
/*!*************************************!*\
  !*** ./src/modules/global/index.js ***!
  \*************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	__webpack_require__(/*! commons/css/global.scss */ 3);

	__webpack_require__(/*! ../rlog */ 7);

	__webpack_require__(/*! ./ydk.extend.js */ 9);

	__webpack_require__(/*! ./ydk.simulate.extend.js */ 10);

	__webpack_require__(/*! ./ydk.config.js */ 11);

	__webpack_require__(/*! ./debug.js */ 13);

/***/ },

/***/ 3:
/*!*************************************!*\
  !*** ./src/commons/css/global.scss ***!
  \*************************************/
/***/ function(module, exports) {

	// removed by extract-text-webpack-plugin

/***/ },

/***/ 7:
/*!***********************************!*\
  !*** ./src/modules/rlog/index.js ***!
  \***********************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.default = rlog;

	var _config = __webpack_require__(/*! config */ 8);

	var _config2 = _interopRequireDefault(_config);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	function rlog(self) {
	  var $this;

	  //判断是否jquery对象
	  if (self.jquery) {
	    $this = self;
	    self = self[0];
	  } else {
	    $this = $(self);
	  }

	  var params = {
	    keyfrom: 'deskdict.main'
	  };

	  _.each(self.attributes, function (attr) {
	    var attrName = attr.name;
	    if (/^data-log-/.test(attrName)) {
	      var val = attr.value;
	      if (!val) {
	        return;
	      }

	      var key = attrName.substring(9);
	      //当为true时候，自动向上查找属性
	      if (val == '^') {
	        var $el = $this.parents('[' + attrName + ']');
	        // console.log($el.length , attrName);
	        //找不到父级属性，跳过
	        if ($el.length == 0) {
	          attr.value = '';
	          return;
	        } else {
	          val = $el[0].getAttribute(attrName);
	          attr.value = val;
	          params[key] = val;
	        }
	      } else {
	        params[key] = val;
	      }
	    }
	  });

	  // console.log(params);

	  ydk.rlog(params);
	} /**
	   * 自动捕获data-log-*的点击事件，触发rlog发送事件
	   * 当data-log-xxx='true'时候，自动找到父级节点
	   *
	   * 如：<a href="#" data-log-action="go_channelList" data-log-location="hot_circle">全部圈子</a>
	   */


	$(document).on('click', '[data-log-action]', function () {
	  rlog(this);
	});

	/**
	 * 自动记录pv，并且可以根据版本号区分
	 */
	$(function () {
	  if (_config2.default.pageId) {
	    ydk.rlog({
	      show: _config2.default.pageId,
	      version: new Date(_config2.default.version).format('yyyy-MM-dd HH:mm:ss')
	    });
	  }
	});

/***/ },

/***/ 8:
/*!****************************!*\
  !*** ./src/conf/config.js ***!
  \****************************/
/***/ function(module, exports) {

	'use strict';

	module.exports = {
	  version: 1489546854380,
	  debug: false,
	  platform: 'win',
	  serverInfoLine: 'http://dict.youdao.com/infoline',
	  swPathPrefix: 'frame:mainFrame://'
	};

/***/ },

/***/ 9:
/*!******************************************!*\
  !*** ./src/modules/global/ydk.extend.js ***!
  \******************************************/
/***/ function(module, exports) {

	'use strict';

	var _typeof = typeof Symbol === "function" && typeof Symbol.iterator === "symbol" ? function (obj) { return typeof obj; } : function (obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; };

	var omit = function omit(params) {
	  return _.omit(params, function (val) {
	    return _.isFunction(val);
	  });
	};

	ydk.extend({

	  rlog: function rlog(params) {
	    ydk._invoke('rlog', omit(params), params);
	  },

	  /**
	   * 以下为PC词典私有方法
	   */

	  /**
	   * 获取信息流数据 和 栏目
	   */
	  getInfoLineData: function getInfoLineData(params) {
	    ydk._invoke('getInfoLineData', params.data, params);
	  },

	  /**
	   * 设置客户端查询关键字
	   * @param {String} params.keyword 关键字
	   * @param {String} params.lang 语言
	   */
	  setKeyword: function setKeyword(params) {
	    ydk._invoke('setKeyword', params, params);
	  },

	  /**
	   * 获取客户端关键字
	   */
	  getKeyword: function getKeyword(params) {
	    ydk._invoke('getKeyword', params, params);
	  },

	  /**
	   * 监听客户端关键字变化，onKeyUp
	   */
	  onKeywordChanged: function onKeywordChanged(params) {
	    ydk._on('onKeywordChanged', {}, params);
	  },

	  /**
	   * 监听客户端关键字变更，onSubmit
	   */
	  onKeywordSubmit: function onKeywordSubmit(params) {
	    ydk._on('onKeywordSubmit', {}, params);
	  },

	  /**
	   * 获取查词释义(本地和网络，哪个先有结果哪个先返回)
	   *
	   * params.data.type:
	   *   quick:：jsonresult，速查页面使用
	   *   detail：jsonapi，查词结果页
	   *   mini：fsearch，mini窗口
	   */
	  getDictResult: function getDictResult(params) {
	    ydk._invoke('getDictResult', params.data, params);
	  },

	  /**
	   * 获取翻译结果
	   */
	  getTranslateResult: function getTranslateResult(params) {
	    ydk._invoke('getTranslateResult', params.data, params);
	  },

	  /**
	   * 获取相似例句结果
	   */
	  getSimsentResult: function getSimsentResult(params) {
	    ydk._invoke('getSimsentResult', params.data, params);
	  },

	  /**
	   * 客户端UI事件
	   *
	   * 仅仅用来，客户端通知前端打开某页面使用
	   *
	   * key: 
	   *   SettingTab设置页
	   *   Feedback反馈页
	   *   Invest调查页面
	   */
	  onTriggerNativeEvent: function onTriggerNativeEvent(params) {
	    ydk._on('onTriggerNativeEvent', {}, params);
	  },

	  /**
	   * 设置客户端左侧激活tab
	   */
	  /*setNativeTab : function(params){
	    ydk._invoke('setNativeTab', {
	      key : params.key
	    } , params);
	  },*/

	  /**
	   * 获取客户端设置
	   */
	  getSetting: function getSetting(params) {
	    ydk._invoke('getSetting', {}, params);
	  },

	  /**
	   * 保存客户端设置
	   */
	  saveSetting: function saveSetting(params) {
	    ydk._invoke('saveSetting', {
	      setting: params.setting
	    }, params);
	  },

	  /**
	   * 设置主窗口URL
	   */
	  /*loadMainURL : function(params){
	    ydk._invoke('loadMainURL' , {
	      url : params.url
	    } , params);
	  },*/

	  /**
	   * 关闭suggest
	   */
	  closeSuggest: function closeSuggest(params) {
	    ydk._invoke('closeSuggest', {}, params);
	  },

	  /**
	   * 监控客户端传输的键盘事件
	   */
	  onNativeKeyDown: function onNativeKeyDown(params) {
	    ydk._on('onNativeKeyDown', {}, params);
	  },

	  /**
	   * 复制到剪贴板
	   */
	  copyToClipboard: function copyToClipboard(params) {
	    ydk._invoke('copyToClipboard', {
	      content: params.content
	    }, params);
	  },

	  /**
	   * 监听广播的消息
	   */
	  onBroadcast: function onBroadcast(params) {
	    //还原数据
	    params._complete = function (res) {
	      if (res.data.format == 'json' && typeof res.data.data == 'string') {
	        res.data.data = JSON.parse(res.data.data);
	      }
	    };
	    ydk._on('onBroadcast', {}, params);
	  },

	  /**
	   * 广播消息
	   *
	   * route.change 页面切换
	   * keyword.submit 查询关键字变更
	   * delete: keyword.submit.to 查询关键字，而打开指定页面
	   * delete: fanyi.submit 翻译指定内容
	   * history.save 通知保存历史记录
	   * 
	   */
	  broadcast: function broadcast(params) {
	    var data = params.data;
	    var format = 'string';
	    //自动格式化数据
	    if ((typeof data === 'undefined' ? 'undefined' : _typeof(data)) == 'object') {
	      data = JSON.stringify(data);
	      format = 'json';
	    }
	    ydk._invoke('broadcast', {
	      type: params.type,
	      format: format,
	      data: data
	    }, params);
	  },

	  /**
	   * 显示历史记录
	   */
	  onHistory: function onHistory(params) {
	    ydk._on('onHistory', {}, params);
	  },

	  /**
	   * 通知客户端，当前是否有历史记录
	   */
	  setHasHistory: function setHasHistory(params) {
	    ydk._invoke('setHasHistory', {
	      has: params.has
	    }, params);
	  },

	  /**
	   * 监听右下角弹窗
	   */
	  onCornerPopupShow: function onCornerPopupShow(params) {
	    ydk._on('onCornerPopupShow', {}, params);
	  },

	  /**
	   * 展示右下角弹窗
	   */
	  showCornerPopup: function showCornerPopup(params) {
	    ydk._invoke('showCornerPopup', {}, params);
	  },

	  /**
	   * 展示划词结果
	   */
	  onStrokeResult: function onStrokeResult(params) {
	    ydk._on('onStrokeResult', {}, params);
	  },

	  /**
	   * 设置划词结果语言
	   */
	  setStroke: function setStroke(params) {
	    ydk._invoke('setStroke', omit(params), params);
	  },

	  /**
	   * 关闭窗口
	   */
	  closeWin: function closeWin(params) {
	    ydk._invoke('closeWin', {}, params);
	  },

	  /**
	   * 检测更新
	   */
	  checkUpdate: function checkUpdate(params) {
	    ydk._invoke('checkUpdate', {}, params);
	  },

	  /**
	   * 设置窗口高度
	   */
	  setWinHeight: function setWinHeight(params) {
	    ydk._invoke('setWinHeight', omit(params), params);
	  },

	  /**
	   * 设置窗口宽高
	   */
	  setWinSize: function setWinSize(params) {
	    ydk._invoke('setWinSize', omit(params), params);
	  },

	  /**
	   * 词典设置更新
	   * (只有客户端修改了设置项，才会更新，saveSetting不会触发)
	   */
	  onSettingChange: function onSettingChange(params) {
	    ydk._on('onSettingChange', {}, params);
	  },

	  /**
	   * 激活词典，置于最前
	   */
	  setTop: function setTop(params) {
	    ydk._invoke('setTop', {}, params);
	  },

	  /**
	   * 检查单词是否添加到单词本
	   */
	  checkWordBook: function checkWordBook(params) {
	    ydk._invoke('checkWordBook', {
	      word: params.word,
	      lang: params.lang
	    }, params);
	  },

	  removeFromWordBook: function removeFromWordBook(params) {
	    ydk._invoke('removeFromWordBook', omit(params), params);
	  },

	  addToWordBook: function addToWordBook(params) {
	    ydk._invoke('addToWordBook', omit(params), params);
	  },

	  updateToWordBook: function updateToWordBook(params) {
	    ydk._invoke('updateToWordBook', omit(params), params);
	  },

	  /**
	   * 同步单词本
	   */
	  syncWordBook: function syncWordBook(params) {
	    ydk._invoke('syncWordBook', {}, params);
	  },

	  /**
	   * 读取单词本
	   */
	  queryWordBook: function queryWordBook(params) {
	    ydk._invoke('queryWordBook', omit(params), params);
	  },

	  /**
	   * 单词本变更
	   */
	  onWordBookChanged: function onWordBookChanged(params) {
	    ydk._on('onWordBookChanged', {}, params);
	  },

	  /**
	   * 读取单词本分类
	   */
	  queryWordBookCategory: function queryWordBookCategory(params) {
	    ydk._invoke('queryWordBookCategory', omit(params), params);
	  },

	  /**
	   * 新增单词本分类
	   */
	  addWordBookCategory: function addWordBookCategory(params) {
	    ydk._invoke('addWordBookCategory', omit(params), params);
	  },

	  /**
	   * 修改单词本分类
	   */
	  updateWordBookCategory: function updateWordBookCategory(params) {
	    ydk._invoke('updateWordBookCategory', omit(params), params);
	  },

	  /**
	   * 删除单词本分类
	   */
	  removeWordBookCategory: function removeWordBookCategory(params) {
	    ydk._invoke('removeWordBookCategory', omit(params), params);
	  },

	  /**
	   * 导入单词本
	   */
	  importToWordBook: function importToWordBook(params) {
	    ydk._invoke('importToWordBook', omit(params), params);
	  },

	  /**
	   * 读取需要复习的单词
	   */
	  queryWordBookForReview: function queryWordBookForReview(params) {
	    ydk._invoke('queryWordBookForReview', omit(params), params);
	  },

	  /**
	   * 复习单词-记得/不记得
	   */
	  reviewWordBook: function reviewWordBook(params) {
	    ydk._invoke('reviewWordBook', omit(params), params);
	  },

	  /**
	   * 导出单词本
	   */
	  exportFromWordBook: function exportFromWordBook(params) {
	    ydk._invoke('exportFromWordBook', omit(params), params);
	  },

	  /**
	   * 批量修改单词分类
	   */
	  setWordBookCategory: function setWordBookCategory(params) {
	    ydk._invoke('setWordBookCategory', omit(params), params);
	  },

	  /**
	   * 批量单词是否加入复习计划
	   */
	  setWordBookPlan: function setWordBookPlan(params) {
	    ydk._invoke('setWordBookPlan', omit(params), params);
	  },
	  /**
	   * 最小化窗口
	   */
	  minimizeWin: function minimizeWin() {
	    ydk._invoke('minimizeWin', {}, {});
	  },

	  /**
	   * 设置debug模式
	   */
	  setDebug: function setDebug(params) {
	    ydk._invoke('setDebug', omit(params), params);
	  },

	  /**
	   * 设置窗口可移动
	   */
	  setWinMove: function setWinMove(params) {
	    ydk._invoke('setWinMove', {}, params);
	  },

	  /**
	   * 显示当前cef窗口
	   */
	  showWin: function showWin(params) {
	    ydk._invoke('showWin', {}, params);
	  },

	  /**
	   * 获取OCR模型列表
	   */
	  getOcrModelList: function getOcrModelList(params) {
	    ydk._invoke('getOcrModelList', {}, params);
	  },

	  /**
	   * 下载/更新OCR模式文件
	   */
	  downloadOcrModel: function downloadOcrModel(params) {
	    ydk._invoke('downloadOcrModel', omit(params), params);
	  },

	  /**
	   * 删除OCR模型文件
	   */
	  removeOcrModel: function removeOcrModel(params) {
	    params = omit(params);
	    ydk._invoke('removeOcrModel', params, params);
	  },

	  /**
	   * 下载进度
	   */
	  onDownloadProgress: function onDownloadProgress(params) {
	    ydk._on('onDownloadProgress', {}, params);
	  },

	  /**
	   * 下载浏览器插件
	   */
	  downloadBrowserPlugin: function downloadBrowserPlugin(params) {
	    params = omit(params);
	    ydk._invoke('downloadBrowserPlugin', params, params);
	  },

	  /**
	   * 当主窗口右侧页面加载
	   */
	  onPageLoadStart: function onPageLoadStart(params) {
	    ydk._on('onPageLoadStart', {}, params);
	  },

	  /**
	   * 保存缓存(基于内存)
	   */
	  saveCache: function saveCache(params) {
	    params = omit(params);
	    ydk._invoke('saveCache', omit(params), params);
	  },

	  /**
	   * 读取缓存
	   */
	  getCache: function getCache(params) {
	    ydk._invoke('getCache', omit(params), params);
	  },

	  /**
	   * 删除缓存
	   */
	  removeCache: function removeCache(params) {
	    params = omit(params);
	    ydk._invoke('removeCache', params, params);
	  },

	  /**
	   * 清空缓存
	   */
	  clearCache: function clearCache(params) {
	    params = omit(params);
	    ydk._invoke('clearCache', params, params);
	  },
	  /**
	   * 打开一个新的cef窗口
	   */
	  openWin: function openWin(params) {
	    params = omit(params);
	    ydk._invoke('openWin', params, params);
	  },
	  /**
	   * 调用客户端发音
	   */
	  playNativeVoice: function playNativeVoice(params) {
	    params = omit(params);
	    ydk._invoke('playNativeVoice', params, params);
	  },
	  /**
	   * 调用客户端停止发音
	   */
	  stopNativeVoice: function stopNativeVoice(params) {
	    ydk._invoke('stopNativeVoice', {}, {});
	  }
	});

/***/ },

/***/ 10:
/*!***************************************************!*\
  !*** ./src/modules/global/ydk.simulate.extend.js ***!
  \***************************************************/
/***/ function(module, exports) {

	"use strict";

	//当页面隐藏时候，停止当前页面的音频
	ydk.onPageVisibilityChange({
	  success: function success(res) {
	    if (res.hidden) {
	      ydk.stopVoice({});
	    }
	  }
	});

/***/ },

/***/ 11:
/*!******************************************!*\
  !*** ./src/modules/global/ydk.config.js ***!
  \******************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	var _event = __webpack_require__(/*! event */ 12);

	var _event2 = _interopRequireDefault(_event);

	var _config = __webpack_require__(/*! config */ 8);

	var _config2 = _interopRequireDefault(_config);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	ydk.config({
	    debug: false, // 开启调试模式,调用的所有api的返回值会在客户端alert出来，若要查看传入的参数，可以在pc端打开，参数信息会通过log打出，仅在pc端时才会打印。
	    jsApiList: ['checkJsApi', 'getClientInfo', 'getNetworkType',
	    // 'onNetStatusChange',
	    'getOrientationStatus', 'onOrientationChange', 'share', 'playVoice', 'pauseVoice', 'stopVoice', 'onVoicePlayEnd', 'onVoicePlayProgress', 'downloadImage', 'ajax', 'isLogin', 'login', 'getUserInfo', 'rlog', // 发log
	    'onPageVisibilityChange', 'onKeywordChanged', 'onNativeKeyDown', 'copyToClipboard', 'getNetworkType', 'onNetStatusChange', 'broadcast', 'onBroadcast', 'setHasHistory', 'onHistory', 'onCornerPopupShow', 'onStrokeResult', 'onSettingChange', 'onPageLoadStart', 'openWin', 'playNativeVoice', 'stopNativeVoice']
	});

	ydk.getClientInfo({
	    success: function success(res) {
	        if (_config2.default.debug) {
	            res.debug = true;
	        }
	        ydk.client = res;
	        _event2.default.trigger('ydk.ready', res);
	    }
	});

/***/ },

/***/ 12:
/*!******************************!*\
  !*** ./src/commons/event.js ***!
  \******************************/
/***/ function(module, exports) {

	"use strict";

	var events = {};

	var copy = function copy(args, start) {
	  // avoid leaking arguments:
	  // http://jsperf.com/closure-with-arguments
	  var len = args.length;
	  var arr = [];
	  for (var i = start; i < len; i++) {
	    arr.push(args[i]);
	  }
	  return arr;
	};

	module.exports = {
	  //一次性事件
	  one: function one(name, callback) {
	    if (!events[name]) {
	      events[name] = [[callback], //one
	      []];
	    } else {
	      events[name][0].push(callback);
	    }
	  },
	  //绑定事件
	  bind: function bind(name, callback) {
	    if (!events[name]) {
	      events[name] = [[], [callback]];
	    } else {
	      events[name][1].push(callback);
	    }
	  },

	  //触发事件
	  trigger: function trigger(name) {
	    var arr = copy(arguments, 1);
	    var es = events[name];
	    if (!es) return;

	    var self = this;

	    $.each(es[0], function (index, callback) {
	      callback.apply(self, arr);
	    });
	    $.each(es[1], function (index, callback) {
	      callback.apply(self, arr);
	    });
	    es[0] = [];
	  }
	};

/***/ },

/***/ 13:
/*!*************************************!*\
  !*** ./src/modules/global/debug.js ***!
  \*************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	var _event = __webpack_require__(/*! event */ 12);

	var _event2 = _interopRequireDefault(_event);

	var _config = __webpack_require__(/*! config */ 8);

	var _config2 = _interopRequireDefault(_config);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	// 开发阶段页面最新版的标识：日期字符串
	// 方便debug模式下确定客户端更新到了最新的模板
	function showVersion(client) {
	  if (client.debug) {
	    // var _dev_flag = $('<a href="http://c.youdao.com/test/dingzq/swydktest.html"></a>')
	    var _dev_flag = $('<a href="frame:mainFrame://ydk.html" class="_dev_flag"></a>');

	    _dev_flag.text(new Date(_config2.default.version).format('yyyy-MM-dd HH:mm:ss')).appendTo(document.body);
	  }
	}

	_event2.default.one('ydk.ready', showVersion);

/***/ },

/***/ 23:
/*!**************************************!*\
  !*** ./src/components/ajax/index.js ***!
  \**************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});

	var _localStorage = __webpack_require__(/*! commons/localStorage.js */ 24);

	var _localStorage2 = _interopRequireDefault(_localStorage);

	__webpack_require__(/*! ./directive.js */ 25);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	var DEFAULT = {
	  isCacheUpdate: function isCacheUpdate(cacheData, ajaxData) {
	    // console.log(cacheData , ajaxData);
	    return JSON.stringify(cacheData) != JSON.stringify(ajaxData);
	  }
	};

	var queryInit = function queryInit(self, refresh) {
	  if (self._on_ajax) return;

	  var cacheData;

	  var cacheKey = _.isFunction(self.dataCache) ? self.dataCache.call(self._context) : self.dataCache;

	  if (cacheKey && !refresh) {
	    cacheData = _localStorage2.default.get(cacheKey);
	    var cacheString = JSON.stringify(cacheData);
	    if (cacheData) {
	      var status = {
	        cache: true
	      };
	      var data;
	      if (self.filter) {
	        try {
	          data = self.filter(cacheData);
	        } catch (e) {
	          data = null;
	          console.error(e);
	        }
	      } else {
	        data = cacheData;
	      }
	      if (data) {
	        self.$emit('ajax-success', cacheData, data, status);

	        //由于$emit('ajax-success')时候，有可能被外部方法修改cacheData，因此需要还原为初始状态的cacheData
	        cacheData = JSON.parse(cacheString);
	        self.$nextTick(function () {
	          self.$emit('ajax-end', cacheData, data, status);
	        });
	      }
	    }
	  }
	  var start = _.now();
	  self.$emit('ajax-before');
	  self._on_ajax = true;
	  self.dataSource({
	    data: self.dataSourceParams,
	    fail: function fail(res) {
	      self.$emit('ajax-complete');
	      self.$emit('ajax-fail', res);
	      self._on_ajax = false;
	    },
	    success: function success(res) {
	      self._on_ajax = false;
	      if (cacheKey && res) {
	        _localStorage2.default.set(cacheKey, res);
	      }
	      var data;
	      var status = {
	        cache: false,
	        sameAsCache: false,
	        duration: _.now() - start
	      };
	      try {

	        if (self.filter) {
	          data = self.filter(res);
	        } else {
	          data = res;
	        }

	        if (cacheKey) {
	          if (self.filter && cacheData) {
	            try {
	              cacheData = self.filter(cacheData);
	            } catch (e) {
	              cacheData = null;
	              console.error(e);
	            }
	          }

	          status.sameAsCache = cacheData && !self.isCacheUpdate(cacheData, data);
	        }
	      } finally {
	        self.$emit('ajax-complete');
	      }

	      self.$emit('ajax-success', res, data, status);
	      self.$nextTick(function () {
	        self.$emit('ajax-end', res, data, status);
	      });
	    }
	  });
	};

	var onVmReady = function onVmReady() {
	  var self = this;

	  self.$on('pulldown-end', function () {
	    queryInit(self, true);
	    return true;
	  });

	  queryInit(self);
	};

	var Ajax = Vue.extend({
	  _is_ajax: true,
	  props: {
	    dataSource: Function,
	    filter: Function,
	    isCacheUpdate: {
	      type: [Function],
	      default: function _default() {
	        return DEFAULT.isCacheUpdate;
	      }
	    },
	    dataCache: [String, Function],
	    dataSourceParams: {
	      type: [Object],
	      default: function _default() {
	        return {};
	      }
	    },
	    out: {
	      type: [String],
	      default: function _default() {
	        return '$ajax';
	      }
	    }

	  },
	  watch: {
	    dataSourceParams: {
	      handler: function handler(val) {
	        queryInit(this, true);
	      },
	      deep: true
	    }
	  },
	  template: '<ajax-scope :out="out"></ajax-scope>',
	  ready: onVmReady
	});

	Vue.component('ajax', Ajax);

	exports.default = Ajax;

/***/ },

/***/ 24:
/*!*************************************!*\
  !*** ./src/commons/localStorage.js ***!
  \*************************************/
/***/ function(module, exports) {

	'use strict';

	var store;

	function generateKey(key) {
	  return KEY_PREFIX + '-' + key;
	}

	if (typeof localStorage === 'undefined' || localStorage === null) {
	  console.log('localStorage不可用');
	  store = false;
	} else {
	  var ls = window.localStorage;
	  var KEY_PREFIX = 'desk';

	  store = {
	    set: function set(key, data) {
	      console.log('【LS】本地存储存储' + key + '数据', data);
	      var val = JSON.stringify(data);
	      key = generateKey(key);
	      try {
	        return ls.setItem(key, val);
	      } catch (e) {
	        if (e.name == 'QuotaExceededError') {
	          ls.clear();
	          ls.setItem(key, val);
	        }
	      }
	    },
	    get: function get(key) {
	      var data = JSON.parse(ls.getItem(generateKey(key)));
	      console.log('【LS】本地存储获取' + key + '数据', data);
	      return data;
	    }
	  };
	}

	module.exports = store;

/***/ },

/***/ 25:
/*!******************************************!*\
  !*** ./src/components/ajax/directive.js ***!
  \******************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	var _diff_update = __webpack_require__(/*! commons/diff_update.js */ 26);

	var _diff_update2 = _interopRequireDefault(_diff_update);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	// var FragmentFactory = Vue.FragmentFactory
	var remove = Vue.util.remove;
	// var before = Vue.util.before
	var replace = Vue.util.replace;
	var defineReactive = Vue.util.defineReactive;
	// var createAnchor = Vue.util.createAnchor
	var extractContent = Vue.util.extractContent;

	Vue.directive('ajax', {});

	var slot = Vue.elementDirective('slot');

	/**
	 *
	 * 为ajax组件构建作用域，并自动初始化内容
	 * 
	 * @see https://github.com/vuejs/vue/blob/dev/src/directives/element/slot.js
	 */
	Vue.elementDirective('ajax-scope', {
	  priority: slot.priority,
	  // _data : null,
	  _scope: null,
	  params: ['out'],
	  bind: function bind() {
	    var self = this;
	    /**
	     * ajax首次绑定时候，需要绑定每个的insert方法，当数据更新时候，只需要更新一次
	     */
	    var _host = self.vm;

	    _host.$on('ajax-success', function (res, data, status) {
	      // console.log('ajax-success' , res , data , status);
	      if (status.sameAsCache) {
	        // console.log('same as cache , skip');
	      } else {
	        self.render(data);
	      }
	    });
	  },
	  compile: function compile(content, context, host, data) {
	    var self = this;
	    var vm = self.vm;
	    var out = self.params.out;
	    if (content && context) {
	      //多个ajax时候，都会修改context，从而影响其他数据
	      var scope = self._scope = Object.create(context);

	      Object.defineProperty(vm, '$ajaxScope', {
	        value: scope,
	        writable: false,
	        enumerable: false,
	        configurable: false
	      });

	      defineReactive(self, '_data', {});

	      Object.defineProperty(scope, out, {
	        get: function get() {
	          return self._data;
	        },
	        set: function set(newData) {
	          if (newData !== self._data) {
	            (0, _diff_update2.default)(self._data, newData);
	          }
	        }
	      });

	      Object.defineProperty(vm, '$ajaxData', {
	        value: scope[out],
	        writable: false,
	        enumerable: false,
	        configurable: false
	      });

	      scope[out] = data;

	      self.unlink = context.$compile(content, host, scope, self._frag);
	    }
	    if (content) {
	      replace(self.el, content);

	      /**
	       * 因为整个vm的ready钩子，在ajax前期已经触发过了，因此需要手动触发子元素的ready钩子
	       *
	       * @see http://vuejs.org.cn/api/#ready
	       */
	      vm.$children.forEach(function (vm2) {
	        if (vm2._isAttached) return;
	        vm2._initDOMHooks();
	        vm2._callHook('attached');
	      });
	    } else {
	      remove(self.el);
	    }
	  },


	  render: function render(data) {
	    var self = this;
	    if (!self.unlink) {
	      // console.debug('insert')
	      self.insert(data);
	    } else {
	      // console.debug('update')
	      self.update(data);
	    }
	  },

	  insert: function insert(data) {
	    var self = this;
	    var content = self.vm._slotContents && self.vm._slotContents['default'];

	    if (!content || !content.hasChildNodes()) {
	      self.fallback();
	    } else {
	      self.compile(content.cloneNode(true), self.vm._context, self.vm, data);
	    }
	  },

	  fallback: function fallback() {
	    var self = this;
	    self.compile(extractContent(self.el, true), self.vm);
	  },


	  update: function update(data) {
	    var self = this,
	        scope = self._scope,
	        out = self.params.out;

	    //深度对比修改
	    scope[out] = data;
	    // DiffUpdate(scope[out] , data);
	  },

	  unbind: function unbind() {
	    var self = this;
	    if (self.unlink) {
	      self.unlink();
	    }
	  }
	});

/***/ },

/***/ 26:
/*!************************************!*\
  !*** ./src/commons/diff_update.js ***!
  \************************************/
/***/ function(module, exports) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	/**
	 * 基于Vue的对象差异更新
	 */
	var defineReactive = Vue.util.defineReactive;

	var diff = function diff(parentSource, sourceKey, source, target, paths) {
	  if (_.isArray(source) && _.isArray(target)) {
	    diffArray(source, target, paths);
	  } else if (_.isObject(source) && _.isObject(target) && !_.isArray(source) && !_.isArray(target)) {
	    diffObject(source, target, paths);
	  } else {
	    //对比基础类型差异
	    if (source != target) {
	      //必须通过父级节点修改，否则修改的只是引用值
	      // console.log(parentSource , sourceKey , target);
	      // parentSource[sourceKey] = target;
	      if (Array.isArray(parentSource)) {
	        parentSource.$set(sourceKey, target);
	      } else {
	        Vue.set(parentSource, sourceKey, target);
	      }
	      logDiff(source, target, paths);
	    }
	  }
	};

	var diffArray = function diffArray(source, target, paths) {
	  var len = source.length;
	  var tlen = target.length;

	  for (var i = Math.min(len, tlen) - 1; i >= 0; i--) {
	    diff(source, i, source[i], target[i], paths + '.' + i);
	  };

	  if (len < tlen) {
	    target.slice(len, tlen).forEach(function (item) {
	      source.push(item);
	    });
	  } else if (len > tlen) {
	    source.splice(tlen, len - tlen);
	  }
	};

	var diffObject = function diffObject(source, target, paths) {

	  Object.keys(source).forEach(function (k) {
	    if (!target.hasOwnProperty(k)) {
	      source[k] = null;
	      // console.debug('delete' , k , source , target);
	    }
	  });

	  Object.keys(target).forEach(function (k) {
	    var p = paths + '.' + k;
	    var sourceVal = source[k];
	    if (target[k] !== undefined && (sourceVal == null || sourceVal == undefined)) {
	      logDiff(source[k], target[k], p);
	      Vue.set(source, k, target[k]);
	    } else {
	      diff(source, k, sourceVal, target[k], p);
	    }
	  });
	};

	var logDiff = function logDiff(source, target, path) {
	  // console.trace('Diff: ' + path , source , target)
	};

	var diffUpdate = function diffUpdate(source, target) {

	  /*Object.keys(target).forEach(function(k){
	    if(!source.hasOwnProperty(k) ){
	      defineReactive(source , k , target[k]);
	    }
	  });*/

	  diff(source, target, source, target, '');
	};

	exports.default = diffUpdate;

/***/ },

/***/ 49:
/*!****************************************!*\
  !*** ./src/modules/urlparams/index.js ***!
  \****************************************/
/***/ function(module, exports) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	function getURLParams(url) {
	  var params = url;
	  var obj = {};
	  if (!params) return obj;
	  params = params.replace(/^[?]{1}|[#]{1}.*$/g, '').split('&');
	  for (var i = 0, len = params.length; i < len; i++) {
	    var e = params[i].split('=');
	    obj[e[0]] = decodeURIComponent(e[1]);
	  }
	  return obj;
	}

	var params = getURLParams(window.location.search);

	var get = exports.get = getURLParams;

	exports.default = params;

/***/ },

/***/ 50:
/*!****************************************!*\
  !*** ./src/modules/broadcast/index.js ***!
  \****************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.emit = emit;
	exports.on = on;
	exports.one = one;

	var _event = __webpack_require__(/*! event */ 12);

	var _event2 = _interopRequireDefault(_event);

	var _frame = __webpack_require__(/*! ./frame.js */ 51);

	var framer = _interopRequireWildcard(_frame);

	var _ydk = __webpack_require__(/*! ./ydk.js */ 52);

	var ydker = _interopRequireWildcard(_ydk);

	function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	/**
	 *
	 * broadcast(type , data , scope(local，frame , all))
	 * 
	 */
	function emit(type, data) {
	  var scope = arguments.length > 2 && arguments[2] !== undefined ? arguments[2] : 'local';

	  switch (scope) {
	    case 'local':
	      _event2.default.trigger('modules/broadcast/' + type, data);
	      break;
	    case 'frame':
	      framer.trigger('modules/broadcast/' + type, data);
	      break;
	    case 'top':
	      framer.triggerTop('modules/broadcast/' + type, data);
	      break;
	    case 'all':
	      ydker.trigger('modules/broadcast/' + type, data);
	      break;
	  }
	} /**
	   * 统一消息通讯组件
	   *
	   * 支持：
	   * 1、当前页面消息广播 local
	   * 2、当前父页面和子页面消息广播 frame
	   * 3、所有cef窗口消息广播 all
	   */

	function on(type, callback) {
	  _event2.default.bind('modules/broadcast/' + type, callback);
	}

	function one(type, callback) {
	  _event2.default.one('modules/broadcast/' + type, callback);
	}

/***/ },

/***/ 51:
/*!****************************************!*\
  !*** ./src/modules/broadcast/frame.js ***!
  \****************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.trigger = trigger;
	exports.triggerTop = triggerTop;

	var _event = __webpack_require__(/*! event */ 12);

	var _event2 = _interopRequireDefault(_event);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	var win = window; /**
	                   * 主框架与子页面通讯模块
	                   * 
	                   */

	var isTop = win == top;

	var _seq = new Date().getTime() + Math.random() * 100000;

	var copy = function copy(args) {
	  // avoid leaking arguments:
	  // http://jsperf.com/closure-with-arguments
	  var i = args.length;
	  var arr = new Array(i);
	  while (i--) {
	    arr[i] = args[i];
	  }
	  return arr;
	};

	var postToFrames = function postToFrames(msg) {
	  var len = win.frames.length;
	  /**
	   * 向子iframe窗口广播消息
	   */
	  for (var i = 0; i < len; i++) {
	    try {
	      win.frames[i].postMessage({
	        _seq: ++_seq,
	        dictbroadcast: msg
	      }, '/');
	    } catch (e) {
	      console.error(e);
	    }
	  }
	};

	function trigger() {
	  var arr = copy(arguments);
	  _event2.default.trigger.apply(this, arr);

	  if (isTop) {
	    postToFrames(JSON.stringify(arr));
	  } else {
	    top.postMessage({
	      _seq: ++_seq,
	      dictbroadcast: JSON.stringify(arr)
	    }, '/');
	  }
	};

	function triggerTop() {
	  var arr = copy(arguments);

	  if (top == win) return;

	  top.postMessage({
	    _seq: ++_seq,
	    scope: 'top',
	    dictbroadcast: JSON.stringify(arr)
	  }, '/');
	};

	win.addEventListener('message', function (e) {
	  if (!e.data.dictbroadcast) {
	    return;
	  }
	  var len = win.frames.length;
	  if (isTop) {
	    var match = false;
	    //保证消息来源可信
	    for (var i = 0; i < len; i++) {
	      if (e.source == win.frames[i]) {
	        match = true;
	        break;
	      }
	    }

	    if (!match && location.protocol != e.source.location.protocol) {
	      return;
	    }
	  } else {
	    if (e.source != top && location.protocol != e.source.location.protocol) return;
	  }

	  try {
	    _event2.default.trigger.apply(this, JSON.parse(e.data.dictbroadcast));
	  } catch (e) {
	    console.error(e);
	  }

	  if (e.data.scope != 'top') {
	    postToFrames(e.data.dictbroadcast);
	  }
	}, false);

/***/ },

/***/ 52:
/*!**************************************!*\
  !*** ./src/modules/broadcast/ydk.js ***!
  \**************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	var _event = __webpack_require__(/*! event */ 12);

	var _event2 = _interopRequireDefault(_event);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	exports.trigger = function (type, data) {
	  ydk.broadcast({
	    type: type,
	    data: data
	  });
	};

	$(function () {
	  ydk.onBroadcast({
	    success: function success(res) {
	      _event2.default.trigger.call(null, res.data.type, res.data.data);
	    }
	  });
	});

/***/ },

/***/ 59:
/*!***************************************!*\
  !*** ./src/modules/clienter/index.js ***!
  \***************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.autoHeight = exports.autoSize = undefined;
	exports.ready = ready;

	var _event = __webpack_require__(/*! event */ 12);

	var _event2 = _interopRequireDefault(_event);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	var $html = $('html'),
	    devicePixelRatio = window.devicePixelRatio || 1;

	function ready(callback) {
	  if (ydk.client) {
	    callback(ydk.client);
	  } else {
	    _event2.default.one('ydk.ready', callback);
	  }
	}

	var autoSize = exports.autoSize = _.throttle(function () {
	  Vue.nextTick(function () {
	    ydk.setWinSize({
	      width: Math.ceil($html.width() * devicePixelRatio),
	      height: Math.ceil($html.height() * devicePixelRatio)
	    });
	  });
	}, 100);

	var autoHeight = exports.autoHeight = _.throttle(function () {
	  Vue.nextTick(function () {
	    ydk.setWinHeight({
	      height: Math.ceil($html.height() * devicePixelRatio)
	    });
	  });
	}, 100);

/***/ },

/***/ 67:
/*!****************************************!*\
  !*** ./src/modules/debug_msg/index.js ***!
  \****************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.log = exports.stop = exports.start = undefined;
	exports.clear = clear;

	var _clienter = __webpack_require__(/*! modules/clienter */ 59);

	var clienter = _interopRequireWildcard(_clienter);

	__webpack_require__(/*! ./index.scss */ 68);

	function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

	var _timer;
	/* istanbul ignore next */
	var fadeOut = function fadeOut($el) {
	  clearTimeout(_timer);
	  _timer = setTimeout(function () {
	    $el.fadeOut(500, function () {
	      $el.remove();
	    });
	  }, 5000);
	};

	var date;
	var start = exports.start = function start() {
	  date = _.now();
	};

	/* istanbul ignore next */
	var stop = exports.stop = function stop(title, start) {
	  log([title, '：<em>', _.now() - (start || date), '</em> ms']);
	};

	var log = exports.log = function log(msg) {
	  clienter.ready(function (client) {
	    if (!client.debug) return;

	    var $msg = $('._debug_msg');
	    if ($msg.length == 0) {
	      $msg = $('<div class="_debug_msg"></div>');
	      $('body').append($msg);
	    }

	    $msg.append('<p>' + (_.isArray(msg) ? msg.join('') : msg) + '</p>');

	    fadeOut($msg);
	  });
	};

	function clear() {
	  $('._debug_msg').empty();
	}

	/* istanbul ignore next */
	$(function () {
	  clienter.ready(function (client) {
	    if (!client.debug) return;
	    $('body').on('mouseenter', '._debug_msg', function () {
	      clearTimeout(_timer);
	    }).on('mouseleave', '._debug_msg', function () {
	      fadeOut($(this));
	    });
	  });
	});

/***/ },

/***/ 68:
/*!******************************************!*\
  !*** ./src/modules/debug_msg/index.scss ***!
  \******************************************/
/***/ function(module, exports) {

	// removed by extract-text-webpack-plugin

/***/ },

/***/ 133:
/*!*******************************************!*\
  !*** ./src/modules/dict_setting/index.js ***!
  \*******************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.init = undefined;
	exports.getDefault = getDefault;
	exports.get = get;
	exports.save = save;

	var _default_setting = __webpack_require__(/*! ./default_setting.js */ 134);

	var _default_setting2 = _interopRequireDefault(_default_setting);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	var store = window.localStorage;
	var key = 'dict_setting';
	var defaultSettingStr = JSON.stringify(_default_setting2.default);

	ydk.onSettingChange({
	  success: clearCache
	});

	function clearCache() {
	  store.removeItem(key);
	}

	function putCache(setting) {
	  // console.trace('put cache' , JSON.stringify(setting));
	  store.setItem(key, JSON.stringify(setting));
	}

	function getDefault() {
	  return JSON.parse(defaultSettingStr);
	}
	function get(callback) {
	  var cache = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : true;

	  if (cache) {
	    var res = store.getItem(key);
	    if (res) {
	      try {
	        callback(JSON.parse(res));
	        // console.trace('get from cache' , res);
	        return;
	      } catch (e) {
	        console.error(e);
	      }
	    }
	  }

	  ydk.getSetting({
	    success: function success(res) {
	      var setting = res.data;
	      if (!setting) {
	        setting = getDefault();
	      } else {
	        setting = $.extend(true, getDefault(), setting);
	      }
	      callback(setting);
	      putCache(setting);
	    }
	  });
	}

	function save(params, callback) {
	  //清除缓存，使用接口返回的配置
	  get(function (setting) {
	    setting = $.extend(true, setting, params);
	    ydk.saveSetting({
	      setting: setting,
	      success: function success() {
	        callback && callback(setting);
	      },
	      complete: clearCache
	    });
	  }, false);
	}

	var init = exports.init = clearCache;

/***/ },

/***/ 134:
/*!*****************************************************!*\
  !*** ./src/modules/dict_setting/default_setting.js ***!
  \*****************************************************/
/***/ function(module, exports) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	/**
	 * 默认设置
	 */
	exports.default = {
	  //常规
	  basic: {
	    //字体大小
	    fontSize: 'small',
	    //开机启动
	    startup: true,
	    //启动后最小化到系统托盘
	    start_minify: false,
	    //启用主窗口总在最前
	    start_front: false,
	    //窗口关闭最小化到系统托盘
	    close_mini: true,
	    //打开有道词典快捷键
	    dict_hotkey: 'Ctrl + Alt + X',
	    //打开mini窗口快捷键
	    mini_hotkey: 'Ctrl + Alt + M',
	    // 添加/删除单词快捷键
	    word_hotkey: 'Ctrl + Alt + S',
	    //单词发音
	    sound_hotkey: 'Ctrl + Alt + V'
	  },

	  content: {
	    //自动发音
	    auto_pronounce: true,
	    //英音uk/美音us
	    pronounce_type: 'us',
	    //有道指点
	    dict_directions: true,
	    //每日推荐
	    daily_promote: true,
	    //查词历史记录条数
	    history_num: '20'
	  },

	  quci: {
	    //取词开关
	    enable: true,
	    //快捷键
	    hotkey: 'F8',
	    // 取词方式:
	    // mouse鼠标取词|middleMouse鼠标中键取词|
	    // alt+mouse Alt+鼠标取词|ctrl+mouse Ctrl+鼠标取词|shift+mouse Shift+鼠标取词
	    way: 'mouse',
	    scope: {
	      // 中文取词
	      chinese: true,
	      // 系统界面取词
	      system: false,
	      // 强力取词
	      force: false
	    },
	    //在取词结果中显示百科内容
	    baike: true
	  },

	  huaci: {
	    //划词开关
	    enable: true,
	    // 划词方式：
	    // showIcon展示划词图标|showResult直接展示结果|dobuleCtrl双击ctrl展示结果
	    way: 'showIcon',
	    //快捷键
	    hotkey: '',
	    // 复制查词
	    clipboard: false
	  },
	  dict: {},
	  network: {
	    http: 'no', //no 不使用代理/ie IE代理/custom 自定义
	    custom: {
	      //自定义代理参数
	      host: '', //服务器
	      port: '', //端口
	      username: '', //用户名
	      password: '' //密码
	    }
	  },
	  about: {
	    // 自动更新
	    auto_update: true
	  },
	  //单词本
	  wordbook: {
	    // 在系统任务栏（系统托盘）提醒复习
	    notice: true,
	    // 浏览时，单词自动发音
	    viewAutoVoice: false,
	    // 复习时，单词自动发音
	    reviewAutoVoice: false,
	    // 添加单词时默认加入复习计划
	    addReview: true,
	    // 每日进入复习流程的新单词上限
	    wordNum: '20',
	    // 单词本默认分类
	    defaultCategory: '未分类'
	  }
	};

/***/ },

/***/ 145:
/*!******************************************!*\
  !*** ./src/modules/dict_search/index.js ***!
  \******************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.search = search;
	exports.any = any;
	exports.local = local;
	exports.remote = remote;
	exports.mini = mini;
	exports.detail = detail;

	var _jsonapi = __webpack_require__(/*! ./jsonapi.js */ 146);

	var _jsonapi2 = _interopRequireDefault(_jsonapi);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	var seq = 0; // import * as msger from 'modules/debug_msg';

	var searcher = function searcher(options) {
	  var self = this;
	  self.options = options || {
	    mode: 'all'
	  };
	  self.isLocal = false;
	  self.isNet = false;
	};

	var now = function now() {
	  return parseInt(performance.now(), 10);
	};

	/**
	 * 本地释义
	 */
	searcher.prototype.local = function (params) {
	  var self = this;
	  var start = now(),
	      duration = 0;
	  var wrap = function wrap(callback) {
	    if (!callback) return null;
	    var _seq = seq;
	    return function (res) {
	      //如果网络释义已返回，则丢掉本地释义
	      if (self.isNet) return;
	      if (res.code == 1000) {
	        self.isLocal = true;
	      }
	      res = res || {};
	      res.from = 'local';
	      res.seq = _seq;
	      res.duration = duration || (duration = now() - start);
	      callback(res);
	    };
	  };

	  ydk.getDictResult({
	    data: {
	      keyword: params.data.keyword,
	      lang: params.data.lang
	    },
	    complete: wrap(params.complete),
	    fail: wrap(params.fail),
	    success: wrap(params.success)
	  });

	  return self;
	};

	/**
	 * 网络释义
	 */
	searcher.prototype.remote = function (params) {
	  var self = this;
	  var start = now(),
	      duration = 0;
	  var wrap = function wrap(callback) {
	    if (!callback) return null;
	    var _seq = seq;
	    return function (res) {
	      //如果本地已经返回，则丢掉该结果
	      if (self.options.mode == 'any' && self.isLocal) return;
	      if (res.code == 1000) {
	        self.isNet = true;
	      }
	      res = res || {};
	      res.seq = _seq;
	      res.from = 'net';
	      res.duration = duration || (duration = now() - start);
	      callback(res);
	    };
	  };
	  //网络
	  ydk.getDictResult({
	    data: {
	      keyword: params.data.keyword,
	      lang: params.data.lang,
	      type: 'quick'
	    },
	    complete: wrap(params.complete),
	    fail: wrap(params.fail),
	    success: wrap(params.success)
	  });
	  return self;
	};

	/**
	 * mini模式
	 */
	searcher.prototype.mini = function (params) {
	  var self = this;
	  var start = now(),
	      duration = 0;
	  var wrap = function wrap(callback) {
	    if (!callback) return null;
	    var _seq = seq;
	    return function (res) {
	      //如果本地已经返回，则丢掉该结果
	      if (self.options.mode == 'any' && self.isLocal) return;
	      if (res.code == 1000) {
	        self.isNet = true;
	      }
	      res = res || {};
	      res.seq = _seq;
	      res.from = 'net';
	      res.duration = duration || (duration = now() - start);
	      callback(res);
	    };
	  };
	  //网络
	  ydk.getDictResult({
	    data: {
	      keyword: params.data.keyword,
	      lang: params.data.lang,
	      type: 'mini'
	    },
	    complete: wrap(params.complete),
	    fail: wrap(params.fail),
	    success: wrap(params.success)
	  });
	  return self;
	};

	/**
	 * 同时发起本地释义和网络释义
	 */
	searcher.prototype.auto = function (params) {
	  var self = this;
	  self.local(params).remote(params);;
	};

	/**
	 * 同时发起本地释义和mini网络释义
	 */
	searcher.prototype.miniSearch = function (params) {
	  var self = this;
	  self.local(params).mini(params);
	};

	/**
	 * 先返回本地释义，然后再返回网络释义
	 */
	function search(params) {
	  new searcher().auto(params);
	}

	/**
	 * 本地 或者 网络释义返回即可
	 */
	function any(params) {
	  new searcher({
	    mode: 'any'
	  }).auto(params);
	}

	function local(params) {
	  seq++;
	  new searcher().local(params);
	}

	function remote(params) {
	  seq++;
	  new searcher().remote(params);
	}

	function mini(params) {
	  new searcher().miniSearch(params);
	}

	function detail(params) {
	  var _seq = seq++;
	  var wrap = function wrap(callback) {
	    if (!callback) return null;
	    return function (res) {
	      res = res || {};
	      res.seq = _seq;
	      callback(res);
	    };
	  };

	  (0, _jsonapi2.default)({
	    data: {
	      keyword: params.data.keyword,
	      lang: params.data.lang
	    },
	    complete: wrap(params.complete),
	    fail: wrap(params.fail),
	    success: wrap(params.success)
	  });
	}

/***/ },

/***/ 146:
/*!********************************************!*\
  !*** ./src/modules/dict_search/jsonapi.js ***!
  \********************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.clearCache = exports.prefetch = undefined;

	var _typeof = typeof Symbol === "function" && typeof Symbol.iterator === "symbol" ? function (obj) { return typeof obj; } : function (obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; /**
	                                                                                                                                                                                                                                                                               * @see https://dev.corp.youdao.com/outfoxwiki/Dict/Projects/DictDataServer
	                                                                                                                                                                                                                                                                               */


	var _config = __webpack_require__(/*! config */ 8);

	var _config2 = _interopRequireDefault(_config);

	var _clienter = __webpack_require__(/*! modules/clienter */ 59);

	var clienter = _interopRequireWildcard(_clienter);

	var _debug_msg = __webpack_require__(/*! modules/debug_msg */ 67);

	var msger = _interopRequireWildcard(_debug_msg);

	function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	var TABLE = 'dict_prefresh';

	var getKey = function getKey(params) {
	  return [params.keyword, params.lang || 'en'].join('_');
	};

	var now = function now() {
	  return parseInt(performance.now(), 10);
	};

	var ajax = function ajax(params) {
	  clienter.ready(function () {
	    var data = params.data;
	    var start = now();
	    ydk.getDictResult({
	      timeout: params.timeout,
	      // url : 'http://dict.youdao.com/jsonapi?client=deskdict&dogVersion=1.0&dogui=json&in=YoudaoDict',
	      data: {
	        keyword: data.keyword,
	        lang: data.lang,
	        type: 'detail',
	        dicts: data.dicts
	      },
	      success: function success(res) {
	        res.duration = now() - start;

	        params.compete && params.compete(res);
	        params.success && params.success(res);

	        ydk.rlog({
	          duration: res.duration,
	          timing: 'webdict_query',
	          keyfrom: 'deskdict.main',
	          page: _config2.default.pageId,
	          type: 'success',
	          des: params.des,
	          q: data.keyword,
	          le: data.lang
	        });
	      },
	      fail: function fail(res) {
	        res.duration = now() - start;

	        ydk.rlog({
	          duration: res.duration,
	          timing: 'webdict_query',
	          keyfrom: 'deskdict.main',
	          page: _config2.default.pageId,
	          type: 'error',
	          des: params.des,
	          q: data.keyword,
	          le: data.lang
	        });

	        params.compete && params.compete(res);
	        params.fail && params.fail(res);
	      }
	    });
	  });
	};

	/**
	 * ajax或者从缓存读取
	 */
	var ajaxOrCache = function ajaxOrCache(params) {
	  var start = now(),
	      key = getKey(params.data);

	  ydk.getCache({
	    table: TABLE,
	    keys: [key],
	    success: function success(res) {
	      if (res.data && res.data[key]) {
	        res = {
	          data: JSON.parse(res.data[key]),
	          cache: true,
	          online: true,
	          duration: now() - start
	        };
	        params.success && params.success(res);
	        params.complete && params.complete(res);
	        return;
	      }

	      ajax(params);
	    }
	  });
	};

	/**
	 * 合并查词数据
	 */
	var extend = function extend(source, target) {
	  source = source || {};
	  if (!target) return source;

	  Object.keys(target).forEach(function (key) {
	    var val = target[key];
	    if (val && (typeof val === 'undefined' ? 'undefined' : _typeof(val)) == 'object' && !source[key]) {
	      source[key] = val;
	    }
	  });
	  return source;
	};

	/**
	 * 获取查词结果页主要/首屏数据
	 */
	var getMainData = function getMainData(params) {

	  ajaxOrCache({
	    des: 'first_dict_query',
	    timeout: params.timeout,
	    data: {
	      dicts: '{"count":14,"dicts":[["ec","ce","cj","jc","ck","kc","cf","fc" , "multle" , "related-langs"],["pic_dict"],["splongman" , "longman" ,"collins","ec21","ce_new"],["web_trans","special","ee","hh"],["phrs","syno","rel_word"],["blng_sents_part","media_sents_part","auth_sents_part"],["baike"],["fanyi"],["web_search"],["typos"],["collins_part"]]}',
	      keyword: params.data.keyword,
	      lang: params.data.lang
	    },
	    complete: params.complete,
	    fail: params.fail,
	    success: params.success
	  });
	};

	/**
	 * 预加载数据
	 */
	var prefetch = exports.prefetch = _.debounce(function (params) {
	  var key = getKey(params);
	  getMainData({
	    data: params,
	    timeout: 2000,
	    success: function success(res) {
	      ydk.saveCache({
	        table: TABLE,
	        key: key,
	        value: JSON.stringify(res.data)
	      });
	    }
	  });
	}, 50);

	/**
	 * 清空缓存
	 */
	var clearCache = exports.clearCache = _.debounce(function () {
	  ydk.clearCache({
	    table: TABLE
	  });
	  msger.log('查词缓存已清空');
	}, 1000);

	var search = function search(params) {
	  var data = null;
	  getMainData({
	    data: params.data,
	    complete: params.compete,
	    fail: params.fail,
	    success: function success(res) {
	      if (!data) {
	        data = res.data;
	      } else {
	        res.data = data = extend(data, res.data);
	      }
	      params.success && params.success(res);
	    }
	  });

	  ajax({
	    des: 'second_dict_query',
	    data: {
	      dicts: '{"count":11,"dicts":[["auth_sents_part"], ["longman"] , ["collins"] , ["ec21"],["hh"],["ee"],["media_sents_part"],["rel_word"],["special"],["syno"]]}',
	      keyword: params.data.keyword,
	      lang: params.data.lang
	    },
	    complete: params.complete,
	    fail: params.fail,
	    success: function success(res) {
	      if (!data) {
	        data = res.data;
	        return;
	      }
	      res.data = extend(data, res.data);
	      params.success && params.success(res);
	    }
	  });
	};

	exports.default = search;

/***/ },

/***/ 215:
/*!*************************************!*\
  !*** ./src/entrys/editword/main.js ***!
  \*************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	__webpack_require__(/*! global */ 2);

	var _config = __webpack_require__(/*! config */ 8);

	var _config2 = _interopRequireDefault(_config);

	__webpack_require__(/*! modules/pannel */ 216);

	__webpack_require__(/*! components/ajax */ 23);

	__webpack_require__(/*! components/nicescroll */ 217);

	__webpack_require__(/*! components/event */ 222);

	__webpack_require__(/*! ../wordbook/dialog/category/components/add */ 224);

	var _dialog = __webpack_require__(/*! modules/dialog */ 228);

	var dialog = _interopRequireWildcard(_dialog);

	var _template = __webpack_require__(/*! ./template.html */ 229);

	var _template2 = _interopRequireDefault(_template);

	var _api = __webpack_require__(/*! ./api.js */ 230);

	var _api2 = _interopRequireDefault(_api);

	var _filter = __webpack_require__(/*! ./filter.js */ 231);

	var _filter2 = _interopRequireDefault(_filter);

	__webpack_require__(/*! ./index.scss */ 232);

	var _methods = __webpack_require__(/*! ./methods.js */ 234);

	var methods = _interopRequireWildcard(_methods);

	var _urlparams = __webpack_require__(/*! modules/urlparams */ 49);

	var _urlparams2 = _interopRequireDefault(_urlparams);

	var _dict_search = __webpack_require__(/*! modules/dict_search */ 145);

	var dict_search = _interopRequireWildcard(_dict_search);

	var _dict_setting = __webpack_require__(/*! modules/dict_setting */ 133);

	var settinger = _interopRequireWildcard(_dict_setting);

	function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	_config2.default.pageId = 'editword';

	new Vue({
	  el: '#main',
	  data: {
	    categoryText: '',
	    isAdd: false, //是否添加分类
	    editword: _urlparams2.default.keyword,
	    lang: _urlparams2.default.lang,
	    trans: '',
	    phonetic: '',
	    setting: settinger.getDefault(),
	    source: {
	      init: {
	        provider: _api2.default,
	        filter: _filter2.default
	      }
	    }
	  },
	  template: (0, _template2.default)(),
	  methods: methods,
	  watch: {
	    isAdd: function isAdd(val) {
	      if (val) {
	        $('#js_category_add_input').val('').focus();
	      }
	    }
	  },
	  ready: function ready() {
	    var self = this;
	    dialog.autoSize();
	    ydk.checkWordBook({
	      word: self.editword,
	      lang: self.lang,
	      success: function success(res) {
	        if (res.has) {
	          self.trans = res.data.trans;
	          self.phonetic = res.data.phonetic;
	          self.categoryText = res.data.category;
	        } else {
	          dict_search.search({
	            data: {
	              keyword: self.editword,
	              lang: self.lang || 'en'
	            },
	            success: function success(res) {
	              var trans,
	                  data = res.data;
	              if (data.basic && data.basic.length > 0) {
	                trans = data.basic;
	              } else if (data.web && data.web.length > 0) {
	                trans = [];
	                data.web.forEach(function (d) {
	                  Object.keys(d).forEach(function (d2) {
	                    trans.push(d2 + ' ：' + d[d2].join(','));
	                  });
	                });
	              }
	              self.trans = trans ? trans.join('\n') : '';
	              if (data.ussm || data.uksm) {
	                self.phonetic = self.setting.content.pronounce_type == 'us' ? data.ussm : data.uksm;
	              } else {
	                self.phonetic = data.sm || '';
	              }
	            }
	          });
	        }
	      }
	    });
	  }

	});

	Vue.filter('phoneticDataClean', function (str) {
	  str = str.replace(/\[|]/g, '');
	  return str;
	});

/***/ },

/***/ 216:
/*!*************************************!*\
  !*** ./src/modules/pannel/index.js ***!
  \*************************************/
/***/ function(module, exports) {

	'use strict';

	/**
	 * 面板展示/隐藏控制工具
	 * 常用于：下拉菜单
	 *
	 * 说明：
	 * pannel=''，表示当点击时候，显示哪个对象
	 * pannel-close，表示当点击时候，自动关闭面板
	 *
	 * 用法:
	 * <a href='' pannel='#pannel1'>展开</a>
	 *
	 * <ul id='pannel1'>
	 *   <li pannel-close>菜单1</li>
	 *   <li pannel-close>菜单2</li>
	 *   <li pannel-close>菜单3</li>
	 * </ul>
	 */

	$(function () {

	  var win = window,
	      $lastLinker,
	      $lastPannel;

	  var closeAll = function closeAll(e) {
	    $lastLinker && $lastLinker.removeClass('active');
	    $lastPannel && $lastPannel.hide().removeClass('active').removeAttr('onpannel').trigger('close');
	    $lastLinker = null;
	    $lastPannel = null;
	  };

	  $('body').on('click', '[pannel]', function (e) {
	    var $self = $(this),
	        $target = $($self.attr('pannel'));

	    if ($target.is(':visible')) {
	      closeAll();
	    } else {
	      //关闭其他窗口
	      closeAll();

	      /**
	       * 这里使用delay，避免事件冒泡，到顶层，又被立刻关闭
	       */
	      _.delay(function () {
	        //显示目标面板
	        $target.show().attr('onpannel', '1');
	        $lastLinker = $self.addClass('active');
	        $lastPannel = $target.addClass('active').trigger('open');
	      });
	    }
	  }).on('click', '[onpannel]', function (e) {
	    e.stopPropagation();
	  }).on('click', '[pannel-close]', function (e) {
	    closeAll();
	  }).bind('click', closeAll).bind('mousedown', function (e) {
	    //如果不是左键，则关闭
	    if (e.button != 0) {
	      closeAll();
	    }
	  });

	  $(win).bind('blur', closeAll);
	});

/***/ },

/***/ 217:
/*!********************************************!*\
  !*** ./src/components/nicescroll/index.js ***!
  \********************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	__webpack_require__(/*! libs/jquery.nicescroll.min.js */ 218);

	__webpack_require__(/*! ./directive.js */ 220);

/***/ },

/***/ 218:
/*!*******************************************!*\
  !*** ./src/libs/jquery.nicescroll.min.js ***!
  \*******************************************/
/***/ function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;"use strict";

	var _typeof = typeof Symbol === "function" && typeof Symbol.iterator === "symbol" ? function (obj) { return typeof obj; } : function (obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; };

	/* jquery.nicescroll 3.6.8 InuYaksa*2015 MIT http://nicescroll.areaaperta.com */(function (f) {
	   true ? !(__WEBPACK_AMD_DEFINE_ARRAY__ = [__webpack_require__(/*! jquery */ 219)], __WEBPACK_AMD_DEFINE_FACTORY__ = (f), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__)) : "object" === (typeof exports === "undefined" ? "undefined" : _typeof(exports)) ? module.exports = f(require("jquery")) : f(jQuery);
	})(function (f) {
	  var B = !1,
	      F = !1,
	      O = 0,
	      P = 2E3,
	      A = 0,
	      J = ["webkit", "ms", "moz", "o"],
	      v = window.requestAnimationFrame || !1,
	      w = window.cancelAnimationFrame || !1;if (!v) for (var Q in J) {
	    var G = J[Q];if (v = window[G + "RequestAnimationFrame"]) {
	      w = window[G + "CancelAnimationFrame"] || window[G + "CancelRequestAnimationFrame"];break;
	    }
	  }var x = window.MutationObserver || window.WebKitMutationObserver || !1,
	      K = { zindex: "auto", cursoropacitymin: 0, cursoropacitymax: 1, cursorcolor: "#424242", cursorwidth: "6px", cursorborder: "1px solid #fff", cursorborderradius: "5px", scrollspeed: 60, mousescrollstep: 24, touchbehavior: !1, hwacceleration: !0, usetransition: !0, boxzoom: !1, dblclickzoom: !0, gesturezoom: !0, grabcursorenabled: !0, autohidemode: !0, background: "", iframeautoresize: !0, cursorminheight: 32, preservenativescrolling: !0, railoffset: !1, railhoffset: !1, bouncescroll: !0, spacebarenabled: !0, railpadding: { top: 0, right: 0, left: 0, bottom: 0 },
	    disableoutline: !0, horizrailenabled: !0, railalign: "right", railvalign: "bottom", enabletranslate3d: !0, enablemousewheel: !0, enablekeyboard: !0, smoothscroll: !0, sensitiverail: !0, enablemouselockapi: !0, cursorfixedheight: !1, directionlockdeadzone: 6, hidecursordelay: 400, nativeparentscrolling: !0, enablescrollonselection: !0, overflowx: !0, overflowy: !0, cursordragspeed: .3, rtlmode: "auto", cursordragontouch: !1, oneaxismousemode: "auto", scriptpath: function () {
	      var f = document.getElementsByTagName("script"),
	          f = f.length ? f[f.length - 1].src.split("?")[0] : "";return 0 < f.split("/").length ? f.split("/").slice(0, -1).join("/") + "/" : "";
	    }(), preventmultitouchscrolling: !0, disablemutationobserver: !1 },
	      H = !1,
	      R = function R() {
	    if (H) return H;var f = document.createElement("DIV"),
	        c = f.style,
	        k = navigator.userAgent,
	        l = navigator.platform,
	        d = { haspointerlock: "pointerLockElement" in document || "webkitPointerLockElement" in document || "mozPointerLockElement" in document };d.isopera = "opera" in window;d.isopera12 = d.isopera && "getUserMedia" in navigator;d.isoperamini = "[object OperaMini]" === Object.prototype.toString.call(window.operamini);d.isie = "all" in document && "attachEvent" in f && !d.isopera;d.isieold = d.isie && !("msInterpolationMode" in c);d.isie7 = d.isie && !d.isieold && (!("documentMode" in document) || 7 == document.documentMode);d.isie8 = d.isie && "documentMode" in document && 8 == document.documentMode;d.isie9 = d.isie && "performance" in window && 9 == document.documentMode;d.isie10 = d.isie && "performance" in window && 10 == document.documentMode;d.isie11 = "msRequestFullscreen" in f && 11 <= document.documentMode;d.isieedge12 = navigator.userAgent.match(/Edge\/12\./);d.isieedge = "msOverflowStyle" in f;d.ismodernie = d.isie11 || d.isieedge;d.isie9mobile = /iemobile.9/i.test(k);d.isie9mobile && (d.isie9 = !1);d.isie7mobile = !d.isie9mobile && d.isie7 && /iemobile/i.test(k);d.ismozilla = "MozAppearance" in c;d.iswebkit = "WebkitAppearance" in c;d.ischrome = "chrome" in window;d.ischrome38 = d.ischrome && "touchAction" in c;d.ischrome22 = !d.ischrome38 && d.ischrome && d.haspointerlock;d.ischrome26 = !d.ischrome38 && d.ischrome && "transition" in c;d.cantouch = "ontouchstart" in document.documentElement || "ontouchstart" in window;d.hasw3ctouch = (window.PointerEvent || !1) && (0 < navigator.MaxTouchPoints || 0 < navigator.msMaxTouchPoints);d.hasmstouch = !d.hasw3ctouch && (window.MSPointerEvent || !1);d.ismac = /^mac$/i.test(l);d.isios = d.cantouch && /iphone|ipad|ipod/i.test(l);d.isios4 = d.isios && !("seal" in Object);d.isios7 = d.isios && "webkitHidden" in document;d.isios8 = d.isios && "hidden" in document;d.isandroid = /android/i.test(k);d.haseventlistener = "addEventListener" in f;d.trstyle = !1;d.hastransform = !1;
	    d.hastranslate3d = !1;d.transitionstyle = !1;d.hastransition = !1;d.transitionend = !1;l = ["transform", "msTransform", "webkitTransform", "MozTransform", "OTransform"];for (k = 0; k < l.length; k++) {
	      if (void 0 !== c[l[k]]) {
	        d.trstyle = l[k];break;
	      }
	    }d.hastransform = !!d.trstyle;d.hastransform && (c[d.trstyle] = "translate3d(1px,2px,3px)", d.hastranslate3d = /translate3d/.test(c[d.trstyle]));d.transitionstyle = !1;d.prefixstyle = "";d.transitionend = !1;for (var l = "transition webkitTransition msTransition MozTransition OTransition OTransition KhtmlTransition".split(" "), q = " -webkit- -ms- -moz- -o- -o -khtml-".split(" "), t = "transitionend webkitTransitionEnd msTransitionEnd transitionend otransitionend oTransitionEnd KhtmlTransitionEnd".split(" "), k = 0; k < l.length; k++) {
	      if (l[k] in c) {
	        d.transitionstyle = l[k];d.prefixstyle = q[k];d.transitionend = t[k];break;
	      }
	    }d.ischrome26 && (d.prefixstyle = q[1]);d.hastransition = d.transitionstyle;a: {
	      k = ["grab", "-webkit-grab", "-moz-grab"];if (d.ischrome && !d.ischrome38 || d.isie) k = [];for (l = 0; l < k.length; l++) {
	        if (q = k[l], c.cursor = q, c.cursor == q) {
	          c = q;break a;
	        }
	      }c = "url(//patriciaportfolio.googlecode.com/files/openhand.cur),n-resize";
	    }d.cursorgrabvalue = c;d.hasmousecapture = "setCapture" in f;d.hasMutationObserver = !1 !== x;return H = d;
	  },
	      S = function S(h, c) {
	    function k() {
	      var b = a.doc.css(e.trstyle);return b && "matrix" == b.substr(0, 6) ? b.replace(/^.*\((.*)\)$/g, "$1").replace(/px/g, "").split(/, +/) : !1;
	    }function l() {
	      var b = a.win;if ("zIndex" in b) return b.zIndex();for (; 0 < b.length && 9 != b[0].nodeType;) {
	        var g = b.css("zIndex");if (!isNaN(g) && 0 != g) return parseInt(g);b = b.parent();
	      }return !1;
	    }function d(b, g, u) {
	      g = b.css(g);b = parseFloat(g);return isNaN(b) ? (b = z[g] || 0, u = 3 == b ? u ? a.win.outerHeight() - a.win.innerHeight() : a.win.outerWidth() - a.win.innerWidth() : 1, a.isie8 && b && (b += 1), u ? b : 0) : b;
	    }function q(b, g, u, c) {
	      a._bind(b, g, function (a) {
	        a = a ? a : window.event;var c = { original: a, target: a.target || a.srcElement, type: "wheel", deltaMode: "MozMousePixelScroll" == a.type ? 0 : 1, deltaX: 0, deltaZ: 0, preventDefault: function preventDefault() {
	            a.preventDefault ? a.preventDefault() : a.returnValue = !1;return !1;
	          }, stopImmediatePropagation: function stopImmediatePropagation() {
	            a.stopImmediatePropagation ? a.stopImmediatePropagation() : a.cancelBubble = !0;
	          } };"mousewheel" == g ? (a.wheelDeltaX && (c.deltaX = -.025 * a.wheelDeltaX), a.wheelDeltaY && (c.deltaY = -.025 * a.wheelDeltaY), c.deltaY || c.deltaX || (c.deltaY = -.025 * a.wheelDelta)) : c.deltaY = a.detail;return u.call(b, c);
	      }, c);
	    }function t(b, g, c) {
	      var d, e;0 == b.deltaMode ? (d = -Math.floor(a.opt.mousescrollstep / 54 * b.deltaX), e = -Math.floor(a.opt.mousescrollstep / 54 * b.deltaY)) : 1 == b.deltaMode && (d = -Math.floor(b.deltaX * a.opt.mousescrollstep), e = -Math.floor(b.deltaY * a.opt.mousescrollstep));
	      g && a.opt.oneaxismousemode && 0 == d && e && (d = e, e = 0, c && (0 > d ? a.getScrollLeft() >= a.page.maxw : 0 >= a.getScrollLeft()) && (e = d, d = 0));a.isrtlmode && (d = -d);d && (a.scrollmom && a.scrollmom.stop(), a.lastdeltax += d, a.debounced("mousewheelx", function () {
	        var b = a.lastdeltax;a.lastdeltax = 0;a.rail.drag || a.doScrollLeftBy(b);
	      }, 15));if (e) {
	        if (a.opt.nativeparentscrolling && c && !a.ispage && !a.zoomactive) if (0 > e) {
	          if (a.getScrollTop() >= a.page.maxh) return !0;
	        } else if (0 >= a.getScrollTop()) return !0;a.scrollmom && a.scrollmom.stop();a.lastdeltay += e;
	        a.synched("mousewheely", function () {
	          var b = a.lastdeltay;a.lastdeltay = 0;a.rail.drag || a.doScrollBy(b);
	        }, 15);
	      }b.stopImmediatePropagation();return b.preventDefault();
	    }var a = this;this.version = "3.6.8";this.name = "nicescroll";this.me = c;this.opt = { doc: f("body"), win: !1 };f.extend(this.opt, K);this.opt.snapbackspeed = 80;if (h) for (var r in a.opt) {
	      void 0 !== h[r] && (a.opt[r] = h[r]);
	    }a.opt.disablemutationobserver && (x = !1);this.iddoc = (this.doc = a.opt.doc) && this.doc[0] ? this.doc[0].id || "" : "";this.ispage = /^BODY|HTML/.test(a.opt.win ? a.opt.win[0].nodeName : this.doc[0].nodeName);this.haswrapper = !1 !== a.opt.win;this.win = a.opt.win || (this.ispage ? f(window) : this.doc);this.docscroll = this.ispage && !this.haswrapper ? f(window) : this.win;this.body = f("body");this.iframe = this.isfixed = this.viewport = !1;this.isiframe = "IFRAME" == this.doc[0].nodeName && "IFRAME" == this.win[0].nodeName;this.istextarea = "TEXTAREA" == this.win[0].nodeName;this.forcescreen = !1;this.canshowonmouseevent = "scroll" != a.opt.autohidemode;this.page = this.view = this.onzoomout = this.onzoomin = this.onscrollcancel = this.onscrollend = this.onscrollstart = this.onclick = this.ongesturezoom = this.onkeypress = this.onmousewheel = this.onmousemove = this.onmouseup = this.onmousedown = !1;this.scroll = { x: 0, y: 0 };this.scrollratio = { x: 0, y: 0 };this.cursorheight = 20;this.scrollvaluemax = 0;if ("auto" == this.opt.rtlmode) {
	      r = this.win[0] == window ? this.body : this.win;var p = r.css("writing-mode") || r.css("-webkit-writing-mode") || r.css("-ms-writing-mode") || r.css("-moz-writing-mode");"horizontal-tb" == p || "lr-tb" == p || "" == p ? (this.isrtlmode = "rtl" == r.css("direction"), this.isvertical = !1) : (this.isrtlmode = "vertical-rl" == p || "tb" == p || "tb-rl" == p || "rl-tb" == p, this.isvertical = "vertical-rl" == p || "tb" == p || "tb-rl" == p);
	    } else this.isrtlmode = !0 === this.opt.rtlmode, this.isvertical = !1;this.observerbody = this.observerremover = this.observer = this.scrollmom = this.scrollrunning = !1;do {
	      this.id = "ascrail" + P++;
	    } while (document.getElementById(this.id));this.hasmousefocus = this.hasfocus = this.zoomactive = this.zoom = this.selectiondrag = this.cursorfreezed = this.cursor = this.rail = !1;this.visibility = !0;this.hidden = this.locked = this.railslocked = !1;this.cursoractive = !0;this.wheelprevented = !1;this.overflowx = a.opt.overflowx;this.overflowy = a.opt.overflowy;this.nativescrollingarea = !1;this.checkarea = 0;this.events = [];this.saved = {};this.delaylist = {};this.synclist = {};this.lastdeltay = this.lastdeltax = 0;this.detected = R();var e = f.extend({}, this.detected);this.ishwscroll = (this.canhwscroll = e.hastransform && a.opt.hwacceleration) && a.haswrapper;this.hasreversehr = this.isrtlmode ? this.isvertical ? !(e.iswebkit || e.isie || e.isie11) : !(e.iswebkit || e.isie && !e.isie10 && !e.isie11) : !1;this.istouchcapable = !1;e.cantouch || !e.hasw3ctouch && !e.hasmstouch ? !e.cantouch || e.isios || e.isandroid || !e.iswebkit && !e.ismozilla || (this.istouchcapable = !0) : this.istouchcapable = !0;a.opt.enablemouselockapi || (e.hasmousecapture = !1, e.haspointerlock = !1);this.debounced = function (b, g, c) {
	      a && (a.delaylist[b] || (g.call(a), a.delaylist[b] = { h: v(function () {
	          a.delaylist[b].fn.call(a);a.delaylist[b] = !1;
	        }, c) }), a.delaylist[b].fn = g);
	    };var I = !1;this.synched = function (b, g) {
	      a.synclist[b] = g;(function () {
	        I || (v(function () {
	          if (a) {
	            I = !1;for (var b in a.synclist) {
	              var g = a.synclist[b];g && g.call(a);a.synclist[b] = !1;
	            }
	          }
	        }), I = !0);
	      })();return b;
	    };this.unsynched = function (b) {
	      a.synclist[b] && (a.synclist[b] = !1);
	    };this.css = function (b, g) {
	      for (var c in g) {
	        a.saved.css.push([b, c, b.css(c)]), b.css(c, g[c]);
	      }
	    };this.scrollTop = function (b) {
	      return void 0 === b ? a.getScrollTop() : a.setScrollTop(b);
	    };this.scrollLeft = function (b) {
	      return void 0 === b ? a.getScrollLeft() : a.setScrollLeft(b);
	    };var D = function D(a, g, c, d, e, f, k) {
	      this.st = a;this.ed = g;this.spd = c;this.p1 = d || 0;this.p2 = e || 1;this.p3 = f || 0;this.p4 = k || 1;this.ts = new Date().getTime();this.df = this.ed - this.st;
	    };D.prototype = { B2: function B2(a) {
	        return 3 * a * a * (1 - a);
	      }, B3: function B3(a) {
	        return 3 * a * (1 - a) * (1 - a);
	      }, B4: function B4(a) {
	        return (1 - a) * (1 - a) * (1 - a);
	      }, getNow: function getNow() {
	        var a = 1 - (new Date().getTime() - this.ts) / this.spd,
	            g = this.B2(a) + this.B3(a) + this.B4(a);return 0 > a ? this.ed : this.st + Math.round(this.df * g);
	      }, update: function update(a, g) {
	        this.st = this.getNow();this.ed = a;this.spd = g;this.ts = new Date().getTime();
	        this.df = this.ed - this.st;return this;
	      } };if (this.ishwscroll) {
	      this.doc.translate = { x: 0, y: 0, tx: "0px", ty: "0px" };e.hastranslate3d && e.isios && this.doc.css("-webkit-backface-visibility", "hidden");this.getScrollTop = function (b) {
	        if (!b) {
	          if (b = k()) return 16 == b.length ? -b[13] : -b[5];if (a.timerscroll && a.timerscroll.bz) return a.timerscroll.bz.getNow();
	        }return a.doc.translate.y;
	      };this.getScrollLeft = function (b) {
	        if (!b) {
	          if (b = k()) return 16 == b.length ? -b[12] : -b[4];if (a.timerscroll && a.timerscroll.bh) return a.timerscroll.bh.getNow();
	        }return a.doc.translate.x;
	      };
	      this.notifyScrollEvent = function (a) {
	        var g = document.createEvent("UIEvents");g.initUIEvent("scroll", !1, !0, window, 1);g.niceevent = !0;a.dispatchEvent(g);
	      };var y = this.isrtlmode ? 1 : -1;e.hastranslate3d && a.opt.enabletranslate3d ? (this.setScrollTop = function (b, g) {
	        a.doc.translate.y = b;a.doc.translate.ty = -1 * b + "px";a.doc.css(e.trstyle, "translate3d(" + a.doc.translate.tx + "," + a.doc.translate.ty + ",0px)");g || a.notifyScrollEvent(a.win[0]);
	      }, this.setScrollLeft = function (b, g) {
	        a.doc.translate.x = b;a.doc.translate.tx = b * y + "px";a.doc.css(e.trstyle, "translate3d(" + a.doc.translate.tx + "," + a.doc.translate.ty + ",0px)");g || a.notifyScrollEvent(a.win[0]);
	      }) : (this.setScrollTop = function (b, g) {
	        a.doc.translate.y = b;a.doc.translate.ty = -1 * b + "px";a.doc.css(e.trstyle, "translate(" + a.doc.translate.tx + "," + a.doc.translate.ty + ")");g || a.notifyScrollEvent(a.win[0]);
	      }, this.setScrollLeft = function (b, g) {
	        a.doc.translate.x = b;a.doc.translate.tx = b * y + "px";a.doc.css(e.trstyle, "translate(" + a.doc.translate.tx + "," + a.doc.translate.ty + ")");g || a.notifyScrollEvent(a.win[0]);
	      });
	    } else this.getScrollTop = function () {
	      return a.docscroll.scrollTop();
	    }, this.setScrollTop = function (b) {
	      return setTimeout(function () {
	        a && a.docscroll.scrollTop(b);
	      }, 1);
	    }, this.getScrollLeft = function () {
	      return a.hasreversehr ? a.detected.ismozilla ? a.page.maxw - Math.abs(a.docscroll.scrollLeft()) : a.page.maxw - a.docscroll.scrollLeft() : a.docscroll.scrollLeft();
	    }, this.setScrollLeft = function (b) {
	      return setTimeout(function () {
	        if (a) return a.hasreversehr && (b = a.detected.ismozilla ? -(a.page.maxw - b) : a.page.maxw - b), a.docscroll.scrollLeft(b);
	      }, 1);
	    };this.getTarget = function (a) {
	      return a ? a.target ? a.target : a.srcElement ? a.srcElement : !1 : !1;
	    };this.hasParent = function (a, g) {
	      if (!a) return !1;for (var c = a.target || a.srcElement || a || !1; c && c.id != g;) {
	        c = c.parentNode || !1;
	      }return !1 !== c;
	    };var z = { thin: 1, medium: 3, thick: 5 };this.getDocumentScrollOffset = function () {
	      return { top: window.pageYOffset || document.documentElement.scrollTop, left: window.pageXOffset || document.documentElement.scrollLeft };
	    };this.getOffset = function () {
	      if (a.isfixed) {
	        var b = a.win.offset(),
	            g = a.getDocumentScrollOffset();b.top -= g.top;
	        b.left -= g.left;return b;
	      }b = a.win.offset();if (!a.viewport) return b;g = a.viewport.offset();return { top: b.top - g.top, left: b.left - g.left };
	    };this.updateScrollBar = function (b) {
	      var g, c, e;if (a.ishwscroll) a.rail.css({ height: a.win.innerHeight() - (a.opt.railpadding.top + a.opt.railpadding.bottom) }), a.railh && a.railh.css({ width: a.win.innerWidth() - (a.opt.railpadding.left + a.opt.railpadding.right) });else {
	        var f = a.getOffset();g = f.top;c = f.left - (a.opt.railpadding.left + a.opt.railpadding.right);g += d(a.win, "border-top-width", !0);
	        c += a.rail.align ? a.win.outerWidth() - d(a.win, "border-right-width") - a.rail.width : d(a.win, "border-left-width");if (e = a.opt.railoffset) e.top && (g += e.top), e.left && (c += e.left);a.railslocked || a.rail.css({ top: g, left: c, height: (b ? b.h : a.win.innerHeight()) - (a.opt.railpadding.top + a.opt.railpadding.bottom) });a.zoom && a.zoom.css({ top: g + 1, left: 1 == a.rail.align ? c - 20 : c + a.rail.width + 4 });if (a.railh && !a.railslocked) {
	          g = f.top;c = f.left;if (e = a.opt.railhoffset) e.top && (g += e.top), e.left && (c += e.left);b = a.railh.align ? g + d(a.win, "border-top-width", !0) + a.win.innerHeight() - a.railh.height : g + d(a.win, "border-top-width", !0);c += d(a.win, "border-left-width");a.railh.css({ top: b - (a.opt.railpadding.top + a.opt.railpadding.bottom), left: c, width: a.railh.width });
	        }
	      }
	    };this.doRailClick = function (b, g, c) {
	      var d;a.railslocked || (a.cancelEvent(b), g ? (g = c ? a.doScrollLeft : a.doScrollTop, d = c ? (b.pageX - a.railh.offset().left - a.cursorwidth / 2) * a.scrollratio.x : (b.pageY - a.rail.offset().top - a.cursorheight / 2) * a.scrollratio.y, g(d)) : (g = c ? a.doScrollLeftBy : a.doScrollBy, d = c ? a.scroll.x : a.scroll.y, b = c ? b.pageX - a.railh.offset().left : b.pageY - a.rail.offset().top, c = c ? a.view.w : a.view.h, g(d >= b ? c : -c)));
	    };a.hasanimationframe = v;a.hascancelanimationframe = w;a.hasanimationframe ? a.hascancelanimationframe || (w = function w() {
	      a.cancelAnimationFrame = !0;
	    }) : (v = function v(a) {
	      return setTimeout(a, 15 - Math.floor(+new Date() / 1E3) % 16);
	    }, w = clearTimeout);this.init = function () {
	      a.saved.css = [];if (e.isie7mobile || e.isoperamini) return !0;e.hasmstouch && a.css(a.ispage ? f("html") : a.win, { _touchaction: "none" });var b = e.ismodernie || e.isie10 ? { "-ms-overflow-style": "none" } : { "overflow-y": "hidden" };a.zindex = "auto";a.zindex = a.ispage || "auto" != a.opt.zindex ? a.opt.zindex : l() || "auto";!a.ispage && "auto" != a.zindex && a.zindex > A && (A = a.zindex);a.isie && 0 == a.zindex && "auto" == a.opt.zindex && (a.zindex = "auto");if (!a.ispage || !e.cantouch && !e.isieold && !e.isie9mobile) {
	        var c = a.docscroll;a.ispage && (c = a.haswrapper ? a.win : a.doc);e.isie9mobile || a.css(c, b);a.ispage && e.isie7 && ("BODY" == a.doc[0].nodeName ? a.css(f("html"), { "overflow-y": "hidden" }) : "HTML" == a.doc[0].nodeName && a.css(f("body"), b));!e.isios || a.ispage || a.haswrapper || a.css(f("body"), { "-webkit-overflow-scrolling": "touch" });var d = f(document.createElement("div"));d.css({ position: "relative", top: 0, "float": "right", width: a.opt.cursorwidth, height: 0, "background-color": a.opt.cursorcolor, border: a.opt.cursorborder, "background-clip": "padding-box", "-webkit-border-radius": a.opt.cursorborderradius, "-moz-border-radius": a.opt.cursorborderradius, "border-radius": a.opt.cursorborderradius });d.hborder = parseFloat(d.outerHeight() - d.innerHeight());d.addClass("nicescroll-cursors");
	        a.cursor = d;var m = f(document.createElement("div"));m.attr("id", a.id);m.addClass("nicescroll-rails nicescroll-rails-vr");var k,
	            h,
	            p = ["left", "right", "top", "bottom"],
	            L;for (L in p) {
	          h = p[L], (k = a.opt.railpadding[h]) ? m.css("padding-" + h, k + "px") : a.opt.railpadding[h] = 0;
	        }m.append(d);m.width = Math.max(parseFloat(a.opt.cursorwidth), d.outerWidth());m.css({ width: m.width + "px", zIndex: a.zindex, background: a.opt.background, cursor: "default" });m.visibility = !0;m.scrollable = !0;m.align = "left" == a.opt.railalign ? 0 : 1;a.rail = m;d = a.rail.drag = !1;!a.opt.boxzoom || a.ispage || e.isieold || (d = document.createElement("div"), a.bind(d, "click", a.doZoom), a.bind(d, "mouseenter", function () {
	          a.zoom.css("opacity", a.opt.cursoropacitymax);
	        }), a.bind(d, "mouseleave", function () {
	          a.zoom.css("opacity", a.opt.cursoropacitymin);
	        }), a.zoom = f(d), a.zoom.css({ cursor: "pointer", zIndex: a.zindex, backgroundImage: "url(" + a.opt.scriptpath + "zoomico.png)", height: 18, width: 18, backgroundPosition: "0px 0px" }), a.opt.dblclickzoom && a.bind(a.win, "dblclick", a.doZoom), e.cantouch && a.opt.gesturezoom && (a.ongesturezoom = function (b) {
	          1.5 < b.scale && a.doZoomIn(b);.8 > b.scale && a.doZoomOut(b);return a.cancelEvent(b);
	        }, a.bind(a.win, "gestureend", a.ongesturezoom)));a.railh = !1;var n;a.opt.horizrailenabled && (a.css(c, { overflowX: "hidden" }), d = f(document.createElement("div")), d.css({ position: "absolute", top: 0, height: a.opt.cursorwidth, width: 0, backgroundColor: a.opt.cursorcolor, border: a.opt.cursorborder, backgroundClip: "padding-box", "-webkit-border-radius": a.opt.cursorborderradius, "-moz-border-radius": a.opt.cursorborderradius,
	          "border-radius": a.opt.cursorborderradius }), e.isieold && d.css("overflow", "hidden"), d.wborder = parseFloat(d.outerWidth() - d.innerWidth()), d.addClass("nicescroll-cursors"), a.cursorh = d, n = f(document.createElement("div")), n.attr("id", a.id + "-hr"), n.addClass("nicescroll-rails nicescroll-rails-hr"), n.height = Math.max(parseFloat(a.opt.cursorwidth), d.outerHeight()), n.css({ height: n.height + "px", zIndex: a.zindex, background: a.opt.background }), n.append(d), n.visibility = !0, n.scrollable = !0, n.align = "top" == a.opt.railvalign ? 0 : 1, a.railh = n, a.railh.drag = !1);a.ispage ? (m.css({ position: "fixed", top: 0, height: "100%" }), m.align ? m.css({ right: 0 }) : m.css({ left: 0 }), a.body.append(m), a.railh && (n.css({ position: "fixed", left: 0, width: "100%" }), n.align ? n.css({ bottom: 0 }) : n.css({ top: 0 }), a.body.append(n))) : (a.ishwscroll ? ("static" == a.win.css("position") && a.css(a.win, { position: "relative" }), c = "HTML" == a.win[0].nodeName ? a.body : a.win, f(c).scrollTop(0).scrollLeft(0), a.zoom && (a.zoom.css({ position: "absolute", top: 1, right: 0, "margin-right": m.width + 4 }), c.append(a.zoom)), m.css({ position: "absolute", top: 0 }), m.align ? m.css({ right: 0 }) : m.css({ left: 0 }), c.append(m), n && (n.css({ position: "absolute", left: 0, bottom: 0 }), n.align ? n.css({ bottom: 0 }) : n.css({ top: 0 }), c.append(n))) : (a.isfixed = "fixed" == a.win.css("position"), c = a.isfixed ? "fixed" : "absolute", a.isfixed || (a.viewport = a.getViewport(a.win[0])), a.viewport && (a.body = a.viewport, 0 == /fixed|absolute/.test(a.viewport.css("position")) && a.css(a.viewport, { position: "relative" })), m.css({ position: c }), a.zoom && a.zoom.css({ position: c }), a.updateScrollBar(), a.body.append(m), a.zoom && a.body.append(a.zoom), a.railh && (n.css({ position: c }), a.body.append(n))), e.isios && a.css(a.win, { "-webkit-tap-highlight-color": "rgba(0,0,0,0)", "-webkit-touch-callout": "none" }), e.isie && a.opt.disableoutline && a.win.attr("hideFocus", "true"), e.iswebkit && a.opt.disableoutline && a.win.css("outline", "none"));!1 === a.opt.autohidemode ? (a.autohidedom = !1, a.rail.css({ opacity: a.opt.cursoropacitymax }), a.railh && a.railh.css({ opacity: a.opt.cursoropacitymax })) : !0 === a.opt.autohidemode || "leave" === a.opt.autohidemode ? (a.autohidedom = f().add(a.rail), e.isie8 && (a.autohidedom = a.autohidedom.add(a.cursor)), a.railh && (a.autohidedom = a.autohidedom.add(a.railh)), a.railh && e.isie8 && (a.autohidedom = a.autohidedom.add(a.cursorh))) : "scroll" == a.opt.autohidemode ? (a.autohidedom = f().add(a.rail), a.railh && (a.autohidedom = a.autohidedom.add(a.railh))) : "cursor" == a.opt.autohidemode ? (a.autohidedom = f().add(a.cursor), a.railh && (a.autohidedom = a.autohidedom.add(a.cursorh))) : "hidden" == a.opt.autohidemode && (a.autohidedom = !1, a.hide(), a.railslocked = !1);if (e.isie9mobile) a.scrollmom = new M(a), a.onmangotouch = function () {
	          var b = a.getScrollTop(),
	              c = a.getScrollLeft();if (b == a.scrollmom.lastscrolly && c == a.scrollmom.lastscrollx) return !0;var g = b - a.mangotouch.sy,
	              d = c - a.mangotouch.sx;if (0 != Math.round(Math.sqrt(Math.pow(d, 2) + Math.pow(g, 2)))) {
	            var e = 0 > g ? -1 : 1,
	                f = 0 > d ? -1 : 1,
	                u = +new Date();a.mangotouch.lazy && clearTimeout(a.mangotouch.lazy);80 < u - a.mangotouch.tm || a.mangotouch.dry != e || a.mangotouch.drx != f ? (a.scrollmom.stop(), a.scrollmom.reset(c, b), a.mangotouch.sy = b, a.mangotouch.ly = b, a.mangotouch.sx = c, a.mangotouch.lx = c, a.mangotouch.dry = e, a.mangotouch.drx = f, a.mangotouch.tm = u) : (a.scrollmom.stop(), a.scrollmom.update(a.mangotouch.sx - d, a.mangotouch.sy - g), a.mangotouch.tm = u, g = Math.max(Math.abs(a.mangotouch.ly - b), Math.abs(a.mangotouch.lx - c)), a.mangotouch.ly = b, a.mangotouch.lx = c, 2 < g && (a.mangotouch.lazy = setTimeout(function () {
	              a.mangotouch.lazy = !1;a.mangotouch.dry = 0;a.mangotouch.drx = 0;a.mangotouch.tm = 0;a.scrollmom.doMomentum(30);
	            }, 100)));
	          }
	        }, m = a.getScrollTop(), n = a.getScrollLeft(), a.mangotouch = { sy: m, ly: m, dry: 0, sx: n, lx: n, drx: 0, lazy: !1, tm: 0 }, a.bind(a.docscroll, "scroll", a.onmangotouch);else {
	          if (e.cantouch || a.istouchcapable || a.opt.touchbehavior || e.hasmstouch) {
	            a.scrollmom = new M(a);a.ontouchstart = function (b) {
	              if (b.pointerType && 2 != b.pointerType && "touch" != b.pointerType) return !1;a.hasmoving = !1;if (!a.railslocked) {
	                var c;if (e.hasmstouch) for (c = b.target ? b.target : !1; c;) {
	                  var g = f(c).getNiceScroll();if (0 < g.length && g[0].me == a.me) break;if (0 < g.length) return !1;if ("DIV" == c.nodeName && c.id == a.id) break;c = c.parentNode ? c.parentNode : !1;
	                }a.cancelScroll();if ((c = a.getTarget(b)) && /INPUT/i.test(c.nodeName) && /range/i.test(c.type)) return a.stopPropagation(b);!("clientX" in b) && "changedTouches" in b && (b.clientX = b.changedTouches[0].clientX, b.clientY = b.changedTouches[0].clientY);a.forcescreen && (g = b, b = { original: b.original ? b.original : b }, b.clientX = g.screenX, b.clientY = g.screenY);a.rail.drag = { x: b.clientX, y: b.clientY, sx: a.scroll.x, sy: a.scroll.y, st: a.getScrollTop(), sl: a.getScrollLeft(), pt: 2, dl: !1 };if (a.ispage || !a.opt.directionlockdeadzone) a.rail.drag.dl = "f";else {
	                  var g = f(window).width(),
	                      d = f(window).height(),
	                      d = Math.max(0, Math.max(document.body.scrollHeight, document.documentElement.scrollHeight) - d),
	                      g = Math.max(0, Math.max(document.body.scrollWidth, document.documentElement.scrollWidth) - g);a.rail.drag.ck = !a.rail.scrollable && a.railh.scrollable ? 0 < d ? "v" : !1 : a.rail.scrollable && !a.railh.scrollable ? 0 < g ? "h" : !1 : !1;a.rail.drag.ck || (a.rail.drag.dl = "f");
	                }a.opt.touchbehavior && a.isiframe && e.isie && (g = a.win.position(), a.rail.drag.x += g.left, a.rail.drag.y += g.top);a.hasmoving = !1;a.lastmouseup = !1;a.scrollmom.reset(b.clientX, b.clientY);if (!e.cantouch && !this.istouchcapable && !b.pointerType) {
	                  if (!c || !/INPUT|SELECT|TEXTAREA/i.test(c.nodeName)) return !a.ispage && e.hasmousecapture && c.setCapture(), a.opt.touchbehavior ? (c.onclick && !c._onclick && (c._onclick = c.onclick, c.onclick = function (b) {
	                    if (a.hasmoving) return !1;c._onclick.call(this, b);
	                  }), a.cancelEvent(b)) : a.stopPropagation(b);/SUBMIT|CANCEL|BUTTON/i.test(f(c).attr("type")) && (pc = { tg: c, click: !1 }, a.preventclick = pc);
	                }
	              }
	            };a.ontouchend = function (b) {
	              if (!a.rail.drag) return !0;
	              if (2 == a.rail.drag.pt) {
	                if (b.pointerType && 2 != b.pointerType && "touch" != b.pointerType) return !1;a.scrollmom.doMomentum();a.rail.drag = !1;if (a.hasmoving && (a.lastmouseup = !0, a.hideCursor(), e.hasmousecapture && document.releaseCapture(), !e.cantouch)) return a.cancelEvent(b);
	              } else if (1 == a.rail.drag.pt) return a.onmouseup(b);
	            };var q = a.opt.touchbehavior && a.isiframe && !e.hasmousecapture;a.ontouchmove = function (b, c) {
	              if (!a.rail.drag || b.targetTouches && a.opt.preventmultitouchscrolling && 1 < b.targetTouches.length || b.pointerType && 2 != b.pointerType && "touch" != b.pointerType) return !1;if (2 == a.rail.drag.pt) {
	                if (e.cantouch && e.isios && void 0 === b.original) return !0;a.hasmoving = !0;a.preventclick && !a.preventclick.click && (a.preventclick.click = a.preventclick.tg.onclick || !1, a.preventclick.tg.onclick = a.onpreventclick);b = f.extend({ original: b }, b);"changedTouches" in b && (b.clientX = b.changedTouches[0].clientX, b.clientY = b.changedTouches[0].clientY);if (a.forcescreen) {
	                  var g = b;b = { original: b.original ? b.original : b };b.clientX = g.screenX;b.clientY = g.screenY;
	                }var d,
	                    g = d = 0;q && !c && (d = a.win.position(), g = -d.left, d = -d.top);var u = b.clientY + d;d = u - a.rail.drag.y;var m = b.clientX + g,
	                    k = m - a.rail.drag.x,
	                    h = a.rail.drag.st - d;a.ishwscroll && a.opt.bouncescroll ? 0 > h ? h = Math.round(h / 2) : h > a.page.maxh && (h = a.page.maxh + Math.round((h - a.page.maxh) / 2)) : (0 > h && (u = h = 0), h > a.page.maxh && (h = a.page.maxh, u = 0));var l;a.railh && a.railh.scrollable && (l = a.isrtlmode ? k - a.rail.drag.sl : a.rail.drag.sl - k, a.ishwscroll && a.opt.bouncescroll ? 0 > l ? l = Math.round(l / 2) : l > a.page.maxw && (l = a.page.maxw + Math.round((l - a.page.maxw) / 2)) : (0 > l && (m = l = 0), l > a.page.maxw && (l = a.page.maxw, m = 0)));g = !1;if (a.rail.drag.dl) g = !0, "v" == a.rail.drag.dl ? l = a.rail.drag.sl : "h" == a.rail.drag.dl && (h = a.rail.drag.st);else {
	                  d = Math.abs(d);var k = Math.abs(k),
	                      C = a.opt.directionlockdeadzone;if ("v" == a.rail.drag.ck) {
	                    if (d > C && k <= .3 * d) return a.rail.drag = !1, !0;k > C && (a.rail.drag.dl = "f", f("body").scrollTop(f("body").scrollTop()));
	                  } else if ("h" == a.rail.drag.ck) {
	                    if (k > C && d <= .3 * k) return a.rail.drag = !1, !0;d > C && (a.rail.drag.dl = "f", f("body").scrollLeft(f("body").scrollLeft()));
	                  }
	                }a.synched("touchmove", function () {
	                  a.rail.drag && 2 == a.rail.drag.pt && (a.prepareTransition && a.prepareTransition(0), a.rail.scrollable && a.setScrollTop(h), a.scrollmom.update(m, u), a.railh && a.railh.scrollable ? (a.setScrollLeft(l), a.showCursor(h, l)) : a.showCursor(h), e.isie10 && document.selection.clear());
	                });e.ischrome && a.istouchcapable && (g = !1);if (g) return a.cancelEvent(b);
	              } else if (1 == a.rail.drag.pt) return a.onmousemove(b);
	            };
	          }a.onmousedown = function (b, c) {
	            if (!a.rail.drag || 1 == a.rail.drag.pt) {
	              if (a.railslocked) return a.cancelEvent(b);a.cancelScroll();
	              a.rail.drag = { x: b.clientX, y: b.clientY, sx: a.scroll.x, sy: a.scroll.y, pt: 1, hr: !!c };var g = a.getTarget(b);!a.ispage && e.hasmousecapture && g.setCapture();a.isiframe && !e.hasmousecapture && (a.saved.csspointerevents = a.doc.css("pointer-events"), a.css(a.doc, { "pointer-events": "none" }));a.hasmoving = !1;return a.cancelEvent(b);
	            }
	          };a.onmouseup = function (b) {
	            if (a.rail.drag) {
	              if (1 != a.rail.drag.pt) return !0;e.hasmousecapture && document.releaseCapture();a.isiframe && !e.hasmousecapture && a.doc.css("pointer-events", a.saved.csspointerevents);
	              a.rail.drag = !1;a.hasmoving && a.triggerScrollEnd();return a.cancelEvent(b);
	            }
	          };a.onmousemove = function (b) {
	            if (a.rail.drag) {
	              if (1 == a.rail.drag.pt) {
	                if (e.ischrome && 0 == b.which) return a.onmouseup(b);a.cursorfreezed = !0;a.hasmoving = !0;if (a.rail.drag.hr) {
	                  a.scroll.x = a.rail.drag.sx + (b.clientX - a.rail.drag.x);0 > a.scroll.x && (a.scroll.x = 0);var c = a.scrollvaluemaxw;a.scroll.x > c && (a.scroll.x = c);
	                } else a.scroll.y = a.rail.drag.sy + (b.clientY - a.rail.drag.y), 0 > a.scroll.y && (a.scroll.y = 0), c = a.scrollvaluemax, a.scroll.y > c && (a.scroll.y = c);a.synched("mousemove", function () {
	                  a.rail.drag && 1 == a.rail.drag.pt && (a.showCursor(), a.rail.drag.hr ? a.hasreversehr ? a.doScrollLeft(a.scrollvaluemaxw - Math.round(a.scroll.x * a.scrollratio.x), a.opt.cursordragspeed) : a.doScrollLeft(Math.round(a.scroll.x * a.scrollratio.x), a.opt.cursordragspeed) : a.doScrollTop(Math.round(a.scroll.y * a.scrollratio.y), a.opt.cursordragspeed));
	                });return a.cancelEvent(b);
	              }
	            } else a.checkarea = 0;
	          };if (e.cantouch || a.opt.touchbehavior) a.onpreventclick = function (b) {
	            if (a.preventclick) return a.preventclick.tg.onclick = a.preventclick.click, a.preventclick = !1, a.cancelEvent(b);
	          }, a.bind(a.win, "mousedown", a.ontouchstart), a.onclick = e.isios ? !1 : function (b) {
	            return a.lastmouseup ? (a.lastmouseup = !1, a.cancelEvent(b)) : !0;
	          }, a.opt.grabcursorenabled && e.cursorgrabvalue && (a.css(a.ispage ? a.doc : a.win, { cursor: e.cursorgrabvalue }), a.css(a.rail, { cursor: e.cursorgrabvalue }));else {
	            var r = function r(b) {
	              if (a.selectiondrag) {
	                if (b) {
	                  var c = a.win.outerHeight();b = b.pageY - a.selectiondrag.top;0 < b && b < c && (b = 0);b >= c && (b -= c);a.selectiondrag.df = b;
	                }0 != a.selectiondrag.df && (a.doScrollBy(2 * -Math.floor(a.selectiondrag.df / 6)), a.debounced("doselectionscroll", function () {
	                  r();
	                }, 50));
	              }
	            };a.hasTextSelected = "getSelection" in document ? function () {
	              return 0 < document.getSelection().rangeCount;
	            } : "selection" in document ? function () {
	              return "None" != document.selection.type;
	            } : function () {
	              return !1;
	            };a.onselectionstart = function (b) {
	              a.ispage || (a.selectiondrag = a.win.offset());
	            };a.onselectionend = function (b) {
	              a.selectiondrag = !1;
	            };a.onselectiondrag = function (b) {
	              a.selectiondrag && a.hasTextSelected() && a.debounced("selectionscroll", function () {
	                r(b);
	              }, 250);
	            };
	          }e.hasw3ctouch ? (a.css(a.rail, { "touch-action": "none" }), a.css(a.cursor, { "touch-action": "none" }), a.bind(a.win, "pointerdown", a.ontouchstart), a.bind(document, "pointerup", a.ontouchend), a.bind(document, "pointermove", a.ontouchmove)) : e.hasmstouch ? (a.css(a.rail, { "-ms-touch-action": "none" }), a.css(a.cursor, { "-ms-touch-action": "none" }), a.bind(a.win, "MSPointerDown", a.ontouchstart), a.bind(document, "MSPointerUp", a.ontouchend), a.bind(document, "MSPointerMove", a.ontouchmove), a.bind(a.cursor, "MSGestureHold", function (a) {
	            a.preventDefault();
	          }), a.bind(a.cursor, "contextmenu", function (a) {
	            a.preventDefault();
	          })) : this.istouchcapable && (a.bind(a.win, "touchstart", a.ontouchstart), a.bind(document, "touchend", a.ontouchend), a.bind(document, "touchcancel", a.ontouchend), a.bind(document, "touchmove", a.ontouchmove));if (a.opt.cursordragontouch || !e.cantouch && !a.opt.touchbehavior) a.rail.css({ cursor: "default" }), a.railh && a.railh.css({ cursor: "default" }), a.jqbind(a.rail, "mouseenter", function () {
	            if (!a.ispage && !a.win.is(":visible")) return !1;
	            a.canshowonmouseevent && a.showCursor();a.rail.active = !0;
	          }), a.jqbind(a.rail, "mouseleave", function () {
	            a.rail.active = !1;a.rail.drag || a.hideCursor();
	          }), a.opt.sensitiverail && (a.bind(a.rail, "click", function (b) {
	            a.doRailClick(b, !1, !1);
	          }), a.bind(a.rail, "dblclick", function (b) {
	            a.doRailClick(b, !0, !1);
	          }), a.bind(a.cursor, "click", function (b) {
	            a.cancelEvent(b);
	          }), a.bind(a.cursor, "dblclick", function (b) {
	            a.cancelEvent(b);
	          })), a.railh && (a.jqbind(a.railh, "mouseenter", function () {
	            if (!a.ispage && !a.win.is(":visible")) return !1;a.canshowonmouseevent && a.showCursor();a.rail.active = !0;
	          }), a.jqbind(a.railh, "mouseleave", function () {
	            a.rail.active = !1;a.rail.drag || a.hideCursor();
	          }), a.opt.sensitiverail && (a.bind(a.railh, "click", function (b) {
	            a.doRailClick(b, !1, !0);
	          }), a.bind(a.railh, "dblclick", function (b) {
	            a.doRailClick(b, !0, !0);
	          }), a.bind(a.cursorh, "click", function (b) {
	            a.cancelEvent(b);
	          }), a.bind(a.cursorh, "dblclick", function (b) {
	            a.cancelEvent(b);
	          })));e.cantouch || a.opt.touchbehavior ? (a.bind(e.hasmousecapture ? a.win : document, "mouseup", a.ontouchend), a.bind(document, "mousemove", a.ontouchmove), a.onclick && a.bind(document, "click", a.onclick), a.opt.cursordragontouch ? (a.bind(a.cursor, "mousedown", a.onmousedown), a.bind(a.cursor, "mouseup", a.onmouseup), a.cursorh && a.bind(a.cursorh, "mousedown", function (b) {
	            a.onmousedown(b, !0);
	          }), a.cursorh && a.bind(a.cursorh, "mouseup", a.onmouseup)) : (a.bind(a.rail, "mousedown", function (a) {
	            a.preventDefault();
	          }), a.railh && a.bind(a.railh, "mousedown", function (a) {
	            a.preventDefault();
	          }))) : (a.bind(e.hasmousecapture ? a.win : document, "mouseup", a.onmouseup), a.bind(document, "mousemove", a.onmousemove), a.onclick && a.bind(document, "click", a.onclick), a.bind(a.cursor, "mousedown", a.onmousedown), a.bind(a.cursor, "mouseup", a.onmouseup), a.railh && (a.bind(a.cursorh, "mousedown", function (b) {
	            a.onmousedown(b, !0);
	          }), a.bind(a.cursorh, "mouseup", a.onmouseup)), !a.ispage && a.opt.enablescrollonselection && (a.bind(a.win[0], "mousedown", a.onselectionstart), a.bind(document, "mouseup", a.onselectionend), a.bind(a.cursor, "mouseup", a.onselectionend), a.cursorh && a.bind(a.cursorh, "mouseup", a.onselectionend), a.bind(document, "mousemove", a.onselectiondrag)), a.zoom && (a.jqbind(a.zoom, "mouseenter", function () {
	            a.canshowonmouseevent && a.showCursor();a.rail.active = !0;
	          }), a.jqbind(a.zoom, "mouseleave", function () {
	            a.rail.active = !1;a.rail.drag || a.hideCursor();
	          })));a.opt.enablemousewheel && (a.isiframe || a.mousewheel(e.isie && a.ispage ? document : a.win, a.onmousewheel), a.mousewheel(a.rail, a.onmousewheel), a.railh && a.mousewheel(a.railh, a.onmousewheelhr));a.ispage || e.cantouch || /HTML|^BODY/.test(a.win[0].nodeName) || (a.win.attr("tabindex") || a.win.attr({ tabindex: O++ }), a.jqbind(a.win, "focus", function (b) {
	            B = a.getTarget(b).id || !0;a.hasfocus = !0;a.canshowonmouseevent && a.noticeCursor();
	          }), a.jqbind(a.win, "blur", function (b) {
	            B = !1;a.hasfocus = !1;
	          }), a.jqbind(a.win, "mouseenter", function (b) {
	            F = a.getTarget(b).id || !0;a.hasmousefocus = !0;a.canshowonmouseevent && a.noticeCursor();
	          }), a.jqbind(a.win, "mouseleave", function () {
	            F = !1;a.hasmousefocus = !1;a.rail.drag || a.hideCursor();
	          }));
	        }a.onkeypress = function (b) {
	          if (a.railslocked && 0 == a.page.maxh) return !0;b = b ? b : window.e;var c = a.getTarget(b);if (c && /INPUT|TEXTAREA|SELECT|OPTION/.test(c.nodeName) && (!c.getAttribute("type") && !c.type || !/submit|button|cancel/i.tp) || f(c).attr("contenteditable")) return !0;if (a.hasfocus || a.hasmousefocus && !B || a.ispage && !B && !F) {
	            c = b.keyCode;if (a.railslocked && 27 != c) return a.cancelEvent(b);var g = b.ctrlKey || !1,
	                d = b.shiftKey || !1,
	                e = !1;switch (c) {case 38:case 63233:
	                a.doScrollBy(72);e = !0;break;case 40:case 63235:
	                a.doScrollBy(-72);e = !0;break;case 37:case 63232:
	                a.railh && (g ? a.doScrollLeft(0) : a.doScrollLeftBy(72), e = !0);break;case 39:case 63234:
	                a.railh && (g ? a.doScrollLeft(a.page.maxw) : a.doScrollLeftBy(-72), e = !0);break;case 33:case 63276:
	                a.doScrollBy(a.view.h);e = !0;break;case 34:case 63277:
	                a.doScrollBy(-a.view.h);e = !0;break;case 36:case 63273:
	                a.railh && g ? a.doScrollPos(0, 0) : a.doScrollTo(0);e = !0;break;case 35:case 63275:
	                a.railh && g ? a.doScrollPos(a.page.maxw, a.page.maxh) : a.doScrollTo(a.page.maxh);e = !0;break;case 32:
	                a.opt.spacebarenabled && (d ? a.doScrollBy(a.view.h) : a.doScrollBy(-a.view.h), e = !0);break;case 27:
	                a.zoomactive && (a.doZoom(), e = !0);}if (e) return a.cancelEvent(b);
	          }
	        };a.opt.enablekeyboard && a.bind(document, e.isopera && !e.isopera12 ? "keypress" : "keydown", a.onkeypress);a.bind(document, "keydown", function (b) {
	          b.ctrlKey && (a.wheelprevented = !0);
	        });a.bind(document, "keyup", function (b) {
	          b.ctrlKey || (a.wheelprevented = !1);
	        });a.bind(window, "blur", function (b) {
	          a.wheelprevented = !1;
	        });a.bind(window, "resize", a.lazyResize);a.bind(window, "orientationchange", a.lazyResize);a.bind(window, "load", a.lazyResize);if (e.ischrome && !a.ispage && !a.haswrapper) {
	          var t = a.win.attr("style"),
	              m = parseFloat(a.win.css("width")) + 1;a.win.css("width", m);a.synched("chromefix", function () {
	            a.win.attr("style", t);
	          });
	        }a.onAttributeChange = function (b) {
	          a.lazyResize(a.isieold ? 250 : 30);
	        };a.isie11 || !1 === x || (a.observerbody = new x(function (b) {
	          b.forEach(function (b) {
	            if ("attributes" == b.type) return f("body").hasClass("modal-open") && f("body").hasClass("modal-dialog") && !f.contains(f(".modal-dialog")[0], a.doc[0]) ? a.hide() : a.show();
	          });if (document.body.scrollHeight != a.page.maxh) return a.lazyResize(30);
	        }), a.observerbody.observe(document.body, { childList: !0, subtree: !0, characterData: !1, attributes: !0, attributeFilter: ["class"] }));a.ispage || a.haswrapper || (!1 !== x ? (a.observer = new x(function (b) {
	          b.forEach(a.onAttributeChange);
	        }), a.observer.observe(a.win[0], { childList: !0, characterData: !1, attributes: !0, subtree: !1 }), a.observerremover = new x(function (b) {
	          b.forEach(function (b) {
	            if (0 < b.removedNodes.length) for (var c in b.removedNodes) {
	              if (a && b.removedNodes[c] == a.win[0]) return a.remove();
	            }
	          });
	        }), a.observerremover.observe(a.win[0].parentNode, { childList: !0, characterData: !1, attributes: !1, subtree: !1 })) : (a.bind(a.win, e.isie && !e.isie9 ? "propertychange" : "DOMAttrModified", a.onAttributeChange), e.isie9 && a.win[0].attachEvent("onpropertychange", a.onAttributeChange), a.bind(a.win, "DOMNodeRemoved", function (b) {
	          b.target == a.win[0] && a.remove();
	        })));!a.ispage && a.opt.boxzoom && a.bind(window, "resize", a.resizeZoom);a.istextarea && (a.bind(a.win, "keydown", a.lazyResize), a.bind(a.win, "mouseup", a.lazyResize));a.lazyResize(30);
	      }if ("IFRAME" == this.doc[0].nodeName) {
	        var N = function N() {
	          a.iframexd = !1;var c;try {
	            c = "contentDocument" in this ? this.contentDocument : this.contentWindow.document;
	          } catch (g) {
	            a.iframexd = !0, c = !1;
	          }if (a.iframexd) return "console" in window && console.log("NiceScroll error: policy restriced iframe"), !0;a.forcescreen = !0;a.isiframe && (a.iframe = { doc: f(c), html: a.doc.contents().find("html")[0], body: a.doc.contents().find("body")[0] }, a.getContentSize = function () {
	            return { w: Math.max(a.iframe.html.scrollWidth, a.iframe.body.scrollWidth), h: Math.max(a.iframe.html.scrollHeight, a.iframe.body.scrollHeight) };
	          }, a.docscroll = f(a.iframe.body));if (!e.isios && a.opt.iframeautoresize && !a.isiframe) {
	            a.win.scrollTop(0);a.doc.height("");var d = Math.max(c.getElementsByTagName("html")[0].scrollHeight, c.body.scrollHeight);a.doc.height(d);
	          }a.lazyResize(30);e.isie7 && a.css(f(a.iframe.html), b);a.css(f(a.iframe.body), b);e.isios && a.haswrapper && a.css(f(c.body), { "-webkit-transform": "translate3d(0,0,0)" });"contentWindow" in this ? a.bind(this.contentWindow, "scroll", a.onscroll) : a.bind(c, "scroll", a.onscroll);
	          a.opt.enablemousewheel && a.mousewheel(c, a.onmousewheel);a.opt.enablekeyboard && a.bind(c, e.isopera ? "keypress" : "keydown", a.onkeypress);if (e.cantouch || a.opt.touchbehavior) a.bind(c, "mousedown", a.ontouchstart), a.bind(c, "mousemove", function (b) {
	            return a.ontouchmove(b, !0);
	          }), a.opt.grabcursorenabled && e.cursorgrabvalue && a.css(f(c.body), { cursor: e.cursorgrabvalue });a.bind(c, "mouseup", a.ontouchend);a.zoom && (a.opt.dblclickzoom && a.bind(c, "dblclick", a.doZoom), a.ongesturezoom && a.bind(c, "gestureend", a.ongesturezoom));
	        };
	        this.doc[0].readyState && "complete" == this.doc[0].readyState && setTimeout(function () {
	          N.call(a.doc[0], !1);
	        }, 500);a.bind(this.doc, "load", N);
	      }
	    };this.showCursor = function (b, c) {
	      a.cursortimeout && (clearTimeout(a.cursortimeout), a.cursortimeout = 0);if (a.rail) {
	        a.autohidedom && (a.autohidedom.stop().css({ opacity: a.opt.cursoropacitymax }), a.cursoractive = !0);a.rail.drag && 1 == a.rail.drag.pt || (void 0 !== b && !1 !== b && (a.scroll.y = Math.round(1 * b / a.scrollratio.y)), void 0 !== c && (a.scroll.x = Math.round(1 * c / a.scrollratio.x)));a.cursor.css({ height: a.cursorheight,
	          top: a.scroll.y });if (a.cursorh) {
	          var d = a.hasreversehr ? a.scrollvaluemaxw - a.scroll.x : a.scroll.x;!a.rail.align && a.rail.visibility ? a.cursorh.css({ width: a.cursorwidth, left: d + a.rail.width }) : a.cursorh.css({ width: a.cursorwidth, left: d });a.cursoractive = !0;
	        }a.zoom && a.zoom.stop().css({ opacity: a.opt.cursoropacitymax });
	      }
	    };this.hideCursor = function (b) {
	      a.cursortimeout || !a.rail || !a.autohidedom || a.hasmousefocus && "leave" == a.opt.autohidemode || (a.cursortimeout = setTimeout(function () {
	        a.rail.active && a.showonmouseevent || (a.autohidedom.stop().animate({ opacity: a.opt.cursoropacitymin }), a.zoom && a.zoom.stop().animate({ opacity: a.opt.cursoropacitymin }), a.cursoractive = !1);a.cursortimeout = 0;
	      }, b || a.opt.hidecursordelay));
	    };this.noticeCursor = function (b, c, d) {
	      a.showCursor(c, d);a.rail.active || a.hideCursor(b);
	    };this.getContentSize = a.ispage ? function () {
	      return { w: Math.max(document.body.scrollWidth, document.documentElement.scrollWidth), h: Math.max(document.body.scrollHeight, document.documentElement.scrollHeight) };
	    } : a.haswrapper ? function () {
	      return { w: a.doc.outerWidth() + parseInt(a.win.css("paddingLeft")) + parseInt(a.win.css("paddingRight")), h: a.doc.outerHeight() + parseInt(a.win.css("paddingTop")) + parseInt(a.win.css("paddingBottom")) };
	    } : function () {
	      return { w: a.docscroll[0].scrollWidth, h: a.docscroll[0].scrollHeight };
	    };this.onResize = function (b, c) {
	      if (!a || !a.win) return !1;if (!a.haswrapper && !a.ispage) {
	        if ("none" == a.win.css("display")) return a.visibility && a.hideRail().hideRailHr(), !1;a.hidden || a.visibility || a.showRail().showRailHr();
	      }var d = a.page.maxh,
	          e = a.page.maxw,
	          f = a.view.h,
	          k = a.view.w;a.view = { w: a.ispage ? a.win.width() : parseInt(a.win[0].clientWidth), h: a.ispage ? a.win.height() : parseInt(a.win[0].clientHeight) };a.page = c ? c : a.getContentSize();a.page.maxh = Math.max(0, a.page.h - a.view.h);a.page.maxw = Math.max(0, a.page.w - a.view.w);if (a.page.maxh == d && a.page.maxw == e && a.view.w == k && a.view.h == f) {
	        if (a.ispage) return a;d = a.win.offset();if (a.lastposition && (e = a.lastposition, e.top == d.top && e.left == d.left)) return a;a.lastposition = d;
	      }0 == a.page.maxh ? (a.hideRail(), a.scrollvaluemax = 0, a.scroll.y = 0, a.scrollratio.y = 0, a.cursorheight = 0, a.setScrollTop(0), a.rail && (a.rail.scrollable = !1)) : (a.page.maxh -= a.opt.railpadding.top + a.opt.railpadding.bottom, a.rail.scrollable = !0);0 == a.page.maxw ? (a.hideRailHr(), a.scrollvaluemaxw = 0, a.scroll.x = 0, a.scrollratio.x = 0, a.cursorwidth = 0, a.setScrollLeft(0), a.railh && (a.railh.scrollable = !1)) : (a.page.maxw -= a.opt.railpadding.left + a.opt.railpadding.right, a.railh && (a.railh.scrollable = a.opt.horizrailenabled));a.railslocked = a.locked || 0 == a.page.maxh && 0 == a.page.maxw;if (a.railslocked) return a.ispage || a.updateScrollBar(a.view), !1;a.hidden || a.visibility ? !a.railh || a.hidden || a.railh.visibility || a.showRailHr() : a.showRail().showRailHr();a.istextarea && a.win.css("resize") && "none" != a.win.css("resize") && (a.view.h -= 20);a.cursorheight = Math.min(a.view.h, Math.round(a.view.h / a.page.h * a.view.h));a.cursorheight = a.opt.cursorfixedheight ? a.opt.cursorfixedheight : Math.max(a.opt.cursorminheight, a.cursorheight);a.cursorwidth = Math.min(a.view.w, Math.round(a.view.w / a.page.w * a.view.w));a.cursorwidth = a.opt.cursorfixedheight ? a.opt.cursorfixedheight : Math.max(a.opt.cursorminheight, a.cursorwidth);a.scrollvaluemax = a.view.h - a.cursorheight - a.cursor.hborder - (a.opt.railpadding.top + a.opt.railpadding.bottom);a.railh && (a.railh.width = 0 < a.page.maxh ? a.view.w - a.rail.width : a.view.w, a.scrollvaluemaxw = a.railh.width - a.cursorwidth - a.cursorh.wborder - (a.opt.railpadding.left + a.opt.railpadding.right));a.ispage || a.updateScrollBar(a.view);a.scrollratio = { x: a.page.maxw / a.scrollvaluemaxw, y: a.page.maxh / a.scrollvaluemax };a.getScrollTop() > a.page.maxh ? a.doScrollTop(a.page.maxh) : (a.scroll.y = Math.round(a.getScrollTop() * (1 / a.scrollratio.y)), a.scroll.x = Math.round(a.getScrollLeft() * (1 / a.scrollratio.x)), a.cursoractive && a.noticeCursor());a.scroll.y && 0 == a.getScrollTop() && a.doScrollTo(Math.floor(a.scroll.y * a.scrollratio.y));return a;
	    };this.resize = a.onResize;this.hlazyresize = 0;this.lazyResize = function (b) {
	      a.haswrapper || a.hide();a.hlazyresize && clearTimeout(a.hlazyresize);a.hlazyresize = setTimeout(function () {
	        a && a.show().resize();
	      }, 240);return a;
	    };this.jqbind = function (b, c, d) {
	      a.events.push({ e: b, n: c, f: d, q: !0 });f(b).bind(c, d);
	    };this.mousewheel = function (b, c, d) {
	      b = "jquery" in b ? b[0] : b;if ("onwheel" in document.createElement("div")) a._bind(b, "wheel", c, d || !1);else {
	        var e = void 0 !== document.onmousewheel ? "mousewheel" : "DOMMouseScroll";q(b, e, c, d || !1);"DOMMouseScroll" == e && q(b, "MozMousePixelScroll", c, d || !1);
	      }
	    };e.haseventlistener ? (this.bind = function (b, c, d, e) {
	      a._bind("jquery" in b ? b[0] : b, c, d, e || !1);
	    }, this._bind = function (b, c, d, e) {
	      a.events.push({ e: b, n: c, f: d, b: e, q: !1 });b.addEventListener(c, d, e || !1);
	    }, this.cancelEvent = function (a) {
	      if (!a) return !1;a = a.original ? a.original : a;a.cancelable && a.preventDefault();a.stopPropagation();a.preventManipulation && a.preventManipulation();return !1;
	    }, this.stopPropagation = function (a) {
	      if (!a) return !1;a = a.original ? a.original : a;a.stopPropagation();return !1;
	    }, this._unbind = function (a, c, d, e) {
	      a.removeEventListener(c, d, e);
	    }) : (this.bind = function (b, c, d, e) {
	      var f = "jquery" in b ? b[0] : b;a._bind(f, c, function (b) {
	        (b = b || window.event || !1) && b.srcElement && (b.target = b.srcElement);"pageY" in b || (b.pageX = b.clientX + document.documentElement.scrollLeft, b.pageY = b.clientY + document.documentElement.scrollTop);return !1 === d.call(f, b) || !1 === e ? a.cancelEvent(b) : !0;
	      });
	    }, this._bind = function (b, c, d, e) {
	      a.events.push({ e: b, n: c, f: d, b: e, q: !1 });b.attachEvent ? b.attachEvent("on" + c, d) : b["on" + c] = d;
	    }, this.cancelEvent = function (a) {
	      a = window.event || !1;if (!a) return !1;a.cancelBubble = !0;a.cancel = !0;return a.returnValue = !1;
	    }, this.stopPropagation = function (a) {
	      a = window.event || !1;if (!a) return !1;a.cancelBubble = !0;return !1;
	    }, this._unbind = function (a, c, d, e) {
	      a.detachEvent ? a.detachEvent("on" + c, d) : a["on" + c] = !1;
	    });
	    this.unbindAll = function () {
	      for (var b = 0; b < a.events.length; b++) {
	        var c = a.events[b];c.q ? c.e.unbind(c.n, c.f) : a._unbind(c.e, c.n, c.f, c.b);
	      }
	    };this.showRail = function () {
	      0 == a.page.maxh || !a.ispage && "none" == a.win.css("display") || (a.visibility = !0, a.rail.visibility = !0, a.rail.css("display", "block"));return a;
	    };this.showRailHr = function () {
	      if (!a.railh) return a;0 == a.page.maxw || !a.ispage && "none" == a.win.css("display") || (a.railh.visibility = !0, a.railh.css("display", "block"));return a;
	    };this.hideRail = function () {
	      a.visibility = !1;a.rail.visibility = !1;a.rail.css("display", "none");return a;
	    };this.hideRailHr = function () {
	      if (!a.railh) return a;a.railh.visibility = !1;a.railh.css("display", "none");return a;
	    };this.show = function () {
	      a.hidden = !1;a.railslocked = !1;return a.showRail().showRailHr();
	    };this.hide = function () {
	      a.hidden = !0;a.railslocked = !0;return a.hideRail().hideRailHr();
	    };this.toggle = function () {
	      return a.hidden ? a.show() : a.hide();
	    };this.remove = function () {
	      a.stop();a.cursortimeout && clearTimeout(a.cursortimeout);for (var b in a.delaylist) {
	        a.delaylist[b] && w(a.delaylist[b].h);
	      }a.doZoomOut();a.unbindAll();e.isie9 && a.win[0].detachEvent("onpropertychange", a.onAttributeChange);!1 !== a.observer && a.observer.disconnect();!1 !== a.observerremover && a.observerremover.disconnect();!1 !== a.observerbody && a.observerbody.disconnect();a.events = null;a.cursor && a.cursor.remove();a.cursorh && a.cursorh.remove();a.rail && a.rail.remove();a.railh && a.railh.remove();a.zoom && a.zoom.remove();for (b = 0; b < a.saved.css.length; b++) {
	        var c = a.saved.css[b];c[0].css(c[1], void 0 === c[2] ? "" : c[2]);
	      }a.saved = !1;a.me.data("__nicescroll", "");var d = f.nicescroll;d.each(function (b) {
	        if (this && this.id === a.id) {
	          delete d[b];for (var c = ++b; c < d.length; c++, b++) {
	            d[b] = d[c];
	          }d.length--;d.length && delete d[d.length];
	        }
	      });for (var k in a) {
	        a[k] = null, delete a[k];
	      }a = null;
	    };this.scrollstart = function (b) {
	      this.onscrollstart = b;return a;
	    };this.scrollend = function (b) {
	      this.onscrollend = b;return a;
	    };this.scrollcancel = function (b) {
	      this.onscrollcancel = b;return a;
	    };this.zoomin = function (b) {
	      this.onzoomin = b;return a;
	    };this.zoomout = function (b) {
	      this.onzoomout = b;return a;
	    };this.isScrollable = function (a) {
	      a = a.target ? a.target : a;if ("OPTION" == a.nodeName) return !0;for (; a && 1 == a.nodeType && !/^BODY|HTML/.test(a.nodeName);) {
	        var c = f(a),
	            c = c.css("overflowY") || c.css("overflowX") || c.css("overflow") || "";if (/scroll|auto/.test(c)) return a.clientHeight != a.scrollHeight;a = a.parentNode ? a.parentNode : !1;
	      }return !1;
	    };this.getViewport = function (a) {
	      for (a = a && a.parentNode ? a.parentNode : !1; a && 1 == a.nodeType && !/^BODY|HTML/.test(a.nodeName);) {
	        var c = f(a);if (/fixed|absolute/.test(c.css("position"))) return c;
	        var d = c.css("overflowY") || c.css("overflowX") || c.css("overflow") || "";if (/scroll|auto/.test(d) && a.clientHeight != a.scrollHeight || 0 < c.getNiceScroll().length) return c;a = a.parentNode ? a.parentNode : !1;
	      }return !1;
	    };this.triggerScrollEnd = function () {
	      if (a.onscrollend) {
	        var b = a.getScrollLeft(),
	            c = a.getScrollTop();a.onscrollend.call(a, { type: "scrollend", current: { x: b, y: c }, end: { x: b, y: c } });
	      }
	    };this.onmousewheel = function (b) {
	      if (!a.wheelprevented) {
	        if (a.railslocked) return a.debounced("checkunlock", a.resize, 250), !0;if (a.rail.drag) return a.cancelEvent(b);
	        "auto" == a.opt.oneaxismousemode && 0 != b.deltaX && (a.opt.oneaxismousemode = !1);if (a.opt.oneaxismousemode && 0 == b.deltaX && !a.rail.scrollable) return a.railh && a.railh.scrollable ? a.onmousewheelhr(b) : !0;var c = +new Date(),
	            d = !1;a.opt.preservenativescrolling && a.checkarea + 600 < c && (a.nativescrollingarea = a.isScrollable(b), d = !0);a.checkarea = c;if (a.nativescrollingarea) return !0;if (b = t(b, !1, d)) a.checkarea = 0;return b;
	      }
	    };this.onmousewheelhr = function (b) {
	      if (!a.wheelprevented) {
	        if (a.railslocked || !a.railh.scrollable) return !0;if (a.rail.drag) return a.cancelEvent(b);
	        var c = +new Date(),
	            d = !1;a.opt.preservenativescrolling && a.checkarea + 600 < c && (a.nativescrollingarea = a.isScrollable(b), d = !0);a.checkarea = c;return a.nativescrollingarea ? !0 : a.railslocked ? a.cancelEvent(b) : t(b, !0, d);
	      }
	    };this.stop = function () {
	      a.cancelScroll();a.scrollmon && a.scrollmon.stop();a.cursorfreezed = !1;a.scroll.y = Math.round(a.getScrollTop() * (1 / a.scrollratio.y));a.noticeCursor();return a;
	    };this.getTransitionSpeed = function (b) {
	      b = Math.min(Math.round(10 * a.opt.scrollspeed), Math.round(b / 20 * a.opt.scrollspeed));return 20 < b ? b : 0;
	    };a.opt.smoothscroll ? a.ishwscroll && e.hastransition && a.opt.usetransition && a.opt.smoothscroll ? (this.prepareTransition = function (b, c) {
	      var d = c ? 20 < b ? b : 0 : a.getTransitionSpeed(b),
	          f = d ? e.prefixstyle + "transform " + d + "ms ease-out" : "";a.lasttransitionstyle && a.lasttransitionstyle == f || (a.lasttransitionstyle = f, a.doc.css(e.transitionstyle, f));return d;
	    }, this.doScrollLeft = function (b, c) {
	      var d = a.scrollrunning ? a.newscrolly : a.getScrollTop();a.doScrollPos(b, d, c);
	    }, this.doScrollTop = function (b, c) {
	      var d = a.scrollrunning ? a.newscrollx : a.getScrollLeft();a.doScrollPos(d, b, c);
	    }, this.doScrollPos = function (b, c, d) {
	      var f = a.getScrollTop(),
	          k = a.getScrollLeft();(0 > (a.newscrolly - f) * (c - f) || 0 > (a.newscrollx - k) * (b - k)) && a.cancelScroll();0 == a.opt.bouncescroll && (0 > c ? c = 0 : c > a.page.maxh && (c = a.page.maxh), 0 > b ? b = 0 : b > a.page.maxw && (b = a.page.maxw));if (a.scrollrunning && b == a.newscrollx && c == a.newscrolly) return !1;a.newscrolly = c;a.newscrollx = b;a.newscrollspeed = d || !1;if (a.timer) return !1;a.timer = setTimeout(function () {
	        var d = a.getScrollTop(),
	            f = a.getScrollLeft(),
	            k = Math.round(Math.sqrt(Math.pow(b - f, 2) + Math.pow(c - d, 2))),
	            k = a.newscrollspeed && 1 < a.newscrollspeed ? a.newscrollspeed : a.getTransitionSpeed(k);a.newscrollspeed && 1 >= a.newscrollspeed && (k *= a.newscrollspeed);a.prepareTransition(k, !0);a.timerscroll && a.timerscroll.tm && clearInterval(a.timerscroll.tm);0 < k && (!a.scrollrunning && a.onscrollstart && a.onscrollstart.call(a, { type: "scrollstart", current: { x: f, y: d }, request: { x: b, y: c }, end: { x: a.newscrollx, y: a.newscrolly }, speed: k }), e.transitionend ? a.scrollendtrapped || (a.scrollendtrapped = !0, a.bind(a.doc, e.transitionend, a.onScrollTransitionEnd, !1)) : (a.scrollendtrapped && clearTimeout(a.scrollendtrapped), a.scrollendtrapped = setTimeout(a.onScrollTransitionEnd, k)), a.timerscroll = { bz: new D(d, a.newscrolly, k, 0, 0, .58, 1), bh: new D(f, a.newscrollx, k, 0, 0, .58, 1) }, a.cursorfreezed || (a.timerscroll.tm = setInterval(function () {
	          a.showCursor(a.getScrollTop(), a.getScrollLeft());
	        }, 60)));a.synched("doScroll-set", function () {
	          a.timer = 0;a.scrollendtrapped && (a.scrollrunning = !0);a.setScrollTop(a.newscrolly);a.setScrollLeft(a.newscrollx);
	          if (!a.scrollendtrapped) a.onScrollTransitionEnd();
	        });
	      }, 50);
	    }, this.cancelScroll = function () {
	      if (!a.scrollendtrapped) return !0;var b = a.getScrollTop(),
	          c = a.getScrollLeft();a.scrollrunning = !1;e.transitionend || clearTimeout(e.transitionend);a.scrollendtrapped = !1;a._unbind(a.doc[0], e.transitionend, a.onScrollTransitionEnd);a.prepareTransition(0);a.setScrollTop(b);a.railh && a.setScrollLeft(c);a.timerscroll && a.timerscroll.tm && clearInterval(a.timerscroll.tm);a.timerscroll = !1;a.cursorfreezed = !1;a.showCursor(b, c);return a;
	    }, this.onScrollTransitionEnd = function () {
	      a.scrollendtrapped && a._unbind(a.doc[0], e.transitionend, a.onScrollTransitionEnd);a.scrollendtrapped = !1;a.prepareTransition(0);a.timerscroll && a.timerscroll.tm && clearInterval(a.timerscroll.tm);a.timerscroll = !1;var b = a.getScrollTop(),
	          c = a.getScrollLeft();a.setScrollTop(b);a.railh && a.setScrollLeft(c);a.noticeCursor(!1, b, c);a.cursorfreezed = !1;0 > b ? b = 0 : b > a.page.maxh && (b = a.page.maxh);0 > c ? c = 0 : c > a.page.maxw && (c = a.page.maxw);if (b != a.newscrolly || c != a.newscrollx) return a.doScrollPos(c, b, a.opt.snapbackspeed);a.onscrollend && a.scrollrunning && a.triggerScrollEnd();a.scrollrunning = !1;
	    }) : (this.doScrollLeft = function (b, c) {
	      var d = a.scrollrunning ? a.newscrolly : a.getScrollTop();a.doScrollPos(b, d, c);
	    }, this.doScrollTop = function (b, c) {
	      var d = a.scrollrunning ? a.newscrollx : a.getScrollLeft();a.doScrollPos(d, b, c);
	    }, this.doScrollPos = function (b, c, d) {
	      function e() {
	        if (a.cancelAnimationFrame) return !0;a.scrollrunning = !0;if (p = 1 - p) return a.timer = v(e) || 1;var b = 0,
	            c,
	            d,
	            f = d = a.getScrollTop();if (a.dst.ay) {
	          f = a.bzscroll ? a.dst.py + a.bzscroll.getNow() * a.dst.ay : a.newscrolly;c = f - d;if (0 > c && f < a.newscrolly || 0 < c && f > a.newscrolly) f = a.newscrolly;a.setScrollTop(f);f == a.newscrolly && (b = 1);
	        } else b = 1;d = c = a.getScrollLeft();if (a.dst.ax) {
	          d = a.bzscroll ? a.dst.px + a.bzscroll.getNow() * a.dst.ax : a.newscrollx;c = d - c;if (0 > c && d < a.newscrollx || 0 < c && d > a.newscrollx) d = a.newscrollx;a.setScrollLeft(d);d == a.newscrollx && (b += 1);
	        } else b += 1;2 == b ? (a.timer = 0, a.cursorfreezed = !1, a.bzscroll = !1, a.scrollrunning = !1, 0 > f ? f = 0 : f > a.page.maxh && (f = Math.max(0, a.page.maxh)), 0 > d ? d = 0 : d > a.page.maxw && (d = a.page.maxw), d != a.newscrollx || f != a.newscrolly ? a.doScrollPos(d, f) : a.onscrollend && a.triggerScrollEnd()) : a.timer = v(e) || 1;
	      }c = void 0 === c || !1 === c ? a.getScrollTop(!0) : c;if (a.timer && a.newscrolly == c && a.newscrollx == b) return !0;a.timer && w(a.timer);a.timer = 0;var f = a.getScrollTop(),
	          k = a.getScrollLeft();(0 > (a.newscrolly - f) * (c - f) || 0 > (a.newscrollx - k) * (b - k)) && a.cancelScroll();a.newscrolly = c;a.newscrollx = b;a.bouncescroll && a.rail.visibility || (0 > a.newscrolly ? a.newscrolly = 0 : a.newscrolly > a.page.maxh && (a.newscrolly = a.page.maxh));a.bouncescroll && a.railh.visibility || (0 > a.newscrollx ? a.newscrollx = 0 : a.newscrollx > a.page.maxw && (a.newscrollx = a.page.maxw));a.dst = {};a.dst.x = b - k;a.dst.y = c - f;a.dst.px = k;a.dst.py = f;var h = Math.round(Math.sqrt(Math.pow(a.dst.x, 2) + Math.pow(a.dst.y, 2)));a.dst.ax = a.dst.x / h;a.dst.ay = a.dst.y / h;var l = 0,
	          n = h;0 == a.dst.x ? (l = f, n = c, a.dst.ay = 1, a.dst.py = 0) : 0 == a.dst.y && (l = k, n = b, a.dst.ax = 1, a.dst.px = 0);h = a.getTransitionSpeed(h);d && 1 >= d && (h *= d);a.bzscroll = 0 < h ? a.bzscroll ? a.bzscroll.update(n, h) : new D(l, n, h, 0, 1, 0, 1) : !1;if (!a.timer) {
	        (f == a.page.maxh && c >= a.page.maxh || k == a.page.maxw && b >= a.page.maxw) && a.checkContentSize();var p = 1;a.cancelAnimationFrame = !1;a.timer = 1;a.onscrollstart && !a.scrollrunning && a.onscrollstart.call(a, { type: "scrollstart", current: { x: k, y: f }, request: { x: b, y: c }, end: { x: a.newscrollx, y: a.newscrolly }, speed: h });e();(f == a.page.maxh && c >= f || k == a.page.maxw && b >= k) && a.checkContentSize();a.noticeCursor();
	      }
	    }, this.cancelScroll = function () {
	      a.timer && w(a.timer);a.timer = 0;a.bzscroll = !1;a.scrollrunning = !1;return a;
	    }) : (this.doScrollLeft = function (b, c) {
	      var d = a.getScrollTop();a.doScrollPos(b, d, c);
	    }, this.doScrollTop = function (b, c) {
	      var d = a.getScrollLeft();a.doScrollPos(d, b, c);
	    }, this.doScrollPos = function (b, c, d) {
	      var e = b > a.page.maxw ? a.page.maxw : b;0 > e && (e = 0);var f = c > a.page.maxh ? a.page.maxh : c;0 > f && (f = 0);a.synched("scroll", function () {
	        a.setScrollTop(f);a.setScrollLeft(e);
	      });
	    }, this.cancelScroll = function () {});this.doScrollBy = function (b, c) {
	      var d = 0,
	          d = c ? Math.floor((a.scroll.y - b) * a.scrollratio.y) : (a.timer ? a.newscrolly : a.getScrollTop(!0)) - b;if (a.bouncescroll) {
	        var e = Math.round(a.view.h / 2);d < -e ? d = -e : d > a.page.maxh + e && (d = a.page.maxh + e);
	      }a.cursorfreezed = !1;e = a.getScrollTop(!0);if (0 > d && 0 >= e) return a.noticeCursor();if (d > a.page.maxh && e >= a.page.maxh) return a.checkContentSize(), a.noticeCursor();a.doScrollTop(d);
	    };this.doScrollLeftBy = function (b, c) {
	      var d = 0,
	          d = c ? Math.floor((a.scroll.x - b) * a.scrollratio.x) : (a.timer ? a.newscrollx : a.getScrollLeft(!0)) - b;if (a.bouncescroll) {
	        var e = Math.round(a.view.w / 2);d < -e ? d = -e : d > a.page.maxw + e && (d = a.page.maxw + e);
	      }a.cursorfreezed = !1;e = a.getScrollLeft(!0);if (0 > d && 0 >= e || d > a.page.maxw && e >= a.page.maxw) return a.noticeCursor();a.doScrollLeft(d);
	    };this.doScrollTo = function (b, c) {
	      a.cursorfreezed = !1;a.doScrollTop(b);
	    };this.checkContentSize = function () {
	      var b = a.getContentSize();b.h == a.page.h && b.w == a.page.w || a.resize(!1, b);
	    };a.onscroll = function (b) {
	      a.rail.drag || a.cursorfreezed || a.synched("scroll", function () {
	        a.scroll.y = Math.round(a.getScrollTop() * (1 / a.scrollratio.y));a.railh && (a.scroll.x = Math.round(a.getScrollLeft() * (1 / a.scrollratio.x)));
	        a.noticeCursor();
	      });
	    };a.bind(a.docscroll, "scroll", a.onscroll);this.doZoomIn = function (b) {
	      if (!a.zoomactive) {
	        a.zoomactive = !0;a.zoomrestore = { style: {} };var c = "position top left zIndex backgroundColor marginTop marginBottom marginLeft marginRight".split(" "),
	            d = a.win[0].style,
	            k;for (k in c) {
	          var h = c[k];a.zoomrestore.style[h] = void 0 !== d[h] ? d[h] : "";
	        }a.zoomrestore.style.width = a.win.css("width");a.zoomrestore.style.height = a.win.css("height");a.zoomrestore.padding = { w: a.win.outerWidth() - a.win.width(), h: a.win.outerHeight() - a.win.height() };e.isios4 && (a.zoomrestore.scrollTop = f(window).scrollTop(), f(window).scrollTop(0));a.win.css({ position: e.isios4 ? "absolute" : "fixed", top: 0, left: 0, zIndex: A + 100, margin: 0 });c = a.win.css("backgroundColor");("" == c || /transparent|rgba\(0, 0, 0, 0\)|rgba\(0,0,0,0\)/.test(c)) && a.win.css("backgroundColor", "#fff");a.rail.css({ zIndex: A + 101 });a.zoom.css({ zIndex: A + 102 });a.zoom.css("backgroundPosition", "0px -18px");a.resizeZoom();a.onzoomin && a.onzoomin.call(a);return a.cancelEvent(b);
	      }
	    };this.doZoomOut = function (b) {
	      if (a.zoomactive) return a.zoomactive = !1, a.win.css("margin", ""), a.win.css(a.zoomrestore.style), e.isios4 && f(window).scrollTop(a.zoomrestore.scrollTop), a.rail.css({ "z-index": a.zindex }), a.zoom.css({ "z-index": a.zindex }), a.zoomrestore = !1, a.zoom.css("backgroundPosition", "0px 0px"), a.onResize(), a.onzoomout && a.onzoomout.call(a), a.cancelEvent(b);
	    };this.doZoom = function (b) {
	      return a.zoomactive ? a.doZoomOut(b) : a.doZoomIn(b);
	    };this.resizeZoom = function () {
	      if (a.zoomactive) {
	        var b = a.getScrollTop();a.win.css({ width: f(window).width() - a.zoomrestore.padding.w + "px", height: f(window).height() - a.zoomrestore.padding.h + "px" });a.onResize();a.setScrollTop(Math.min(a.page.maxh, b));
	      }
	    };this.init();f.nicescroll.push(this);
	  },
	      M = function M(f) {
	    var c = this;this.nc = f;this.steptime = this.lasttime = this.speedy = this.speedx = this.lasty = this.lastx = 0;this.snapy = this.snapx = !1;this.demuly = this.demulx = 0;this.lastscrolly = this.lastscrollx = -1;this.timer = this.chky = this.chkx = 0;this.time = function () {
	      return +new Date();
	    };this.reset = function (f, h) {
	      c.stop();var d = c.time();c.steptime = 0;c.lasttime = d;c.speedx = 0;c.speedy = 0;c.lastx = f;c.lasty = h;c.lastscrollx = -1;c.lastscrolly = -1;
	    };this.update = function (f, h) {
	      var d = c.time();c.steptime = d - c.lasttime;c.lasttime = d;var d = h - c.lasty,
	          q = f - c.lastx,
	          t = c.nc.getScrollTop(),
	          a = c.nc.getScrollLeft(),
	          t = t + d,
	          a = a + q;c.snapx = 0 > a || a > c.nc.page.maxw;c.snapy = 0 > t || t > c.nc.page.maxh;c.speedx = q;c.speedy = d;c.lastx = f;c.lasty = h;
	    };this.stop = function () {
	      c.nc.unsynched("domomentum2d");c.timer && clearTimeout(c.timer);c.timer = 0;c.lastscrollx = -1;c.lastscrolly = -1;
	    };this.doSnapy = function (f, h) {
	      var d = !1;0 > h ? (h = 0, d = !0) : h > c.nc.page.maxh && (h = c.nc.page.maxh, d = !0);0 > f ? (f = 0, d = !0) : f > c.nc.page.maxw && (f = c.nc.page.maxw, d = !0);d ? c.nc.doScrollPos(f, h, c.nc.opt.snapbackspeed) : c.nc.triggerScrollEnd();
	    };this.doMomentum = function (f) {
	      var h = c.time(),
	          d = f ? h + f : c.lasttime;f = c.nc.getScrollLeft();var q = c.nc.getScrollTop(),
	          t = c.nc.page.maxh,
	          a = c.nc.page.maxw;c.speedx = 0 < a ? Math.min(60, c.speedx) : 0;c.speedy = 0 < t ? Math.min(60, c.speedy) : 0;d = d && 60 >= h - d;if (0 > q || q > t || 0 > f || f > a) d = !1;f = c.speedx && d ? c.speedx : !1;if (c.speedy && d && c.speedy || f) {
	        var r = Math.max(16, c.steptime);50 < r && (f = r / 50, c.speedx *= f, c.speedy *= f, r = 50);c.demulxy = 0;c.lastscrollx = c.nc.getScrollLeft();c.chkx = c.lastscrollx;c.lastscrolly = c.nc.getScrollTop();c.chky = c.lastscrolly;var p = c.lastscrollx,
	            e = c.lastscrolly,
	            v = function v() {
	          var d = 600 < c.time() - h ? .04 : .02;c.speedx && (p = Math.floor(c.lastscrollx - c.speedx * (1 - c.demulxy)), c.lastscrollx = p, 0 > p || p > a) && (d = .1);c.speedy && (e = Math.floor(c.lastscrolly - c.speedy * (1 - c.demulxy)), c.lastscrolly = e, 0 > e || e > t) && (d = .1);c.demulxy = Math.min(1, c.demulxy + d);c.nc.synched("domomentum2d", function () {
	            c.speedx && (c.nc.getScrollLeft(), c.chkx = p, c.nc.setScrollLeft(p));c.speedy && (c.nc.getScrollTop(), c.chky = e, c.nc.setScrollTop(e));c.timer || (c.nc.hideCursor(), c.doSnapy(p, e));
	          });1 > c.demulxy ? c.timer = setTimeout(v, r) : (c.stop(), c.nc.hideCursor(), c.doSnapy(p, e));
	        };v();
	      } else c.doSnapy(c.nc.getScrollLeft(), c.nc.getScrollTop());
	    };
	  },
	      y = f.fn.scrollTop;f.cssHooks.pageYOffset = { get: function get(h, c, k) {
	      return (c = f.data(h, "__nicescroll") || !1) && c.ishwscroll ? c.getScrollTop() : y.call(h);
	    }, set: function set(h, c) {
	      var k = f.data(h, "__nicescroll") || !1;k && k.ishwscroll ? k.setScrollTop(parseInt(c)) : y.call(h, c);return this;
	    } };f.fn.scrollTop = function (h) {
	    if (void 0 === h) {
	      var c = this[0] ? f.data(this[0], "__nicescroll") || !1 : !1;return c && c.ishwscroll ? c.getScrollTop() : y.call(this);
	    }return this.each(function () {
	      var c = f.data(this, "__nicescroll") || !1;c && c.ishwscroll ? c.setScrollTop(parseInt(h)) : y.call(f(this), h);
	    });
	  };var z = f.fn.scrollLeft;f.cssHooks.pageXOffset = { get: function get(h, c, k) {
	      return (c = f.data(h, "__nicescroll") || !1) && c.ishwscroll ? c.getScrollLeft() : z.call(h);
	    }, set: function set(h, c) {
	      var k = f.data(h, "__nicescroll") || !1;k && k.ishwscroll ? k.setScrollLeft(parseInt(c)) : z.call(h, c);return this;
	    } };f.fn.scrollLeft = function (h) {
	    if (void 0 === h) {
	      var c = this[0] ? f.data(this[0], "__nicescroll") || !1 : !1;return c && c.ishwscroll ? c.getScrollLeft() : z.call(this);
	    }return this.each(function () {
	      var c = f.data(this, "__nicescroll") || !1;c && c.ishwscroll ? c.setScrollLeft(parseInt(h)) : z.call(f(this), h);
	    });
	  };var E = function E(h) {
	    var c = this;this.length = 0;this.name = "nicescrollarray";
	    this.each = function (d) {
	      f.each(c, d);return c;
	    };this.push = function (d) {
	      c[c.length] = d;c.length++;
	    };this.eq = function (d) {
	      return c[d];
	    };if (h) for (var k = 0; k < h.length; k++) {
	      var l = f.data(h[k], "__nicescroll") || !1;l && (this[this.length] = l, this.length++);
	    }return this;
	  };(function (f, c, k) {
	    for (var l = 0; l < c.length; l++) {
	      k(f, c[l]);
	    }
	  })(E.prototype, "show hide toggle onResize resize remove stop doScrollPos".split(" "), function (f, c) {
	    f[c] = function () {
	      var f = arguments;return this.each(function () {
	        this[c].apply(this, f);
	      });
	    };
	  });f.fn.getNiceScroll = function (h) {
	    return void 0 === h ? new E(this) : this[h] && f.data(this[h], "__nicescroll") || !1;
	  };f.expr[":"].nicescroll = function (h) {
	    return void 0 !== f.data(h, "__nicescroll");
	  };f.fn.niceScroll = function (h, c) {
	    void 0 !== c || "object" != (typeof h === "undefined" ? "undefined" : _typeof(h)) || "jquery" in h || (c = h, h = !1);c = f.extend({}, c);var k = new E();void 0 === c && (c = {});h && (c.doc = f(h), c.win = f(this));var l = !("doc" in c);l || "win" in c || (c.win = f(this));this.each(function () {
	      var d = f(this).data("__nicescroll") || !1;d || (c.doc = l ? f(this) : c.doc, d = new S(c, f(this)), f(this).data("__nicescroll", d));k.push(d);
	    });return 1 == k.length ? k[0] : k;
	  };window.NiceScroll = { getjQuery: function getjQuery() {
	      return f;
	    } };f.nicescroll || (f.nicescroll = new E(), f.nicescroll.options = K);
	});

/***/ },

/***/ 219:
/*!********************!*\
  !*** external "$" ***!
  \********************/
/***/ function(module, exports) {

	module.exports = $;

/***/ },

/***/ 220:
/*!************************************************!*\
  !*** ./src/components/nicescroll/directive.js ***!
  \************************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	var _options = __webpack_require__(/*! ./options.js */ 221);

	var _options2 = _interopRequireDefault(_options);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	Vue.directive('nicescroll', {
	  bind: function bind() {
	    var self = this;
	    self.unbind();
	    Vue.nextTick(function () {
	      $(self.el).niceScroll(_options2.default);
	    });
	  },
	  update: function update(val) {},
	  unbind: function unbind() {
	    var self = this;
	    if (self.frag) {
	      self.frag.destroy();
	    }
	  }
	});

/***/ },

/***/ 221:
/*!**********************************************!*\
  !*** ./src/components/nicescroll/options.js ***!
  \**********************************************/
/***/ function(module, exports) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.default = {
	  cursorcolor: '#D2D2D2', // change cursor color in hex
	  cursoropacitymin: 0, // change opacity when cursor is inactive (scrollabar 'hidden' state), range from 1 to 0
	  cursoropacitymax: 1, // change opacity when cursor is active (scrollabar 'visible' state), range from 1 to 0
	  cursorwidth: '12px', // cursor width in pixel (you can also write '5px')
	  cursorborder: '4px solid rgba(255,255,255,0)', // css definition for cursor border
	  cursorborderradius: '12px', // border radius in pixel for cursor
	  zindex: 'auto', // change z-index for scrollbar div
	  scrollspeed: 60, // scrolling speed
	  mousescrollstep: 40, // scrolling speed with mouse wheel (pixel)
	  touchbehavior: false, // enable cursor-drag scrolling like touch devices in desktop computer
	  hwacceleration: true, // use hardware accelerated scroll when supported
	  /**
	   * 由于不兼容该css属性，同时nicescroll远程加载google的cur，因此屏蔽该功能
	   * 
	   * http://www.zhangxinxu.com/wordpress/2014/12/css3-cursor-zoom-in-zoom-out-grab-grabbing/
	   */
	  grabcursorenabled: false, // (only when touchbehavior=true) display 'grab' icon
	  autohidemode: 'leave', // how hide the scrollbar works, possible values: 
	  background: '', // change css for rail background
	  iframeautoresize: true, // autoresize iframe on load event
	  cursorminheight: 32, // set the minimum cursor height (pixel)
	  preservenativescrolling: true, // you can scroll native scrollable areas with mouse, bubbling mouse wheel event
	  railoffset: false, // you can add offset top/left for rail position
	  bouncescroll: false, // (only hw accell) enable scroll bouncing at the end of content as mobile-like 
	  spacebarenabled: true, // enable page down scrolling when space bar has pressed
	  railpadding: { top: 0, right: 0, left: 0, bottom: 0 }, // set padding for rail bar
	  disableoutline: true, // for chrome browser, disable outline (orange highlight) when selecting a div with nicescroll
	  horizrailenabled: true, // nicescroll can manage horizontal scroll
	  enabletranslate3d: true, // nicescroll can use css translate to scroll content
	  enablemouselockapi: true, // can use mouse caption lock API (same issue on object dragging)
	  cursorfixedheight: false, // set fixed height for cursor in pixel
	  hidecursordelay: 400, // set the delay in microseconds to fading out scrollbars
	  directionlockdeadzone: 6, // dead zone in pixels for direction lock activation
	  nativeparentscrolling: true, // detect bottom of content and let parent to scroll, as native scroll does
	  enablescrollonselection: true, // enable auto-scrolling of content when selection text
	  cursordragspeed: 0.3, // speed of selection when dragged with cursor
	  rtlmode: 'auto', // horizontal div scrolling starts at left side
	  //PC词典检测为touch设备的，因此以下为true，否则部分功能不正常
	  cursordragontouch: true, // drag cursor in touch / touchbehavior mode also
	  oneaxismousemode: 'auto', // it permits horizontal scrolling with mousewheel on horizontal only content, if false (vertical-only) mousewheel don't scroll horizontally, if value is auto detects two-axis mouse
	  preventmultitouchscrolling: true, // prevent scrolling on multitouch events
	  disablemutationobserver: false // force MutationObserver disabled

	};

/***/ },

/***/ 222:
/*!***************************************!*\
  !*** ./src/components/event/index.js ***!
  \***************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	__webpack_require__(/*! ./directive.js */ 223);

/***/ },

/***/ 223:
/*!*******************************************!*\
  !*** ./src/components/event/directive.js ***!
  \*******************************************/
/***/ function(module, exports) {

	'use strict';

	Vue.directive('event', {
	  _handler: null,
	  update: function update(handler, old) {
	    var self = this,
	        name = self.descriptor.arg;

	    if (!name) return;

	    var $el = $(self.el);

	    if (old) {
	      $el.off(self._name, self._handler);
	    }
	    self._handler = handler;
	    $el.on(name, function (e) {
	      handler.call(self, e);
	    });
	  },
	  unbind: function unbind() {
	    var self = this;
	    if (self.frag) {
	      self.frag.destroy();
	    }
	  }
	});

/***/ },

/***/ 224:
/*!*********************************************************************!*\
  !*** ./src/entrys/wordbook/dialog/category/components/add/index.js ***!
  \*********************************************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	var _template = __webpack_require__(/*! ./template.html */ 225);

	var _template2 = _interopRequireDefault(_template);

	__webpack_require__(/*! ./index.scss */ 226);

	function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

	var cancel = function cancel(self, type) {
	  self.$emit('cancel', {
	    type: type
	  });
	  self.text = '';
	};

	var config = {
	  props: {
	    text: [String],
	    placeholder: {
	      type: [String],
	      default: '未命名分类'
	    },
	    btnText: {
	      type: [String],
	      default: '确定'
	    }
	  },
	  template: (0, _template2.default)(),
	  methods: {
	    keyup: function keyup(e) {
	      var self = this;
	      switch (e.keyCode) {
	        //esc
	        case 27:
	          cancel(self, 'esc');
	          break;
	        //enter
	        case 13:
	          self.submit();
	          break;
	      }
	    },
	    submit: function submit() {
	      var self = this;
	      if (!self.text) {
	        cancel(self, 'empty');
	        return;
	      }

	      ydk.addWordBookCategory({
	        name: self.text,
	        success: function success(res) {
	          if (res.code == 1000) {
	            self.$emit('success', self.text);
	            self.text = '';
	          }
	        }
	      });
	    }
	  }
	};

	Vue.component('category-add', config);

/***/ },

/***/ 225:
/*!**************************************************************************!*\
  !*** ./src/entrys/wordbook/dialog/category/components/add/template.html ***!
  \**************************************************************************/
/***/ function(module, exports) {

	module.exports = function (obj) {
	obj || (obj = {});
	var __t, __p = '';
	with (obj) {
	__p += '<div class="category-add">\r\n  <input type="text" v-model="text" :placeholder="placeholder" @keyup="keyup" id="js_category_add_input">\r\n  <a href="javascript:;" class="submit" @click="submit">{{btnText}}</a>\r\n</div>';

	}
	return __p
	}

/***/ },

/***/ 226:
/*!***********************************************************************!*\
  !*** ./src/entrys/wordbook/dialog/category/components/add/index.scss ***!
  \***********************************************************************/
/***/ function(module, exports) {

	// removed by extract-text-webpack-plugin

/***/ },

/***/ 228:
/*!*************************************!*\
  !*** ./src/modules/dialog/index.js ***!
  \*************************************/
/***/ function(module, exports, __webpack_require__) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.open = open;
	exports.close = close;
	exports.setSize = setSize;
	exports.alert = alert;
	exports.confirm = confirm;
	exports.autoSize = autoSize;

	var _broadcast = __webpack_require__(/*! modules/broadcast */ 50);

	var broadcaster = _interopRequireWildcard(_broadcast);

	function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

	var win = window,
	    $html = $('html'),
	    $doc = $(document); /**
	                         * 打开对话框（不含头部）
	                         * @param  {Object} params {
	                         *   url : String,
	                         *   width : Number,
	                         *   height : Number
	                         * }
	                         *
	                         * 打开对话框（含头部）
	                         * @param  {Object} params {
	                         *   header : {
	                         *     title : '标题',
	                         *     showClose : true
	                         *   },
	                         *   url : String,
	                         *   width : Number,
	                         *   height : Number
	                         * }
	                         */
	function open(params) {
	  broadcaster.emit('dialog.open', params, win == top ? 'local' : 'top');
	}

	/**
	 * 关闭对话框
	 */
	function close() {
	  broadcaster.emit('dialog.close', null, win == top ? 'local' : 'top');
	}

	/**
	 * 设置对话框宽高
	 * @param {Object} params {
	 *   width : Number,
	 *   height : Number
	 * }
	 */
	function setSize(params) {
	  broadcaster.emit('dialog.setSize', params, window == top ? null : 'top');
	}

	/**
	 * alert
	 * @param  {Object} params {
	 *  msg : String                      
	 * }
	 */
	function alert(params) {
	  var callbackId = 'alert_' + _.now(),
	      success = params.success,
	      cancel = params.cancel,
	      complete = params.complete;

	  if (typeof params == 'string') {
	    params = {
	      msg: params
	    };
	  }

	  params.success = undefined;
	  params.cancel = undefined;
	  params.complete = undefined;
	  params.callbackId = callbackId;

	  broadcaster.emit('dialog.alert', params, 'top');
	  broadcaster.one(callbackId, function (res) {
	    if (res.type == 'success') {
	      success && success();
	      complete && complete();
	    } else {
	      cancel && cancel();
	      complete && complete();
	    }
	  });
	}

	/**
	 * confirm
	 * @param  {Object} params {
	 *  msg : String                      
	 * }
	 */
	function confirm(params) {
	  var callbackId = 'confirm_' + _.now(),
	      success = params.success,
	      cancel = params.cancel,
	      complete = params.complete;

	  if (typeof params == 'string') {
	    params = {
	      msg: params
	    };
	  }

	  params.success = undefined;
	  params.cancel = undefined;
	  params.complete = undefined;
	  params.callbackId = callbackId;

	  broadcaster.emit('dialog.confirm', params, 'top');
	  broadcaster.one(callbackId, function (res) {
	    if (res.type == 'success') {
	      success && success();
	      complete && complete();
	    } else {
	      cancel && cancel();
	      complete && complete();
	    }
	  });
	  top.focus();
	}

	/**
	 * 自动设置窗口大小
	 *
	 * 要兼顾以下情况：
	 * 1、首次展示对话框（此时size:0,0）
	 * 2、已经打开了对话框，调整宽高（此时size不为0,0）
	 */
	function autoSize() {
	  Vue.nextTick(function () {
	    setSize({
	      width: $doc.width(), //支持case 1,2
	      height: $html.height() //支持case 2
	    });
	  });
	}

/***/ },

/***/ 229:
/*!*******************************************!*\
  !*** ./src/entrys/editword/template.html ***!
  \*******************************************/
/***/ function(module, exports) {

	module.exports = function (obj) {
	obj || (obj = {});
	var __t, __p = '';
	with (obj) {
	__p += '<!-- 编辑单词 -->\r\n<div class="wb-alert wb-word-opt">\r\n	<ul>\r\n	<li>\r\n		<a href="javascript:;" class="btn-remove btn" @click="removeFromWordbook">从单词本中删除</a>\r\n	</li>\r\n	<li class="category">\r\n			<label>分类：<div class="sort-select ellipsis" pannel="#js_category_add"><span>{{categoryText || \'未分类\'}}</span><span class="icon icon-down"></span></div></label>\r\n			<div class="pannel-add hide" id="js_category_add" v-event:close="onPannelClose" v-nicescroll>\r\n				<ajax \r\n				  :data-source="source.init.provider" \r\n				  :filter="source.init.filter"\r\n				  v-ref:ajax1\r\n				>\r\n				<ul class="wb-sub-nav">\r\n          <li><a href="javascript:;" class="add" @click="toggleAdd">创建分类</a></li>\r\n          <li v-show="isAdd" class="add"><category-add @success="onCategoryAdded" @cancel="onCategoryCancel"></category-add></li>\r\n          <li v-for="item in $ajax.data" class="item"><a href="javascript:;" pannel-close class="cat ellipsis" @click="selectSort(item.name)" :selectName="item.name">{{item.name}}</a></li>\r\n        </ul>\r\n        </ajax>\r\n			</div>\r\n		</li>\r\n		<li>\r\n			<label>单词：<input type="text" v-model="editword" class="g-input-text" readonly="readonly"></label>\r\n		</li>\r\n		<li>\r\n			<label>音标：<input type="text" v-model="phonetic" class="g-input-text" maxlength="63"></label>\r\n		</li>\r\n		<li>\r\n			<label>解析：<textarea type="textarea" v-model="trans" class="g-textarea"></textarea></label>\r\n		</li>\r\n	</ul>\r\n	<div class="wb-btn clear-fix">\r\n			<a href="javascript:;" class="g-btn-normal btn cancel" @click="closeWin">取消</a>\r\n			<a href="javascript:;" class="g-btn-red btn confirm" @click="editComfirm">确定</a>\r\n	</div>\r\n</div>';

	}
	return __p
	}

/***/ },

/***/ 230:
/*!************************************!*\
  !*** ./src/entrys/editword/api.js ***!
  \************************************/
/***/ function(module, exports) {

	"use strict";

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});

	exports.default = function (params) {
	  ydk.queryWordBookCategory(params);
	};

/***/ },

/***/ 231:
/*!***************************************!*\
  !*** ./src/entrys/editword/filter.js ***!
  \***************************************/
/***/ function(module, exports) {

	"use strict";

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	var filter = function filter(res) {
	  res.data = res.data || [];
	  return res;
	};

	exports.default = filter;

/***/ },

/***/ 232:
/*!****************************************!*\
  !*** ./src/entrys/editword/index.scss ***!
  \****************************************/
/***/ function(module, exports) {

	// removed by extract-text-webpack-plugin

/***/ },

/***/ 234:
/*!****************************************!*\
  !*** ./src/entrys/editword/methods.js ***!
  \****************************************/
/***/ function(module, exports) {

	'use strict';

	Object.defineProperty(exports, "__esModule", {
	  value: true
	});
	exports.editComfirm = editComfirm;
	exports.closeWin = closeWin;
	exports.selectSort = selectSort;
	exports.onCategoryCancel = onCategoryCancel;
	exports.onCategoryAdded = onCategoryAdded;
	exports.toggleAdd = toggleAdd;
	exports.onPannelClose = onPannelClose;
	exports.removeFromWordbook = removeFromWordbook;
	function editComfirm() {
	  var self = this;
	  var word = self.editword,
	      lang = self.lang || 'en',
	      trans = self.trans,
	      phonetic = self.phonetic,
	      category = self.categoryText;

	  if (trans.length < 1000 && phonetic.length < 60) {

	    ydk.checkWordBook({
	      data: {
	        word: word,
	        lang: lang
	      },
	      success: function success(res) {
	        var params = {
	          word: word,
	          lang: lang,
	          trans: trans,
	          phonetic: phonetic,
	          category: category
	        };
	        if (res.has) {
	          params.progress = res.data.progress;
	          ydk.updateToWordBook(params);
	        } else {
	          params.plan = self.setting.content.addReview;
	          ydk.addToWordBook(params);
	        }
	      }
	    });

	    ydk.toast({
	      msg: '已保存',
	      ext: {
	        type: 'success'
	      }
	    });
	    setTimeout(function () {
	      ydk.closeWin();
	    }, 1500);
	  } else {
	    if (trans.length > 1000) {
	      ydk.toast({
	        msg: '释义文字长度不能大于1000',
	        ext: {
	          type: 'warn'
	        }
	      });
	    }
	    if (phonetic.length > 60) {
	      ydk.toast({
	        msg: '发音字符长度不能大于60',
	        ext: {
	          type: 'warn'
	        }
	      });
	    }
	  }
	}

	/**
	 * 关闭对话框
	 */
	function closeWin() {
	  ydk.closeWin();
	}

	function selectSort(params) {
	  var self = this;
	  self.isAdd = false;
	  self.categoryText = params;
	}

	/**
	 * 分类添加取消事件
	 */
	function onCategoryCancel(status) {
	  var self = this;
	  self.isAdd = false;
	};

	/**
	 * 分类添加完成事件
	 */
	function onCategoryAdded(name) {
	  var self = this;
	  self.isAdd = false;
	  self.$refs.ajax1.$ajaxData.data.splice(0, 0, {
	    name: name
	  });
	};

	function toggleAdd() {
	  var self = this;
	  self.isAdd = !self.isAdd;
	}

	function onPannelClose() {
	  var self = this;
	  self.isAdd = false;
	}

	function removeFromWordbook() {
	  var self = this;
	  ydk.removeFromWordBook({
	    data: [{
	      word: self.editword,
	      lang: self.lang
	    }]
	  });
	  ydk.toast({
	    msg: '已从单词本删除',
	    ext: {
	      type: 'success'
	    }
	  });
	  setTimeout(function () {
	    ydk.closeWin();
	  }, 1500);
	}

/***/ }

/******/ });