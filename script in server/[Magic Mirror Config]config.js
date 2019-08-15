/* Magic Mirror Config Sample
 *
 * By Michael Teeuw http://michaelteeuw.nl
 * MIT Licensed.
 *
 * For more information how you can configurate this file
 * See https://github.com/MichMich/MagicMirror#configuration
 *
 */

var config = {
	address: "", // Address to listen on, can be:
	                      // - "localhost", "127.0.0.1", "::1" to listen on loopback interface
	                      // - another specific IPv4/6 to listen on a specific interface
	                      // - "", "0.0.0.0", "::" to listen on any interface
	                      // Default, when address config is left out, is "localhost"
	port: 8080,
	ipWhitelist: ["127.0.0.1", "::ffff:127.0.0.1", "::1", "192.168.123.1/24"], // Set [] to allow all IP addresses
	                                                       // or add a specific IPv4 of 192.168.1.5 :
	                                                       // ["127.0.0.1", "::ffff:127.0.0.1", "::1", "::ffff:192.168.1.5"],
	                                                       // or IPv4 range of 192.168.3.0 --> 192.168.3.15 use CIDR format :
	                                                       // ["127.0.0.1", "::ffff:127.0.0.1", "::1", "::ffff:192.168.3.0/28"],

	language: "zh-cn",
	timeFormat: 12,
	units: "metric",

	modules: [
		{
			module: 'MMM-Remote-Control',		//https://github.com/Jopyth/MMM-Remote-Control
			// uncomment the following line to show the URL of the remote control on the mirror
			// , position: 'bottom_left'
			// you can hide this module afterwards from the remote control itself
			config: {
			    	apiKey: 'b6f5bb1f5f9c45a896d49959370c42a5',
				customCommand: {
					monitorOnCommand: 'vcgencmd display_power 1',
					monitorOffCommand: 'vcgencmd display_power 0',
					monitorStatusCommand: 'if [ `vcgencmd display_power` = "display_power=1" ]; then echo true; else echo false; fi'
				}
			}
	    	},
		{
		       	module: "MMM-Wallpaper",		//https://github.com/kolbyjack/MMM-Wallpaper
			position: "fullscreen_below",
			config: { // See "Configuration options" for more information.
				source: "bing",
				slideInterval: 60 * 1000, // Change slides every minute
				filter: "grayscale(0) brightness(0.4)",
				crossfade: true
				}
		},
		{
			module: "alert",
		},
		{
			module: "updatenotification",
			position: "top_bar",
			disabled: true
		},
		{
			module: "clock",
			position: "top_left"
		},
		{
			module: "calendar",
			header: "CHINA Holidays",
			position: "top_left",
			config: {
				timeFormat: "absolute",
				colored: true,
				calendars: [
					{
						symbol: "calendar-check",
						url: "webcal://www.calendarlabs.com/ical-calendar/ics/40/China_Holidays.ics",
						maximumNumberOfDays: 30,
						color: "#8FFFAD"
					},
				]
			}
		},
		{
		    module: "MMM-WeeklySchedule",
		    position: "top_left",
		    header: "今天",
		    config: {
			schedule: {
			    timeslots: [ "7:50", "9:40", "2:00", "15:45", "18:30" ],
			    lessons: {
				mon: [ "计算机通信与网络", "UML系统分析与设计", "嵌入式系统与开发", "" ],  
				tue: [ "计算机组成与结构", "软件测试", "网络信息安全", "", "" ],
				wed: [ "", "数据库系统", "", "计算机通信与网络", "大学物理" ],
				thu: [ "", "", "[双周]嵌入式系统与开发", "软件测试", "" ],
				fri: [ "计算机组成与结构", "", "[双周]网络信息安全", "数据库系统", "" ],
				// no entries for saturday
				//sun: [ "", "", "" ]   // short day on sundays
			    }
			},
			updateInterval: 1 * 60 * 60 * 1000, // every hour
			showNextDayAfter: "20:00"
		    }
		},
		{
			module: "compliments",
			position: "lower_third"
		},
		{
            		module: "MMM-LocalTemperature",		//https://github.com/glitch452/MMM-LocalTemperature
            		position: "top_right", // Only add a position if you want this module to display the data
          		//header: "室内温度",
            		config: {
              		  	sensorPin: 4, // For GPIO 4
                		units: "metric",
				sendTemperature: true,
				sendHumidity: true,
				showTemperature: true,
				showHumidity: true,
				updateInterval: 0.5
            		}
        	},
		{
			module: "currentweather",
			position: "top_right",
			config: {
				location: "Yangzhou",
				locationID: "1787227",  //ID from http://bulk.openweathermap.org/sample/; unzip the gz file and find your city
				appid: "deba5f1c317f3710f3b0af4f8082a336",
				//showIndoorTemperature: true,
				showHumidity: true
			}
		},
		{
			module: "weatherforecast",
			position: "top_right",
			header: "Weather Forecast",
			config: {
				location: "Yangzhou",
                                locationID: "1787227",  //ID from http://bulk.openweathermap.org/sample/; unzip the gz file and find your city
                                appid: "deba5f1c317f3710f3b0af4f8082a336",
                                showRainAmount: true,
                                colored: true
			}
		},
		{
			module: "newsfeed",
			position: "bottom_bar",
			config: {
				feeds: [
					{
						title: "China Daily",
						url: "https://feedx.net/rss/cddual.xml"
					},
					{
						title: "CNN",
						url: "https://feedx.net/rss/cnn.xml"
					},
					{
						title: "一个",
						url: "https://feedx.net/rss/one.xml"
					},
					{
						title: "36kr",
						url: "https://36kr.com/feed"
					}

				],
				showSourceTitle: true,
				showPublishDate: true
			}
		},
		{
			module: 'MMM-Buttons',			//https://github.com/Jopyth/MMM-Buttons
			disabled: true,
		   	config: {
				buttons: [
					{
						pin: 14,
						name: "monitor_control",
						longPress: undefined,
						shortPress: {
				    			notification: "REMOTE_ACTION",
				    			payload: {action: "MONITORTOGGLE"}
						}
			    		}
				],
				bounceTimeout: 100
	    		}
		},
		{
			module: "MMM-Navigate",			//https://github.com/Ax-LED/MMM-Navigate
			header: "Navigation",
			position: "bottom_left",
			config: {
					Alias: [
						'展开全文',
						'滚动',
						'刷新页面',
						'重启mm',
					],
					Action: [
						[{notification:'ARTICLE_MORE_DETAILS',payload:''},{notification:'ARTICLE_LESS_DETAILS',payload:''}],
						[{notification:'ARTICLE_NEXT',payload:''},{notification:'ARTICLE_PREVIOUS',payload:''}],
						{notification: "REMOTE_ACTION", payload: {action: "REFRESH"}},
						{notification: "REMOTE_ACTION", payload: {action: "RESTART"}},
						//[{notification:'PAGE_INCREMENT',payload:''},{notification:'PAGE_DECREMENT',payload:''}],//action array, first press locks menu, after this rotation CW/CCW executes, second press release lock mode
					],
					GPIOPins: [2,3,15]//rotary cw, rotary ccw, rotary press (BCM Numbering)
			}
		},
	]
};

/*************** DO NOT EDIT THE LINE BELOW ***************/
if (typeof module !== "undefined") {module.exports = config;}
