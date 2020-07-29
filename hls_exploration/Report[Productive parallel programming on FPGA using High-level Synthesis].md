# 《Productive parallel programming on FPGA using High-level Synthesis》Report

_<入门教程>_

## 1. 理解流水线启动延迟的影响

* 代码示例
```
constexpr int N = 1024;
void InitiationInterval(float const *a_mem, float const *b_mem, float *c_mem) {
  for (int i = 0; i < N; ++i) {
    const auto a = a_mem[i];
    const auto b = b_mem[i];
    // -------------------------
    // Try changing the target initiation interval (II) and re-running HLS.
    // Notice what happens to the total number of cycles to completion, and to
    // the number of adders instantiated.
    #pragma HLS PIPELINE II=2
    float c = (a + b) * (a - b);
    // -------------------------
    c_mem[i] = c;
  }
}
```

## 2. 理解添加buffer对访存密集型应用的改善
 当访存密集型的应用对同一存储器端口同时发起更多的访问时，访存端口的冲突便会发生，计算单元因等待数据而暂停运行，影响系统的性能。

```
/*鉴于端口访存的需求,需要多个周期才能获取数据*/
void Simple1DStencil(float const *memory_in, float *memory_out){

 float left,center,right; // 暂存计算数据
 float average; // 暂存计算结果

 Loop_1D:
 for(int i = 1; i<N-1; ++i)
 {

   // 从外存中获取数据
   left = memory_in[i-1];
   center = memory_in[i];
   right = memory_in[i+1];

   //数值计算
   average = factor *(left + center + right);

   //输出结果
   memory_out[i] = average;

 }


}
```
通过插入buffer的方式，缓存从外部端口获取的数据，为后续使用服务，减少对外存的访问，提升性能。

```
void Pipe1DStencil(float const *memory_in, float *memory_out){

 float left,center,right; // 暂存计算数据
 float average; // 暂存计算结果

 left = memory_in[0]; // 初始化 left
 center = memory_in[1]; // 初始化 center

 Loop_1D:
 for(int i = 2; i<N-2; ++i)  // start address is [2] for right
 {

   // 从外存中获取数据
   right = memory_in[i];

   //数值计算
   average = factor *(left + center + right);

   //输出结果
   memory_out[i] = average;
   
   // 三个操作数整体向右滑动
   left = center ;  // 更新left为 center
   center = right ; // 更新center为 right
 }


}
```

