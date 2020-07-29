/*
 * 参考文档 <hls_tutorial_examples> - 2
 * 测试不同Period下 性能和资源开销
 */

const int N = 1024 ; // 存储数据遍历空间
const float factor = 0.3333; //


/**/
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



