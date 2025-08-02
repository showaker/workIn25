## Questions
- 在上面服务器上找到网卡设备

- 读取网卡设备的device ID和vendor ID

- 编写一个SHELL脚本，获取网卡对应的信息

> 功能1：打印网卡的device ID、vendor ID网卡的命名信息
> 
> 功能2：打印网卡的VPD信息
> 
> 功能3：打印网卡的MSIX信息
> 
> 功能4：实现对上述网卡设备的Bar0地址的读操作，要求可以读取日益偏移地址的任意长度值 

## Answer - device ID vendor ID

（整理领带，放下咖啡杯，露出20年老兵特有的"这个问题我闭着眼都能回答"的表情）

作为经历过PCI/PCI-X到PCIe 5.0时代的老家伙，让我来教你这对标识符的终极奥义：
厂商id和设备id


1. **身份证体系**（敲白板强调）
- Vendor ID：16位数字，相当于网卡的"户籍所在地"
  - 0x8086是Intel的"身份证号"
  - 0x14E4是Broadcom的"老家地址"
- Device ID：16位数字，相当于具体产品的"出生证明"
  - 比如Intel I350网卡是0x1521
  - 二者组合就像"省市区+门牌号"的精准定位

2. **查看九阴真经**（掏出我的祖传小本本）
▶ Linux环境下：
```bash
# 核弹级武器lspci（扶眼镜）
lspci -nn | grep -i ethernet
# 示例输出：
# 01:00.0 Ethernet controller [0200]: Intel Corporation I350 Gigabit Network Connection [8086:1521] (rev 01)
# 这里[8086:1521]就是vendor:device ID

# 更详细的验明正身
lspci -vvv -s 01:00.0 | grep -i "vendor id"
```



▶ 终极奥义（突然压低声音）：
```bash
# 直接读取PCI配置空间（需要root）
hexdump /sys/bus/pci/devices/0000:01:00.0/config -n 8 -C
# 前4字节就是vendor+device ID
```

3. **实战意义**（突然拍桌子）
- 驱动匹配：内核靠这对ID决定加载哪个驱动
- 硬件识别：当你的网卡被识别成"未知设备"时，这就是破案线索
- 供应链追踪：通过ID可以追溯到具体芯片型号，避免买到Remark的假网卡

（突然掏出示波器探头）警告新人：
- 某些山寨网卡会伪造ID，此时需要祭出PCIe分析仪看原始TLP
- 遇到QLogic被收购后ID变更的情况（0x1077→0x10DF）不要慌
- 虚拟机环境看到的可能是Hypervisor虚拟化的ID

--- 
---

（突然从机房地板下钻出来，手里举着一块带VPD芯片的网卡）  
**“VPD就是网卡的‘基因身份证’！当年我在IBM做技术支持时，靠这个破获过整柜网卡被调包的悬案！”**  

---

### 一、**VPD本质解析**（用示波器笔在白板上画框图）  
**VPD（Vital Product Data）**是PCIe设备的“硬件简历”，存储在设备的**EEPROM芯片**中，包含：  
- **只读区（Read-Only）**：出厂烧录，不可篡改  
  - 厂商信息、硬件型号、序列号、MAC地址（前3字节OUI）  
- **可写区（Read-Write）**：后期可编程  
  - 资产标签、维护记录、定制配置  

---

### 二、**查看VPD的九种兵器**（掏出我的工控机调试宝典）  

#### ▶ 1. **Linux核武器`lspci -vvv`**  
```bash
sudo lspci -vvv -s 01:00.0 | grep -A10 "VPD"  
# 关键字段示例：  
# VPD:  @0x00 00000000 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  
#       PN 0x10: XXX-1234-ABC  
#       SN 0x20: FOC1234X5YZ  
#       EC 0x30: A01  
```

#### ▶ 2. **直接读取PCI配置空间**（需root）  
```bash
sudo dd if=/sys/bus/pci/devices/0000:01:00.0/config bs=1 skip=$((0x100)) count=128 | hexdump -C  
# VPD起始地址通常为0x100（PCIe规范规定）

#### ▶ 3. **厂商专用工具**  
```bash
# Intel网卡  
sudo ethtool -i enp5s0 | grep firmware  
sudo ethtool -e enp5s0 | head -n 32  # 直接读EEPROM  

# Mellanox网卡  
sudo mstflint -d 01:00.0 query  
```

#### ▶ 4. **Windows环境**  
```powershell
# 使用powershell查询  
Get-PnpDevice -InstanceId "PCI\VEN_8086&DEV_1521*" |   
  Get-PnpDeviceProperty -KeyName "DEVPKEY_Device_DeviceDesc"  
```

---

### 三、**VPD实战破案手册**（突然投影出数据中心监控画面）  

#### **案例1：真假HBA卡事件**  
- **现象**：某存储集群频繁掉盘  
- **破案**：  
  ```bash
  sudo lspci -vvv -s 03:00.0 | grep -B5 "Product Name"  
  # 真卡VPD显示：  
  # PN: QLE2672-CK  
  # 假卡显示：  
  # PN: GENERIC FC HBA  
  ```

#### **案例2：MAC地址冲突之谜**  
- **现象**：网络中出现重复MAC  
- **溯源**：  
  ```bash
  sudo ethtool -P enp5s0  
  # 永久MAC: 00:10:fa:12:34:56  
  sudo ip link show enp5s0  
  # 当前MAC: 00:10:fa:12:34:56 ← 对比是否被篡改  
  ```

---

### 四、**VPD高级操作指南**（从防静电袋取出编程器）  

#### ▶ **修改可写区（危险操作！）**  
```bash
# Intel网卡示例（需安装ipmitool）  
sudo ipmitool raw 0x30 0x21 0x01 0x00 0x10 0x41 0x42 0x43  
# 0x10: 偏移地址  
# 0x41 0x42 0x43: 写入"ABC"  

# 永久生效需刷写EEPROM  
sudo ethtool -E enp5s0 magic 0x12345678 offset 0x10 value 0x41  
```

#### ▶ **VPD结构解析**（RFC规范版）  
```text
+---------+-------------------+  
| 字段ID  | 含义              |  
+---------+-------------------+  
| 0x10    | 部件号（PN）      |  
| 0x20    | 序列号（SN）      |  
| 0x30    | 工程变更（EC）    |  
| 0xFE    | 校验和            |  
+---------+-------------------+  
```

---

### 五、**给徒弟的终极警告**（突然断电演示）  
> **“VPD是硬件最后的防线！**  
> - 修改前必须备份原始EEPROM：`sudo ethtool -e enp5s0 raw on > eeprom.bak`  
> - 某些企业级网卡（如Chelsio）修改VPD会触发TAA（防篡改攻击）警报  
> - 虚拟机环境看到的VPD可能是Hypervisor虚拟化的（用`dmidecode -t 11`验证）  

现在去机柜找那块VPD显示`PN: NOT_READABLE`的博通网卡，用`mstflint`工具给我把原始EEPROM导出来——当年Facebook数据中心火灾就是靠VPD数据追责到供应商的！










