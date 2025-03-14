### 注意！ 直接使用CANFD接口，可能会由于不可抗力因素导致机器人失控等状况，引发安全风险。 

### 如您直接使用CANFD接口控制机器人的关节电机，将视为已经签署免责协议。 免责协议具体条款请联系我们的售后工程师获取！！

#### 实现功能
- 读取TITA上传的电机，IMU数据,joint motor status数据
- 利用SDK控制电机
- 利用SDK控制TITA站立和运动


#### 硬件要求
使用PC进行控制：
- Ubuntu22.04电脑 （==20.04上socketcan驱动暂不支持canfd协议！==）
- usb2canfd
- 
使用TITA内置Orin NX :
无需准备额外硬件。

### TITA Robot 机器人SDK通用函数

> tita_robot
>>
>> def_can.h------------------------------ 通讯协议结构体定义
>>
>> can_receive.hpp ----------------------- 读取can数据解包实现
>>
>> can_sender.hpp ------------------------ 机器人控制方法实现
>>
>> tita_robot.hpp ------------------------ 机器人SDK通用函数

#### 使用方法1
- 直接clone 至 tita os 

```
# in tita os environment
#clone API source code
cd tita_robot
mkdir build
cd build
cmake ..
make

```


#### 使用方法2

- 正确的电气连接（当usb2canfd通过usb-a连接到电脑后可以被时别为`can`设备,可通过`ip link show`来查看是否存在，

应该类似如下显示:

```bash
can0: <NOARP,ECHO> mtu 16 qdisc noop state DOWN group default qlen 10
    link/can
```

- 初始化can

> 需要下载`can-utils` ： `sudo apt-get install can-utils`

```bash
sudo ip link set can0 up type can bitrate 100000 dbitrate 5000000 fd on
```

其中bitrate后的1M为canfd的仲裁域速度，dbitrate的5M为数据域速度速度。需要根据具体情况设置（示例和TITA规定一致）

如果前两步正确，新开终端利用`can-utils`进行测试:`candump can0`，步骤无问题应该看到滚动的can消息帧

- 运行测试代码

```bash
./test_control 
```
