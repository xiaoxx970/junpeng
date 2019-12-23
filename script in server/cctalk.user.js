document.getElementsByClassName("ocs_overlay_play")[0].click()
var delayInMilliseconds = 1000; //1 second
setTimeout(function() {
    var content = document.getElementsByClassName("swiper-wrapper")[0].getElementsByTagName("video")[0].src;
    var fileName = document.getElementsByClassName("video-title_2DoT")[0].innerText.split("\n")[1]+".mp4";
}, delayInMilliseconds);


window.location.href = document.getElementsByClassName("video-review_3Wq3")[0].href
downloadFile(fileName,content)
name = ""
for (var i=0;i<document.getElementsByClassName("video-review_3Wq3").length;i++){
    name+=document.getElementsByClassName("video-review_3Wq3")[i].innerText.split("\n")[0]+"\n"
    }