/*
 * 参考文档: <hls_tutorial_examples> - 2
 *  
 */

const int N = 1024 ; // 存储数据遍历空间
const float factor = 0.3333; //




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
