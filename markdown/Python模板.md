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