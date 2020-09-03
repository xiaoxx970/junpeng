## 网页抓取的四种方法

|    库\支持     | Cookies | Javascript |
| :------------: | :-----: | :--------: |
| http.cookiejar |   Yes   |     No     |
|    requests    |   Yes   |     No     |
|  HTMLSession   |   No    |    Yes     |
|    selenium    |   Yes   |    Yes     |

### http.cookiejar

```python
url = "example.com"
###########################################
# https://blog.csdn.net/pipisorry/article/details/47905781
import http.cookiejar
import urllib.request
from bs4 import BeautifulSoup
cookie = http.cookiejar.CookieJar()
handler = urllib.request.HTTPCookieProcessor(cookie)
opener = urllib.request.build_opener(handler)
response = opener.open(url)
html_doc = response.read()
soup = BeautifulSoup(html_doc, 'html.parser')
```

### requests

```python
url = "example.com"
##########################################
import requests
from bs4 import BeautifulSoup
session = requests.Session()
req = session.get(url)
html_doc = req.text
soup = BeautifulSoup(html_doc, 'html.parser')
```

### HTMLSession

https://github.com/psf/requests-html

```python
url = "example.com"
#########################################
from requests_html import HTMLSession
from bs4 import BeautifulSoup
session = HTMLSession()
r = session.get(url)
r.html.render(timeout=30)
html_doc = r.html.html
soup = BeautifulSoup(html_doc, 'html.parser')
```

### selenium

https://www.selenium.dev/documentation/zh-cn/

```python
url = "example.com"
##########################################
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from bs4 import BeautifulSoup
driver = webdriver.Chrome()     # 打开 Chrome 浏览器
driver.implicitly_wait(20) # seconds
driver.get(url)
# https://www.cnblogs.com/hushaojun/p/5985673.html
html_doc = driver.find_element_by_xpath("//*").get_attribute("outerHTML")
soup = BeautifulSoup(html_doc, 'html.parser')
```

## 写入文件

```python
with open(file, 'w') as f:
    for line in content: 
        f.write(line + '\n')
```

## 读取文件

```python
with open(file, encoding='utf-8') as f:
    for line in f.readlines():
        #做事情
```

## 写文件函数

```python
def write_file(filename, content):
    if not os.path.exists('result'):
        os.makedirs('result')
    # 如果内容是字典
    if type(content) is dict or type(content) is defaultdict:
        for name in filename:
            path_name = 'result/{name}.txt'
            with open(path_name.format_map(vars()), 'w') as f:
                f.write('\n'.join(content[name]))
    # 否则内容是数组
    else:
        with open('result/'+filename+'.txt', 'w') as f:
            f.write('\n'.join(content))
```

## 格式化

```python
name = "xiaoxx"
path_name = 'result/{name}.txt'
path_name.format_map(vars())
```

## log

```python
import logging
logging.basicConfig(filename='/root/screen.log', level=logging.INFO, format='%(asctime)s %(message)s', datefmt='[%Y-%m-%d %I:%M:%S %p]')
logging.info('hi')
```
```bash
cat screen.log
[2018-10-08 09:36:36 PM] hi
```


其他用法还有：

```python
logging.debug("debug") 
logging.info("info") 
logging.warning("warning") 
logging.error("error")
logging.critical("critical")
```
参照：https://docs.python.org/2/howto/logging.html

进程管理工具Supervisor:[管理Python](https://www.restran.net/2015/10/04/supervisord-tutorial/)