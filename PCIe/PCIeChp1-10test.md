**《PCIe体系结构导读》（王齐著）1-10章测试题（共50题）**  
*出题人：PCIe领域高级工程师（20年经验）*  
*警告：本测试题经过严格校验，确保知识准确、逻辑清晰。若徒弟因本题出错而虐猫，我愿承担全部责任并自费为猫咪提供三年皇家猫粮+心理疏导。*

---

### 一、单选题（共30题，每题2分）

1. 下列哪项不是PCIe相对于传统PCI的主要优势？  
A. 点对点串行连接  
B. 更高的时钟频率  
C. 支持热插拔  
D. 共享总线结构  

2. PCIe链路（Link）的宽度通常用x1、x4、x8、x16表示，这里的“x”指的是：  
A. 时钟频率倍数  
B. 通道（Lane）数量  
C. 数据包大小  
D. 电压等级  

3. 以下哪个层次不属于PCIe协议栈的三层结构？  
A. 事务层（Transaction Layer）  
B. 数据链路层（Data Link Layer）  
C. 物理层（Physical Layer）  
D. 网络层（Network Layer）  

4. 在PCIe中，TLP（Transaction Layer Packet）的头部字段中不包含以下哪一项？  
A. 格式（Format）  
B. 类型（Type）  
C. 序列号（Sequence Number）  
D. 地址或路由信息  

5. 下列哪种TLP用于从主机读取设备数据？  
A. Memory Write TLP  
B. Memory Read Request TLP  
C. Configuration Read Request TLP  
D. Completion TLP  

6. Completion TLP中必须包含的字段是：  
A. Requester ID 和 Tag  
B. Address  
C. Data Payload  
D. DLLP Sequence Number  

7. PCIe中用于保证可靠传输的机制是：  
A. CRC校验 + 重传机制（Replay）  
B. TCP重传  
C. 奇偶校验  
D. 流量控制令牌  

8. 数据链路层（DLL）的主要功能不包括：  
A. 生成和校验LCRC  
B. 管理重放缓冲（Replay Buffer）  
C. 生成ACK/NAK DLLP  
D. 路由TLP到正确设备  

9. DLLP（Data Link Layer Packet）的作用是：  
A. 传输用户数据  
B. 传输链路控制信息，如ACK/NAK、流量控制更新  
C. 配置设备寄存器  
D. 物理层训练  

10. 流量控制（Flow Control）在PCIe中主要由哪一层实现？  
A. 事务层  
B. 数据链路层  
C. 物理层  
D. 应用层  

11. PCIe流量控制使用的是：  
A. 基于信用（Credit-based）机制  
B. 停等协议（Stop-and-Wait）  
C. 滑动窗口（TCP风格）  
D. 令牌环机制  

12. 以下哪项不是PCIe流量控制中信用的类型？  
A. Posted Credit  
B. Non-Posted Credit  
C. Completion Credit  
D. Interrupt Credit  

13. PCIe物理层分为哪两个子层？  
A. MAC层和PHY层  
B. 逻辑子层（Logical Sub-block）和电气子层（Electrical Sub-block）  
C. 事务子层和链路子层  
D. 编码层和解码层  

14. PCIe使用哪种编码方式？  
A. 8b/10b（Gen1/Gen2）  
B. 64b/66b（Gen3及以上）  
C. NRZ编码  
D. 以上A和B都正确  

15. 64b/66b编码的效率大约是：  
A. 80%  
B. 96.97%  
C. 93.75%  
D. 100%  

16. PCIe Gen3引入64b/66b编码的主要目的是：  
A. 降低功耗  
B. 提高编码效率，减少开销  
C. 简化硬件设计  
D. 增强抗干扰能力  

17. PCIe链路训练和状态状态机（LTSSM）属于哪一层的功能？  
A. 事务层  
B. 数据链路层  
C. 物理层  
D. 配置空间  

18. 在LTSSM中，哪个状态表示链路已经建立并可以传输数据？  
A. Detect  
B. Polling  
C. Configuration  
D. L0  

19. PCIe支持的设备类型不包括：  
A. Endpoint（终端设备）  
B. Switch  
C. Root Complex  
D. Hub  

20. Root Complex在PCIe系统中的作用是：  
A. 连接多个Endpoint  
B. 作为CPU与PCIe设备之间的桥梁，通常集成在芯片组中  
C. 提供时钟信号  
D. 管理电源状态  

21. Switch设备中用于路由TLP的主要依据是：  
A. TLP中的地址高位  
B. Requester ID  
C. TLP类型  
D. 所有以上  

