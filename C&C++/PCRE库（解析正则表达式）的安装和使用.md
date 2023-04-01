# 一、pcre

PCRE(Perl Compatible Regular Expressions)是一个轻量级的Perl函数库，包括 perl 兼容的正则表达式库。它比Boost之类的正则表达式库小得多。PCRE十分易用，同时功能也很强大，性能超过了POSIX正则表达式库和一些经典的正则表达式库。
# 二、Linux中安装PCRE

PCRE目前最新版本为8.45 以8.45举例

1. 下载
   在线下载 wget http://downloads.sourceforge.net/project/pcre/pcre/8.45/pcre-8.45.tar.gz
   或者[官网]（https://sourceforge.net/projects/pcre/files/pcre/）下载后上传

2. 解压缩  `tar -zxvf pcre-8.45.tar.gz`

3. 运行 `chmod -R 777 /pcre-8.45`对当前文件夹授予全部读写权限。

4. 配置（在pcre-8.45目录下）

   * 运行`./configure`进行pcre初始化配置，会在控制台打印出一大堆的输出信息。（可参考`./configure --help`手册）
   * 如果最后提示`configure: error: You need a C++ compiler for C++ support还得安装C++环境yum -y install gcc-c++

5. 编译`make`（在pcre-8.45目录下）

6. 安装`make install`（在pcre-8.45目录下）

7. 输入`pcre-config --version`检测版本如果提示为8.45则成功

8. 检查

   * `ls /usr/local` 检查是否有pcre-7.8目录

   * `ls /usr/local/lib`  检查是否有pcre目录
   * `ls /usr/local/include`  检查是否有pcre目录

9. 将库文件导入cache：（目前还不清楚这个的作用）
      方法1：在`/etc/ld.so.conf`中加入： `／usr/local/lib/pcre`，然后运行`ldconfig`
      方法2：在`/etc/ld.so.conf.d/`下新生成一个文件（或在其中的文件中加入同样内容），文件内容为： `/usr/local/lib/pcre`，然后运行`ldconfig`

10. 使用

    * 使用pcre编写C或C＋＋程序，然后编译。
    * 对于C程序，编译命令为：`gcc -I/usr/local/include/pcre -L/usr/local/lib/pcre -l**pcre** *file.c*
    * 对于C++程序，编译命令为：gcc -I/usr/local/include/pcre -L/usr/local/lib/pcre -l**pcrecpp** *file.cpp*

11. 代码编写

    ```C++
    ///
    //函数说明 :  pcre正则解析字符串
    //参数说明 :  [pSubject]  规则字符串
    //           [nSubjectLen]   字符串长度
    //           [pPattern]    正则规则
    //           [pMatchVec]    捕获字符串偏移量
    //           [nMatchVec]    捕获字符串偏移量的最大长度
    //           [nMatchGroup]   捕获组数
    //返回值   :  true代表命中规则，false代表未命中
    //作者     :  buding  
    //修改日期 :  2021-09-22
    bool PcreMatchCapture(char* pSubject, size_t nSubjectLen, const char* pPattern, int* pMatchVec, size_t nMatchVec, int& nMatchGroup)
    {
    	pcre* pPcre = NULL;
    	const char* pError = NULL;
    	int nErrorOffset = 0;
    
    	pPcre = pcre_compile(pPattern, 0, &pError, &nErrorOffset, NULL);
    	if (!pPcre)
    	{
    		printf("[pcre] compile failed at offset %d: %s\n", nErrorOffset, pError);
    		return false;
    	}
    
    	nMatchGroup = pcre_exec(pPcre, NULL, pSubject, nSubjectLen, 0, 0, pMatchVec, nMatchVec);
    	if (nMatchGroup < 0)
    	{
    		pcre_free(pPcre);
    		return false;
    	}
    	pcre_free(pPcre);
    	return true;
    }
    
    
    
    ///
    //函数说明 :  pcre正则解析字符串
    //参数说明 :  [linedata]  规则字符串
    //           [cb_arg]   回调参数，返回捕获特定内容
    //返回值   :  无
    //作者     :  buding  
    //修改日期 :  2021-09-22
    void * MatchStrFileName(std::string linedata, void *cb_arg)
    {
    	int nMatchGroup = 0;
    	int MatchVec[30] = {0};
    	// 特殊符号'\'在程序中需要转义
    	std::string regex = "(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s(\\S+)";
    	if(PcreMatchCapture((char *)linedata.c_str(), linedata.size(), regex.c_str(), MatchVec, 30, nMatchGroup))
    	{
    		//字符串中有7组数据命中(特定字符组数 + 1)
    		if(nMatchGroup == 7)
    		{
    			std::string makefile(linedata.c_str()+MatchVec[2],MatchVec[3] - MatchVec[2]);
    			printf("one hit data:%s\n", makefile.c_str());
    
    			std::string auth(linedata.c_str()+MatchVec[4],MatchVec[5] - MatchVec[4]);
    			printf("two hit data:%s\n", auth.c_str());
    			
    			std::string authfile(linedata.c_str()+MatchVec[6],MatchVec[7] - MatchVec[6]);
    			printf("three hit data:%s\n", authfile.c_str());
    
    			std::string gensigfile(linedata.c_str()+MatchVec[8],MatchVec[9] - MatchVec[8]);
    			printf("four hit data:%s\n", gensigfile.c_str());
    
    			std::string gensig(linedata.c_str()+MatchVec[10],MatchVec[11] - MatchVec[10]);
    			printf("five hit data:%s\n", gensig.c_str());
    
    			std::string licensefile(linedata.c_str()+MatchVec[12],MatchVec[13] - MatchVec[12]);
    			printf("six hit data:%s\n", licensefile.c_str());
    		}
    	}
    }
    
    
    
    ```

    