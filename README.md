# Software-engineering
project management

---

[结对作业——第二次作业](http://www.cnblogs.com/easteast/p/7604534.html)

## **department\_student\_matching**

---

### **version 1.2**

- **update:**

---

### **version 1.1**

- **update：**
	- 生成数据支持定制部门数、学生数、班级数
	- 生成数据支持命令行格式：
		- `generator.exe X`
		- `generator.exe X A B C`
	- 其中X为生成文件路径，A为部门数、B为学生数、C为班级数
	- 仅支持`0<A<=20`,`0<B<=300`,`0<C<=6`,且班级数不能超过学生数

---

### **version 1.0**

- 编程语言：C++
- 编程IDE：Visual Studio 2015
- 初步实现项目需求
- 命令行传参,可执行文件位于BIN目录下，支持 `dep_stu_matching.exe input_filename output_filename`
- 输入输出文件格式：json格式
- 匹配算法较为简单，可支持按申请优先/按时间段优先/按兴趣优先匹配
- 失配率较高