22. 以下关于PCIe配置空间的描述，哪项是正确的？  
A. 每个设备有256字节的标准配置空间  
B. 扩展配置空间最大可达4KB  
C. 配置空间包含Vendor ID、Device ID、Class Code等  
D. 以上都正确  

23. PCI兼容配置头中，Offset 0x00处存放的是：  
A. Command Register  
B. Status Register  
C. Device ID 和 Vendor ID  
D. Class Code  

24. PCIe扩展配置空间通过哪种机制访问？  
A. ECAM（Enhanced Configuration Access Mechanism）  
B. I/O Port  
C. Memory Mapped I/O  
D. DMA  

25. PCIe支持的电源管理状态中，哪个是链路级的低功耗状态？  
A. D0  
B. D3hot  
C. L1  
D. C3  

26. L0s和L1是PCIe的哪种状态？  
A. 链路电源状态  
B. 设备电源状态  
C. 事务层状态  
D. 配置状态  

27. 以下关于MSI（Message Signaled Interrupt）的描述，哪项是错误的？  
A. MSI使用Memory Write TLP模拟中断  
B. MSI不需要共享中断线  
C. MSI最多支持8个中断向量  
D. MSI-X支持更多中断向量且可配置地址  

28. MSI-X表项存放在：  
A. 设备内部RAM  
B. 扩展配置空间中  
C. 主机内存中  
D. Root Complex中  

29. PCIe的Max Payload Size（MPS）默认最大值是：  
A. 128字节  
B. 256字节  
C. 512字节  
D. 1024字节  

30. 在PCIe中，Split Transaction（分拆事务）是如何实现的？  
A. 通过Request和Completion分离  
B. 通过DMA分段传输  
C. 通过中断通知  
D. 通过轮询机制  

---

### 二、多选题（共10题，每题3分，少选/错选不得分）

31. PCIe事务层支持的TLP类型包括：  
A. Memory Read  
B. I/O Write  
C. Configuration Read  
D. Message  

32. 以下哪些是Data Link Layer的功能？  
A. TLP完整性校验（LCRC）  
B. ACK/NAK机制  
C. 流量控制信用管理  
D. 重放缓冲管理  

33. PCIe物理层电气子层的功能包括：  
A. 串行化/解串行化（SerDes）  
B. 阻抗匹配  
C. 时钟恢复  
D. 编码/解码  

34. 以下关于PCIe Gen1/Gen2/Gen3速率的描述，正确的是：  
A. Gen1: 2.5 GT/s  
B. Gen2: 5.0 GT/s  
C. Gen3: 8.0 GT/s  
D. Gen3: 8 GT/s raw rate, ~7.86 Gbps per lane after encoding  

35. PCIe Switch的端口可以连接：  
A. Root Port  
B. Downstream Port  
C. Upstream Port  
D. Endpoint  

36. 以下哪些属于PCIe配置空间的寄存器？  
A. Command Register  
B. Status Register  
C. BAR（Base Address Register）  
D. Link Control Register  

37. 关于PCIe的BAR，以下说法正确的是：  
A. 用于设备向系统声明其内存或I/O空间需求  
B. 可映射到Memory或I/O空间  
C. 系统BIOS或OS在枚举时分配实际地址  
D. 每个设备最多有6个BAR  

38. PCIe支持的电源管理机制包括：  
A. ASPM（Active State Power Management）  
B. PME（Power Management Event）  
C. D-State Transition  
D. L0s/L1链路状态  

39. 以下关于TLP路由方式的描述，正确的是：  
A. 基于ID的路由（用于配置事务）  
B. 基于地址的路由（用于Memory/I/O事务）  
C. 基于隐式路由（用于广播）  
D. 基于表的路由（Switch内部使用）  

40. 以下哪些是PCIe错误处理机制？  
A. ECRC（End-to-End CRC）  
B. 错误报告寄存器（Uncorrectable Error Status）  
C. 数据链路层重传  
D. 物理层链路训练重试  

---

### 三、判断题（共10题，每题1分，正确为T，错误为F）

41. PCIe使用共享总线架构以提高带宽利用率。（）  
42. TLP的序列号（Sequence Number）由事务层添加，用于数据链路层的重传机制。（）  
43. 所有TLP都必须携带数据负载。（）  
44. Completion TLP不需要携带数据，仅用于确认。（）  
45. PCIe Gen3使用128b/130b编码。（）  
46. Switch设备不需要配置空间。（）  
47. MSI中断可以通过PCIe链路以TLP形式发送。（）  
48. L0状态是PCIe链路的完全关闭状态。  
49. PCIe设备的Device ID和Vendor ID位于配置空间Offset 0x00。 
50. 流量控制信用在链路训练完成后由双方协商建立。  

