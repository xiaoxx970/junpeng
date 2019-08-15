function copy(content){
    const input = document.createElement('input');
    document.body.appendChild(input);
    input.setAttribute('value', content);
    input.select();
    if (document.execCommand('copy')) {
        document.execCommand('copy');
        console.log('复制成功');
    }
    document.body.removeChild(input);
}
link = document.getElementsByClassName(
    "swiper-slide swiper-slide-active"
    )[0].getElementsByTagName("video")[0].src
copy(link)


/**
 * 获取 blob
 * @param  {String} url 目标文件地址
 * @return {Promise} 
 */
function getBlob(url) {
    return new Promise(resolve => {
        const xhr = new XMLHttpRequest();

        xhr.open('GET', url, true);
        xhr.responseType = 'blob';
        xhr.onload = () => {
            if (xhr.status === 200) {
                resolve(xhr.response);
            }
        };

        xhr.send();
    });
}

/**
 * 保存
 * @param  {Blob} blob     
 * @param  {String} filename 想要保存的文件名称
 */
function saveAs(blob, filename) {
    if (window.navigator.msSaveOrOpenBlob) {
        navigator.msSaveBlob(blob, filename);
    } else {
        const link = document.createElement('a');
        const body = document.querySelector('body');

        link.href = window.URL.createObjectURL(blob);
        link.download = filename;

        // fix Firefox
        link.style.display = 'none';
        body.appendChild(link);
        
        link.click();
        body.removeChild(link);

        window.URL.revokeObjectURL(link.href);
    }
}

/**
 * 下载
 * @param  {String} url 目标文件地址
 * @param  {String} filename 想要保存的文件名称
 */
function download(url, filename) {
    getBlob(url).then(blob => {
        saveAs(blob, filename);
    });
}

function sleep(ms) {
    var unixtime_ms = new Date().getTime();
    while(new Date().getTime() < unixtime_ms + ms) {}
}
for (i in document.getElementsByClassName("swiper-slide"))
{
    var src = document.getElementsByClassName("swiper-slide")[i].getElementsByTagName("img")[0].src
    var name = i + ".jpg"
    download(src,name)
    sleep(100)
}

var out = ""
for (i in document.getElementsByClassName("swiper-slide"))
{
    var src = document.getElementsByClassName("swiper-slide")[i].getElementsByTagName("img")[0].src
    out += src+"\n"
}



