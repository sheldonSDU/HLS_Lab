# HLS 性能研究
 在HLS的研究中，大多数工作专注于执行的周期数和资源的使用
## 1.HLS中Period 对性能和开销的影响

随着Period的减少,HLS工具会添加越来越多的FF以及用于提高时钟频率。相应得，逻辑资源未必依据period


###　测试结果
![比较结果](./image/CriticalPathDelay_Compare.png)

###　资源开销


