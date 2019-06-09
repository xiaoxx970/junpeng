对于ss服务器的多端口管理，官方有它的管道可以做到：
https://github.com/shadowsocks/shadowsocks/wiki/Manage-Multiple-Users 

而我的是单纯的通过改配置文件然后重启来达到同样的效果

# 学到的东西：
  - 把二进制字符串转换成字符串：`bytes.decode(b"string")`
  - 字符串在base64编码之前先用ASCII编码防止出现`'str' does not support the buffer interface`的错误：
    ```python
    ss = ("{}:{}@{}:{}".format(Method, Password, Hostname, port)).encode('ascii')
    ```
   - 在dict中不管是想找内容in keys还是in values，都可以用`[内容] in [字典]`来实现
   - 要在字典里添加之前没有的key，直接赋值就可以了，如果想给不存在的key中的key赋值，那就先给外面的key赋空值：
    ``` python
    conf['port_password'] = {}                                               
    conf['port_password'][port_origin] = password_origin
    ```
   - 删除某个key和对应的值，在前面加del就可以了：
    ``` py
    del conf['server_port']
    ```
