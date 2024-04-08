# uart-to-mqtt

[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language](https://img.shields.io/badge/language-c++11-red.svg)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/platform-linux-lightgrey.svg)](https://img.shields.io/badge/platform-linux-lightgrey.svg)

[[English]](README.md)

## 介绍
基于 [cpp-tbox](https://gitee.com/cpp-master/cpp-tbox) 框架实现的串口转MQTT通信中间件。

## 起源
当我们需要将一种串口设备通过MQTT连接到网络上，以便在任何有网络的地方都能与之进行交互时，我们需要一种串口与MQTT协议转换中间件。  
它一方面通过串口与设备进行通信，另一方面连接MQTT服务器。将设备通过串口上报的数据以MQTT的消息发送到MQTT服务器上。同时，接收MQTT服务器下发的数据，再通过串口发送给设备。由此达到数据互通的目的。  
由于该需求比较普遍，为此我创建了该开源项目。

## 功能

- 支持通过配置文件，指定MQTT服务器的domain, port, username, passwd, tls等相关参数；
- 支持通过配置文件，指定串口的设置文件、波特率、数据位、校验位、停止位；
- 支持通过终端，开关详细数据日志打印功能。

## 构建
### 步骤一：构建 [cpp-tbox](https://gitee.com/cpp-master/cpp-tbox) 项目  
```
git clone https://gitee.com/cpp-master/cpp-tbox.git
cd cpp-tbox;
STAGING_DIR=$HOME/.tbox make 3rd-party modules RELEASE=1
cd -
```

### 步骤二：构建 uart-to-mqtt 自身
```
git clone https://gitee.com/cpp-master/uart-to-mqtt.git
cd uart-to-mqtt/src;
make
```
构建完成之后，在 src 目录下会生成：uart\_to\_mqtt 可执行文件。

## 运行
执行命令：
```
./uart_to_mqtt -c ../config/default.conf
```
提示：  

- 如果没有权限打开串口文件的问题，则加 sudo 再执行。
- 使用者可以根据需要修改 config/default.conf

## 配置文件
详见 config/default.conf，或阅读源码。

## 反馈途径
- Issue: 任何问题都欢迎在issue里交流
- 微信: hevake\_lee
- QQ群: 738084942 (cpp-tbox 技术交流)

## 鼓励我们
如果你觉得很有用，请您给我更多的鼓励。  
你可以做这些：

- 关注 [cpp-tbox](https://gitee.com/cpp-master/cpp-tbox) 开源项目；
- 给它点亮三连： Star, Watch, Fork；
- 向身边的同事与伙伴推荐，在技术论坛向您的读者推荐；
- 加入上面的QQ群、加我微信进入微信群；
- 积极反馈问题，提出建议；
- 参与项目的开发，贡献您的力量。
