#### 实现功能
- [x]读取TITA上传的电机，IMU数据,joint motor status数据
- [X]利用SDK控制电机
- [X]利用SDK控制TITA站立和运动


#### 硬件要求

- Ubuntu22.04电脑 （==20.04上socketcan驱动暂不支持canfd协议！==）
- usb2canfd


###TITA Robot 机器人SDK通用函数
```
>tita_robot
>>def_can.h------------------------------>通讯协议结构体定义
>>can_receive.hpp ----------------------- 读取can数据解包实现
>>can_sender.hpp ------------------------ 机器人控制方法实现
>>tita_robot.hpp ------------------------ 机器人SDK通用函数
```
####
代码编译-
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
