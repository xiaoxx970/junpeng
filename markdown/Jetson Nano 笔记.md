## Fan

https://github.com/xiaoxx970/Jetson_Nano_CPU_PWM

Enabling Fan

```
sudo sh -c 'echo 255 > /sys/devices/pwm-fan/target_pwm'
```
Disabling Fan
```
sudo sh -c 'echo 0 > /sys/devices/pwm-fan/target_pwm'
```
## Other

查看实时负载：

```
tegrastats
```
拷贝文件时显示进度：
```
rsync -avPh www2 www3
```