# 图片隐写术演示程序

### 基本信息

- 本项目源于大学英语课程要求完成一篇论文，本组选题图片隐写术为研究内容

- 参考资料: [《常见图片格式详解》 作者:Xiangism](https://www.cnblogs.com/xiangism/p/5311314.html)

- 引用项目: [常见图片格式详解 作者:Xiangism](https://gitee.com/xiangism/blogData/tree/master/)

### 开发者

- [Libro](https://github.com/LibroWu)
  
- [PaperL](https://www.github.com/PaperL)

### 文件结构

- Basic

    - TransImage.cpp 
    
        - 将图片转为黑白图
    
    - R-LSB_encrypt.cpp

        - 将一张图片以黑白形式加密入另一张等规格的图
    
    - R-LSB_decrypt.cpp

        - 从图片解密出隐藏的黑白图
    
- Experiment1

    - R-LSB_decrypt.cpp

        - 从图片解密出 `exe` 文件
      
    - R-LSB_encrypt.cpp

        - 将 `exe` 文件以二进制加密入图片

- Extension

    - city_decrypt.cpp
      
    - city_encrypt.cpp
      
    - LSBrecorder.hpp
      
    - R-LSB_decrypt.cpp
      
    - R-LSB_encrypt.cpp
  
- Extension1
  
    - checkSimilarity.cpp
      
    - city_decrypt.cpp
      
    - city_encrypt.cpp
      
    - LSBrecorderEx.hpp
    
### 说明

- 本仓库涉及涉及图片格式均为 'bmp' '24位RGB色'

    - 其中 `Basic` 和 `Experiment1` 部分仅支持 `1024x768` 分辨率图片
    
- 图片处理操作代码引用了 `Xiangism` 的代码, 代码文件位于 `third` 文件夹下

- `Extention` 及 `Extention` 部分为基础算法改进, 内容有:

    - 采用多通道及多比特存储密文
    
    - 以并查集算法找出大片颜色变化极小的区域, 降低该区域像素存储密文所用的比特数, 减少对原图视觉上的影响。