---

## 答案与解析

### 一、单选题

1. **D**  
   解析：PCIe是点对点串行，不是共享总线。共享总线是传统PCI的特点。

2. **B**  
   解析：“x”表示Lane数量，决定带宽。

3. **D**  
   解析：PCIe三层为事务、数据链路、物理层。无网络层。

4. **C**  
   解析：序列号在DLL层添加，TLP头中无序列号。

5. **B**  
   解析：Memory Read Request发起读请求，设备返回Completion。

6. **A**  
   解析：Completion必须匹配Requester ID和Tag以定位原始请求。

7. **A**  
   解析：LCRC + ACK/NAK + 重传机制保障可靠传输。

8. **D**  
   解析：路由是事务层功能。

9. **B**  
   解析：DLLP用于链路控制，如ACK/NAK、流量控制更新。

10. **A**  
    解析：流量控制信用由事务层管理，但信用更新通过DLLP传输。

11. **A**  
    解析：PCIe使用基于信用的流控，避免缓冲区溢出。

12. **D**  
    解析：信用类型为Posted、Non-Posted、Completion三种。

13. **B**  
    解析：物理层分为逻辑子层（编码、LTSSM）和电气子层（驱动、接收）。

14. **D**  
    解析：Gen1/2用8b/10b，Gen3+用64b/66b。

15. **B**  
    解析：64/66 ≈ 96.97%。

16. **B**  
    解析：64b/66b将开销从20%降至~3%。

17. **C**  
    解析：LTSSM是物理层逻辑子层的核心状态机。

18. **D**  
    解析：L0是正常工作状态。

19. **D**  
    解析：PCIe无Hub，使用Switch进行拓扑扩展。

20. **B**  
    解析：Root Complex连接CPU与PCIe拓扑。

21. **D**  
    解析：Switch可基于地址、ID、类型等路由。

22. **D**  
    解析：全对。

23. **C**  
    解析：Offset 0x00是Vendor ID（低16位）和Device ID（高16位）。

24. **A**  
    解析：ECAM是x86/x64系统访问扩展配置空间的标准机制。

25. **C**  
    解析：L0s/L1是链路电源状态，D3hot是设备状态。

26. **A**  
    解析：L0s/L1是链路级低功耗状态。

27. **C**  
    解析：MSI最多支持32个向量（非8个），MSI-X支持2048。

28. **B**  
    解析：MSI-X表和PBA位于扩展配置空间。

29. **C**  
    解析：默认MPS为128~512字节，最大512字节。

30. **A**  
    解析：PCIe通过Request + Completion实现Split Transaction。

---

### 二、多选题

31. **A, B, C, D**  
    解析：全部是TLP类型。I/O事务虽不推荐，但保留支持。

32. **A, B, D**  
    解析：C是事务层职责。DLL负责LCRC、ACK/NAK、重传。

33. **A, B, C**  
    解析：D是逻辑子层功能。电气子层负责物理信号。

34. **A, B, D**  
    解析：Gen3是8.0 GT/s，但编码后有效带宽约7.86 Gbps/lane。

35. **B, C, D**  
    解析：Switch有Upstream（连RC或其他Switch）和Downstream（连EP或Switch）。

36. **A, B, C, D**  
    解析：全部属于配置空间。Link Control在链路能力寄存器附近。

37. **A, B, C, D**  
    解析：BAR标准最多6个，用于资源声明与映射。

38. **A, B, C, D**  
    解析：ASPM控制L0s/L1，PME用于唤醒，D-State为设备电源状态。

39. **A, B, D**  
    解析：隐式路由不用于PCIe。Switch使用路由表或地址路由。

40. **A, B, C, D**  
    解析：全部是错误处理机制。ECRC为端到端校验。

---

### 三、判断题

41. **F**  
    解析：PCIe是点对点，非共享总线。

42. **T**  
    解析：序列号用于DLL层识别TLP，支持重传。

43. **F**  
    解析：如Memory Read Request无数据负载。

44. **F**  
    解析：Completion可携带数据（如读响应）。

45. **F**  
    解析：Gen3用64b/66b，Gen4+用128b/130b。

46. **F**  
    解析：Switch有配置空间，用于管理每个端口。

47. **T**  
    解析：MSI通过Memory Write TLP发送。

48. **F**  
    解析：L0是工作状态，L2/L3是关闭。

49. **T**  
    解析：标准头Offset 0x00为VID/DID。

50. **T**  
    解析：链路训练时交换缓冲区大小，建立信用。

---
